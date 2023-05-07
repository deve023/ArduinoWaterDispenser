//=====[#include guards - begin]===============================================

#ifndef _TRAY_H_
#define _TRAY_H_

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initialices Tray.
 * @param[dt] How often to update the motors.
 */
void trayInit(int dt);

/**
 * @brief Updates Tray status and pins.
 * @return Boolean indicating whether the tray is in motion or not.
 */
bool trayUpdate();

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

#endif _TRAY_H_