#include "../headers/stm32fx.h"
#include "../headers/RCC.h"
#include "../headers/I2C.h"

void I2C_Init(I2Cx_Handler_t* I2C){
    if(I2C->I2Cx == I2C1){
        RCC->APB1ENR |= (1 << I2C1_EN);
    }else if(I2C->I2Cx == I2C2){
        RCC->APB1ENR |= (1 << I2C2_EN);
    }else {
        RCC->APB1ENR |= (1 << I2C3_EN);
    }
    uint32_t tempreg = 0;
    //Freq config
    tempreg = RCC_GetPCKVal1() / 1000000U;
    I2C->I2Cx->CR2 = (0x3F & tempreg);

    //OAR1 management
    tempreg = 0;
    tempreg |= (I2C->I2Cx_Config.I2C_ADDRESS << 1);
    tempreg |= (1 << 14);
    I2C->I2Cx->OAR1 = tempreg;

    //CCR caluclations
    tempreg = 0;
    uint16_t ccr = 0;
    if(I2C->I2Cx_Config.SPEED <= I2C_SCL_SPEED_SM){
       ccr = RCC_GetPCKVal1() / (2 * I2C->I2Cx_Config.SPEED);
       tempreg |= (ccr & 0xFFF); 
    }else{
        //FM mode
        tempreg |= (1 << 15);
        tempreg |= (I2C->I2Cx_Config.DUTY << 14);
        if(I2C->I2Cx_Config.DUTY == I2C_FM_DUTY_2){
           ccr = RCC_GetPCKVal1() / (3 * I2C->I2Cx_Config.SPEED);
        }else{
           ccr = RCC_GetPCKVal1() / (25 * I2C->I2Cx_Config.SPEED);
        }
        tempreg |= (ccr & 0xFFF); 
    }
    I2C->I2Cx->CCR = tempreg;

    tempreg = 0;
    if(I2C->I2Cx_Config.SPEED <= I2C_SCL_SPEED_SM){
        tempreg = (RCC_GetPCKVal1() / 1000000U) + 1;
    }else{
        tempreg = ((RCC_GetPCKVal1() * 300) / 1000000U) + 1;
    }
    I2C->I2Cx->TRISE = (tempreg & 0x3F);

    //DMA Capabilities
    if(I2C->I2Cx_Config.DMAtx == ENABLE || I2C->I2Cx_Config.DMArx == ENABLE){
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_DMAEN);
    }
}

void I2C_SendMsg(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr, uint8_t cmd){
    uint32_t dummy = 0;
    // enable start bit
    I2C->I2Cx->CR1 |= (1 << I2C_CR1_START);
    // clear sb bit by writing address
    while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_SB)));
    I2C->I2Cx->DR = (slaveAddr << 1) | 0;
    while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_ADDR)));
    dummy = I2C->I2Cx->SR1;
    dummy = I2C->I2Cx->SR2;

    while(len > 0){
        while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_TXE)));
        I2C->I2Cx->DR = *msg;
        ++msg;
        --len;
    }

    while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_TXE)));
    while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_BTF)));
    if(cmd == STOP_CONDITION){
        I2C->I2Cx->CR1 |= (1 << I2C_CR1_STOP);
    }
    (void)dummy;
}

void I2C_ReceiveMsg(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr, uint8_t cmd){

    uint32_t dummy = 0;
    // enable start bit
    I2C->I2Cx->CR1 |= (1 << I2C_CR1_START);
    // clear sb bit by writing address
    while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_SB)));
    I2C->I2Cx->DR = (slaveAddr << 1) | 1;
    
    if(len == 1){
        while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_ADDR)));
        dummy = I2C->I2Cx->SR1;
        dummy = I2C->I2Cx->SR2;

        I2C->I2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
        while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_RXNE)));
        if(cmd == STOP_CONDITION){
            I2C->I2Cx->CR1 |= (1 << I2C_CR1_STOP);
        }

        *msg = I2C->I2Cx->DR;

    }else {
        while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_ADDR)));
        dummy = I2C->I2Cx->SR1;
        dummy = I2C->I2Cx->SR2;

        while(len > 0){
            while(!(I2C->I2Cx->SR1 & (1 << I2C_SR1_RXNE)));

            if(len == 2){
                I2C->I2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
                if(cmd == STOP_CONDITION){
                    I2C->I2Cx->CR1 |= (1 << I2C_CR1_STOP);
                }
            }

            *msg = I2C->I2Cx->DR;
            ++msg;
            --len;
        }
    }
    I2C->I2Cx->CR1 |= (1 << I2C_CR1_ACK);
    (void)dummy;
}

uint8_t I2C_SendIT(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr){
    // we update communication of the new data only when communication is not in place
    uint8_t busyState = ((I2C->I2Cx->SR2 >> I2C_SR2_BUSY) & 0x1);

    if(busyState != BUSY_RXNE && busyState != BUSY_TXE){
        I2C->TxLen = len;
        I2C->Addr = slaveAddr;
        I2C->TxBuffer = msg;
        I2C->BusyState = BUSY_TXE;

        I2C->I2Cx->CR1 |= (1 << I2C_CR1_START);
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITEREN);
    }

    return busyState;

}

