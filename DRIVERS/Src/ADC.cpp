/***********************************************************************
 * @file	:	ADC.c
 * @brief 	:	ADC library
 * 				GPIOB0 / GPIOB1 as analog input using ADC1 channels 8,9
 * 				Data moved with DMA Channel1 to box and box+1 addresses
 * 				Triggered by TIM2 Channel2 Event (when CNT = CCR2)
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "ADC.h"

namespace ANALOG{
	/*----------- Constructors -----------*/

	// Start ADC in AUTO mode as default
	ADC::ADC(const std::vector<char> channels) : ADC(MODE::AUTO,channels){	}

	// Initialize ADC mode
	ADC::ADC(MODE mod, const std::vector<char> channels) : mode_(mod){		
		this->channels_ = channels;
		setup();
	}

	/*-------------- Methods -------------*/

	void ADC::setup(){
		// GPIOB Configuration
		RCC->APB2ENR |=	(1 << 3);		// Enable GPIOB Clock
		GPIOB->CRL &= ~(0xFF << 0);		// Port B0 and	 B1 as analog input

		// ADC Configuration for CORE_freq = 4.5 MHz
		RCC->CFGR |= (0x3 << 14);		// ADC clock = 4.5 MHz. 36Mhz / 8 = 4.5 MHz
		RCC->APB2ENR |= (1 << 9);		// Enable ADC1 Clock
		ADC1->SMPR2 |= (0x3F << 24);	// Set a sample time of 239.5+12.5 cycles =  56 us
										// The external circuit connected to the ADC affects the measurement
										// But if you read really slow, it affects less and the max external
										// resistance becomes negligible


		// Select operation mode and set channels
		if(channels_.size() > 6) exit(EXIT_FAILURE);			// Constraint to 6 channels
		switch (mode_)		
		{
			// Manual triggered
			case MODE::TRIG:
				ADC1->SQR3 |= channels_[0];		// Scan the channel 8 first
				ADC1->CR2 |= ~(1 << 11);		// ALIGN. Align data to the right
				ADC1->CR2 |= ~(1 << 1);			// CONT. Single conversion mode
				break;

			// TIM2 triggered
			case MODE::AUTO:
				ADC1->CR1 |= 0x00100;				// Independent mode, scan mode
				ADC1->CR2 |= 0x00160100; 			// Regular conversion, external event enabled (Timer 2 event) , right aligned, single conversion, DMA enabled
				ADC1->SQR1 |= ((channels_.size()-1) << 20);	// Set sequence length
				for(char i = 0; i < 6; i++){		// Set conversion sequence (1-6)
					ADC1->SQR3 |= (channels_[i] << (5*i));		// Load channel order to the ADC list
				}
				ADC1->SQR2 = 0x0000;				// Disable sequence (7-12)

				break;
		}

		// ADC initialization
		ADC1->CR2 |= (1 << 0);			// ADON. Wake up the ADC
							
		delay_us(20);
		ADC1->CR2 |= (1 << 2);			// CAL. Start calibration
		while(ADC1->CR2 & (1 << 2));	// Wait until calibration is done

		/*CR2 REGISTER  bits:
			0	ADON:			Change from 0 to 1, wakes up the ADC from power down
								Change from 1 to 1, starts conversion
		
			1	CONT:		0 	Single conversion
							1 	Continuous conversion
		
			2	CAL:		1 	Start calibration
							0 	Pin reset by hardware when calibration finishes
		
			8	DMA:		0 	DMA disabled
							1 	DMA enabled (only for ADC1 & ADC3)
		
			11	ALIGN:		0 	Right alignment
							1	Left alignment
		
		[14:12] JEXTSEL:	111 Injected group activated by JSWSTART bit
								
		[19:17] EXTSEL:		Regular group activated by
							000	Timer 1 CC1 event
							001	Timer 1 CC2 event
							011 Timer 2 CC2 event
							111	SWSTART bit
							
			20	EXTTRIG		0 	Conversion on external event disabled
							1	Conversion on external event enabled
							
			22	SWSTART		0	Cleared by hardware when conversion starts
							1	Start Conversion
							
			23	TSVREFE		0	Internal temperature sensor disabled
							1	Internal temperature sensor enabled
		
		*/

	}

	int ADC::measure(){
		ADC1->CR2 |= (1 << 0);			// ADON. Second adon to start conversion
		while(!(ADC1->SR & (1 << 1)));	// EOC. Wait until end of conversion
		return (ADC1->DR & 0xFFFF);		// Reading the DR clears EOC in SR
	}

	void ADC::calibrate(){
		ADC1->CR2 |= (1 << 2);			// CAL. Start calibration
		while(ADC1->CR2 & (1 << 2));	// Wait until calibration is done
	}
}



void DMA::start(uint16_t *box){
	RCC->AHBENR |=0x01;							//Enable DMA1 clock
	for(volatile int i=0; i<1000; i++);			// Crazy delay
	DMA1_Channel1->CCR = 0x000035A0;			//Very High priority, 32 bits registers, circular mode, memory increment mode,  from peripheral to memory, no interruptions
	DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR));	//Peripheral address
	DMA1_Channel1->CMAR = (uint32_t) box;		//Memory Address
	DMA1_Channel1->CNDTR = (((ADC1->SQR1 >> 20) & 0xF) + 1);  // Number of data to transfer
	DMA1_Channel1->CCR |= 0x01;					//Channel Enable
}
