/***********************************************************************
 * @file	:	PWM.c
 * @brief 	:	PWM library
 * 				Using GPIOA7 for PWM support.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

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
void pwm_config();


/**
 * @brief Enable PWM
 *
 * @param void
 *
 * @return void
 */
void enable_pwm();

/**
 * @brief Change duty cycle value
 *
 * @param duty_cycle (0-100)
 *
 * @return void
 */
void set_duty(const uint16_t duty_cycle);
#endif /* PWM_H_ */


