/***********************************************************************
 * @file	:	LED.cpp
 * @brief 	:	LED library
 * 				Using the built-in LED.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "LED.h"

LED::LED(){
	setup();
}

void LED::setup(){

	// Enable Port C
	RCC->APB2ENR |= (1 << 4);
	GPIOC->ODR |= (1 << 13);
	// Clean and configure pin PC13 as output mode 50 Mhz
	GPIOC->CRH &= (0xFF0FFFFF);
	GPIOC->CRH |= (1 << 20);
	state = 0;

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

// Bit Banding was used instead of GPIOC->ODR
void LED::turn(const char arg){
	state = arg;
	switch(state){
	case 0:
		PC13 = 1;
		break;
	default:
		PC13 = 0;
	}
}

// Inline function for faster performance
void LED::toggle(){
	GPIOC->ODR ^= (1 << 13);
	state ^= 0x1;
}

