#pragma once

#include "stm32f10x.h"
#include <cstdint>

namespace MEMORY
{
    enum class DMA_PERIPHERAL { ADC, I2C };
    class DMA
    {
        private:
            
        public:
        static void start(uint32_t& box, DMA_PERIPHERAL peripheral, uint8_t periph_number);
    };

    
} // namespace MEMORY
