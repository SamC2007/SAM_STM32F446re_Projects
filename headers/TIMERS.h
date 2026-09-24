#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

/**********************************************************


TIMER 2 and TIMER 5 Definitions


***********************************************************/

#define TIM2 ((GP_TIMx_t*)(0x40000000))
#define TIM3 ((GP_TIMx_t*)(0x40000400 ))
#define TIM4 ((GP_TIMx_t*)(0x40000800 ))
#define TIM5 ((GP_TIMx_t*)(0x40000C00))

#define TIM9 ((GP_TIMx_t*)(0x40014000))
#define TIM10 ((GP_TIMx_t*)(0x40014400))
#define TIM11 ((GP_TIMx_t*)(0x40014800))

#define TIM12 ((GP_TIMx_t*)(0x40001800))
#define TIM13 ((GP_TIMx_t*)(0x40001C00))
#define TIM14 ((GP_TIMx_t*)(0x40002000))


#define INPUT_CAPTURE 0
#define OUTPUT_COMPARE 1
#define OPM_OUTPUT 2

#define TIM_OUTPUT 0
#define TIM_INPUT1 1
#define TIM_INPUT2 2

#define TIM_INPUT3 1
#define TIM_INPUT4 2

#define PWM_OFF 0
#define PWM_MODE1 6
#define PWM_MODE2 7

#define TIM_CHANNEL_1 0
#define TIM_CHANNEL_2 1
#define TIM_CHANNEL_3 2
#define TIM_CHANNEL_4 3

typedef struct{
    uint32_t ARR;
    uint32_t PSC;
    uint8_t CHANNEL_MODE;
    uint8_t CHANNEL;
    uint8_t TI_SELECTION;
    uint8_t OUTPUT_MODE;
}GP_TIMx_Config_t;

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t R;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t reserve;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t reserve2;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t OR;
}GP_TIMx_t;

typedef struct{
    GP_TIMx_Config_t TIMx_Config;
    GP_TIMx_t* TIMx;
}GP_TIMx_Handler_t;

void GPTIM_PeriCLK(GP_TIMx_t* TIM, uint8_t cmd);
void GP_TIM_Init(GP_TIMx_Handler_t* TIM);
void CNT_Control(GP_TIMx_t* TIM, uint8_t cmd);
void UG_Control(GP_TIMx_t* TIM, uint8_t cmd);
void SetCCR(GP_TIMx_Handler_t* TIM, uint32_t v);

/**********************************************************


TIMER 6 and TIMER 7 Definitions


***********************************************************/
#define TIM6 ((TIM6_7_TypeDef_t*)(0x40001000))
#define TIM7 ((TIM6_7_TypeDef_t*)(0x40001400))
typedef struct {
	uint32_t CEN: 1;
	uint32_t UDIS: 1;
	uint32_t URS: 1;
	uint32_t OPM: 1;
	uint32_t RES1: 3;
	uint32_t ARPE: 1;
	uint32_t RES: 24;
}TIM6_7_CR1_t;

typedef struct {
	uint32_t RES1: 4;
	uint32_t MMS: 3;
	uint32_t RES: 25;
}TIM6_7_CR2_t;


typedef struct {
	uint32_t UIE: 1;
	uint32_t RES1: 7;
	uint32_t UDE: 1;
	uint32_t RES: 23;
}TIM6_7_DIER_t;

typedef struct {
	uint32_t UIF: 1;
	uint32_t RES: 31;
}TIM6_7_SR_t;


typedef struct {
	uint32_t UG: 1;
	uint32_t RES: 31;
}TIM6_7_EGR_t;

typedef struct{
	TIM6_7_CR1_t CR1;
	TIM6_7_CR2_t CR2;
	uint32_t RESERVE1;
	TIM6_7_DIER_t DIER;
	TIM6_7_SR_t SR;
	TIM6_7_EGR_t EGR;
	uint32_t RESERVE2;
	uint32_t RESERVE3;
	uint32_t RESERVE4;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
}TIM6_7_TypeDef_t;

#endif
