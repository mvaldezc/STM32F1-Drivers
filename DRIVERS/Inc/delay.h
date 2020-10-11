/***********************************************************************
 * @file	:	delay.h
 * @brief 	:	Delay library using Systick Timer to achieve accurate
 * 				ms and us software delays (really based on hardware).
 * 				CMSIS functions are needed, and a modification of
 * 				core_cmx header is required to avoid using systick
 * 				exceptions.
 * 
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

# pragma once
#include "stm32f10x.h"

// Max delay 1860 ms
inline void delay_ms(uint32_t time){
	// A custom core_cmx header without SysTick IRQ enable needed
	// The 8000 is due to dividing by 1000 gives ms, 8 is the applied prescaler
	SysTick_Config((SystemCoreClock / 8000) * time);
	while(!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG));
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

inline void delay_us(uint32_t time){
	// A custom core_cmx header without SysTick IRQ enable needed
	// The 8000000 is due to dividing by 1000000 gives ms, 8 is the applied prescaler
	SysTick_Config((SystemCoreClock / 8000000) * time);
	while(!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG));
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}
