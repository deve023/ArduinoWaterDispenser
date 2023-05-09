//=====[Libraries]=============================================================

#include "waterPump.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

#define PRESSED LOW // PULL UP
#define NOT_PRESSED HIGH // PULL UP
#define BUTTON_TOGGLE 2 // PULL UP
#define LED_FLOW_ON_PIN 3
#define WATER_PUMP_PIN 4 // Send PWM. 

#define DEBOUNCE_WATER_PUMP_BUTTON_TIME_MS 40

#define FLOW_RATE 50 // 255: full power. 50: 20% aprox.
#define NO_FLOW 0

//=====[Declaration of private data types]=====================================

typedef enum {
    FLOWING, 
    NOT_FLOWING,
    DEBOUNCE_TOGGLE_BUTTON
} WaterPumpStatus_t;

//=====[Declaration and initialization of private global variables]============

static WaterPumpStatus_t waterPumpStatus;
static int timeIncrement_ms;
static bool waterFlowing;

//=====[Declarations (prototypes) of private functions]========================

/**
 *  @brief Starts water flow.
 *
 */
static void startFlow();

/**
 *  @brief Stops water flow.
 *
 */
static void stopFlow();

//=====[Implementations of public functions]===================================

void waterPumpInit(int dt)
{
    pinMode(BUTTON_TOGGLE, INPUT_PULLUP);
    pinMode(LED_FLOW_ON_PIN, OUTPUT);
    pinMode(WATER_PUMP_PIN, OUTPUT);

    waterPumpStatus = NOT_FLOWING;
    stopFlow();

    timeIncrement_ms = dt;
}

bool waterPumpUpdate(bool flowBlock)
{
    static int accumulatedToggleButtonTime = 0;

    static bool toggleButtonPressed = false;
    static bool toggleButtonTentativePressed = false;

    switch(waterPumpStatus) {
        case FLOWING:
            if(flowBlock)
                waterPumpStatus = NOT_FLOWING;
            else {
                if(!waterFlowing)
                    startFlow();
                if(!toggleButtonPressed) {
                    if(digitalRead(BUTTON_TOGGLE) == PRESSED) {
                        toggleButtonTentativePressed = true;
                        waterPumpStatus = DEBOUNCE_TOGGLE_BUTTON;
                    }
                } else {
                    if(digitalRead(BUTTON_TOGGLE) == NOT_PRESSED) {
                        toggleButtonTentativePressed = false;
                        waterPumpStatus = DEBOUNCE_TOGGLE_BUTTON;
                    }                    
                }
            }
            break;
        case NOT_FLOWING:
            if(waterFlowing)
                stopFlow();
            if(!toggleButtonPressed) {
                if(digitalRead(BUTTON_TOGGLE) == PRESSED) {
                    toggleButtonTentativePressed = true;
                    waterPumpStatus = DEBOUNCE_TOGGLE_BUTTON;
                }
            } else {
                    if(digitalRead(BUTTON_TOGGLE) == NOT_PRESSED) {
                        toggleButtonTentativePressed = false;
                        waterPumpStatus = DEBOUNCE_TOGGLE_BUTTON;
                    }                    
                }
            break;
        case DEBOUNCE_TOGGLE_BUTTON:
            if(accumulatedToggleButtonTime >= DEBOUNCE_WATER_PUMP_BUTTON_TIME_MS) {
                if(toggleButtonTentativePressed) {
                    if(digitalRead(BUTTON_TOGGLE) == PRESSED) {
                        toggleButtonPressed = true;
                        if(waterFlowing)
                            waterPumpStatus = NOT_FLOWING;
                        else
                            waterPumpStatus = FLOWING;
                    } else {
                        if(waterFlowing)
                            waterPumpStatus = FLOWING;
                        else
                            waterPumpStatus = NOT_FLOWING;
                    }
                } else {
                    if(digitalRead(BUTTON_TOGGLE) == NOT_PRESSED)
                        toggleButtonPressed = false;
                    if(waterFlowing)
                        waterPumpStatus = FLOWING;
                    else
                        waterPumpStatus = NOT_FLOWING;                    
                }
            } else {
                accumulatedToggleButtonTime += timeIncrement_ms;
            }
            break;
        default:
            waterPumpStatus = NOT_FLOWING;
    }

    return waterFlowing;
}

bool isWaterFlowing()
{
    return waterFlowing;
}

//=====[Implementations of private functions]==================================

static void startFlow()
{
    waterFlowing = true;
    digitalWrite(WATER_PUMP_PIN, HIGH);
    digitalWrite(LED_FLOW_ON_PIN, HIGH);
}

static void stopFlow()
{
    waterFlowing = false;
    digitalWrite(WATER_PUMP_PIN, LOW);
    digitalWrite(LED_FLOW_ON_PIN, LOW);
}
