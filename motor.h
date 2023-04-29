#ifndef _MOTOR_H_
#define _MOTOR_H_

/*
    Module description.
    Pinout.
*/

#include <Arduino.h>

#define MOTOR_RUNNING_SPEED 150

/**
 *  @brief Initialices the motors, divers and related pins.
 *  @param[dt] How often to update the motors.
 */
void motorInit(int dt);

/**
 *  @brief Updates the motor according to input pins.
 *  @return Boolean indicating whether the motors are in motion or not.
 */
bool motorUpdate();

#endif // _MOTOR_H_