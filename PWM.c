/********************************************************
 * @file PWM.c
 * @brief PWM library
 * 		Using GPIOA7 for PWM support.
 * @authors:
 * 		Derrant
 * 		Morales
 * 		Valdez
 *
 *******************************************************/

#include 	"PWM.h"

/********************* USER INPUTS *********************/
#define		MAIN_FREQ	8		// MHz
#define 	PWM_FREQ	0.010	// kHz
#define		RESOLUTION	100		// 100 %
#define		DUTY_CYCLE  50		// In percentage

/********************** VARIABLES **********************/
#define		PSC_VAL	 (MAIN_FREQ/(PWM_FREQ*RESOLUTION)*1000)-1 // Calculated prescaler value to achieve PWM_FREQ


void PWM_config(){

	// GPIOA7 Configuration
	RCC->APB2ENR |= (1 << 2);	//Enable GPIOA Clock
	GPIOA->CRL		 = (GPIOA->CRL & 0x0FFFFFFF)|(0xB0000000); // Pin PA7 as Alternate Function mode 50 Mhz

	// TIM3 Channel 2 as PWM
	RCC->APB1ENR   |= (1 << 1);					// Enable TIM3 Clock
	TIM3->PSC		= (uint16_t) PSC_VAL; 		// Set the prescaler
	TIM3->ARR		= (uint16_t) RESOLUTION;	// Maximum CNT Value
	TIM3->CCR2		= (uint16_t) DUTY_CYCLE; 	// if CNT>=CCR2 => OC2REF = 1 else OCREF = 0
	TIM3->CCMR1    |= (0x6000);					// Output mode PWM mode 1
	TIM3->CCER 	   |= (1 <<4 ); 				// Enable Channel 2 to be seen in output pin
	/*CCMR1 REGISTER OUTPUT COMPARE MODE  bits:
		[9:8]	CC2S:		Direction of the channel (input/output) as well as the used input.
								00	Output
								01	Input mapped on TI1
								10	Input mapped on TI2
								11	Input mapped on TRC (depends on internal trigger)

		[10]	OC2FE:		Fast enable

		[11]	OC2PE:		Preload enable

		[14:12]	OC2M:		These bits define the behavior of the output reference signal OC2REF
								110	PWM mode 1 In upcounting, channel 2 is active as long as TIMx_CNT<TIMx_CCR1
								111 PWM mode 2 In upcounting, channel 2 is inactive as long as TIMx_CNT<TIMx_CCR1

		[15]	OC2CE:		Clear enable

	*/

}

void Enable_PWM(){
	TIM3->CR1 |= (1<<0); 		// Enable Timer3 PWM
}
