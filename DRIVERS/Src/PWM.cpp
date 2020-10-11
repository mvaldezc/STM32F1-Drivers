/***********************************************************************
 * @file	:	PWM.c
 * @brief 	:	PWM library
 * 				Using GPIOA7 for PWM support.
 * 				Use TIM3C2 for PWM output.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "PWM.h"

namespace TIMER {

	/*----------- Constructors -----------*/

	PWM::PWM():PWM(1,0){};

	PWM::PWM(double freq, double duty){
		(*this).frequency = freq;
		(*this).dutyCycle = duty;
		setup();
	}

	/*-------------- Methods -------------*/

	void PWM::setup(){
		// GPIOA7 Configuration
		RCC->APB2ENR |= (1 << 2);		// Enable GPIOA Clock
		GPIOA->CRL	 &= ~(0xF << 28); 	// Pin PA7 as Alternate Function mode 50 Mhz
		GPIOA->CRL	 |= (0xB << 28);

		// TIM3 Channel 2 as PWM
		RCC->APB1ENR |= (1 << 1);		// Enable TIM3 Clock

		set(frequency,dutyCycle);		// PSC, ARR and CCR2

		TIM3->CCMR1  |= (0x6000);		// OC2M.  PWM mode 1. If CNT < CCR2 -> OC2REF=1
		TIM3->CCMR1  |= (1 << 11);		// OC2PE. Write operations on CCR2 are taken into account at next update event
		TIM3->CR1	 |= (1 << 7);		// ARPE.  Operations on ARR are taken into account at next update event
		TIM3->CR1	 &= ~(1 << 4);		// DIR.	  Counter in upcounting mode
		TIM3->CR1	 &= ~(1 << 1);		// UDIS.  Update Event enabled at counter overflow or UG bit
	}

	void PWM::enable(){
		TIM3->EGR 	|= (1 << 0);		// UG.  Update generation to restart CNT and load new ARR and CCR2 values
		TIM3->CCER	|= (1 << 4);		// CC2E.  Enable Channel 2 to be seen in output pin
		TIM3->CR1	|= (1 << 0); 		// CEN. Enable Timer3 PWM
	}

	void PWM::disable(){
		TIM3->CCER	&= ~(1 << 4);		// CC2E. Disable Channel 2 to be seen in output pin
		TIM3->CR1	&= ~(1 << 0); 		// CEN. Disable Timer3
	}

	void PWM::duty(const uint16_t duty){
		if(duty == 0){
			TIM3->CCR2 = 0;
			return;
		}
		TIM3->CCR2 = duty * (TIM3->ARR + 1) / 100;
	}

	void PWM::set(const double pwm_f, const double duty){
		// PWM frequency 	Hz
		// Duty Cycle 		In percentage (0-100)
		/*    0.02 < pwm_f < 720000 	hz	*/
		/* 0.0000014 < pwm_T < 50   	seg	*/

		const uint32_t tim_f = TIM_FREQ;

		// Set maximum CNT Value (Restart counter)
		if( pwm_f == 0) disable(); 
		else if	(tim_f / pwm_f > 3600000000)    exit(EXIT_FAILURE);
		else if	(tim_f / pwm_f > 600000000) 	TIM3->ARR = static_cast<uint16_t> (59999);
		else if (tim_f / pwm_f > 60000000) 		TIM3->ARR = static_cast<uint16_t> (9999);
		else if (tim_f / pwm_f > 6000000) 		TIM3->ARR = static_cast<uint16_t> (999);
		else if (tim_f / pwm_f > 100) 			TIM3->ARR = static_cast<uint16_t> (99);
		else	exit(EXIT_FAILURE);

		// Set the prescaler
		TIM3->PSC = static_cast<uint16_t> ((tim_f / (pwm_f * (TIM3->ARR + 1))) - 1);

		// If CNT < CCR2 -> OC2REF = 1
		if(duty == 0){
			TIM3->CCR2 = 0;
		}
		else{
			TIM3->CCR2 = static_cast<uint16_t> (duty * (TIM3->ARR + 1) / 100);
		}
	}

} /* namespace TIM */
