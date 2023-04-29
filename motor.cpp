#include "motor.h"

#define PRESSED LOW // PULL UP
#define NOT_PRESSED HIGH // PULL UP
#define BUTTON_UP 2 // PULL UP
#define BUTTON_DOWN 3 // PULL UP
#define DRIVER_ENABLE_PIN 1
#define DEBOUNCE_MOTOR_BUTTON_TIME_MS 40

typedef enum {
    MOTOR_IN_PLACE,
    MOTOR_GOING_UP,
    MOTOR_GOING_DOWN,
    MOTOR_DEBOUNCE_UP,
    MOTOR_DEBOUNCE_DOWN
} MotorStatus_t;

static MotorStatus_t motorStatus;
static int timeIncrement_ms;

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
            if(digitalRead(BUTTON_DOWN) == PRESSED) { // #TODO: if(button down pressed)
                buttonDownTentativePressed = true;
                motorStatus = MOTOR_DEBOUNCE_DOWN;
            } else if(digitalRead(BUTTON_UP) == PRESSED) {
                buttonUpTentativePressed = true;
                motorStatus = MOTOR_DEBOUNCE_UP;
            }
            // #TODO: Update output pins so motor does not move.
            break;
        case MOTOR_GOING_UP:
            if(digitalRead(BUTTON_UP) == NOT_PRESSED) {
                buttonUpTentativePressed = false;
                motorStatus = MOTOR_DEBOUNCE_UP;
            }
            // #TODO: Update output pins so motor goes up.
            break;
        case MOTOR_GOING_DOWN:
            if(digitalRead(BUTTON_DOWN) == NOT_PRESSED) {
                buttonDownTentativePressed = false;
                motorStatus = MOTOR_DEBOUNCE_DOWN;
            }
            // #TODO: Update output pins so motor goes down.
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
            }
            accumulatedDebounceMotorButtonTime += timeIncrement_ms;
            break;
        case MOTOR_DEBOUNCE_DOWN:
            if(accumulatedDebounceMotorButtonTime >= DEBOUNCE_MOTOR_BUTTON_TIME_MS) {
                if(buttonDownTentativePressed) {
                    if(digitalRead(BUTTON_DOWN) == PRESSED) // #TODO: if(button down pressed)
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
            }
            accumulatedDebounceMotorButtonTime += timeIncrement_ms;
            break;
        default:
            motorStatus = MOTOR_IN_PLACE;
            buttonDownTentativePressed = false;
            buttonDownTentativePressed = false;
    }

    if( motorStatus == MOTOR_GOING_UP || motorStatus == MOTOR_GOING_DOWN)
        return true;
    return false;
}