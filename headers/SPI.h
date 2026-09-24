#ifndef SPI_H
#define SPI_H
#include <stdint.h>

#define SPI1 ((SPIx_t*)(0x40013000))
#define SPI2 ((SPIx_t*)(0x40003800))
#define SPI3 ((SPIx_t*)(0x40003C00))
#define SPI4 ((SPIx_t*)(0x40013400))

#define FULL_DUPLEX 0
#define HALF_DUPLEX 1
#define SIMPLEX 3

#define BAUD_DIV_2 0
#define BAUD_DIV_4 1
#define BAUD_DIV_8 2
#define BAUD_DIV_16 3
#define BAUD_DIV_32 4
#define BAUD_DIV_64 5
#define BAUD_DIV_128 6
#define BAUD_DIV_256 7

#define BITF_8 0
#define BITF_16 1

#define SPI_FREE 0
#define SPI_BSY_TX 1
#define SPI_BSY_RX 2

typedef struct {
    uint8_t CPOL;
    uint8_t CPHA;
    uint8_t MSTR;
    uint8_t BR;
    uint8_t SPE;
    uint8_t DFF;
    uint8_t MODE;
    uint8_t SSM;
}SPIx_Config_t;

typedef struct {
   volatile uint32_t CR1;
   volatile uint32_t CR2;
   volatile uint32_t SR;
   volatile uint32_t DR;
   volatile uint32_t CRCPR;
   volatile uint32_t RXCRCR;
   volatile uint32_t TXCRCR;
   volatile uint32_t I2SCFGR;
   volatile uint32_t I2SPR;
}SPIx_t;

typedef struct{
    SPIx_Config_t SPIx_Config;
    SPIx_t* SPIx; 
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t* TxBuffer;
    uint8_t* RxBuffer;
    uint8_t BusyState;
}SPIx_Handler_t;
// Bit positions of SPI peripheral
#define SPI_CR1_CPHA						0
#define SPI_CR1_CPOL						1
#define SPI_CR1_MSTR						2
#define SPI_CR1_BR							3
#define SPI_CR1_SPE							6
#define SPI_CR1_LSB							7
#define SPI_CR1_SSI							8
#define SPI_CR1_SSM							9
#define SPI_CR1_RXONLY						10
#define SPI_CR1_DFF							11
#define SPI_CR1_CRC_NEXT					12
#define SPI_CR1_CRC_EN						13
#define SPI_CR1_BIDI_OE						14
#define SPI_CR1_BIDI_MODE					15
// SPI CR2
#define SPI_CR2_RXDMAEN						0
#define SPI_CR2_TXDMAEN						1
#define SPI_CR2_SSOE						2
#define SPI_CR2_FRF							4
#define SPI_CR2_ERRIE						5
#define SPI_CR2_RXNEIE						6
#define SPI_CR2_TXEIE						7
//SPI Status Register
#define SPI_SR_RXNE							0
#define SPI_SR_TXE							1
#define SPI_SR_CHSIDE						2
#define SPI_SR_UDR							3
#define SPI_SR_CRC							4
#define SPI_SR_MODF							5
#define SPI_SR_OVR							6
#define SPI_SR_BSY							7
#define SPI_SR_FRE							8

//functions
void SPI_Init(SPIx_Handler_t* SPI);
void SSOE_Config(SPIx_t* SPIx, uint8_t cmd);
void SSI_Config(SPIx_t* SPIx, uint8_t cmd);

void Transfer(SPIx_t* SPIx, uint8_t* tx, uint8_t* rx, uint8_t len);
void SPI_ReceiveMsg(SPIx_t* SPIx, uint8_t* buffer, uint8_t len);
void SPI_SendMsg(SPIx_t* SPIx, uint8_t* msg, uint8_t len);

void SPI_CloseSend(SPIx_Handler_t* SPI);
void SPI_CloseReceive(SPIx_Handler_t* SPI);

void SPI_HandleTx(SPIx_Handler_t * SPI);
void SPI_HandleRx(SPIx_Handler_t* SPI);

uint8_t SPI_ReceiveIT(SPIx_Handler_t* SPI, uint8_t* msg, uint32_t len);
uint8_t SPI_SendIT(SPIx_Handler_t* SPI, uint8_t* msg, uint32_t len);
void SPI_IRQ_Handling(SPIx_Handler_t* SPI);

void SPI_ITControl(uint8_t PeriInterrupt, uint8_t cmd);
void SPI_Control(SPIx_t* SPIx, uint8_t cmd);
#endif
