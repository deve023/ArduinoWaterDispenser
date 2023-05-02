//=====[#include guards - begin]===============================================

#ifndef _WATER_PUMP_H_
#define _WATER_PUMP_H_

/*
    Module description.
    Pinout.
*/

//=====[Declarations (prototypes) of public functions]=========================

/**
 *  @brief Initialices the water pump and related pins.
 *  @param[in] dt How often to update the water pump.
 */
void waterPumpInit(int dt);

/**
 *  @brief Updates the water pump according to input pins
 * and flowBlock if activated.
 *  @param[in] flowBlock Boolean indicating whether the
 * water flow should be activated or not due to system
 * interaction.
 * @return Boolean indicating if the water is flowing.
 */
bool waterPumpUpdate(bool flowBlock);

/**
 * @brief Return Boolean indicating water flow.
 * 
 * @return true if water is flowing.
 * @return false false if water is not flowing.
 */
bool isWaterFlowing();

//=====[#include guards - end]=================================================

#endif //_WATER_PUMP_H_