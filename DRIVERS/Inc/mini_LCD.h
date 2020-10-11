/***********************************************************************
 * @file	:	mini_LCD.h
 * @brief 	:	Functions to control 16x2 and 20x4 lcd displays
 *              based on the Hitachi HD44780 controller
 * @author	:	Marco Valdez
 * 
 * Based on:
 * 		https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *      https://cdn-shop.adafruit.com/datasheets/TC2004A-01.pdf
 *      https://www.sparkfun.com/datasheets/LCD/GDM2004D.pdf
 *      http://www.dinceraydin.com/lcd/commands.htm
 *  
 *
 ***********************************************************************/

#pragma once

#include "stm32f10x.h"
#include "delay.h" 
#include "Communications.h"
#include <cstdlib>		// Change when trycatch implemented

#define RS  10 
#define EN  11 
#define D4  12 

enum COMMAND : uint8_t
{
    CLEAR = 0x01, 
    HOME = 0x02, 
    SHIFT_OFF = 0x06,
    SHIFT_ON = 0x07, 
    CURSOR_OFF = 0x0C,
    UNDERLINE_CURSOR_ON = 0x0E,  
    BLOCK_CURSOR_ON = 0x0F,
    FOUR_BITS_TWO_LINES = 0x28
};



class LCD
{
    public:
        /**
         * @brief Default constructor for 4 bits interface
         */
        LCD();
        /**
         * @brief Send an instruction to LCD
         * @param command action to be taken
         */
        void command(COMMAND command);

        /**
         * @brief Go to a specific row and column
         * @param col lcd column
         * @param row lcd row
         */
        void gotoXY(uint8_t row, uint8_t col);

        /**
         * @brief Print a string
         * @param msg Pointer to the string
         */
        void print(char* msg);
        
    private:

        /**
         * @brief LCD initialization commmands
         */
        void init();
        /**
         * @brief Makes the LCD read an instruction
         */
        void enToggle();

        /**
         * @brief Print a character
         * @param data character to send
         */
        void data (char data);

        uint16_t position_;
        
};


