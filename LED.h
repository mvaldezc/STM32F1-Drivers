/***********************************************************************
 * @file	:	LED.h
 * @brief 	:	LED library
 * 				Using the built-in LED.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

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
void led_config();

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
void led(const char state);

/**
 * @brief Toggle built-in LED for bluepill
 *
 * @param void
 *
 * @return void
 */
void led_toggle();

#endif /* LED_H_ */
