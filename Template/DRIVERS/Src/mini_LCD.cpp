/***********************************************************************
 * @file	:	mini_LCD.cpp
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

#include "mini_LCD.h"

LCD::LCD()
{
    init();
}

void LCD::init( ) { 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 
	GPIOB->CRH = ( GPIOB->CRH & ~0xFFFFFF00 ) | 0x33333300; 
	delay_ms(20);
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 | 1 << RS | 1 << EN ) ) | 3 << D4; 
	enToggle( );  delay_ms(5); 
    // send 0x3 again in D4-D7
    enToggle( ); delay_us(100);  
    // send 0x3 again in D4-D7
	enToggle( );
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 ) ) | 2 << D4; 
	enToggle( ); 
	command(COMMAND::FOUR_BITS_TWO_LINES);      // Set 4 bits interface , 2 lines
	command(COMMAND::UNDERLINE_CURSOR_ON);      // Turn on visible underline cursor
	command(COMMAND::SHIFT_OFF);				// Display shift off, Increment address counter
	command(COMMAND::CLEAR);     				// Clear screen
} 

void LCD::command(COMMAND command) { 
	GPIOB->ODR = ( GPIOB->ODR & ~( 1 << RS | 0xF << D4 ) ) | ( (command >> 4) << D4 );
	enToggle( ); 
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 ) )  | ( command << D4) ;
    enToggle( ); 
	if( ( command == COMMAND::HOME )  |  ( command == COMMAND::CLEAR ) ) delay_ms(2); 
	else delay_us(50);  
} 

void LCD::data( char data ) { 
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 ) ) |  1 << RS | ( data << D4 >> 4 );    
	enToggle( ); 
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 ) ) | data << D4;  
	enToggle( ); delay_us(50);
} 

void LCD::gotoXY( uint8_t row, uint8_t col ) { 
	if(row < 0 || row > 3 || col < 0 || col > 19)	exit(EXIT_FAILURE);
    char row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	position_ = (0x80 | ( col + row_offsets[row]) );
	GPIOB->ODR = ( GPIOB->ODR & ~( 1 << RS | 0xF << D4 ) ) | ( (position_ >> 4) << D4 ); 
	enToggle( ); 
	GPIOB->ODR = ( GPIOB->ODR & ~( 0xF << D4 ) ) | ( position_ << D4) ;
    enToggle( ); 
	delay_us(50);  
} 

void LCD::print( char* msg )  { 
    while (*msg !=0) {						// Remain until null character is found (string end)
        data(*msg++);						// Send character and go to next array position
    } 
} 

void LCD::enToggle( ) { 
	GPIOB->ODR |= ( 1 << EN ); 
	delay_us(200); 
	GPIOB->ODR &= ~( 1 << EN ); 
}



