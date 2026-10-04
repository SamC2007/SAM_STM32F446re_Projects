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

    if(TIM->TIMx_Config.CHANNEL_MODE == INPUT_CAPTURE){
       if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_1){
           TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.TI_SELECTION << 0);
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC1E);
       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_2){
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC2E);
           if(TIM->TIMx_Config.TI_SELECTION == TIM_INPUT1){
                TIM->TIMx->CCMR1 |= (2 << 8);
           }else if(TIM->TIMx_Config.TI_SELECTION == TIM_INPUT2){
                TIM->TIMx->CCMR1 |= (1 << 8);
           }

       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_3){
           TIM->TIMx->CCMR2 |= (TIM->TIMx_Config.TI_SELECTION << 0);
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC3E);
       }else{
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC4E);
            if(TIM->TIMx_Config.TI_SELECTION == TIM_INPUT3){
                TIM->TIMx->CCMR1 |= (2 << 8);
           }else if(TIM->TIMx_Config.TI_SELECTION == TIM_INPUT4){
                TIM->TIMx->CCMR1 |= (1 << 8);
           }
       }

    }else if(TIM->TIMx_Config.CHANNEL_MODE == OPM_OUTPUT){
        //TODO 

    }else {
       // in OUTPUT MODE
       if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_1){
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC1E);
            TIM->TIMx->CCMR1 |= (1 << 3);
            TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.OUTPUT_MODE << 4);
       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_2){
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC2E);
            TIM->TIMx->CCMR1 |= (1 << 11);
            TIM->TIMx->CCMR1 |= (TIM->TIMx_Config.OUTPUT_MODE << 12);
       }else if(TIM->TIMx_Config.CHANNEL == TIM_CHANNEL_3){
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC3E);
            TIM->TIMx->CCMR2 |= (1 << 3);
            TIM->TIMx->CCMR2 |= (TIM->TIMx_Config.OUTPUT_MODE << 4);
       }else{
           TIM->TIMx->CCER |= (1 << TIM_CCER_CC4E);
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

void GP_TIM_PeriControl(GP_TIMx_t* TIM, uint8_t cmd){
    if(cmd == ENABLE){
        TIM->CR1 |= (1 << 0);
    }else{
        TIM->CR1 &= ~(1 << 0);
    }
}

void GP_TIMInterruptConfig(uint8_t NVIC_TIM_TAG, uint8_t cmd){
    if(cmd == ENABLE){
        if(NVIC_TIM_TAG < 32){
           *NVIC_ISER0 |= (1 << NVIC_TIM_TAG);
        }else if(NVIC_TIM_TAG < 64){
            *NVIC_ISER1 |= (1 << (NVIC_TIM_TAG % 32));
        }else{
            *NVIC_ISER2 |= (1 << (NVIC_TIM_TAG % 64));
        }
    }else{
        if(NVIC_TIM_TAG < 32){
           *NVIC_ISER0 &= ~(1 << NVIC_TIM_TAG);
        }else if(NVIC_TIM_TAG < 64){
            *NVIC_ISER1 &= ~(1 << (NVIC_TIM_TAG % 32));
        }else{
            *NVIC_ISER2 &= ~(1 << (NVIC_TIM_TAG % 64));
        }
    }
}

void InterruptBitConfig(GP_TIMx_t* TIM, uint8_t IT_BIT, uint8_t cmd){
    if(cmd == ENABLE){
        TIM->DIER |= (1 << IT_BIT);
    }else{
        TIM->DIER &= ~(1 << IT_BIT);
    }
}
void TIM_CCERConfig(GP_TIMx_t* TIM, uint8_t BIT, uint8_t cmd){
    if(cmd == ENABLE){
        TIM->CCER |= (1 << BIT);
    }else{
        TIM->CCER &= ~(1 << BIT);
    }
}

void ResetStatusFlag(GP_TIMx_t* TIM, uint8_t Flag){
   TIM->SR &= ~(1 << Flag); 
}

uint8_t CheckStatusFlag(GP_TIMx_t* TIM, uint8_t Flag){
    if((TIM->SR >> Flag) & 0x1){
        return 1;
    }else{
        return 0;
    }
}

uint32_t GetTIM_ARRValue(GP_TIMx_t* TIM){
    return TIM->ARR;
}

uint32_t GetTIM_CCR1Value(GP_TIMx_t* TIM){
     return TIM->CCR1;
}
uint32_t GetTIM_CCR2Value(GP_TIMx_t* TIM){
     return TIM->CCR2;
}
uint32_t GetTIM_CCR3Value(GP_TIMx_t* TIM){
     return TIM->CCR3;
}
uint32_t GetTIM_CCR4Value(GP_TIMx_t* TIM){
     return TIM->CCR4;
}

void SetTIM_CCR1Value(GP_TIMx_t* TIM, uint32_t v){
     TIM->CCR1 = v;
}
void SetTIM_CCR2Value(GP_TIMx_t* TIM, uint32_t v){
     TIM->CCR2 = v;
}
void SetTIM_CCR3Value(GP_TIMx_t* TIM, uint32_t v){
     TIM->CCR3 = v;
}
void  SetTIM_CCR4Value(GP_TIMx_t* TIM, uint32_t v){
     TIM->CCR4 = v;
}

