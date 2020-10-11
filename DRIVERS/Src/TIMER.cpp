/***********************************************************************
 * @file	:	SAMPLER.cpp
 * @brief 	:	SAMPLER library
 * 				Using Timer2 for sampling and ADC triggering.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "TIMER.h"

namespace TIMER
{

	/*------------- Constructors -------------*/

    SAMPLER::SAMPLER () : SAMPLER(0.001) {}

    SAMPLER::SAMPLER(double T)
	{
        (*this).sampleTime_ = T;
        setup();
    }

	/*---------------- Methods ---------------*/

    void SAMPLER::setup()
	{
		// TIM2
		/* Sample time must be: */
		/*  0.00005 < T < 5 sec */
		uint16_t ARR_TIM2 = 0;
		RCC->APB1ENR |= (1 << 0);		                // Enable TIM2 Clock

		if(sampleTime_ > 5) exit(EXIT_FAILURE);       	// Calculate best auto reload register value
		else if(sampleTime_ >= 0.005) ARR_TIM2 = 10000;
		else if(sampleTime_ >= 0.00005) ARR_TIM2 = 100;
		else exit(EXIT_FAILURE);

		TIM2->ARR = ARR_TIM2-1;                    		// Set max CNT value
		TIM2->PSC = static_cast<uint16_t>
			((APB1_FREQ*2)/ARR_TIM2*sampleTime_-1); 	// By default, Timers have twice bus freq
		TIM2->CCR2= static_cast<uint16_t> (ARR_TIM2*0.8);			// Take ADC values 0.2*T before

		TIM2->CCMR1 |= 0x7000;			// PWM mode 2
		TIM2->CR1 |= (1 << 2);			// URS. Only counter overflow generates update interrupt
		TIM2->DIER |= (1 << 0);			// CC2IE. Update interrupt enable
		NVIC_EnableIRQ(TIM2_IRQn);
    }

	void SAMPLER::start()
	{
		TIM2->CCER |= (1 << 4);			// Enable Channel 2
		TIM2->CR1 |= (1 << 0); 			// CEN. Enable Timer2
	}

	void SAMPLER::stop()
	{
		TIM2->CCER &= ~(1 << 4);		// Enable Channel 2
		TIM2->CR1 &= ~(1 << 0);			// CEN. Disable Timer 2
	}

} // namespace TIM




