/***********************************************************************
 * @file	:	Communications.cpp
 * @brief 	:	Generic communication protocols library.
 * 				Functions to send and get strings
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "Communications.h"

namespace COM
{
	void IPrintable::print(char* ptr)
	{
		while (*ptr != 0)
		{						// Remain until null character is found (string end)
			sendChar(*ptr++);						// Send character and go to next array position
		}
	}

	void IPrintable::getString(char* ptr)
	{
		do
		{
			*ptr = getChar( );							// Read character
		} while ((*ptr != 0x0) && (*ptr++ != 0x0A)); 	// If character is null or carriage return, then exit loop
														// CTRL-ALT-2 for sending 0 via putty terminal
		*(ptr - 1) = 0x0;									// Make sure string ends with null character
	}

} /* namespace COM */
