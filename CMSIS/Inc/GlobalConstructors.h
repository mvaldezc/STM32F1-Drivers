/***********************************************************************
 * @file	:	GlobalConstructors.h
 * @brief 	:	Functions to call the constructors for global objects
 *              in case that the custom startup file does not call
 *              __libc_init_array before the main function
 * @author	:	Marco Valdez
 * 
 * Based on:
 * 		https://bitbashing.io/embedded-cpp.html
 * 
 *
 ***********************************************************************/

#pragma once


static void callConstructors()
{
    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    // Call each function in the list.
    // We have to take the address of the symbols, as __init_array_start *is*
    // the first function pointer, not the address of it.
    for (void (** p)() = &__init_array_start; p < &__init_array_end; ++p) {
        (*p)();
    }
}

