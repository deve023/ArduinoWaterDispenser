//=====[Libraries]=============================================================

#include "waterPump.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

#define PRESSED LOW // PULL UP
#define NOT_PRESSED HIGH // PULL UP
#define BUTTON_HOLD 2 // PULL UP
#define BUTTON_TOGGLE 3 // PULL UP
#define LED_FLOW_ON_PIN 4
#define WATER_PUMP_PIN 5 // Relay. Send PWM. 

#define DEBOUNCE_WATER_PUMP_BUTTON_TIME_MS 40
#define FLOW_RATE 50 // 255: full power. 50: 20% aprox.

//=====[Declaration of private data types]=====================================

typedef enum {
    FLOWING, 
    NOT_FLOWING, 
    DEBOUNCE_HOLD_BUTTON, 
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
    pinMode(BUTTON_HOLD, INPUT_PULLUP);
    pinMode(BUTTON_TOGGLE, INPUT_PULLUP);
    pinMode(LED_FLOW_ON_PIN, OUTPUT);
    pinMode(WATER_PUMP_PIN, OUTPUT);

    waterPumpStatus = NOT_FLOWING;
    stopFlow();

    timeIncrement_ms = dt;
}

bool waterPumpUpdate(bool flowBlock)
{
    // #TODO: Implement.
    static int accumulatedHoldButtonTime = 0;
    static int accumulatedToggleButtonTime = 0;

    static bool holdButtonTentativePressed = false;
    static bool toggleButtonTentativePressed = false;

    switch(waterPumpStatus) {
        case FLOWING:
            if(flowBlock)
                waterPumpStatus = NOT_FLOWING;
            else {
                if(!waterFlowing)
                    startFlow();
            }
            break;
        case NOT_FLOWING:
            if(waterFlowing)
                stopFlow();
            break;
        case DEBOUNCE_HOLD_BUTTON:
            break;
        case DEBOUNCE_TOGGLE_BUTTON:
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
    analogWrite(WATER_PUMP_PIN, FLOW_RATE);
    digitalWrite(LED_FLOW_ON_PIN, HIGH);
    Serial.println("Water flow activated."); // Debug
}

static void stopFlow()
{
    waterFlowing = false;
    analogWrite(WATER_PUMP_PIN, 0);
    digitalWrite(LED_FLOW_ON_PIN, LOW);
}
