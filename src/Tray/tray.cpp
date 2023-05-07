//=====[Libraries]=============================================================

#include "tray.h"
#include ".\Motor\motor.h"
#include ".\Positions\positions.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
    TRAY_IN_PLACE,
    TRAY_GOING_UP,
    TRAY_GOING_DOWN,
    TRAY_MOVING_TO_POSITION
} TrayStatus_t;

typedef enum {
    POSITION_1,
    POSITION_2,
    POSITION_3,
    POSITION_X
} Position_t;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

void moveToPosition(Position_t pos);

//=====[Implementations of public functions]===================================

void trayInit(int dt)
{
    motorInit(dt);
}

bool trayUpdate()
{
    return motorUpdate();
}

bool isTrayInPlace()
{
    return isMotorInPlace();
}

bool isTrayMovingUp()
{
    return isMotorMovingUp();
}

bool isTrayMovingDown()
{
    return isMotorMovingDown();
}

//=====[Implementations of private functions]==================================


void moveToPosition(Position_t pos)
{
    // TODO: Implement
}