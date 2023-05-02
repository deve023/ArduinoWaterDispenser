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

/**
 * @brief Returns boolean indicating if the tray is standing still.
 * 
 * @return true If the tray is still.
 * @return false If the tray is moving.
 */
bool isTrayInPlace();

/**
 * @brief Returns boolean indicating if the tray is moving up.
 * 
 * @return true If the tray is moving up.
 * @return false If the tray is not moving up.
 */
bool isTrayMovingUp();

/**
 * @brief Returns boolean indicating if the tray is moving down.
 * 
 * @return true If the tray is moving down.
 * @return false If the tray is not moving down.
 */
bool isTrayMovingDown();

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_