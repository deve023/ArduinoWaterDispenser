#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <Arduino.h>

#define MOTOR_RUNNING_SPEED 150

/**
 *  @brief Initialices the motor and drivers.
 *  @param[dt] How often to update the motors.
 */
void motorInit(int dt);

/**
 *  @brief Updates the motor according to current program variables.
 *  @return Boolean indicating whether the motors are in motion or not.
 */
bool motorUpdate();

#endif // _MOTOR_H_