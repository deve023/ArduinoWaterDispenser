//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

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

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_