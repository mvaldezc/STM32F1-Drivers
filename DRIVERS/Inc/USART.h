/***********************************************************************
 * @file	:	USART.h
 * @brief 	:	USART library
 * 				Library to use USART communication based on 
 * 				the generic communication class
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

#include "Communications.h"
#include "stm32f10x.h"
#include <cstdlib>		// Change when trycatch implemented

enum BAUDS : char {B2400,B9600,B19200,B57600,B115200,B250000};

namespace COM {

	class USART : IPrintable
	{
		protected:
			char getChar(void) override;   // override ensures original getchar is virtual

			void sendChar (char ch) override;

		public:

			/**
             * @brief Custom constructor
			 * @param USARTx Usart structure overlay 
             * @param baudRate Options: 
			 * B2400
			 * B9600
			 * B19200
			 * B57600
			 * B115200
			 * B250000
             */
			USART(USART_TypeDef* USARTx, BAUDS baudRate);

			/**
             * @brief Send string using USART protocol
             * @param ptr Pointer to string output buffer
             * @return void
             */
			//void print (char *ptr);

			/**
             * @brief Get string from USART protocol
             * @param ptr Pointer to string input buffer
             * @return void
             */
			//void getString (char *ptr);

			void setBaudRate(BAUDS baudrate);

		private:
		
			USART_TypeDef* USARTx;

			BAUDS baudRate_;

			void setup ();	
	};
} /* namespace COM */

