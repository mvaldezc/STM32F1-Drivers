/********************************************************
 * @file LED.c
 * @brief LED library
 * @authors:
 * 		Derrant
 * 		Morales
 * 		Valdez
 *
 *******************************************************/

#include "LED.h"

void LED_config(){

	// Enable Port C
	RCC->APB2ENR |= (1 << 4);

	// Clean and configure pin PC13 as output mode 50 Mhz
	GPIOC->CRH &= (0xFF0FFFFF);
	GPIOC->CRH |= (0x0001<<20);

	/*CRH REGISTER For each PIN:

	 [1:0]		MODE:	Port mode bits
							00 Input mode
							01 Output mode 10 MHz
							10 Output mode 2 MHz
							11 Output mode 50 MHz

	 [3:2]		CNF:	Port configuration bits
						In input mode:
							00 Analog mode
							01 Floating input
							10 Input with pull-up / pull-down
							11 Reserved
						In output mode:
							00 General purpose output push-pull
							01 General purpose output open-drain
							10 Alternate function output push-pull
							11 Alternate function output open-drain
	 */
}

void LED(const char state){
	switch(state){
	case 0:
		GPIOC->ODR |= (1 << 13);
		break;
	default:
		GPIOC->ODR &= ~(1 << 13);
	}
}

void LED_toggle(){
	GPIOC->ODR ^= (1 << 13);
}
