//=====[Libraries]=============================================================

#include "userInterface.h"
#include "..\Display\display.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of private global variables]============

static int timeIncrement_ms;

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Initialices the display.
 * 
 */
static void userInterfaceDisplayInit(int dt);

/**
 * @brief Updates the display.
 * 
 */
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit(int dt)
{
    userInterfaceDisplayInit(dt);
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================

static void userInterfaceDisplayInit(int dt)
{
    // #TODO: Adjust display style.
    timeIncrement_ms = dt;
    displayInit();

    displayCharPositionWrite(0,0);
    displayStringWrite("Water flowing: ");

    displayCharPositionWrite(0,1);
    displayStringWrite("Tray ");

    // Date & Time
    displayCharPositionWrite(3,0);
    displayStringWrite("20:55");
    displayCharPositionWrite(3,12);
    displayStringWrite("01/05/23");
}

static void userInterfaceDisplayUpdate()
{
    // #TODO: Implement how to know the info to update.
    static int accumulatedDisplayTime = 0;

    if(accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS) {
        accumulatedDisplayTime = 0;

        displayCharPositionWrite(15,0);
        displayStringWrite("No."); // Or yes depending on water flow.
        displayCharPositionWrite(5,1);
        displayStringWrite("standing still."); // Or moving up. / moving down.

        /*
        *  Which position the tray is on.
        * Only update if tray standing still. 
        * Put X if the position is not recorded.
        */
        displayCharPositionWrite(0,2);
        displayStringWrite("Position X");
        
        // Date & Time - Update
        displayCharPositionWrite(3,0);
        displayStringWrite("20:55");
        displayCharPositionWrite(3,12);
        displayStringWrite("01/05/23");

    } else {
        accumulatedDisplayTime += timeIncrement_ms;
    }
}