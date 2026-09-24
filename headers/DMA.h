#ifndef DMA_H
#define DMA_H

#include <stdint.h>

#define DMA1 ((DMAx_t*)(0x40026000))
#define DMA2 ((DMAx_t*)(0x40026400))

#define DMA_STREAM_0 0
#define DMA_STREAM_1 1
#define DMA_STREAM_2 2
#define DMA_STREAM_3 3
#define DMA_STREAM_4 4
#define DMA_STREAM_5 5
#define DMA_STREAM_6 6
#define DMA_STREAM_7 7

#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3
#define DMA_CHANNEL_4 4
#define DMA_CHANNEL_5 5
#define DMA_CHANNEL_6 6
#define DMA_CHANNEL_7 7


#define LOW_PRIORITY 0
#define MEDIUM_PRIORITY 1
#define HIGH_PRIORITY 2
#define VHIGH_PRIORITY 3

#define PERI_TO_MEM 0
#define MEM_TO_PERI 1
#define MEM_TO_MEM 2

#define SINGLE_TRANSFER 0
#define INCR4 1
#define INCR8 2
#define INCR16 3

#define DMA_CIRC 8
#define DMA_DBM 18

#define DMA_FLOW_CONTROLLER 0
#define PERI_FLOW_CONTROLLER 1

#define DMA_SIZE_BYTE 0
#define DMA_SIZE_HWORD 1
#define DMA_SIZE_WORD 2

#define DIRECT_MODE_ENABLE 0
#define DIRECT_MODE_DISABLE 1

#define DMA_1QUARTER_FIFO 0
#define DMA_2QUARTERS_FIFO 1
#define DMA_3QUARTERS_FIFO 2
#define DMA_FULL_FIFO 3


typedef struct{
    uint8_t DMA_STREAM;
    uint8_t DMA_CHANNEL;
    uint8_t DMA_STREAM_PRIORITY;
    uint8_t DMA_DATA_DIR;
    uint8_t DMA_MEM_BURST;
    uint8_t DMA_PERI_BURST;
    uint8_t DMA_MODE;
    uint8_t DMA_PERI_FLOW_CONT;
    uint8_t DMA_MSIZE;
    uint8_t DMA_PSIZE;
    uint8_t DMA_FIFO_THR;
    uint8_t DMA_MEM_INCREMENT;
    uint8_t DMA_PERI_INCREMENT;
}DMAx_Config_t;

typedef struct{
    uint32_t LISR;
    uint32_t HISR;
    uint32_t LIFCR;
    uint32_t HIFCR;
    uint32_t S0CR;
    uint32_t S0NDTR;
    uint32_t S0PAR;
    uint32_t S0M0AR;
    uint32_t S0M1AR;
    uint32_t S0FCR;
    uint32_t S1CR;
    uint32_t S1NDTR;
    uint32_t S1PAR;
    uint32_t S1M0AR;
    uint32_t S1M1AR;
    uint32_t S1FCR;
    uint32_t S2CR;
    uint32_t S2NDTR;
    uint32_t S2PAR;
    uint32_t S2M0AR;
    uint32_t S2M1AR;
    uint32_t S2FCR;
    uint32_t S3CR;
    uint32_t S3NDTR;
    uint32_t S3PAR;
    uint32_t S3M0AR;
    uint32_t S3M1AR;
    uint32_t S3FCR;
    uint32_t S4CR;
    uint32_t S4NDTR;
    uint32_t S4PAR;
    uint32_t S4M0AR;
    uint32_t S4M1AR;
    uint32_t S4FCR;
    uint32_t S5CR;
    uint32_t S5NDTR;
    uint32_t S5PAR;
    uint32_t S5M0AR;
    uint32_t S5M1AR;
    uint32_t S5FCR;
    uint32_t S6CR;
    uint32_t S6NDTR;
    uint32_t S6PAR;
    uint32_t S6M0AR;
    uint32_t S6M1AR;
    uint32_t S6FCR;
    uint32_t S7CR;
    uint32_t S7NDTR;
    uint32_t S7PAR;
    uint32_t S7M0AR;
    uint32_t S7M1AR;
    uint32_t S7FCR;
}DMAx_t;

typedef struct{
    DMAx_t* DMAx;
    DMAx_Config_t DMAx_Config;
}DMAx_Handler_t;

#define DMA_CR_CHSEL 25
#define DMA_CR_MBURST 23
#define DMA_CR_PBURST 21
#define DMA_CR_CT 19
#define DMA_CR_DBM 18
#define DMA_CR_PINCOS 15
#define DMA_CR_PL 16
#define DMA_CR_MSIZE 13
#define DMA_CR_PSIZE 11
#define DMA_CR_MINC 10
#define DMA_CR_PINC 9
#define DMA_CR_CIRC 8
#define DMA_CR_DIR 6
#define DMA_CR_PFCTRL 5
#define DMA_CR_TCIE 4
#define DMA_CR_HTIE 3
#define DMA_CR_TEIE 2
#define DMA_CR_DMEIE 1
#define DMA_CR_EN 0

void DMA_PeriClkControl(DMAx_t* DMA, uint8_t cmd);
void DMA_Init(DMAx_Handler_t* DMA);

void DMA_SetNumData(DMAx_t* DMA, uint8_t STREAM, uint16_t val);
void DMA_SetPeriAddress(DMAx_t* DMA, uint8_t STREAM, uint32_t address);
void DMA_SetMemAddress1(DMAx_t* DMA, uint8_t STREAM, uint32_t address);

void DMA_Control(DMAx_t* DMA, uint8_t STREAM, uint8_t cmd);
#endif
