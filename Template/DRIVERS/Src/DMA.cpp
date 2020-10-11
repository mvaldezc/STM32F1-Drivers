
#include "DMA.h"
#include "delay.h"
namespace MEMORY
{
    void DMA::start(uint32_t& box, DMA_PERIPHERAL peripheral, uint8_t periph_number){
        RCC->AHBENR |= RCC_AHBENR_DMA1EN;			    //Enable DMA1 clock
        
        switch (peripheral)
        {
            case DMA_PERIPHERAL::ADC:
            {
                ADC_TypeDef* ADCx = nullptr;
                //static_assert(periph_number != 1 && periph_number != 2, "ERROR: Choose a valid peripheral number");
                if (periph_number == 1)  ADCx = ADC1;
                else if (periph_number == 2)  ADCx = ADC2;

                delay_us(20);
                DMA1_Channel1->CCR = 0x000035A0;			    //Very High priority, 32 bits registers, circular mode, memory increment mode,  from peripheral to memory, no interruptions
                DMA1_Channel1->CPAR = (uint32_t) (&(ADCx->DR));	//Peripheral address
                DMA1_Channel1->CMAR = (uint32_t) box;		    //Memory Address
                DMA1_Channel1->CNDTR = (((ADCx->SQR1 >> 20) & 0xF) + 1);  // Number of data to transfer
                DMA1_Channel1->CCR |= DMA_CCR1_EN;			    //Channel Enable
                break;
            }
            case DMA_PERIPHERAL::I2C:
            {
                I2C_TypeDef* I2Cx = nullptr;
                if (periph_number == 1) I2Cx = I2C1;
                else if (periph_number == 1) I2Cx = I2C2;
                //else static_assert(0, "ERROR: Choose a valid peripheral number");
                DMA1_Channel5->CCR;
                DMA1_Channel5->CPAR = (uint32_t) (&(I2Cx->DR));	//Peripheral address
                DMA1_Channel5->CMAR = (uint32_t) box;           //Memory Address
                DMA1_Channel5->CNDTR = 1;
                DMA1_Channel5->CCR |= 0x080;
                break;
            }
        }
    }
} // namespace MEMORY
