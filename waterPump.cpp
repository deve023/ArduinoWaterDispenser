#include "waterPump.h"

#define PRESSED LOW // PULL UP
#define NOT_PRESSED HIGH // PULL UP
#define BUTTON_HOLD 2 // PULL UP
#define BUTTON_TOGGLE 3 // PULL UP

#define DEBOUNCE_WATER_PUMP_BUTTON_TIME_MS 40

typedef enum {
    FLOWING, 
    NOT_FLOWING, 
    DEBOUNCE_HOLD_BUTTON, 
    DEBOUNCE_TOGGLE_BUTTON
} WaterPumpStatus_t;

static WaterPumpStatus_t waterPumpStatus;
static int timeIncrement_ms;

void waterPumpInit(int dt)
{
    pinMode(BUTTON_HOLD, INPUT_PULLUP);
    pinMode(BUTTON_TOGGLE, INPUT_PULLUP);

    waterPumpStatus = NOT_FLOWING;

    timeIncrement_ms = dt;
}

void motorUpdate(bool flowBlock)
{
    // #TODO: Implement.
    static int accumulatedHoldButtonTime = 0;
    static int accumulatedToggleButtonTime = 0;

    static bool holdButtonTentativePressed = false;
    static bool toggleButtonTentativePressed = false;

    switch(waterPumpStatus) {
        case FLOWING:
            break;
        case NOT_FLOWING:
            break;
        case DEBOUNCE_HOLD_BUTTON:
            break;
        case DEBOUNCE_TOGGLE_BUTTON:
            break;
        default:
            waterPumpStatus = NOT_FLOWING;
    }
}