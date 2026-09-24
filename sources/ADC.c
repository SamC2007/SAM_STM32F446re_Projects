#include "../headers/stm32fx.h"
#include "../headers/RCC.h"
#include "../headers/ADC.h"

void ADC_PeriClkControl(ADCx_t* ADC, uint8_t cmd){
    if(cmd == ENABLE){
        if(ADC == ADC1){
            RCC->APB2ENR |= (1 << ADC1_EN);
        }else if(ADC == ADC2){
            RCC->APB2ENR |= (1 << ADC2_EN);
        }else{
            RCC->APB2ENR |= (1 << ADC3_EN);
        }
    }else{
        if(ADC == ADC1){
            RCC->APB2ENR &= ~(1 << ADC1_EN);
        }else if(ADC == ADC2){
            RCC->APB2ENR &= ~(1 << ADC2_EN);
        }else{
            RCC->APB2ENR &= ~(1 << ADC3_EN);
        }
    }
}

void ADC_Init(ADCx_Handler_t* ADC){
    ADC_PeriClkControl(ADC->ADCx, ENABLE);
    uint32_t tempreg = 0;
    tempreg |= (ADC->ADCx_Config.DISCEN << ADC_DISCEN);
    tempreg |= (ADC->ADCx_Config.JDISCEN << 12);
    tempreg |= (ADC->ADCx_Config.SCAN << ADC_SCAN);

    if(ADC->ADCx_Config.DISCEN_CHANNEL_CONV > 0){
        tempreg |= ((ADC->ADCx_Config.DISCEN_CHANNEL_CONV - 1)<< 13);
    }
    ADC->ADCx->CR1 = tempreg;

    tempreg = 0;
    tempreg |= (ADC->ADCx_Config.CONT << ADC_CONT);
    ADC->ADCx->CR2 = tempreg; 

    if(ADC->ADCx_Config.CONVERSION_LENGTH){
   
        ADC->ADCx->SQR1 |= ((ADC->ADCx_Config.CONVERSION_LENGTH-1) << L);
    }
    if(ADC->ADCx_Config.J_CONVERSION_LENGTH){
        ADC->ADCx->JSQR |= ((ADC->ADCx_Config.J_CONVERSION_LENGTH-1) << JL);
    }
}

void ADC_ADDChannel(ADCx_t* ADC, uint8_t CHANNEL, uint8_t CONVERSION, uint8_t SAMPLE_RATE){
    uint32_t tempreg;
    uint8_t temp;
    if(CONVERSION < INJECTED_CONVERSION_1){
        if(CONVERSION <= CONVERSION_6){
                tempreg = CHANNEL << (CONVERSION * 5);
                ADC->SQR3 |= tempreg;
        }else if(CHANNEL <= CONVERSION_12){
               temp = CONVERSION % 6;
               tempreg = CHANNEL << (temp * 5);
               ADC->SQR2 |= tempreg;
        }else{
            temp = CONVERSION % 12;
            tempreg = CHANNEL << (temp * 5);
            ADC->SQR1 |= tempreg;
        }
    }else{
        temp = CONVERSION % 17;
        tempreg = CHANNEL << (temp * 5);
        ADC->JSQR |= tempreg;

    }

    if(CHANNEL <= CHANNEL_9){
        ADC->SMPR2 |= (SAMPLE_RATE << (CHANNEL * 3));
    }else{
        ADC->SMPR1 |= (SAMPLE_RATE << ((CHANNEL % 10) * 3));
    }
}

void ADC_Control(ADCx_t* ADC, uint8_t cmd){
    if(cmd == ENABLE){
        ADC->CR2 |= (1 << 0);
    }else{
        ADC->CR2 &= ~(1 << 0);
    }
}


void ADC_StartAnalog(ADCx_t* ADC, uint8_t cmd){
    if(cmd == REGULAR_CHANNEL){
        ADC->CR2 |= (1 << ADC_SWSTART);
    }else if(cmd == INJECTED_CHANNEL){
        ADC->CR2 |= (1 << ADC_JSWSTART);
    }
}


void EOCS_Config(ADCx_t* ADC, uint8_t cmd){
    if(cmd == ENABLE){
        ADC->CR2 |= (1 << ADC_EOCS);
    }else{
        ADC->CR2 &= ~(1 << ADC_EOCS);
    }
}

void ADC_InternalTempConfig(ADCx_t* ADC, uint8_t SAMPLE_RATE, uint8_t cmd){
    if(cmd == ENABLE){
        ADC->SMPR1 |= (SAMPLE_RATE << 24);
        ADC_Control(ADC, ENABLE);
        COM_REG_ADC1->CCR &= ~(1 << 22);
        COM_REG_ADC1->CCR |= (1 << 23);
    }
}

