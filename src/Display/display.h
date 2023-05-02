//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  @brief Initialices the display and related pins.
 *  
 */
void displayInit();

/**
 * @brief Sets the position to write the next char.
 * 
 * @param charPositionX X-axis position.
 * @param charPositionY Y-axis position.
 */
void displayCharPositionWrite(uint8_t charPositionX, uint8_t charPositionY);

/**
 * @brief Displays string in the display.
 * 
 * @param str String to display.
 */
void displayStringWrite(const char * str);

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_