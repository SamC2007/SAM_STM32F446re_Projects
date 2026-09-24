#ifndef USART_H
#define USART_H
#include <stdint.h>

#define USART1 ((USARTx_t*)(0x40011000))
#define USART2 ((USARTx_t*)(0x40004400))
#define USART3 ((USARTx_t*)(0x40004800))
#define UART4 ((USARTx_t*)(0x40004C00))
#define UART5 ((USARTx_t*)(0x40005000))
#define USART6 ((USARTx_t*)(0x40011400))

#define TRANSMIT_ONLY 0
#define RECEIVE_ONLY 1
#define TRANSMIT_RECEIVE 2

#define OVER16 0
#define OVER8 1

typedef struct {
    uint32_t BAUD_RATE;
    uint8_t USART_MODE;
    uint8_t SAMPLING;
}USARTx_Config_t;

typedef struct {
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
}USARTx_t;

typedef struct{
    USARTx_Config_t USARTx_Config;
    USARTx_t* USARTx;
}USARTx_Handler_t;

#define USART_CR1_RE 2
#define USART_CR1_TE 3
#define USART_CR1_OVR8 15
#define USART_CR1_UE 13

#define USART_SR_TXE 7
#define USART_SR_TC 6
#define USART_SR_RXNE 5

#define USART_DIV_MANTISSA 4
#define USART_DIV_FRACTION 0

void USART_PeriClk(USARTx_t* USART, uint8_t cmd);
void USART_Init(USARTx_Handler_t* USARTx_Handler_t);
void USART_TransmitByte(USARTx_t* USARTx, uint8_t byte);
void USART_Transmit(USARTx_t* USARTx, uint8_t* string, uint8_t Len);
void USART_Control(USARTx_t* USARTx, uint8_t cmd);

#endif
