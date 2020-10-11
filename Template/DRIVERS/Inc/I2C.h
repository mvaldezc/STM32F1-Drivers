/***********************************************************************
 * @file	:	I2C.h
 * @brief 	:	I2C library
 * 				Library to use i2c communication based on 
 * 				the generic communication class
 * @author	:	Marco Valdez
 *
 ***********************************************************************/

#pragma once
#include "Communications.h"
#include "stm32f10x.h"

#define     I2C_FREQ        APB1_FREQ
#define     SCL_RISE_TIME   250/1000000000  //300 ns rounded to 250 for integer calculation
 // do not write this define between parenthesis

enum class SCL_MODE : uint32_t { SLOW = 100000, FAST = 400000 };
enum class ACK : uint8_t { ENABLE = 1, DISABLE = 0};
enum class I2C_DUTY : uint8_t { TWO = 0, SIXTEENbyNINE =1};

namespace COM
{
    class I2C final // to avoid from being inherited
    {
        protected:

            void masterSend(const char ch, const uint8_t device_addr);

        public:
            I2C(I2C_TypeDef* I2Cx_param, SCL_MODE speed, ACK acknowledge);
            I2C(I2C_TypeDef* I2Cx_param, SCL_MODE speed);

        private:

            uint32_t speed_ = static_cast<uint32_t> (SCL_MODE::SLOW);
            
            uint8_t deviceAddress_;
            
            uint8_t ackControl_ = static_cast<uint8_t> (ACK::DISABLE);

            I2C_TypeDef* I2Cx;
    };

}