#include "../headers/stm32fx.h"
#include "../headers/RCC.h"
#include "../headers/DMA.h"

#include <stdint.h>

void DMA_PeriClkControl(DMAx_t* DMA, uint8_t cmd){
    if(cmd == ENABLE){
        if(DMA == DMA1){
            RCC->AHB1ENR |= (1 << DMA1_EN);
        }else{
            RCC->AHB1ENR |= (1 << DMA2_EN);
        }
    }else{
        if(DMA == DMA1){
            RCC->AHB1ENR &= ~(1 << DMA1_EN);
        }else{
            RCC->AHB1ENR &= ~(1 << DMA2_EN);
        }
    }
}

void DMA_Init(DMAx_Handler_t* DMA){
    DMA_PeriClkControl(DMA->DMAx, ENABLE);
    uint32_t tempreg = 0;

    if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_0){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S0FCR |= (1 << 2);
            DMA->DMAx->S0FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);
            DMA->DMAx->S0CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);

        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);


       DMA->DMAx->S0CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_1){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S1FCR |= (1 << 2);
            DMA->DMAx->S1FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S1CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);


        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);


        DMA->DMAx->S1CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_2){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S2FCR |= (1 << 2);
            DMA->DMAx->S2FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S2CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);


        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);

        DMA->DMAx->S2CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_3){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S3FCR |= (1 << 2);
            DMA->DMAx->S3FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S3CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);


        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);

        DMA->DMAx->S3CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_4){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S4FCR |= (1 << 2);
            DMA->DMAx->S4FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S4CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);

        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);

        DMA->DMAx->S4CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_5){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S5FCR |= (1 << 2);
            DMA->DMAx->S5FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S5CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);
 
        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);

      
        DMA->DMAx->S5CR |= tempreg;
    }else if(DMA->DMAx_Config.DMA_STREAM == DMA_STREAM_6){

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S6FCR |= (1 << 2);
            DMA->DMAx->S6FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S6CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);
 
        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);

       DMA->DMAx->S6CR |= tempreg;
    }else{

        if(DMA->DMAx_Config.DMA_MODE != DIRECT_MODE_ENABLE){
            DMA->DMAx->S7FCR |= (1 << 2);
            DMA->DMAx->S7FCR |= (DMA->DMAx_Config.DMA_FIFO_THR << 0);

            DMA->DMAx->S7CR  |= (1 << DMA->DMAx_Config.DMA_MODE);
        }

        tempreg |= (DMA->DMAx_Config.DMA_STREAM_PRIORITY << DMA_CR_PL);
        tempreg |= (DMA->DMAx_Config.DMA_CHANNEL << DMA_CR_CHSEL);
        tempreg |= (DMA->DMAx_Config.DMA_DATA_DIR << DMA_CR_DIR);
        tempreg |= (DMA->DMAx_Config.DMA_MEM_BURST << DMA_CR_MBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_BURST << DMA_CR_PBURST);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_FLOW_CONT << DMA_CR_PFCTRL);

        tempreg |= (DMA->DMAx_Config.DMA_MEM_INCREMENT << DMA_CR_MINC);
        tempreg |= (DMA->DMAx_Config.DMA_MSIZE << DMA_CR_MSIZE);
        tempreg |= (DMA->DMAx_Config.DMA_PERI_INCREMENT  << DMA_CR_PINC);
        tempreg |= (DMA->DMAx_Config.DMA_PSIZE << DMA_CR_PSIZE);
       DMA->DMAx->S7CR |= tempreg;
    }
}

void DMA_SetNumData(DMAx_t* DMA, uint8_t STREAM, uint16_t val){
    if(STREAM == DMA_STREAM_0){
        DMA->S0NDTR = val;
    }else if(STREAM == DMA_STREAM_1){
        DMA->S1NDTR = val;
    }else if(STREAM == DMA_STREAM_2){
        DMA->S2NDTR = val;
    }else if(STREAM == DMA_STREAM_3){
        DMA->S3NDTR = val;
    }else if(STREAM == DMA_STREAM_4){
        DMA->S4NDTR = val;
    }else if(STREAM == DMA_STREAM_5){
        DMA->S5NDTR = val;
    }else if(STREAM == DMA_STREAM_6){
        DMA->S6NDTR = val;
    }else{
        DMA->S7NDTR = val;
    }
}

void DMA_SetPeriAddress(DMAx_t* DMA, uint8_t STREAM, uint32_t address){
    if(STREAM == DMA_STREAM_0){
        DMA->S0PAR = address;
    }else if(STREAM == DMA_STREAM_1){
        DMA->S1PAR = address;
    }else if(STREAM == DMA_STREAM_2){
        DMA->S2PAR = address;
    }else if(STREAM == DMA_STREAM_3){
        DMA->S3PAR =address;
    }else if(STREAM == DMA_STREAM_4){
        DMA->S4PAR = address;
    }else if(STREAM == DMA_STREAM_5){
        DMA->S5PAR = address;
    }else if(STREAM == DMA_STREAM_6){
        DMA->S6PAR = address;
    }else{
        DMA->S7PAR = address;
    }
}

void DMA_SetMemAddress1(DMAx_t* DMA, uint8_t STREAM, uint32_t address){
    if(STREAM == DMA_STREAM_0){
        DMA->S0M0AR = address;
    }else if(STREAM == DMA_STREAM_1){
        DMA->S1M0AR = address;

    }else if(STREAM == DMA_STREAM_2){
        DMA->S2M0AR = address;

    }else if(STREAM == DMA_STREAM_3){
        DMA->S3M0AR = address;

    }else if(STREAM == DMA_STREAM_4){
        DMA->S4M0AR = address;

    }else if(STREAM == DMA_STREAM_5){
        DMA->S5M0AR = address;

    }else if(STREAM == DMA_STREAM_6){
        DMA->S6M0AR = address;

    }else{
        DMA->S7M0AR = address;
    }
}

void DMA_Control(DMAx_t* DMA, uint8_t STREAM, uint8_t cmd){
    if(cmd == ENABLE){
        if(STREAM == DMA_STREAM_0){
            DMA->S0CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_1){
            DMA->S1CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_2){
            DMA->S2CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_3){
            DMA->S3CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_4){
            DMA->S4CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_5){
            DMA->S5CR |= (1 << DMA_CR_EN);
        }else if(STREAM == DMA_STREAM_6){
            DMA->S6CR |= (1 << DMA_CR_EN);
        }else{
            DMA->S7CR |= (1 << DMA_CR_EN);
        }
    }else{
        if(STREAM == DMA_CHANNEL_0){
            DMA->S0CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_1){
            DMA->S1CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_2){
            DMA->S2CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_3){
            DMA->S3CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_4){
            DMA->S4CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_5){
            DMA->S5CR &= ~(1 << DMA_CR_EN);
        }else if(STREAM == DMA_CHANNEL_6){
            DMA->S6CR &= ~(1 << DMA_CR_EN);
        }else{
            DMA->S7CR &= ~(1 << DMA_CR_EN);
        }
    }
}

