//=====[Libraries]=============================================================

#include "userInterface.h"
#include "..\Motor\motor.h"
#include "..\WaterPump\waterPump.h"

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 500
#define I2C_ADDR 0x27 // Check with I2C Scanner
#define I2C_SDA_PIN 18 // A4 pin
#define I2C_SCL_PIN 19 // A5 pin

//=====[Declaration of private data types]=====================================

typedef enum {
    MAIN_SCREEN,
    DATE_AND_TIME_CONFIG,
    PASSWORD_CONFIG,
    PASSWORD_REQUIRED
} ScreenStatus_t;

//=====[Declaration and initialization of private global variables]============

LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
static ScreenStatus_t screenStatus;
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

/**
 * @brief Updates the main screen on the display.
 * 
 * 23:42       03/05/23
 * WATER NOT FLOWING
 * TRAY STANDING STILL
 * POSITION X  VOL: 98%
 * 
 */
static void mainScreenUpdate();

/**
 * @brief Updates the Date And Time Config screen on the display.
 * 
 * DATE AND TIME CONFIG
 * PLEASE ENTER NEW    
 * DATE AND TIME:      
 * __:__:__  __/__/____
 * 
 * DATE AND TIME CONFIG
 * NEW  DATE  AND  TIME
 *        SAVED!       
 * 15:21:00  25/05/2024
 * 
 */
static void dateAndTimeConfigScreenUpdate();

/**
 * @brief Updates the Password Config screen on the display.
 * 
 *   PASSWORD  CONFIG  
 *     PLEASE ENTER    
 *     NEW PASSWORD    
 * -------______-------
 * 
 *   PASSWORD  CONFIG  
 *   PASSWORD UPDATED  
 *       CORRECTLY     
 * -------XXXXXX-------
 * 
 */
static void passwordConfigScreenUpdate();

/**
 * @brief Updates the Password Required screen on the display.
 * 
 * THIS  CONFIGURATION 
 * IS PROTECTED, PLEASE
 * ENTER YOUR PASSWORD:
 * -------______-------
 * 
 *  INCORRECT PASSWORD 
 *   PLEASE TRY AGAIN
 *  *1 FAILED ATTEMPT* 
 * -------______-------
 * 
 */
static void passwordRequiredScreenUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit(int dt)
{
    screenStatus = MAIN_SCREEN;
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
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;

    if(accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS) {
        accumulatedDisplayTime = 0;

        switch(screenStatus) {
            case MAIN_SCREEN:
                mainScreenUpdate();
                break;
            case DATE_AND_TIME_CONFIG:
                dateAndTimeConfigScreenUpdate();
                break;
            case PASSWORD_CONFIG:
                passwordConfigScreenUpdate();
                break;
            case PASSWORD_REQUIRED:
                passwordRequiredScreenUpdate();
                break;
            default:
                userInterfaceInit(timeIncrement_ms);
        }
    } else {
        accumulatedDisplayTime += timeIncrement_ms;
    }
}

static void mainScreenUpdate()
{
        lcd.setCursor(0,1);
        if(isWaterFlowing())
            lcd.print("WATER FLOWING.    ");
        else
            lcd.print("WATER NOT FLOWING.");
        
        lcd.setCursor(0,2);
        if(isTrayInPlace())
            lcd.print("TRAY STANDING STILL.");
        else if (isTrayMovingUp())
            lcd.print("TRAY MOVING UP.     ");
        else if(isTrayMovingDown())
            lcd.print("TRAY MOVING DOWN.   ");

        /*
        * #TODO:
        *  Which position the tray is on.
        * Only update if tray standing still. 
        * Put X if the position is not recorded.
        */
       if(isTrayInPlace()) {
            lcd.setCursor(0,3);
            lcd.print("POSITION X  ");
        } else {
            lcd.setCursor(0,3);
            lcd.print("          ");
        }

        // #TODO: Show % of water left.
        lcd.setCursor(12,3);
        lcd.print("VOL: 98%");
        
        // #TODO: Date & Time - Update
        lcd.setCursor(0,0);
        lcd.print("18:15       ");
        lcd.setCursor(12,0);
        lcd.print("03/05/23");
}

static void dateAndTimeConfigScreenUpdate()
{
    lcd.setCursor(0,0);
    lcd.print("DATE AND TIME CONFIG");

    lcd.setCursor(0,1);
    lcd.print("PLEASE ENTER NEW    ");

    lcd.setCursor(0,2);
    lcd.print("DATE AND TIME:      ");

    lcd.setCursor(0,3);
    lcd.print("  :  :      /  /    ");

    delay(2000);

    lcd.setCursor(0,1);
    lcd.print("NEW  DATE  AND  TIME");

    lcd.setCursor(0,2);
    lcd.print("       SAVED!       ");

    lcd.setCursor(0,3);
    lcd.print("18:47:00  03/05/2023");    
}

static void passwordConfigScreenUpdate()
{
    lcd.setCursor(0,0);
    lcd.print("  PASSWORD  CONFIG  ");

    lcd.setCursor(0,1);
    lcd.print("    PLEASE ENTER    ");

    lcd.setCursor(0,2);
    lcd.print("    NEW PASSWORD    ");

    lcd.setCursor(0,3);
    lcd.print("-------      -------");

    delay(2000);

    lcd.setCursor(0,1);
    lcd.print("  PASSWORD UPDATED  ");

    lcd.setCursor(0,2);
    lcd.print("      CORRECTLY     ");

    lcd.setCursor(0,3);
    lcd.print("-------******-------");
}

static void passwordRequiredScreenUpdate()
{
    lcd.setCursor(0,0);
    lcd.print("THIS  CONFIGURATION ");

    lcd.setCursor(0,1);
    lcd.print("IS PROTECTED, PLEASE");

    lcd.setCursor(0,2);
    lcd.print("ENTER YOUR PASSWORD:");

    lcd.setCursor(0,3);
    lcd.print("-------      -------");

    delay(2000);

    lcd.setCursor(0,0);
    lcd.print(" INCORRECT PASSWORD ");

    lcd.setCursor(0,1);
    lcd.print("  PLEASE TRY AGAIN  ");

    lcd.setCursor(0,2);
    lcd.print(" *1 FAILED ATTEMPT* ");

    lcd.setCursor(0,3);
    lcd.print("-------      -------");
}