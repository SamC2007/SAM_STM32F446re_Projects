#include "headers/stm32fx.h"
#include "headers/print.h"
#include "headers/GPIO.h"
#include "headers/TIM2_TIM5.h"
#include "headers/RCC.h"


#include <stdint.h>

TIM2_5_TypeDef_INPUT_t volatile* const pTIM2 = TIM2_INPUT;

TIM2_5_TypeDef_OUTPUT_t volatile* const pTIM5 = TIM5_OUTPUT;

GPIOx_TypeDef_t volatile* const pGPIOB = GPIOB;

uint32_t volatile* const ISER0 = NVIC_ISER0; 
uint8_t volatile ready = 0;
uint32_t volatile time_rise = 0;
uint32_t volatile time_fall = 0;
uint32_t volatile time = 0;
uint32_t volatile rose = 0;
float volatile distance = 0.0f;
float const speed = 0.034f;

void init_project(void); 

int main(void){
	init_project();

	while(1){
		//output pin for 10 microseconds
		pGPIOA->ODR.ODR9 = ENABLE;
		for(uint16_t volatile i = 0; i < 160; ++i);
		pGPIOA->ODR.ODR9 = DISABLE;

		while(!(ready));
		print("Distance in Centimeter: ");
		printF(distance, 3);
		print("cm\r\n");
		ready = 0;

		for(uint32_t i = 0; i < 1000000; ++i);
	}

	return 0;
}

void init_project(void){
	//initialize RCC for TIM2 
	init_print();
	pRCC_APB1ENR->TIM2_EN = ENABLE;
	pRCC_APB1ENR->TIM5_EN = ENABLE;

	//initialie NVIC for TIM2
	*ISER0 |= NVIC_TIM2;

	//configure GPIOA 0 for Input capture
	pGPIOA->MODER.MODER0 = DISABLE;
	pGPIOA->MODER.MODER0 = ALTERNATE;
	pGPIOA->PUPDR.PUPDR0 = PULL_DOWN;
	pGPIOA->AFRL.AFRL0 = AF1;

	//configure GPIOA 1 for PWN capture
	pGPIOA->MODER.MODER1 = DISABLE;
	pGPIOA->MODER.MODER1 = ALTERNATE;
	pGPIOA->PUPDR.PUPDR1 = PULL_DOWN;
	pGPIOA->AFRL.AFRL1 = AF2;

	// Configure GPIOA 9 for Output (sensor)
	pGPIOA->MODER.MODER9 = DISABLE;
	pGPIOA->MODER.MODER9 = OUTPUT;

	// Configure GPIOB
	pGPIOB->MODER.MODER9 = DISABLE;
	pGPIOB->MODER.MODER9 = OUTPUT;

	//CONFIGURE TIM5
	pTIM5->ARR = 0;
	pTIM5->ARR = 999;
	pTIM5->PSC = 31;
	pTIM5->CCER.CC2E = ENABLE;
	pTIM5->CCMR1.OC2M = 6;
	pTIM5->CCMR1.OC2PE = ENABLE;
	pTIM5->CCR2 = 499;
	pTIM5->EGR.UG = ENABLE;
	pTIM5->CR1.CEN = ENABLE;


	//CONFIGURE TIM2 
	pTIM2->CCMR1.CC1S = 1;
	pTIM2->ARR = 0;
	pTIM2->ARR = 65535;
	pTIM2->PSC = 15;
	pTIM2->CCER.CC1E = ENABLE;
	pTIM2->DIER.CC1IE = ENABLE;
	pTIM2->EGR.UG = ENABLE;
	pTIM2->CR1.CEN = ENABLE;

}

void TIM2_Handler(void){
	if(pTIM2->SR.CC1IF){
		if(pTIM2->DIER.CC1IE){
			pTIM2->SR.CC1IF = 0;
		}
	}
	if(rose == 0){
		time_rise = pTIM2->CCR1;
		pTIM2->CCER.CC1P = 1;
		rose = 1;
	}else{
		time_fall = pTIM2->CCR1;
		pTIM2->CCER.CC1P = 0;
		
		if(time_rise <= time_fall){
			time = time_fall - time_rise;
		}else {
			time = ((pTIM2->ARR - time_rise) + time_fall);
		}
		distance = ((time * speed) / 2.0f);
		if(distance <= 30.0f){
			pTIM5->CCR2 = (30 - (uint32_t)distance ) * 30;
		}else {
			pTIM5->CCR2 = 0;
		}
		rose = 0;
	}
	ready = 1;
}

