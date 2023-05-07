/*! @mainpage Arduino Water Dispenser 
 * @date Monday, May 1, 2023
 * @authors Agustin de Vedia
 *
 * @file main.ino Main program script for Arduino.
 * Refer to src\ for the implementation of the modules.
 *
 * @note Program is designed to run in an Arduino Nano.
 */

//=====[Libraries]=============================================================

#include ".\src\Tray\tray.h"
#include ".\src\WaterPump\waterPump.h"
#include ".\src\UserInterface\userInterface.h"

//=====[Declaration of public defines]=========================================

#define MAINLOOP_TIME_INCREMENT_MS 10 ///< Time interval to update modules.

//=====[Declaration of public global variables]================================

bool blockWaterFlow = false; ///< Boolean to indicate if the flow of water should be suspended.

//=====[Main setup function, the program entry point after power on or reset]==

/**
 * @brief Main setup function.
 * 
 */
void setup() {
    trayInit(MAINLOOP_TIME_INCREMENT_MS);
    waterPumpInit(MAINLOOP_TIME_INCREMENT_MS);
    userInterfaceInit(MAINLOOP_TIME_INCREMENT_MS);

    Serial.begin(9600); // Debug
}

//=====[Main loop function, the program entry point after power on or reset]===

/**
 * @brief Mainloop.
 * 
 */
void loop() {
    blockWaterFlow = trayUpdate();
    waterPumpUpdate(blockWaterFlow);
    
    userInterfaceUpdate();
    
    delay(MAINLOOP_TIME_INCREMENT_MS);
}
