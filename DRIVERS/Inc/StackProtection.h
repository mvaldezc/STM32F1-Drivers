/***********************************************************************
 * @file	:	StackProtection.h
 * @brief 	:	Functions to protect the stack from corruption
 * @author	:	Marco Valdez
 * 
 * Based on:
 * 		https://bitbashing.io/embedded-cpp.html
 * 		https://phil242.wordpress.com/2016/12/28/hardening-stm32-code-with-system-workbench-ac6-tools/
 * 		https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic
 * 
 *
 ***********************************************************************/

#pragma once
#include <cstdint>
// Add -fstack-protector-strong to compiler

extern "C" {

	// The canary value
	extern const uintptr_t __stack_chk_guard = 0xdeadbeef;

	// Called if the check fails
	[[noreturn]]
	void __stack_chk_fail()
	{
		while(1);
		// print error
	}

} // end extern "C"
