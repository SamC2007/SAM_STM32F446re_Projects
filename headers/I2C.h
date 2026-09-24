#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C1 ((I2Cx_t*)(0x40005400))
#define I2C2 ((I2Cx_t*)(0x40005800))
#define I2C3 ((I2Cx_t*)(0x40005C00))

typedef struct {
    uint32_t SPEED;
    uint8_t ACK;
    uint8_t I2C_ADDRESS;
    uint8_t DUTY;
    uint8_t DMAtx;
    uint8_t DMArx;
}I2Cx_Config_t;

typedef struct{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
    uint32_t FLTR;
}I2Cx_t;

typedef struct {
    I2Cx_Config_t I2Cx_Config;
    I2Cx_t* I2Cx;
    uint8_t Addr;
    uint8_t BusyState;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t RxSize;
    uint8_t* TxBuffer;
    uint8_t* RxBuffer;
}I2Cx_Handler_t;


//CR1
#define I2C_CR1_PE							0
#define I2C_CR1_SMBUS						1
#define I2C_CR1_SMBTYPE						3
#define I2C_CR1_ENARP						4
#define I2C_CR1_ENPEC						5
#define I2C_CR1_ENGC						6
#define I2C_CR1_NOSTRETCH					7
#define I2C_CR1_START						8
#define I2C_CR1_STOP						9
#define I2C_CR1_ACK							10
#define I2C_CR1_POS							11
#define I2C_CR1_PEC							12
#define I2C_CR1_ALERT						13

#define I2C_CR1_SWRTS						15
//CR2
#define I2C_CR2_FREQ						0
#define I2C_CR2_ITEREN						8
#define I2C_CR2_ITEVTEN						9
#define I2C_CR2_ITBUFEN						10
#define I2C_CR2_DMAEN						11
#define I2C_CR1_LAST						12
//SR1
#define I2C_SR1_SB							0
#define I2C_SR1_ADDR						1
#define I2C_SR1_BTF							2
#define I2C_SR1_ADD10						3
#define I2C_SR1_STOPF						4
#define I2C_SR1_RXNE						6
#define I2C_SR1_TXE							7
#define I2C_SR1_BERR						8
#define I2C_SR1_ARLO						9
#define I2C_SR1_AF							10
#define I2C_SR1_OVR							11
#define I2C_SR1_PECERR						12
#define I2C_SR1_TIMEOUT						14
#define I2C_SR1_SMBALERT					15
// SR2
#define I2C_SR2_MSL							0
#define I2C_SR2_BUSY						1
#define I2C_SR2_TRA							2
#define I2C_SR2_GENCALL						4
#define I2C_SR2_SMBDEFAULT					5
#define I2C_SR2_SMBHOST						6
#define I2C_SR2_DUALF						7
#define I2C_SR2_PEC							8
// CCR
#define I2C_CCR								0
#define I2C_CCR_DUTY						14
#define I2C_CCR_FS							15

#define I2C_SCL_SPEED_SM		100000
#define I2C_SCL_SPEED_FM2K		200000
#define I2C_SCL_SPEED_FM4K		400000

/*
 * I2C Duty Cycle
 */
#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1

//define busy state
#define I2C_READY 0
#define BUSY_TXE 1
#define BUSY_RXNE 2

//Define STOP bits
#define STOP_CONDITION 10
#define NO_STOP_CONDITION 11


void I2C_Init(I2Cx_Handler_t* I2C);
void I2C_Control(I2Cx_t* I2C, uint8_t cmd);
void I2C_SendMsg(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr, uint8_t cmd);
void I2C_ReceiveMsg(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr, uint8_t cmd);

uint8_t I2C_SendIT(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr);
uint8_t I2C_ReceiveIT(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr);

void ManageAck(I2Cx_t* I2C, uint8_t cmd);
void CloseReceive(I2Cx_Handler_t* I2C);
void CloseSend(I2Cx_Handler_t* I2C);
void I2C_ITHandling(I2Cx_Handler_t* I2C);
void I2C_HandleInterruptTX(I2Cx_Handler_t* I2C);
void I2C_HandleInterruptRXE(I2Cx_Handler_t* I2C);
void I2C_ITControl(uint8_t PeriInterrupt, uint8_t cmd);

#endif
