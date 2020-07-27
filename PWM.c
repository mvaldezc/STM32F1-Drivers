/***********************************************************************
 * @file	:	PWM.c
 * @brief 	:	PWM library
 * 				Using GPIOA7 for PWM support.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include 	"PWM.h"

/*--------------------------------- USER INPUTS ---------------------------------*/
#define		CORE_FREQ	8000000	// MHz
#define 	PWM_FREQ	24   	// Hz
#define		DUTY_CYCLE  50		// In percentage (0-100)

/*---------------------------------- ARR VALUE ----------------------------------*/
//	ARR calculation to avoid PSC overload
// 		if 					      CORE/PWM > MAX_PSC * ARR_10000 	=> 	error
//		if MAX_PSC * ARR_10000 >= CORE/PWM > MAX_PSC * ARR_1000 	=> 	ARR=10000-1
//		if MAX_PSC * ARR_1000  >= CORE/PWM > MAX_PSC * ARR_100 		=> 	ARR=1000-1
//		if MAX_PSC * ARR_100   >= CORE/PWM > MIN_PSC * ARR_100 		=> 	ARR=100-1
#if 	(CORE_FREQ / PWM_FREQ) > (60000 * 10000)
#error 	"The PWM frequency is to low to be achieved"
#elif 	(CORE_FREQ / PWM_FREQ) > (60000 * 1000)
#define 	ARR_VAL  10000-1
#elif 	(CORE_FREQ / PWM_FREQ) > (60000 * 100)
#define 	ARR_VAL  1000-1
#elif 	(CORE_FREQ / PWM_FREQ) > 100
#define 	ARR_VAL  100-1
#else
#error 	"The PWM frequency is to high to be achieved"
#endif

/*---------------------------------- PSC VALUE ----------------------------------*/
//	PSC calculation to achieve PWM_freq
// 		CNT_freq = CORE_freq / (PSC+1)
//		PWM_freq =  CNT_freq / (ARR+1)
#define		PSC_VAL		( CORE_FREQ / (PWM_FREQ * (ARR_VAL+1))) - 1

/*--------------------------------- CCR2 VALUE ----------------------------------*/
//	CCR2 calculation to achieve duty cycle
//		DUTY_CYCLE = CCR2 / (ARR+1) * 100 %
#define		CCR2_VAL	DUTY_CYCLE * (ARR_VAL+1) / 100


void pwm_config(){

	// GPIOA7 Configuration
	RCC->APB2ENR |= (1 << 2);		// Enable GPIOA Clock
	GPIOA->CRL	 &= ~(0xF << 28); 	// Pin PA7 as Alternate Function mode 50 Mhz
	GPIOA->CRL	 |= (0xB << 28);

	// TIM3 Channel 2 as PWM
	RCC->APB1ENR |= (1 << 1);		// Enable TIM3 Clock

	TIM3->PSC	  = (uint16_t) PSC_VAL; 	// Set the prescaler
	TIM3->ARR	  = (uint16_t) ARR_VAL;		// Maximum CNT Value (Restart counter)
	TIM3->CCR2	  = (uint16_t) CCR2_VAL; 	// If CNT == CCR2 -> OC2REF

	TIM3->CCMR1  |= (0x6000);		// OC2M.  PWM mode 1. If CNT < CCR2 -> OC2REF=1
	TIM3->CCMR1  |= (1 << 11);		// OC2PE. Write operations on CCR2 are taken into account at next update event
	TIM3->CR1	 |= (1 << 7);		// ARPE.  Operations on ARR are taken into account at next update event
	TIM3->CR1	 &= ~(1 << 4);		// DIR.	  Counter in upcounting mode
	TIM3->CR1	 &= ~(1 << 1);		// UDIS.  Update Event enabled at counter overflow or UG bit
	TIM3->CCER   |= (1 << 4);		// CC2E.  Enable Channel 2 to be seen in output pin
}

void enable_pwm(){
	TIM3->EGR |= (1 << 0);		// UG.  Update generation to restart CNT and load new ARR and CCR2 values
	TIM3->CR1 |= (1 << 0); 		// CEN. Enable Timer3 PWM
}

void set_duty(const uint16_t duty_cycle){
	TIM3->CCR2 = duty_cycle * (TIM3->ARR + 1) / 100;
	TIM3->EGR |= (1 << 0);
}
