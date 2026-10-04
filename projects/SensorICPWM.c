#include "headers/stm32fx.h"
#include "headers/GPIO.h"
#include "headers/TIMERS.h"
#include "headers/RCC.h"


#include <stdint.h>

GP_TIMx_Handler_t pTIM2;
GP_TIMx_Handler_t pTIM5;
GPIOx_Handler_t pGPIOA;

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
    print("Initialized\r\n");

	while(1){
		//output pin for 10 microseconds
        OUTPUT_Toggle(&pGPIOA, 9, ENABLE);
		for(uint16_t volatile i = 0; i < 160; ++i);
        OUTPUT_Toggle(&pGPIOA, 9, DISABLE);

		while(!(ready));
		print("Distance in Centimeter: ");
		printF(distance, 3);
		print("cm\r\n");
		ready = 0;

        delay(10);
	}

	return 0;
}

void init_project(void){
	//initialize RCC for TIM2 
	init_functions();

	//initialie NVIC for TIM2
    GP_TIMInterruptConfig(NVIC_TIM2, ENABLE);
	//configure GPIOA 0 for Input capture
    pGPIOA.GPIOx = GPIOA;
	pGPIOA.GPIOx_Config.MODER = ALTERNATE;
	pGPIOA.GPIOx_Config.PUPDR = PULL_DOWN;
	pGPIOA.GPIOx_Config.AFR = AF1;
	pGPIOA.GPIOx_Config.PIN = 0;
    GPIO_Init(&pGPIOA);

	//configure GPIOA 1 for PWN capture
    pGPIOA.GPIOx_Config.AFR = AF2;
    pGPIOA.GPIOx_Config.PIN = 1;
    GPIO_Init(&pGPIOA);

	// Configure GPIOA 9 for Output (sensor)
	pGPIOA.GPIOx_Config.MODER = OUTPUT;
	pGPIOA.GPIOx_Config.PUPDR = PUSH_PULL;
    pGPIOA.GPIOx_Config.PIN = 9;
    GPIO_Init(&pGPIOA);
/*
	pGPIOB->MODER.MODER9 = DISABLE;
	pGPIOB->MODER.MODER9 = OUTPUT;
*/
	//CONFIGURE TIM5
    pTIM5.TIMx = TIM5;
	pTIM5.TIMx_Config.ARR = 999;
    pTIM5.TIMx_Config.PSC = 31;
	pTIM5.TIMx_Config.CHANNEL_MODE = OUTPUT_COMPARE;
    pTIM5.TIMx_Config.CHANNEL = TIM_CHANNEL_2;
    pTIM5.TIMx_Config.TI_SELECTION = TIM_OUTPUT;
    pTIM5.TIMx_Config.OUTPUT_MODE = PWM_MODE1;
    GP_TIM_Init(&pTIM5);
    UG_Control(TIM5, ENABLE);

	//CONFIGURE TIM2 channel 1
    pTIM2.TIMx = TIM2;
	pTIM2.TIMx_Config.ARR = 65535 - 1;
    pTIM2.TIMx_Config.PSC = 15;
    pTIM2.TIMx_Config.CHANNEL = TIM_CHANNEL_1;
    pTIM2.TIMx_Config.CHANNEL_MODE = INPUT_CAPTURE;
    pTIM2.TIMx_Config.TI_SELECTION = TIM_INPUT1;
    GP_TIM_Init(&pTIM2);
    InterruptBitConfig(TIM2, TIM_DIER_CC1IE, ENABLE);
    UG_Control(TIM2, ENABLE);

    GP_TIM_PeriControl(TIM5, ENABLE);
    GP_TIM_PeriControl(TIM2, ENABLE);

}

void TIM2_Handler(void){
   
	if(rose == 0){
		time_rise = GetTIM_CCR1Value(TIM2);
        TIM_CCERConfig(TIM2, TIM_CCER_CC1P, ENABLE);
		rose = 1;
	}else{
		time_fall = GetTIM_CCR1Value(TIM2);
        TIM_CCERConfig(TIM2, TIM_CCER_CC1P, DISABLE);
		
		if(time_rise <= time_fall){
			time = time_fall - time_rise;
		}else {
			time = ((GetTIM_ARRValue(TIM2) - time_rise) + time_fall);
		}
		distance = ((time * speed) / 2.0f);
        uint32_t value_ccr = 0;
		if(distance <= 30.0f){
            value_ccr = (30 - (uint32_t)distance ) * 30;
            SetTIM_CCR2Value(TIM5, value_ccr);
		}else {
			SetTIM_CCR2Value(TIM5, value_ccr);
		}
		rose = 0;
	}
	ready = 1; 
	if(CheckStatusFlag(TIM2, TIM_SR_CC1IF)){
        ResetStatusFlag(TIM2, TIM_SR_CC1IF);
	}
}

