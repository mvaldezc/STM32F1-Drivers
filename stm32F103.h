/********************************************************
 * @file stm32f103.h
 * @brief Standard peripheral library
 *
 * @authors:
 * 		Derrant
 * 		Morales
 * 		Valdez
 *
 *******************************************************/


#ifndef STM32F103_H_
#define STM32F103_H_

#include <stdint.h>

/************************************************
  	          REGISTER DEFINITIONS
 ************************************************/

#define __IO volatile

/************ Peripherals **************/

#define RCC_BASE 			((uint32_t) 0x40021000)
#define GPIOC_BASE			((uint32_t) 0x40011000)
#define GPIOB_BASE			((uint32_t) 0x40010C00)
#define GPIOA_BASE			((uint32_t) 0x40010800)
#define TIM3_BASE			((uint32_t) 0x40000400)
#define TIM4_BASE			((uint32_t) 0x40000800)

typedef struct{
	__IO uint32_t CRL;
	__IO uint32_t CRH;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
	__IO uint32_t LCKR;
} GPIO_t;

typedef struct{
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t APB1RSTR;
	__IO uint32_t AHBENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t APB1ENR;
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	__IO uint32_t AHBRSTR;
	__IO uint32_t CFGR2;
} RCC_t;

typedef struct{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t SMCR;
	__IO uint32_t DIER;
	__IO uint32_t SR;
	__IO uint32_t EGR;
	__IO uint32_t CCMR1;
	__IO uint32_t CCMR2;
	__IO uint32_t CCER;
	__IO uint32_t CNT;
	__IO uint32_t PSC;
	__IO uint32_t ARR;
	__IO uint32_t RCR;
	__IO uint32_t CCR1;
	__IO uint32_t CCR2;
	__IO uint32_t CCR3;
	__IO uint32_t CCR4;
	__IO uint32_t BDTR;
	__IO uint32_t DCR;
	__IO uint32_t DMAR;
} TIM_t;

#define TIM3				((TIM_t* )	TIM3_BASE)
#define TIM4				((TIM_t* )	TIM4_BASE)
#define GPIOA 				((GPIO_t*)	GPIOA_BASE)
#define GPIOB 				((GPIO_t*)	GPIOB_BASE)
#define GPIOC 				((GPIO_t*)	GPIOC_BASE)
#define RCC 				((RCC_t*)	RCC_BASE)


#endif /* STM32F103_H_ */

