#include "../headers/stm32fx.h"
#include "../headers/RCC.h"
#include "../headers/TIMERS.h"
#include <stdint.h>


void GPTIM_PeriCLK(GP_TIMx_t* TIM, uint8_t cmd){

    if(cmd == ENABLE){
        if(TIM == TIM2){
            RCC->APB1ENR |= (1 << TIM2_EN);
        }else if(TIM == TIM3){
            RCC->APB1ENR |= (1 << TIM3_EN);
        }else if(TIM == TIM4){
            RCC->APB1ENR |= (1 << TIM4_EN);
        }else if(TIM == TIM5){
            RCC->APB1ENR |= (1 << TIM5_EN);
        }else if(TIM == TIM9){
            RCC->APB2ENR |= (1 << TIM9_EN);
        }else if(TIM == TIM10){
            RCC->APB2ENR |= (1 << TIM10_EN);
        }else if(TIM == TIM11){
            RCC->APB2ENR |= (1 << TIM11_EN);
        }else if(TIM == TIM12){
            RCC->APB1ENR |= (1 << TIM12_EN);
        }else if(TIM == TIM13){
            RCC->APB1ENR |= (1 << TIM13_EN);
        }else{
            RCC->APB1ENR |= (1 << TIM14_EN);
        }
    }else {

    }
}

void GP_TIM_Init(GP_TIMx_Handler_t* TIM){
    GPTIM_PeriCLK(TIM->TIMx, ENABLE);

    TIM->TIMx->ARR = TIM->TIMx_Config.ARR;
    TIM->TIMx->PSC = TIM->TIMx_Config.PSC;

    // configre CC1S - CC4S
    if(TIM->TIMx_Config.CHANNEL < TIM_CHANNEL_3){
            TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.TI_SELECTION << (TIM->TIMx_Config.CHANNEL * 8));
    }else{
         TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.TI_SELECTION << ((TIM->TIMx_Config.CHANNEL - 2) * 8));
    }

    //configure capture compare enable register
    TIM->TIMx->CCER |= (1 << (TIM->TIMx_Config.CHANNEL * 2));

    if(TIM->TIMx_Config.CHANNEL_MODE == INPUT_CAPTURE){
        //TODO

    }else if(TIM->TIMx_Config.CHANNEL_MODE == OPM_OUTPUT){
        //TODO 

    }else {
       // in OUTPUT MODE
       if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_1){
            TIM->TIMx->CCMR1 |= (1 << 3);
            TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.OUTPUT_MODE << 4);
       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_2){
            TIM->TIMx->CCMR1 |= (1 << 11);
            TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.OUTPUT_MODE << 12);
       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_3){
            TIM->TIMx->CCMR2 |= (1 << 3);
            TIM->TIMx->CCMR2 |= (TIM->TIMx_Config.OUTPUT_MODE << 4);
       }else{
            TIM->TIMx->CCMR2 |= (1 << 11);
            TIM->TIMx->CCMR2 |= (TIM->TIMx_Config.OUTPUT_MODE << 12);
       }
    }
}

void SetCCR(GP_TIMx_Handler_t* TIM, uint32_t v){
    if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_1){
        TIM->TIMx->CCR1 = v;
    }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_2){
        TIM->TIMx->CCR2 = v;
    }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_3){
        TIM->TIMx->CCR3 = v;
    }else{
        TIM->TIMx->CCR4 = v;
    }
}
void UG_Control(GP_TIMx_t* TIM, uint8_t cmd){
    if(cmd == ENABLE){
        TIM->EGR |= (1 << 0);
    }else{
        TIM->EGR &= ~(1 << 0);
    }
}

void CNT_Control(GP_TIMx_t* TIM, uint8_t cmd){
    if(cmd == ENABLE){
        TIM->CR1 |= (1 << 0);
    }else {
        TIM->CR1 &= ~(1 << 0);
    }
}
