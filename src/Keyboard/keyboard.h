//=====[#include guards - begin]===============================================

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initialices keyboard and related pins.
 * 
 * @param updateTime_ms How often to update the keyboard.
 */
void keyboardInit(int dt);

/**
 * @brief Updates the keyboard status and pressed keys.
 * 
 * @return char Key released. If none: returns '\0'.
 */
char keyboardUpdate();

//=====[#include guards - end]=================================================

#endif //_KEYBOARD_H_