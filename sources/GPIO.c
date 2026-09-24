#include "../headers/stm32fx.h"
#include "../headers/RCC.h"
#include "../headers/GPIO.h"
#include <stdint.h>

void GPIO_RCCENABLE(GPIOx_t* GPIOx){
    if(GPIOx == GPIOA){
        RCC->AHB1ENR |= (1 << GPIOA_EN);
    }else if(GPIOx == GPIOB){
        RCC->AHB1ENR |= (1 << GPIOB_EN);
    }else if(GPIOx == GPIOC){
        RCC->AHB1ENR |= (1 << GPIOC_EN);
    }else if(GPIOx == GPIOD){
        RCC->AHB1ENR |= (1 << GPIOD_EN);
    }else if(GPIOx == GPIOE){
        RCC->AHB1ENR |= (1 << GPIOE_EN);
    }else if(GPIOx == GPIOF){
        RCC->AHB1ENR |= (1 << GPIOF_EN);
    }else if(GPIOx == GPIOG){ 
        RCC->AHB1ENR |= (1 << GPIOG_EN);
    }else {
        RCC->AHB1ENR |= (1 << GPIOH_EN);
    }
}

void GPIO_Init(GPIOx_Handler_t* GPIO){
    //turn on respective GPIO RCC clock
    GPIO_RCCENABLE(GPIO->GPIOx);
    uint32_t tempreg = 0;
    tempreg |= (GPIO->GPIOx_Config.MODER << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->MODER &= ~(0x3 << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->MODER |= tempreg;

    tempreg = 0;
    tempreg |= (GPIO->GPIOx_Config.OT << GPIO->GPIOx_Config.PIN);
    GPIO->GPIOx->OT |= tempreg;

    tempreg = 0;
    tempreg |= (GPIO->GPIOx_Config.OSPEEDR << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->OSPEEDR &= ~(0x3 << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->OSPEEDR |= tempreg;

    tempreg = 0;
    tempreg |= (GPIO->GPIOx_Config.PUPDR << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->PUPDR &= ~(0x3 << (2 * GPIO->GPIOx_Config.PIN));
    GPIO->GPIOx->PUPDR |= tempreg;

    tempreg = 0;
    if(GPIO->GPIOx_Config.BSRR == BSRR_RESET){
        tempreg |= (1 << (16 + GPIO->GPIOx_Config.PIN));
        GPIO->GPIOx->BSRR |= tempreg;
    }else {
        tempreg |= (1 << GPIO->GPIOx_Config.PIN);
        GPIO->GPIOx->BSRR |= tempreg;
    }
    tempreg = 0;
    if(GPIO->GPIOx_Config.LCKR == LOCKED){
        tempreg |= (GPIO->GPIOx_Config.LCKR << GPIO->GPIOx_Config.PIN);
        tempreg |= (GPIO->GPIOx_Config.LCKK << 16);
        GPIO->GPIOx->LCKR |= tempreg;
    }
    tempreg = 0;
    uint8_t pin = 0;
    if(GPIO->GPIOx_Config.MODER == ALTERNATE){
        if(GPIO->GPIOx_Config.PIN > 7){
          pin = GPIO->GPIOx_Config.PIN % 8;
          tempreg |= (GPIO->GPIOx_Config.AFR << (4 * pin));
          GPIO->GPIOx->AFR[1] &= ~(0xF << (4 * pin));
          GPIO->GPIOx->AFR[1] |= tempreg;
        }else {
          tempreg |= (GPIO->GPIOx_Config.AFR << (4 * GPIO->GPIOx_Config.PIN));
          GPIO->GPIOx->AFR[0] &= ~(0xF << (4 * GPIO->GPIOx_Config.PIN));
          GPIO->GPIOx->AFR[0] |= tempreg;
        }
    }

}

void LED_Toggle(GPIOx_Handler_t* GPIO, uint8_t cmd){
    if(cmd == ENABLE){
        GPIO->GPIOx->ODR |= (1 << GPIO->GPIOx_Config.PIN);
    }else{
        GPIO->GPIOx->ODR &= ~(1 << GPIO->GPIOx_Config.PIN);
    }

}
