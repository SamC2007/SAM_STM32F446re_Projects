#include "../headers/stm32fx.h"
#include "../headers/USART.h"
#include "../headers/RCC.h"
#include "../headers/GPIO.h"
#include "../headers/TIMERS.h"
#include <stdint.h>

TIM6_7_TypeDef_t volatile* const pTIM6 = TIM6;

uint32_t volatile* const pCAPCR = (uint32_t *)0xE000ED88;

USARTx_Handler_t pUSART2;

void init_print(void){
	//First configure RCC
	RCC->APB1ENR |= (1 << USART2_EN);

	*pCAPCR |= (0xF << 20);

	//Configure GPIO
    GPIOx_Handler_t pGPIOA;
    pGPIOA.GPIOx = GPIOA;

	pGPIOA.GPIOx_Config.PIN = 2;
	pGPIOA.GPIOx_Config.MODER = ALTERNATE;
	pGPIOA.GPIOx_Config.AFR = AF7;
    pGPIOA.GPIOx_Config.PUPDR = PULL_UP;
    pGPIOA.GPIOx_Config.OSPEEDR = MED_SPEED;
    pGPIOA.GPIOx_Config.OT = PUSH_PULL;
    GPIO_Init(&pGPIOA);
	//Configure USART
    pUSART2.USARTx = USART2;
    pUSART2.USARTx_Config.BAUD_RATE = 115200;
    pUSART2.USARTx_Config.USART_MODE = TRANSMIT_ONLY;
    pUSART2.USARTx_Config.SAMPLING = OVER8;
    USART_Init(&pUSART2);
    USART_Control(USART2, ENABLE);
}

void init_tim(void){
    RCC->APB1ENR |= (1 << TIM6_EN);

    pTIM6->PSC = 14;
    pTIM6->ARR = 999;
    pTIM6->SR.UIF = DISABLE;
    pTIM6->CR1.CEN = ENABLE; 
}

void init_functions(void){
    init_print();
    init_tim();
}

uint8_t len(uint8_t str[]){
	uint8_t count = 0;
    for(uint8_t i = 0; str[i] != '\0'; ++i){
        count++;
    }
	return count;
}

void print(char* ptr){
   USART_Transmit(USART2, (uint8_t*)ptr, len((uint8_t*)ptr));
}
void printD(uint32_t digit){
	if(digit == 0){
		USART_TransmitByte(USART2, '0');
		return;
	}

	uint8_t count = 0;
	char message[10];
	while(digit != 0){
		count++;
		uint32_t cur = digit % 10;
		message[count] = (cur + '0');
		digit = (digit - cur) / 10;
	}
	printR(message, count);
}

void printF(float value, uint8_t places){
	uint32_t decimal = (uint32_t)value;
	printD(decimal);
	USART_TransmitByte(USART2, '.');
	float fraction = value - (float)decimal;
	for(uint8_t i = 0; i < places; ++i){
		fraction *= 10;
		decimal = (uint32_t)fraction;
		USART_TransmitByte(USART2, decimal + '0');
		fraction -= decimal;
	}
} 
void printR(char message[], uint8_t len)
{
	for(uint8_t i = len; i > 0; i--)
	{ 
		USART_TransmitByte(USART2, message[i]);
	}
}

void printHex(uint8_t n){
	uint8_t hex[] = "0123456789ABCDEF";
	uint8_t buffer[3];
	buffer[2] = '\0';

	for(uint8_t i = 0; i < 2; ++i){
		buffer[i] = hex[n & 0xF];
		n >>= 4;
	}
	print("0x");
	USART_TransmitByte(USART2, buffer[1]);	
	USART_TransmitByte(USART2, buffer[0]);
	print("\r\n");
}


void delay(uint32_t n){
    for(uint32_t i = 0; i < n; ++i){
       pTIM6->CNT = 0;
       while(pTIM6->CNT < pTIM6->ARR);
    }
}

