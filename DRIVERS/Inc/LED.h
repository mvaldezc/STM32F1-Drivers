/***********************************************************************
 * @file	:	LED.cpp
 * @brief 	:	LED library
 * 				Using the built-in LED for the bluepill.
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

#include "stm32f10x.h"
#define PC13 (*((volatile unsigned long*) 0x422201B4 ))	// Bit Banding for PC13
#define ON  1
#define OFF 0

class LED {
	public:
		LED();

		/**
		 * @brief Activate built-in LED
		 * @param state  (ON / OFF)
		 * @return void
		 */
		void turn(const char state);

		/**
		 * @brief Toggle built-in LED for bluepill
		 */
		void toggle();

		// Built-in LED state
		char state;

	private:
		/**
		 * @brief Set GPIO registers for LED
		 */
		void setup();
};


