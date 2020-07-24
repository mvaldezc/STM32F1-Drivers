/********************************************************
 * @file LED.h
 * @brief LED library
 * @authors:
 * 		Derrant
 * 		Morales
 * 		Valdez
 *
 *******************************************************/

#ifndef LED_H_
#define LED_H_

#include "stm32f103.h"

/**
 * @brief Activate built-in LED for bluepill
 *
 * @param void
 *
 * @return void
 */
void LED_config();

/**
 * @brief Activate built-in LED for bluepill
 *
 * Desired LED status
 * 	1  ON (or any number different from 0)
 * 	0  OFF
 *
 * @param state
 *
 * @return void
 */
void LED(const char state);

/**
 * @brief Toggle built-in LED for bluepill
 *
 * @param void
 *
 * @return void
 */
void LED_toggle();

#endif /* LED_H_ */
