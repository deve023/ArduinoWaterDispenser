//=====[Libraries]=============================================================

#include "userInterface.h"
#include "..\Motor\motor.h"
#include "..\WaterPump\waterPump.h"

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000
#define I2C_ADDR 0x27 // Check with I2C Scanner
#define I2C_SDA_PIN 18 // A4 pin
#define I2C_SCL_PIN 19 // A5 pin

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of private global variables]============

LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

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

    lcd.begin(20,4);
    lcd.backlight();

    lcd.setCursor(0,1);
    lcd.print("Water ");

    lcd.setCursor(0,2);
    lcd.print("Tray ");

    // Date & Time
    lcd.setCursor(0,0);
    lcd.print("20:55");
    lcd.setCursor(12,0);
    lcd.print("01/05/23");
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;

    if(accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS) {
        accumulatedDisplayTime = 0;

        lcd.setCursor(6,1);
        if(isWaterFlowing())
            lcd.print("flowing.");
        else
            lcd.print("not flowing.");
        
        lcd.setCursor(5,2);
        if(isTrayInPlace())
            lcd.print("standing still.");
        else if (isTrayMovingUp())
            lcd.print("moving up.");
        else if(isTrayMovingDown())
            lcd.print("moving down.");

        /*
        * #TODO:
        *  Which position the tray is on.
        * Only update if tray standing still. 
        * Put X if the position is not recorded.
        */
        lcd.setCursor(0,3);
        lcd.print("Position X");
        
        // #TODO: Date & Time - Update
        lcd.setCursor(0,0);
        lcd.print("20:55");
        lcd.setCursor(12,0);
        lcd.print("01/05/23");

    } else {
        accumulatedDisplayTime += timeIncrement_ms;
    }
}