
#include "headers/stm32fx.h"
#include "headers/ADC.h"
#include "headers/GPIO.h"
#include "headers/DMA.h"
#include <stdint.h>

ADCx_Handler_t pADC1;
DMAx_Handler_t pDMA2;

#define ADC1_DR_ADDR ((uint32_t)0x4001204C)

void GPIO_init(void){
    GPIOx_Handler_t pGPIOA;
    pGPIOA.GPIOx = GPIOA;
    pGPIOA.GPIOx_Config.MODER = ANALOG;
    pGPIOA.GPIOx_Config.OT = PUSH_PULL;
    pGPIOA.GPIOx_Config.OSPEEDR = FAST_SPEED;
    pGPIOA.GPIOx_Config.PUPDR = NO_PU_PD;

    pGPIOA.GPIOx_Config.PIN = 1;
    GPIO_Init(&pGPIOA);

    pGPIOA.GPIOx_Config.PIN = 4;
    GPIO_Init(&pGPIOA);
}

void DMA_init(){

    pDMA2.DMAx = DMA2;
    pDMA2.DMAx_Config.DMA_MODE = DMA_CIRC;
    pDMA2.DMAx_Config.DMA_FIFO_THR = DMA_FULL_FIFO;
    pDMA2.DMAx_Config.DMA_STREAM = DMA_STREAM_4;
    pDMA2.DMAx_Config.DMA_CHANNEL = DMA_CHANNEL_0;
    pDMA2.DMAx_Config.DMA_STREAM_PRIORITY = HIGH_PRIORITY;
    pDMA2.DMAx_Config.DMA_DATA_DIR = PERI_TO_MEM;
    pDMA2.DMAx_Config.DMA_MEM_BURST = SINGLE_TRANSFER;
    pDMA2.DMAx_Config.DMA_PERI_BURST = SINGLE_TRANSFER;
    pDMA2.DMAx_Config.DMA_PERI_FLOW_CONT = DMA_FLOW_CONTROLLER;

    pDMA2.DMAx_Config.DMA_MSIZE = DMA_SIZE_HWORD;
    pDMA2.DMAx_Config.DMA_PSIZE = DMA_SIZE_HWORD;

    pDMA2.DMAx_Config.DMA_MEM_INCREMENT = ENABLE;
    pDMA2.DMAx_Config.DMA_PERI_INCREMENT = DISABLE;

    DMA_Init(&pDMA2);
}

void ADC_init(void){
    pADC1.ADCx = ADC1;
    pADC1.ADCx_Config.DISCEN = DISABLE;
    pADC1.ADCx_Config.SCAN = ENABLE;
    pADC1.ADCx_Config.DISCEN_CHANNEL_CONV = 0;
    pADC1.ADCx_Config.CONVERSION_LENGTH = 2;
    pADC1.ADCx_Config.J_CONVERSION_LENGTH = 0;
    pADC1.ADCx_Config.CONT = ENABLE;
    pADC1.ADCx_Config.JDISCEN = DISABLE;

    ADC_Init(&pADC1);
    ADC_ADDChannel(ADC1, CHANNEL_1, CONVERSION_1, SAMPLE_15_CYCLES);
    ADC_ADDChannel(ADC1, CHANNEL_4, CONVERSION_2, SAMPLE_15_CYCLES);
    EOCS_Config(ADC1, DISABLE);
    ADC_DMAConfig(ADC1, ENABLE);
    ADC_Control(ADC1, ENABLE);
}

int main(void){
    uint16_t buffer[2];

    init_functions();
    GPIO_init(); 

    DMA_init();
    DMA_SetNumData(DMA2, DMA_STREAM_4, 2);
    DMA_SetPeriAddress(DMA2, DMA_STREAM_4, ADC1_DR_ADDR);
    DMA_SetMemAddress1(DMA2, DMA_STREAM_4,(uint32_t) buffer);

    DMA_Control(DMA2, DMA_STREAM_4, ENABLE);

    ADC_init();
    ADC_StartAnalog(ADC1, REGULAR_CHANNEL);
    print("Enables ADC\r\n");

    while(1){
        uint16_t Xaxis = buffer[0];
        uint16_t Yaxis = buffer[1];
/*
        print("x-axis: ");
        printD(Xaxis);
        print("\r\n");
        print("y-axis: ");
        printD(Yaxis);
        print("\r\n");
*/
        if(Xaxis < 1000){
            print("LEFT\r\n");
        }else if( Xaxis > 3000){
            print("RIGHT\r\n");
        }else{
            print("CENTER\r\n");
        }

        if(Yaxis < 1000){
            print("UP\r\n");
        }else if( Yaxis > 3000){
            print("DOWN\r\n");
        }else{
            print("CENTER\r\n");
        }
        delay(100);
   }
}
