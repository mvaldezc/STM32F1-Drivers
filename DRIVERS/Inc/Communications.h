/***********************************************************************
 * @file	:	Communications.h
 * @brief 	:	Generic communication protocols library.
 * 				Functions to send and get strings
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once

namespace COM
{
	class IPrintable
	{
		public:

			/**
			 * @brief Send a string using the underlying protocol
			 * @param ptr Pointer to the string beginning
			 */
			void print(char* ptr);

			/**
			 * @brief Receive a string from the underlying protocol
			 * @param ptr Pointer to string input buffer
			 */
			void getString(char* ptr);

		protected:
			~IPrintable( ) = default;	// ensures default constructor and prevents derived class destructor from not existing

			virtual char getChar(void) = 0;

			virtual void sendChar(char ch) = 0;


	};
} /* namespace COM */
