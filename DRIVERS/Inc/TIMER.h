/***********************************************************************
 * @file	:	SAMPLER.h
 * @brief 	:	SAMPLER library
 * 				Using SAMPLER2 for sampling and ADC triggering.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

#include "stm32f10x.h"
#include <cstdint>
#include <cstdlib>

namespace TIMER{
    class SAMPLER{
        public:
            
            /**
             * @brief Default constructor
             * default period = 1 ms
             */
            SAMPLER();
            
            /**
             * @brief Custom constructor
             * @param T Sampling time in sec
             */
            SAMPLER(double T);

            /**
             * @brief Start SAMPLER counting
             * @param void
             * @return void
             */
            void start();

            /**
             * @brief Stop SAMPLER counting
             * @param void
             * @return void
             */
            void stop();

        private:
            double sampleTime_;

            /**
             * @brief Configure TIM2C2 for sampling
             * @param void
             * @return void
             */
            void setup();
            
    };
} // namespace TIMER


