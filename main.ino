#include "motor.h"
#include "waterPump.h"

#define MAINLOOP_TIME_INCREMENT_MS 10

bool blockWaterFlow = false;

void setup() {
    motorInit(MAINLOOP_TIME_INCREMENT_MS);
}

void loop() {
    blockWaterFlow = motorUpdate();
    // #TODO: updateWaterPump(blockWaterFlow);
    
    delay(MAINLOOP_TIME_INCREMENT_MS);
}
