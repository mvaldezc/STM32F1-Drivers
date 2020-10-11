/***********************************************************************
 * @file	:	USART.cpp
 * @brief 	:	USART library
 * 				Library to use USART communication
 * 				It only allows USART 1 and USART 2
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "USART.h"

namespace COM 
{
	
	/*------------- Constructors -------------*/

	USART::USART(USART_TypeDef* USARTx, BAUDS baudRate) 
		: baudRate_(baudRate)
	{
		this->USARTx = USARTx;
		setup();
	}

	/*---------------- Methods ---------------*/

	void USART::setup () {
		uint8_t offset;	// Usart offset

		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		// Enable clock for USARTx
		// Put PA9  / PA2 (TX) to alternate function output push-pull at 50 MHz
		// Put PA10 / PA3 (RX) to floating input
			 if(USARTx == USART1) { RCC->APB2ENR |= RCC_APB2ENR_USART1EN; offset = 0;
									GPIOA->CRH = (GPIOA->CRH & 0xFFFFF00F) | 0x000004B0;}
		else if(USARTx == USART2) { RCC->APB1ENR |= RCC_APB1ENR_USART2EN; offset = 1;
									GPIOA->CRL = (GPIOA->CRL & 0xFFFF00FF) | 0x00004B00;}
		else exit(EXIT_FAILURE);

		// Baud rate	 BRR value
		uint16_t brr_val;
		switch (baudRate_)
		{
			case B2400:
				brr_val = 0x3A98;
				break;
			case B9600:
				brr_val = 0xEA6;
				break;
			case B19200:
				brr_val = 0x753;
				break;
			case B57600:
				brr_val = 0x271;
				break;
			case B115200:
				brr_val = 0x138;
				break;
			case B250000:
				brr_val = 0x9;
				break;
			default:
				exit(EXIT_FAILURE);
		}

		USARTx->BRR = brr_val;
		USARTx->CR1 |= (USART_CR1_RE | USART_CR1_TE);
		// RX, TX enable
		NVIC_EnableIRQ(static_cast<IRQn_Type> ((uint8_t)USART1_IRQn + offset));		// Enable Usart interruption
		USARTx->CR1 |= USART_CR1_RXNEIE;
		USARTx->CR1 |= USART_CR1_UE;		// USART enable
	}

	void USART::sendChar (char ch) {
		USARTx->DR = ch;						// Send a character (auto flag reset)
		while (!(USARTx->SR & USART_SR_TXE));	// Wait until it is sent
	}

	char USART::getChar (void) {
		while (!(USARTx->SR & USART_SR_RXNE));	// Wait until data is received
		return USARTx->DR;							// Read data (auto flag reset)
	}

	void USART::setBaudRate(BAUDS baudrate){
		USARTx->CR1 &= ~USART_CR1_UE;		// USART disable
		this->baudRate_ = baudrate;
		uint16_t brr_val;
		switch (baudRate_)
		{
			case B2400:
				brr_val = 0x3A98;
				break;
			case B9600:
				brr_val = 0xEA6;
				break;
			case B19200:
				brr_val = 0x753;
				break;
			case B57600:
				brr_val = 0x271;
				break;
			case B115200:
				brr_val = 0x138;
				break;
			case B250000:
				brr_val = 0x9;
				break;
			default:
				exit(EXIT_FAILURE);
		}
		USARTx->BRR = brr_val;
		USARTx->CR1 |= USART_CR1_UE;		// USART enable

	}

} /* namespace COM */
	
