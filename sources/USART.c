#include "../headers/stm32fx.h"
#include "../headers/USART.h"
#include "../headers/RCC.h"
#include <stdint.h>

void USART_PeriClk(USARTx_t* USART, uint8_t cmd){
    if(cmd == ENABLE){
        if(USART == USART1){
            RCC->APB2ENR |= (1 << USART1_EN);
        }else if(USART == USART2){
            RCC->APB1ENR |= (1 << USART2_EN);
        }else if(USART == USART3){
            RCC->APB1ENR |= (1 << USART3_EN);
        }else if(USART == UART4){
            RCC->APB1ENR |= (1 << UART4_EN);
        }else if(USART == UART5){
            RCC->APB1ENR |= (1 << UART5_EN);
        }else{
            RCC->APB2ENR |= (1 << USART6_EN);
        }
    }else{
        if(USART == USART1){
            RCC->APB2ENR &= ~(1 << USART1_EN);
        }else if(USART == USART2){
            RCC->APB1ENR &= ~(1 << USART2_EN);
        }else if(USART == USART3){
            RCC->APB1ENR &= ~(1 << USART3_EN);
        }else if(USART == UART4){
            RCC->APB1ENR &= ~(1 << UART4_EN);
        }else if(USART == UART5){
            RCC->APB1ENR &= ~(1 << UART5_EN);
        }else{
            RCC->APB2ENR &= ~(1 << USART6_EN);
        }
    }
}

void USART_Init(USARTx_Handler_t* USART){
    USART_PeriClk(USART->USARTx, ENABLE);
    //configure BAUD RATE
    uint32_t clock;
    if(USART->USARTx == USART1 || USART->USARTx == USART6){
        clock = RCC_GetPCKVal2();
    }else{
        clock = RCC_GetPCKVal1();
    }

    uint32_t div = 0;
    if(USART->USARTx_Config.SAMPLING == OVER8){
        div = clock / (8 * USART->USARTx_Config.BAUD_RATE) * 100;
    }else{
        div = clock / (16 * USART->USARTx_Config.BAUD_RATE) * 100;
    }

    uint32_t Mantissa = div / 100;
    USART->USARTx->BRR |= (Mantissa << USART_DIV_MANTISSA);

    uint8_t Fraction = (Mantissa * 100) - div;

    if(USART->USARTx_Config.SAMPLING == OVER8){
        Fraction = (((Fraction * 8) + 50) / 100);
    }else{
        Fraction = (((Fraction * 16) + 50) / 100);
    }

    USART->USARTx->BRR |= (Fraction << USART_DIV_FRACTION);

    if(USART->USARTx_Config.USART_MODE == TRANSMIT_ONLY){
        USART->USARTx->CR1 |= (USART_CR1_TE << USART_CR1_TE);
    }else if(USART->USARTx_Config.USART_MODE == RECEIVE_ONLY){

        USART->USARTx->CR1 |= (USART_CR1_RE << USART_CR1_RE);
    }else{
        USART->USARTx->CR1 |= (USART_CR1_TE << USART_CR1_TE);
        USART->USARTx->CR1 |= (USART_CR1_RE << USART_CR1_RE);
    }
    USART->USARTx->CR1 |= (USART->USARTx_Config.SAMPLING << USART_CR1_OVR8);
}

void USART_TransmitByte(USARTx_t* USARTx, uint8_t byte){
    while(!((USARTx->SR >> USART_SR_TXE) & 0x1));
    USARTx->DR = byte;
    while(!((USARTx->SR >> USART_SR_TC) & 0x1));
    uint8_t dummy = USARTx->SR;
    (void)dummy;
}
void USART_Transmit(USARTx_t* USARTx, uint8_t* string, uint8_t Len){
    while(Len > 0){
        while(!((USARTx->SR >> USART_SR_TXE) & 0x1));
        USARTx->DR = *string;
        string++;
        --Len;
    }
    while(!((USARTx->SR >> USART_SR_TC) & 0x1));
    uint8_t dummy = USARTx->SR;
    (void)dummy;
}

void USART_Control(USARTx_t* USARTx, uint8_t cmd){
    if(cmd == ENABLE){
        USARTx->CR1 |= (1 << USART_CR1_UE);
    }else{
        USARTx->CR1 &= ~(1 << USART_CR1_UE);
    }
}
