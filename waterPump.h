#ifndef _WATER_PUMP_H_
#define _WATER_PUMP_H_

/*
    Module description.
    Pinout.
*/

#include <Arduino.h>

/**
 *  @brief Initialices the water pump and related pins.
 *  @param[in] dt How often to update the water pump.
 */
void waterPumpInit(int dt);

/**
 *  @brief Updates the water pump according to input pins and flowBlock if activated.
 *  @param[in] flowBlock Boolean indicating whether the motors are in motion or not.
 */
void motorUpdate(bool flowBlock);

#endif //_WATER_PUMP_H_