#pragma once
#include "stm32f10x.h"
#include <cstdlib>      // cambiar cuando existan excepciones
#include <cstdint>


constexpr auto BB_OFFSET = 0x2000000;   // auto detects variable type as var
#define BITBAND_ADDR(addr,bit) ((addr & 0xF0000000) + BB_OFFSET + ((addr & 0xFFFFF << 5) + (bit << 2)))

namespace DIGITAL
{
    enum class STATE { OFF, ON };
    enum class MODE
    {
        GENER_PURP_PUSH_PULL = 0x3,
        GENER_PURP_OPEN_DRAIN = 0x7,
        ALTER_FUNC_PUSH_PULL = 0xB,
        ALTER_FUNC_OPEN_DRAIN = 0xF,
        ANALOG_INPUT = 0x0,
        FLOATING_INPUT = 0X4,
        PULL_DOWN_INPUT = 0x8,
        PULL_UP_INPUT = 0x9
    };
    class GPIO
    {
        // Note: Inline functions are defined in the header because,
        // in order to inline a function call, the compiler must be
        // able to see the function body before linking.

        public:

        /**
        * @brief Enable IO clock in RCC
        * @param GPIOx IO port to enable
        */
        inline static void init(GPIO_TypeDef* GPIOx)
        {
            if (GPIOx == GPIOA)
                RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            else if (GPIOx == GPIOB)
                RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            else if (GPIOx == GPIOC)
                RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
            else
                exit(EXIT_FAILURE);
        }

        /**
        * @brief Select Input/Output pin mode
        * @param GPIOx IO port
        * @param pin Port pin
        * @param mod GPIO configuration
        */
        inline static void mode(GPIO_TypeDef* GPIOx, uint8_t pin, MODE mod)
        {
            if (pin >= 0 && pin < 16)
            {
                // Select between CRL and CRH
                volatile uint32_t* MODER = nullptr;

                pin < 8
                    ? (MODER = &(GPIOx->CRL))
                    : (MODER = &(GPIOx->CRH));

                // Clean config register
                *MODER &= (0xF << (4 * pin));

                // Write corresponding input/output mode
                if (mod != MODE::PULL_UP_INPUT)
                    *MODER |= (static_cast<uint32_t> (mod)) << (4 * pin);
                else
                {
                    *MODER |= (static_cast<uint32_t> (MODE::PULL_DOWN_INPUT));
                    GPIOx->ODR |= (1 << pin);
                }
            }
            else
            {
                exit(EXIT_FAILURE);
            }
        }

        /**
        * @brief Read a GPIO pin
        * @param GPIOx IO port
        * @param pin Pin to read
        * @return Isolated pin value (0/1)
        */
        inline static uint8_t read(GPIO_TypeDef* GPIOx, const uint8_t pin)
        {
            return ((GPIOx->IDR >> pin) & 0x1);
        }

        /**
        * @brief Write a GPIO pin
        * @param GPIOx IO port
        * @param pin Pin to write
        */
        inline static void write(GPIO_TypeDef* GPIOx, const uint8_t pin, STATE pinState)        
        {
            switch (pinState)
            {
                case STATE::ON:
                    // dereference bit band pointer
                    // reinterpret_cast uses the same value, just interprets it as another variable
                    // without doing math calculation. ex. converting int to double representation
                    *(reinterpret_cast<volatile uint32_t*>(BITBAND_ADDR(GPIOx->ODR, pin))) = 1;
                    break;
                case STATE::OFF:
                    *(reinterpret_cast<volatile uint32_t*>(BITBAND_ADDR(GPIOx->ODR, pin))) = 0;
                    break;
                default:
                    exit(EXIT_FAILURE);
            }
        }

        /**
        * @brief Toggle a GPIO pin
        * @param GPIOx IO port
        * @param pin Pin to toggle
        */
        inline static void toggle(GPIO_TypeDef* GPIOx, uint8_t pin)
        {
            GPIOx->ODR ^= (1 << pin);
        }
    };


}