float GetTempData(ADCx_t* ADC){
    ADC->CR2 |= (1 << 30);
    while(!(ADC->SR & (1 << ADC_EOC)));
    //get data 
    uint16_t data = ADC->DR;
    data = (data / 4095) * 1.7f;
    return (((data - V25) / AVG_SLOPE) + 25);
}

uint32_t ReadRegularAnalog(ADCx_t* ADC){
    while(!(ADC->SR & (1 << ADC_EOC)));
    return (uint32_t)ADC->DR;
}

uint32_t HandleInjectRead(ADCx_t* ADC){
    if((ADC->JSQR & (0x1F >> 0)) > 0){
        return (uint32_t)ADC->JDR1;
    }else if((ADC->JSQR & (0x1F >> 5)) > 0){
        return (uint32_t)ADC->JDR2;
    }else if((ADC->JSQR & (0x1F >> 10)) > 0){
        return (uint32_t)ADC->JDR3;
    }else if((ADC->JSQR & (0x1F >> 15)) > 0){
        return (uint32_t)ADC->JDR4;
    }else{
        return 0;
    }

}

uint32_t ReadInjectedAnalog(ADCx_t* ADC){
    while(!(ADC->SR & (1 << ADC_JEOC)));
    uint32_t data = HandleInjectRead(ADC);
    return data;
}

void ADC_StartAnalogIT(ADCx_Handler_t* ADC, uint8_t CHANNEL_TYPE, uint32_t* Buffer, uint8_t CHANNELS){
    if(CHANNEL_TYPE == REGULAR_CHANNEL){
        ADC->Rbuffer = Buffer;
        ADC->Rlen = CHANNELS;
        ADC->State = ADC_FREE;
        ADC->ADCx->CR1 |= (1 << ADC_EOCIE);
    }else{
        ADC->Ibuffer = Buffer;
        ADC->Ilen = CHANNELS;
        ADC->State = ADC_FREE;
        ADC->ADCx->CR1 |= (1 << ADC_JEOCIE);
    }
}

uint8_t ReadRegularAnalogIT(ADCx_Handler_t* ADC){
    if(ADC->State == ADC_FREE){
        ADC->State = ADC_WAITING;
        ADC->ADCx->CR2 |= (1 << ADC_SWSTART);
    }
    return ADC->State;
}
uint8_t ReadInjectedAnalogIT(ADCx_Handler_t* ADC){
    if(ADC->State == ADC_FREE){
        ADC->State = ADC_WAITING;
        ADC->ADCx->CR2 |= (1 << ADC_JSWSTART);
    }
    return ADC->State;
}
void ADC_IRQHandling(ADCx_Handler_t* ADC){
    uint8_t Event = ((ADC->ADCx->SR >> ADC_EOC) & 0x1);
    uint8_t Iflag = ((ADC->ADCx->CR1 >> ADC_EOCIE) & 0x1);

    if(Event && Iflag){
        if(ADC->Rlen > 0){
            *(ADC->Rbuffer) = ADC->ADCx->DR;
            ADC->Rbuffer++;
            ADC->Rlen--;
            if(ADC->Rlen == 0){
                ADC->ADCx->SR &= ~(1 << 1);
                ADC->ADCx->CR1 &= ~(1 << ADC_EOCIE);
                ADC->State = ADC_DATA_READY;
            }else{
                ADC->ADCx->CR2 |= (1 << ADC_SWSTART);
            }

        }
    }
    Event = ((ADC->ADCx->SR >> ADC_JEOC) & 0x1); 
    Iflag = ((ADC->ADCx->CR1 >> ADC_JEOCIE) & 0x1);

    if(Event && Iflag){
        if(ADC->Ilen > 0){
            *(ADC->Ibuffer) = HandleInjectRead(ADC->ADCx);
            ADC->Ibuffer++;
            ADC->Ilen--;
            ADC->ADCx->CR2 |= (1 << ADC_JSWSTART);
        }else{
            ADC->ADCx->SR &= ~(1 << 2);
            ADC->ADCx->CR1 &= ~(1 << ADC_JEOCIE);
            ADC->State = ADC_DATA_READY;
        }
    }
}

void ADC_DMAConfig(ADCx_t* ADC, uint8_t cmd){
    if(cmd == ENABLE){
        ADC->CR2 |= (1 << 8);
        ADC->CR2 |= (1 << 9);
    }else{
        ADC->CR2 &= ~(1 << 8);
        ADC->CR2 &= ~(1 << 9);
    }
}

void ADC_InterruptConfig(uint8_t cmd){
    if(cmd == ENABLE){
        *NVIC_ISER0 |= (1 << NVIC_ADC);
    }else{
        *NVIC_ISER0 &= ~(1 << NVIC_ADC);
    }
}

