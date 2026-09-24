#include "../headers/stm32fx.h"
#include "../headers/RCC.h"

uint8_t APB_PSC[4] = {2,4,8,16};
uint16_t AHB_PSC[9] = {2,4,8,16,32,64,128,256,512};

uint32_t RCC_GetPCKVal1(void){
    uint32_t RCC_CK, SystemClk;
    uint8_t  clk, temp, ahb, apb;
    clk = (RCC->CFGR >> 2) & 0x3;
    if(clk == 0){
        SystemClk = 16000000;
    }else if(clk == 1){
        SystemClk = 8000000;
    }
    //chose ahb1 prescaler
    temp = (RCC->CFGR >> 4) & 0xF;
    if(temp > 7){
        ahb = AHB_PSC[temp - 8];
    }else{
        ahb = 1;
    }
    //choose apb1 prescaler
    temp = (RCC->CFGR >> 10) & 0x7;
    if(temp > 3){
        apb = AHB_PSC[temp - 4];
    }else{
        apb = 1;
    }
    RCC_CK = (SystemClk / ahb) / apb;
    return RCC_CK;
}

uint32_t RCC_GetPCKVal2(void){
    uint32_t RCC_CK, SystemClk;
    uint8_t  clk, temp, ahb, apb;
    clk = (RCC->CFGR >> 2) & 0x3;
    if(clk == 0){
        SystemClk = 16000000;
    }else if(clk == 1){
        SystemClk = 8000000;
    }
    //chose ahb1 prescaler
    temp = (RCC->CFGR >> 4) & 0xF;
    if(temp > 7){
        ahb = AHB_PSC[temp - 8];
    }else{
        ahb = 1;
    }
    //choose apb2 prescaler
    temp = (RCC->CFGR >> 13) & 0x7;
    if(temp > 3){
        apb = AHB_PSC[temp - 4];
    }else{
        apb = 1;
    }
    RCC_CK = (SystemClk / ahb) / apb;
    return RCC_CK;

}
