#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIOA ((GPIOx_t*)(0x40020000))
#define GPIOB ((GPIOx_t*)(0x40020400))
#define GPIOC ((GPIOx_t*)(0x40020800))
#define GPIOD ((GPIOx_t*)(0x40020C00))
#define GPIOE ((GPIOx_t*)(0x40021000))
#define GPIOF ((GPIOx_t*)(0x40021400))
#define GPIOG ((GPIOx_t*)(0x40021800))
#define GPIOH ((GPIOx_t*)(0x40021C00))

typedef struct{
    uint8_t PIN;
    uint8_t MODER;
    uint8_t OT;
    uint8_t OSPEEDR;
    uint8_t PUPDR;
    uint8_t BSRR;
    uint8_t LCKR;
    uint8_t LCKK;
    uint8_t AFR;
}GPIOx_Config_t;

typedef struct {
    uint32_t MODER;
    uint32_t OT;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFR[1];
}GPIOx_t;

typedef struct{
    GPIOx_Config_t GPIOx_Config;
    GPIOx_t* GPIOx;
}GPIOx_Handler_t;

#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

#define PUSH_PULL 0
#define OPEN_DRAIN 1

#define LOW_SPEED 0
#define MED_SPEED 1
#define FAST_SPEED 2
#define HIGH_SPEED 3

#define NO_PU_PD 0
#define PULL_UP 1
#define PULL_DOWN 2

#define BSRR_RESET 1
#define BSRR_SET 2

#define LOCK_NA 0
#define LOCK_A 1
#define UNLOCKED 0
#define LOCKED 1

#define AF0 0
#define AF1 1
#define AF2 2
#define AF3 3
#define AF4 4
#define AF5 5
#define AF6 6
#define AF7 7
#define AF8 8
#define AF9 9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15

void GPIO_Init(GPIOx_Handler_t* GPIO);
void LED_Toggle(GPIOx_Handler_t* GPIO, uint8_t cmd);

#endif
