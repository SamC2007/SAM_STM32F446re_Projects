#ifndef RCC_H
#define RCC_H
#include <stdint.h>

#define RCC ((RCC_TypeDef_t*)(0x40023800))
#define __vo volatile

typedef struct {
    __vo uint32_t CR;           // 0x00: Clock control register
    __vo uint32_t PLLCFGR;      // 0x04: PLL configuration register
    __vo uint32_t CFGR;         // 0x08: Clock configuration register
    __vo uint32_t CIR;          // 0x0C: Clock interrupt register
    __vo uint32_t AHB1RSTR;     // 0x10: AHB1 peripheral reset register
    __vo uint32_t AHB2RSTR;     // 0x14: AHB2 peripheral reset register
    __vo uint32_t AHB3RSTR;     // 0x18: AHB3 peripheral reset register
    uint32_t RESERVED0;             // 0x1C: Reserved
    __vo uint32_t APB1RSTR;     // 0x20: APB1 peripheral reset register
    __vo uint32_t APB2RSTR;     // 0x24: APB2 peripheral reset register
    uint32_t RESERVED1[2];          // 0x28–0x2C: Reserved
    __vo uint32_t AHB1ENR;      // 0x30: AHB1 peripheral clock enable register
    __vo uint32_t AHB2ENR;      // 0x34: AHB2 peripheral clock enable register
    __vo uint32_t AHB3ENR;      // 0x38: AHB3 peripheral clock enable register
    uint32_t RESERVED2;             // 0x3C: Reserved
    __vo uint32_t APB1ENR;      // 0x40: APB1 peripheral clock enable register
    __vo uint32_t APB2ENR;      // 0x44: APB2 peripheral clock enable register
    uint32_t RESERVED3[2];          // 0x48–0x4C: Reserved
    __vo uint32_t AHB1LPENR;    // 0x50: AHB1 low power enable register
    __vo uint32_t AHB2LPENR;    // 0x54
    __vo uint32_t AHB3LPENR;    // 0x58
    uint32_t RESERVED4;             // 0x5C
    __vo uint32_t APB1LPENR;    // 0x60
    __vo uint32_t APB2LPENR;    // 0x64
    uint32_t RESERVED5[2];          // 0x68–0x6C
    __vo uint32_t BDCR;         // 0x70
    __vo uint32_t CSR;          // 0x74
    uint32_t RESERVED6[2];          // 0x78–0x7C
    __vo uint32_t SSCGR;        // 0x80
    __vo uint32_t PLLI2SCFGR;   // 0x84
    __vo uint32_t PLLSAICFGR;   // 0x88
    __vo uint32_t DCKCFGR;      // 0x8C
    __vo uint32_t CKGATENR;     // 0x90
    __vo uint32_t DCKCFGR2;     // 0x94
} RCC_TypeDef_t;

//AHB1ENR code
#define GPIOA_EN 0
#define GPIOB_EN 1
#define GPIOC_EN 2
#define GPIOD_EN 3
#define GPIOE_EN 4
#define GPIOF_EN 5
#define GPIOG_EN 6
#define GPIOH_EN 7
#define CRC_EN 12
#define BKPSRAM_EN 18
#define DMA1_EN 21
#define DMA2_EN 22
#define OTGHS_EN 29
#define OTGHULPI_EN 30
//APB1ENR codes
#define TIM2_EN 0
#define TIM3_EN 1
#define TIM4_EN 2
#define TIM5_EN 3
#define TIM6_EN 4
#define TIM7_EN 5
#define TIM12_EN 6
#define TIM13_EN 7
#define TIM14_EN 8
#define WWDG_EN 11
#define SPI2_EN 14
#define SPI3_EN 15
#define SPDIFRX_EN 16
#define USART2_EN 17
#define USART3_EN 18
#define UART4_EN 19
#define UART5_EN 20
#define I2C1_EN 21
#define I2C2_EN 22
#define I2C3_EN 23
#define FMPI2C1_EN 24
#define CAN1_EN 25
#define CAN2_EN 26
#define CEC_EN 27
#define PWR_EN 28
#define DAC_EN 29

//APB2ENR codes
#define TIM1_EN 0
#define TIM8_EN 1
#define USART1_EN 4
#define USART6_EN 5
#define ADC1_EN 8
#define ADC2_EN 9
#define ADC3_EN 10
#define SDIO_EN 11
#define SPI1_EN 12
#define SPI4_EN 13
#define SYSCFG_EN 14
#define TIM9_EN 16
#define TIM10_EN 17
#define TIM11_EN 18
#define SAI1_EN 22
#define SAI2_EN 23

uint32_t RCC_GetPCKVal1(void);
uint32_t RCC_GetPCKVal2(void);
#endif
