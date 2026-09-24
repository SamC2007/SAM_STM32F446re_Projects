#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC1 ((ADCx_t*)(0x40012000))
#define ADC2 ((ADCx_t*)(0x40012100))
#define ADC3 ((ADCx_t*)(0x40012200))

#define COM_REG_ADC1 ((ADCx_Offset_t*)(0x40012300))

#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7
#define CHANNEL_8 8
#define CHANNEL_9 9
#define CHANNEL_10 10
#define CHANNEL_11 11
#define CHANNEL_12 12
#define CHANNEL_13 13
#define CHANNEL_14 14
#define CHANNEL_15 15
#define CHANNEL_16 16
#define CHANNEL_17 17
#define CHANNEL_18 18
#define CHANNEL_19 19

#define INJECTED_CONVERSION_1 17
#define INJECTED_CONVERSION_2 18
#define INJECTED_CONVERSION_3 19
#define INJECTED_CONVERSION_4 20

#define CONVERSION_1 0
#define CONVERSION_2 1
#define CONVERSION_3 2
#define CONVERSION_4 3
#define CONVERSION_5 4
#define CONVERSION_6 5
#define CONVERSION_7 6
#define CONVERSION_8 7
#define CONVERSION_9 8
#define CONVERSION_10 9
#define CONVERSION_11 10
#define CONVERSION_12 11
#define CONVERSION_13 12
#define CONVERSION_14 13
#define CONVERSION_15 14
#define CONVERSION_16 15

typedef struct{
    uint8_t DISCEN;
    uint8_t JDISCEN;
    uint8_t DISCEN_CHANNEL_CONV;
    uint8_t CONVERSION_LENGTH;
    uint8_t J_CONVERSION_LENGTH;
    uint8_t SCAN;
    uint8_t CONT;
}ADCx_Config_t;

typedef struct{
    uint32_t SR;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMPR1;
    uint32_t SMPR2;
    uint32_t JOFR1;
    uint32_t JOFR2;
    uint32_t JOFR3;
    uint32_t JOFR4;
    uint32_t HTR;
    uint32_t LTR;
    uint32_t SQR1;
    uint32_t SQR2;
    uint32_t SQR3;
    uint32_t JSQR;
    uint32_t JDR1;
    uint32_t JDR2;
    uint32_t JDR3;
    uint32_t JDR4;
    uint32_t DR;
}ADCx_t;

typedef struct{
    uint32_t CSR;
    uint32_t CCR;
    uint32_t CDR;
}ADCx_Offset_t;

typedef struct{
    ADCx_t* ADCx;
    ADCx_Config_t ADCx_Config;
    uint32_t* Rbuffer;
    uint32_t* Ibuffer;
    uint8_t Rlen;
    uint8_t Ilen;
    uint8_t State;
}ADCx_Handler_t;

#define REGULAR_CHANNEL 0
#define INJECTED_CHANNEL 1

//define sample rate 
#define SAMPLE_3_CYCLES 0
#define SAMPLE_15_CYCLES 1
#define SAMPLE_28_CYCLES 2
#define SAMPLE_56_CYCLES 3
#define SAMPLE_84_CYCLES 4
#define SAMPLE_112_CYCLES 5
#define SAMPLE_144_CYCLES 6
#define SAMPLE_480_CYCLES 7

#define V25 0.76f
#define AVG_SLOPE 2.5f

#define L 20
#define JL 20

#define ADC_SWSTART 30
#define ADC_JSWSTART 22
#define ADC_SCAN 8
#define ADC_DISCEN 11
#define ADC_EOCIE 5
#define ADC_JEOCIE 7

#define ADC_CONT 1
#define ADC_EOC 1
#define ADC_EOCS 10
#define ADC_JEOC 2

#define ADC_FREE 0
#define ADC_WAITING 1
#define ADC_DATA_READY 2

void ADC_PeriClkControl(ADCx_t* ADC, uint8_t cmd);
void ADC_Init(ADCx_Handler_t* ADC);
void ADC_Control(ADCx_t* ADC, uint8_t cmd);

void ADC_StartAnalog(ADCx_t* ADC, uint8_t CHANNEL_TYPE);

void ADC_StartAnalogIT(ADCx_Handler_t* ADC, uint8_t CHANNEL_TYPE, uint32_t* Buffer, uint8_t CHANNELS);
uint32_t HandleInjectRead(ADCx_t* ADC);
uint32_t ReadRegularAnalog(ADCx_t* ADC);
uint32_t ReadInjectedAnalog(ADCx_t* ADC);

uint8_t ReadRegularAnalogIT(ADCx_Handler_t* ADC);
uint8_t ReadInjectedAnalogIT(ADCx_Handler_t* ADC);

void ADC_InternalTempConfig(ADCx_t* ADC, uint8_t SAMPLE, uint8_t cmd);
float GetTempData(ADCx_t* ADC);

void EOCS_Config(ADCx_t* ADC, uint8_t cmd);
void ADC_ADDChannel(ADCx_t* ADC, uint8_t CHANNEL, uint8_t CONVERSION, uint8_t SAMPLE_RATE);

void ADC_DMAConfig(ADCx_t* ADC, uint8_t cmd);


void ADC_IRQHandling(ADCx_Handler_t* ADC);
void ADC_InterruptConfig(uint8_t cmd);

#endif
