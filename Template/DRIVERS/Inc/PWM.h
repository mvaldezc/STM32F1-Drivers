/***********************************************************************
 * @file	:	PWM.h
 * @brief 	:	PWM library
 * 				Using GPIOA7 and TIM3 for PWM support.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

#include "stm32f10x.h"
#include <cstdlib>

#define	    TIM_FREQ   (APB1_FREQ*2)

namespace TIMER {
    class PWM {
        public:

            /**
             * @brief Default constructor
             * default freq = 1000
             * default duty = 0
             */
            PWM();

            /**
             * @brief Custom constructor
             * @param freq PWM frequency [Hz]
             * @param duty PWM duty cycle
             */
            PWM(double freq, double duty);

            /**
             * @brief Enable PWM output
             * @param void
             * @return void
             */
            void enable();

            /**
             * @brief Disable PWM output
             * @param void
             * @return void
             */
            void disable();

            /**
             * @brief Change duty cycle
             * @param duty (0-100)
             * @return void
             */
            void duty(const uint16_t duty);

            /**
             * @brief Set PWM freq and duty cycle
             * @param pwm_f (0.02 - 720000) [Hz]
             * @param duty (0 - 100) %
             * @return void
             */
            void set(const double pwm_f, const double duty);

            // PWM output frequency
            double frequency;

            // PWM output dutyCycle
            double dutyCycle;
        
        private: 
            /**
             * @brief Configure PA7-TIM3C2 for PWM
             * @param void
             * @return void
             */
            void setup();

    };

} /* namespace TIM */


