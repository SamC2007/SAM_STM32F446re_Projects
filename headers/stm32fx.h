#ifndef STM_H
#define STM_H

#include <stdint.h>

#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100 )
#define NVIC_ISER1 ((volatile uint32_t*) 0xE000E104 )
#define NVIC_ISER2 ((volatile uint32_t*) 0xE000E108 )
#define NVIC_ISER3 ((volatile uint32_t*) 0xE000E10C )
#define NVIC_ISER4 ((volatile uint32_t*) 0xE000E110 )
#define NVIC_ISER5 ((volatile uint32_t*) 0xE000E114 )
#define NVIC_ISER6 ((volatile uint32_t*) 0xE000E118 )
#define NVIC_ISER7 ((volatile uint32_t*) 0xE000E11C )

#define NVIC_ICER0 ((volatile uint32_t*) 0xE000E180 )
#define NVIC_ICER1 ((volatile uint32_t*) 0xE000E184 )
#define NVIC_ICER2 ((volatile uint32_t*) 0xE000E188 )
#define NVIC_ICER3 ((volatile uint32_t*) 0xE000E18C )
#define NVIC_ICER4 ((volatile uint32_t*) 0xE000E190 )
#define NVIC_ICER5 ((volatile uint32_t*) 0xE000E194 )
#define NVIC_ICER6 ((volatile uint32_t*) 0xE000E198 )
#define NVIC_ICER7 ((volatile uint32_t*) 0xE000E19C )

#define NVIC_WWDG 0
#define NVIC_PVD 1
#define NVIC_TAMPSTAMP  2
#define NVIC_RTCWKUP 3
#define NVIC_Flash  4
#define NVIC_RCC  5
#define NVIC_EXTI0 6
#define NVIC_EXTI1 7
#define NVIC_EXTI2 8
#define NVIC_EXTI3 9
#define NVIC_EXTI4 10
#define NVIC_DMA1_STREAM0  11
#define NVIC_DMA1_STREAM1  12
#define NVIC_DMA1_STREAM2  13
#define NVIC_DMA1_STREAM3  14
#define NVIC_DMA1_STREAM4  15
#define NVIC_DMA1_STREAM5  16
#define NVIC_DMA1_STREAM6  17
#define NVIC_ADC  18
#define NVIC_CAN1_TX  19
#define NVIC_CAN1_RX0  20
#define NVIC_CAN1_RX1  21
#define NVIC_CAN1_SCE  22
#define NVIC_EXTI9_5  23
#define NVIC_TIM1_BRK_TIM9  24
#define NVIC_TIM1_UP_TIM10  25
#define NVIC_TIM1_TRG_COM_TIM11 26
#define NVIC_TIM1_CC  27
#define NVIC_TIM2  28
#define NVIC_TIM3  29
#define NVIC_TIM4  30
#define NVIC_I2C1_EV  31
#define NVIC_I2C1_ER  32
#define NVIC_I2C2_EV  33
#define NVIC_I2C2_ER  34
#define NVIC_SPI1 35
#define NVIC_SPI2 36
#define NVIC_USART1  37
#define NVIC_USART2  38
#define NVIC_USART3  39
#define NVIC_ECTI15_10  40
#define NVIC_RTC_Alarm  41
#define NVIC_OTG_FS_WKUP 42
#define NVIC_TIM8_BRK_TIM12  43
#define NVIC_TIM8_UP_TIM13 44
#define NVIC_TIM8_TRG_COM_TIM14 45
#define NVIC_TIM8_CC  46
#define NVIC_DMA1_Stream7  47
#define NVIC_FMC		 48
#define NVIC_SDIO		 49
#define NVIC_TIM5		 50
#define NVIC_SPI3		 51
#define NVIC_UART4		 52
#define NVIC_UART5		 53
#define NVIC_TIM6_DAC	 54
#define NVIC_TIM7		 55
#define NVIC_DMA2_Stream0 56
#define NVIC_DMA2_Stream1 57
#define NVIC_DMA2_Stream2 58
#define NVIC_DMA2_Stream3 59
#define NVIC_DMA2_Stream4 60

#define NVIC_CAN2_TX 63
#define NVIC_CAN2_RX0			 64
#define NVIC_CAN2_RX1			 65
#define NVIC_CAN2_SCE			 66
#define NVIC_OTG_FS			 67
#define NVIC_DMA2_Stream5 68
#define NVIC_DMA2_Stream6 69
#define NVIC_DMA2_Stream7 70
#define NVIC_USART6				 71
#define NVIC_I2C3_EV				 72
#define NVIC_I2C3_ER				 73
#define NVIC_OTG_HS_EP1_OUT  74
#define NVIC_OTG_HS_EP1_IN 75
#define NVIC_OTG_HS_WKUP			 76
#define NVIC_OTG_HS				 77
#define NVIC_DCMI				 78


#define NVIC_FPU					81


#define NVIC_SPI4				 84


#define NVIC_SAI1				 87


#define NVIC_SAI2	91
#define NVIC_QuadSPI 92
#define NVIC_HDMICEC 93
#define NVIC_SPDIFRx 94
#define NVIC_FMPI2C1 95
#define NVIC_FMPI2C1_error 96

#define DISABLE 0
#define ENABLE 1


//print functions
#include "RCC.h"
#include "USART.h"
#include "GPIO.h"
#include "TIMERS.h"

extern uint32_t volatile* const pCAPCR;
//define USART 2 and RCC
extern USARTx_Handler_t pUSART2;
extern TIM6_7_TypeDef_t volatile* const pTIM6;

void init_print(void);
void init_tim(void);
void uart_write_byte(uint8_t c);
void print(char* ptr);
void printD(uint32_t digit);
void printF(float value, uint8_t places);
void printR(char message[], uint8_t len);
void printS(uint8_t message[]);
void printHex(uint8_t byte);
uint8_t len(uint8_t str[]);

void delay(uint32_t n);
void init_functions(void);

#endif
