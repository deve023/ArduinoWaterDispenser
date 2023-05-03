//=====[Libraries]=============================================================

#include "motor.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

#define PRESSED LOW // PULL UP
#define NOT_PRESSED HIGH // PULL UP
#define BUTTON_UP 5 // PULL UP
#define BUTTON_DOWN 6 // PULL UP
#define DRIVER_ENABLE_PIN 7
#define DRIVER_ANOTHER_PIN 8
#define DEBOUNCE_MOTOR_BUTTON_TIME_MS 40
#define MOTOR_RUNNING_SPEED 150

//=====[Declaration of private data types]=====================================

typedef enum {
    MOTOR_IN_PLACE,
    MOTOR_GOING_UP,
    MOTOR_GOING_DOWN,
    MOTOR_DEBOUNCE_UP,
    MOTOR_DEBOUNCE_DOWN
} MotorStatus_t;

//=====[Declaration and initialization of private global variables]============

static MotorStatus_t motorStatus;
static int timeIncrement_ms;
static char statusInfo[28] = "Motor Status: "; // Insert status in position: 14

//=====[Declarations (prototypes) of private functions]========================

/**
 *  @brief Makes the tray move upwards.
 *
 */
static void goUp();

/**
 *  @brief Makes the tray move upwards.
 *
 */
static void goDown();

/**
 *  @brief Makes the tray stop moving.
 *
 */
static void standStill();

//=====[Implementations of public functions]===================================

void motorInit(int dt)
{
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);

    pinMode(DRIVER_ENABLE_PIN, OUTPUT);
    digitalWrite(DRIVER_ENABLE_PIN, LOW);

    motorStatus = MOTOR_IN_PLACE;

    timeIncrement_ms = dt;
}

bool motorUpdate()
{
    static int accumulatedDebounceMotorButtonTime = 0;
    static bool buttonUpTentativePressed = false;
    static bool buttonDownTentativePressed = false;

    switch(motorStatus) {
        case MOTOR_IN_PLACE:
            if(digitalRead(BUTTON_DOWN) == PRESSED) {
                buttonDownTentativePressed = true;
                motorStatus = MOTOR_DEBOUNCE_DOWN;
            } else if(digitalRead(BUTTON_UP) == PRESSED) {
                buttonUpTentativePressed = true;
                motorStatus = MOTOR_DEBOUNCE_UP;
            }
            standStill();
            break;
        case MOTOR_GOING_UP:
            if(digitalRead(BUTTON_UP) == NOT_PRESSED) {
                buttonUpTentativePressed = false;
                motorStatus = MOTOR_DEBOUNCE_UP;
            }
            goUp();
            break;
        case MOTOR_GOING_DOWN:
            if(digitalRead(BUTTON_DOWN) == NOT_PRESSED) {
                buttonDownTentativePressed = false;
                motorStatus = MOTOR_DEBOUNCE_DOWN;
            }
            goDown();
            break;  
        case MOTOR_DEBOUNCE_UP:
            if(accumulatedDebounceMotorButtonTime >= DEBOUNCE_MOTOR_BUTTON_TIME_MS) {
                if(buttonUpTentativePressed) {
                    if(digitalRead(BUTTON_UP) == PRESSED)
                        motorStatus = MOTOR_GOING_UP;
                    else {
                        motorStatus = MOTOR_IN_PLACE;
                        buttonUpTentativePressed = false;
                    }
                } else {
                    if(digitalRead(BUTTON_UP) == NOT_PRESSED)
                        motorStatus = MOTOR_IN_PLACE;
                    else {
                        motorStatus: MOTOR_GOING_UP;
                        buttonUpTentativePressed = true;
                    }
                }
                accumulatedDebounceMotorButtonTime = 0;
            } else {
                accumulatedDebounceMotorButtonTime += timeIncrement_ms;
            }
            strcpy(statusInfo+14, "DEBOUNCE_UP"); // Debug
            break;
        case MOTOR_DEBOUNCE_DOWN:
            if(accumulatedDebounceMotorButtonTime >= DEBOUNCE_MOTOR_BUTTON_TIME_MS) {
                if(buttonDownTentativePressed) {
                    if(digitalRead(BUTTON_DOWN) == PRESSED)
                        motorStatus = MOTOR_GOING_DOWN;
                    else {
                        motorStatus = MOTOR_IN_PLACE;
                        buttonDownTentativePressed = false;
                    }
                } else {
                    if(digitalRead(BUTTON_DOWN) == NOT_PRESSED)
                        motorStatus = MOTOR_IN_PLACE;
                    else {
                        motorStatus = MOTOR_GOING_DOWN;
                        buttonDownTentativePressed = true;
                    }
                }
                accumulatedDebounceMotorButtonTime = 0;
            } else {
                accumulatedDebounceMotorButtonTime += timeIncrement_ms;
            }
            strcpy(statusInfo+14, "DEBOUNCE_DOWN"); // Debug
            break;
        default:
            motorStatus = MOTOR_IN_PLACE;
            buttonDownTentativePressed = false;
            buttonDownTentativePressed = false;
    }

    Serial.println(statusInfo);

    if( motorStatus == MOTOR_GOING_UP || motorStatus == MOTOR_GOING_DOWN)
        return true;
    return false;
}

bool isTrayInPlace()
{
    return motorStatus == MOTOR_IN_PLACE;
}


bool isTrayMovingUp()
{
    return motorStatus == MOTOR_GOING_UP;
}


bool isTrayMovingDown()
{
    return motorStatus == MOTOR_GOING_DOWN;
}

//=====[Implementations of private functions]==================================

static void goUp()
{
    // #TODO: Update output pins so motor goes up.
    strcpy(statusInfo+14, "GOING_UP"); // Debug
}

static void goDown()
{
    // #TODO: Update output pins so motor goes down.
    strcpy(statusInfo+14, "GOING_DOWN"); // Debug
}

static void standStill()
{

    // #TODO: Update output pins so motor does not move.
    strcpy(statusInfo+14, "IN_PLACE"); // Debug
}
