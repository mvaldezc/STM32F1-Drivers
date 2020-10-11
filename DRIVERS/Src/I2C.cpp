/***********************************************************************
 * @file	:	I2C.cpp
 * @brief 	:	I2C library
 * 				Library to use i2c communication based on 
 * 				the generic communication class
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#include "I2C.h"
#include "GPIO.h"

namespace COM
{
    using namespace DIGITAL;

    #pragma region Constructor

    I2C::I2C(I2C_TypeDef* I2Cx_param, SCL_MODE speed) : I2C(I2Cx_param, speed, ACK::DISABLE){}
    
    I2C::I2C(I2C_TypeDef * I2Cx_param, SCL_MODE speed, ACK ackControl)
        : speed_(static_cast<uint32_t> (speed)), ackControl_(static_cast<uint8_t> (ackControl))
    {
        // GPIOB configuration
        GPIO::init(GPIOB);

        this->I2Cx = I2Cx_param;

        if (I2Cx == I2C1)
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
            GPIO::mode(GPIOB, 6, MODE::ALTER_FUNC_OPEN_DRAIN);
            GPIO::mode(GPIOB, 7, MODE::ALTER_FUNC_OPEN_DRAIN);
        }
        else if (I2Cx == I2C2)
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
            GPIO::mode(GPIOB, 10, MODE::ALTER_FUNC_OPEN_DRAIN);
            GPIO::mode(GPIOB, 11, MODE::ALTER_FUNC_OPEN_DRAIN);
        }

        I2Cx->CR2 |= I2C_FREQ;                  // FREQ. Set peripheral clock frequency to APB1 speed
        I2Cx->CCR |= (speed_ != 100000) 
                    ? I2C_CCR_FS : 0x0;         // F/S. Fast mode enabled
        I2Cx->CCR |= I2C_FREQ / (2 * speed_);   // CCR. Set clock control register (prescaler)
        I2Cx->TRISE |= I2C_FREQ * SCL_RISE_TIME + 1;    //TRISE. Maximum rise time
        I2Cx->CR1 |= ackControl_ ? I2C_CR1_ACK : 0;     // ACK. Acknowledge enable
        I2Cx->CR1 &= ~I2C_CR1_NOSTRETCH;        // NOSTRETCH.Enable slave clock stretching
        I2Cx->OAR1 &= ~I2C_OAR1_ADDMODE;        // ADDMODE. 7-bit addressing mode
        I2Cx->CR1 |= I2C_CR1_PE;                // PE. Peripheral enable
    }

    #pragma endregion 


    #pragma region Methods
    
    void I2C::masterSend(const char ch, const uint8_t device_addr)
    {
        I2Cx->CR1 |= I2C_CR1_START;             // START. Generate the start condition
        while (!(I2Cx->SR1 & I2C_SR1_SB));      // Check that the start bit was sent (cleared when address sent)

        I2Cx->DR = device_addr;                 // Send device address
        while (!(I2Cx->SR1 & I2C_SR1_ADDR));    // Wait for address to be sent and ack received from slave
        volatile auto temp = I2Cx->SR2;         // Read SR2 to clear SR1_ADDR flag
        while (!(I2Cx->SR1 & I2C_SR1_TXE));    // Wait for empty data register
        
        I2Cx->DR = ch;                          // Send data
        while (!(I2Cx->SR1 & I2C_SR1_TXE));     // Wait for data to be sent

        I2Cx->CR1 |= I2C_CR1_STOP;              // Send stop condition

    }

    
    #pragma endregion 



} /* namespace COM */
