//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  @brief Initialices the modules and related pins.
 *  
 */
void userInterfaceInit(int dt);

/**
 *  @brief Initialices updates the modules related to the user interface.
 *  
 */
void userInterfaceUpdate();

//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_