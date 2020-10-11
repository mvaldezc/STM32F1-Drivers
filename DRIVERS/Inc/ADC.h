/***********************************************************************
 * @file	:	ADC.h
 * @brief 	:	ADC library
 * 				GPIOB0 / GPIOB1 as analog input using ADC1 channels 8,9
 * 				Data moved with DMA Channel1 to box and box+1 addresses
 * 				Triggered by TIM2 Channel2 Event (when CNT = CCR2)
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

#include "stm32f10x.h"
#include <vector>
#include <cstdlib>
#include <map>
#include "delay.h"

enum class MODE : char {AUTO , TRIG};       // due to "class" keyword, identifier must be also providen
namespace ANALOG
{
    class ADC
    {
        public:

            /**
             * @brief Custom constructor
             * @param channels Vector with the channels to scan in order
             * default mode : AUTO
             */
            ADC(const std::vector<char> channels);

            /**
             * @brief Custom constructor
             * @param mod ADC scan mode AUTO/TRIGGERED (AUTO - TRIG)
             * @param channels Vector with the channels to scan in order
             */
            ADC(MODE mod, const std::vector<char> channels);

            /**
             * @brief Trigger one measurement and store it
             * @param void
             * @return The 12-bits measurement
             */
            int measure();

            /**
             * @brief Calibrate the capacitors of the ADC module
             * @param void
             * @return void
             */
            void calibrate();

        private:
            /**
             * @brief Configure ADC1 for analog read.
             * GPIOs depend on the channels
             */
            void setup();

            // ADC mode (AUTO - TRIGGERED)
            MODE mode_;

            // ADC vector of channels
            std::vector<char> channels_;

    };
}



class DMA
{
    public:
        static void start(uint16_t *box);
};


