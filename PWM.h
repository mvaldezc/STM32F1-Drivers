/********************************************************
 * @file PWM.h
 * @brief PWM library
 * 		Using GPIOA7 for PWM support.
 * @authors:
 * 		Derrant
 * 		Morales
 * 		Valdez
 *
 *******************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "stm32f103.h"

/**
 * @brief Configure PA7-TIM3C2 for PWM
 *
 * @param void
 *
 * @return void
 */
void PWM_config();


/**
 * @brief Enable PWM
 *
 * @param void
 *
 * @return void
 */
void Enable_PWM();
#endif /* PWM_H_ */


