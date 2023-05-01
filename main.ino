//=====[Libraries]=============================================================

#include ".\src\Motor\motor.h"
#include ".\src\WaterPump\waterPump.h"

//=====[Declaration of public defines]=========================================

#define MAINLOOP_TIME_INCREMENT_MS 10

//=====[Declaration of public global variables]================================

bool blockWaterFlow = false;
bool waterFlowing = false;

//=====[Main setup function, the program entry point after power on or reset]==

void setup() {
    motorInit(MAINLOOP_TIME_INCREMENT_MS);
    waterPumpInit(MAINLOOP_TIME_INCREMENT_MS);

    Serial.begin(9600); // Debug
}

//=====[Main loop function, the program entry point after power on or reset]===

void loop() {
    blockWaterFlow = motorUpdate();
    waterFlowing = waterPumpUpdate(blockWaterFlow);
    
    delay(MAINLOOP_TIME_INCREMENT_MS);
}