uint8_t I2C_ReceiveIT(I2Cx_Handler_t* I2C, uint8_t* msg, uint32_t len, uint8_t slaveAddr){
 // we update communication of the new data only when communication is not in place
    uint8_t busyState = ((I2C->I2Cx->SR2 >> I2C_SR2_BUSY) & 0x1);

    if(busyState != BUSY_RXNE && busyState != BUSY_TXE){
        I2C->RxLen = len;
        I2C->Addr = slaveAddr;
        I2C->RxBuffer = msg;
        I2C->RxSize = len;
        I2C->BusyState = BUSY_RXNE;

        I2C->I2Cx->CR1 |= (1 << I2C_CR1_START);

        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);
        I2C->I2Cx->CR2 |= (1 << I2C_CR2_ITEREN);
    }

    return busyState;
}

void CloseSend(I2Cx_Handler_t* I2C){
    I2C->I2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);
    I2C->I2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
    
    I2C->BusyState = I2C_READY;
    I2C->TxBuffer = 0;
}

void CloseReceive(I2Cx_Handler_t* I2C){
    I2C->I2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);
    I2C->I2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
    
    I2C->BusyState = I2C_READY;
    I2C->RxBuffer = 0;
    I2C->RxSize = 0;

}

void I2C_HandleInterruptTX(I2Cx_Handler_t* I2C){
    if(I2C->BusyState == BUSY_TXE){
        //ensure we are in txe state 
        if(I2C->TxLen > 0){
            I2C->I2Cx->DR = *(I2C->TxBuffer);
            I2C->TxLen--;
            I2C->TxBuffer++;
        }

    }
}

void I2C_HandleInterruptRXE(I2Cx_Handler_t* I2C){
    if(I2C->I2Cx->SR1 & (1 << I2C_SR1_RXNE)){
        if(I2C->RxSize == 1){
            *(I2C->RxBuffer) = I2C->I2Cx->DR;

            I2C->RxLen--;
        }
        if(I2C->RxSize > 1){
            if(I2C->RxLen == 2){
                I2C->I2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
            }
            *(I2C->RxBuffer) = I2C->I2Cx->DR;
            I2C->RxBuffer++;
            I2C->RxLen--;
        }

        if(I2C->RxLen == 0){
            I2C->I2Cx->CR1 |= (1 << I2C_CR1_STOP);
            CloseReceive(I2C);
        }
    }
}

void I2C_ITHandling(I2Cx_Handler_t* I2C){
    uint8_t temp1 = ((I2C->I2Cx->CR2 >> I2C_CR2_ITEVTEN) & 0x1);
    uint8_t temp2 = ((I2C->I2Cx->CR2 >> I2C_CR2_ITBUFEN) & 0x1);

    uint8_t temp3 = ((I2C->I2Cx->SR1 >> I2C_SR1_SB) & 0x1);

    //SB EVENT
    if(temp1 && temp3){
        if(I2C->BusyState == BUSY_TXE){
            // execute phase write address
            I2C->I2Cx->DR = (I2C->Addr << 1) | 0;
        }else {
            // execute phase read address
            I2C->I2Cx->DR = (I2C->Addr << 1) | 1;
        }
    }

    // ADDR EVENT
    temp3 = ((I2C->I2Cx->SR1 >> I2C_SR1_ADDR) & 0x1);
    if(temp1 && temp3){
        // address interrupt
        uint32_t dummy = I2C->I2Cx->SR1;
        dummy = I2C->I2Cx->SR2;
        (void)dummy;
    }

    // BTF EVENT
    temp3 = ((I2C->I2Cx->SR1 >> I2C_SR1_BTF) & 0x1);
    if(temp1 && temp3){
        if(I2C->BusyState == BUSY_TXE){
            if(I2C->TxLen == 0){
                if(I2C->I2Cx->SR1 & (1 << I2C_SR1_TXE)){
                    //generate stop
                    I2C->I2Cx->CR1 |= (1 << I2C_CR1_STOP);
                    CloseSend(I2C);
                }
            }
        }
    }
    temp3 = ((I2C->I2Cx->SR1 >> I2C_SR1_TXE) & 0x1);
    if(temp1 && temp2 && temp3){
        I2C_HandleInterruptTX(I2C);
    }

    temp3 = ((I2C->I2Cx->SR1 >> I2C_SR1_RXNE) & 0x1);
    if(temp1 && temp2 && temp3){
        I2C_HandleInterruptRXE(I2C);
    }
}

void I2C_ITControl(uint8_t PeriInterrupt, uint8_t cmd){
    if(cmd == ENABLE){
        if(PeriInterrupt <= 31){
            *NVIC_ISER0 |= (1 << PeriInterrupt );
        }else if(PeriInterrupt >= 32 && PeriInterrupt <= 63){
            *NVIC_ISER1 |= (1 << (PeriInterrupt % 32));
        }else{
            *NVIC_ISER2 |= (1 << (PeriInterrupt % 64));
        }
    }else{
        if(PeriInterrupt <= 31){
            *NVIC_ISER0 &= ~(1 << PeriInterrupt );
        }else if(PeriInterrupt >= 32 && PeriInterrupt <= 63){
            *NVIC_ISER1 &= ~(1 << (PeriInterrupt % 32));
        }else{
            *NVIC_ISER2 &= ~(1 << (PeriInterrupt % 64));
        }
    }
}

void ManageAck(I2Cx_t* I2C, uint8_t cmd){
    if(cmd == ENABLE){
        I2C->CR1 |= (1 << I2C_CR1_ACK);
    }else {
        I2C->CR1 &= ~(1 << I2C_CR1_ACK);
    }

}

void I2C_Control(I2Cx_t* I2C, uint8_t cmd){
    if(cmd == ENABLE){
        I2C->CR1 |= (1 << I2C_CR1_PE);
    }else{
        I2C->CR1 &= ~(1 << I2C_CR1_PE);
    }
}
