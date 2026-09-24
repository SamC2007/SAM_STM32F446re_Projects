#include "../headers/stm32fx.h"
#include "../headers/SPI.h"
//functions

void SPI_Init(SPIx_Handler_t* SPI){
    //turn on SPI clock
    if(SPI->SPIx == SPI1){
        RCC->APB2ENR |= (1 << SPI1_EN);
    }else if(SPI->SPIx == SPI2){
        RCC->APB1ENR |= (1 << SPI2_EN);
    }else if(SPI->SPIx == SPI3){
        RCC->APB1ENR |= (1 << SPI3_EN);
    }else{
       RCC->APB2ENR |= (1 << SPI4_EN); 
    }
    uint32_t tempreg = 0;
    if(SPI->SPIx_Config.MODE == FULL_DUPLEX){
        tempreg &= ~(1 << SPI_CR1_BIDI_MODE);
    }else if(SPI->SPIx_Config.MODE == HALF_DUPLEX){
        tempreg |= ( 1 << SPI_CR1_BIDI_MODE);
    }else if(SPI->SPIx_Config.MODE == SIMPLEX){
        tempreg |= (1 << SPI_CR1_BIDI_MODE);
        tempreg |= (1 << SPI_CR1_RXONLY);
    }
    //CR1
    tempreg |= (SPI->SPIx_Config.CPHA << SPI_CR1_CPHA);
    tempreg |= (SPI->SPIx_Config.CPOL << SPI_CR1_CPOL);
    tempreg |= (SPI->SPIx_Config.BR << SPI_CR1_BR);
    tempreg |= (SPI->SPIx_Config.DFF << SPI_CR1_DFF);
    tempreg |= (SPI->SPIx_Config.SSM << SPI_CR1_SSM);
    tempreg |= (SPI->SPIx_Config.MSTR << SPI_CR1_MSTR);
    
    SPI->SPIx->CR1 = tempreg; 
}
void SSI_Config(SPIx_t* SPIx, uint8_t cmd){
   if(cmd == ENABLE){
        SPIx->CR1 |= (1 << SPI_CR1_SSI);
   }else {
        SPIx->CR1 &= ~(1 << SPI_CR1_SSI);
   }
}
void SSOE_Config(SPIx_t* SPIx, uint8_t cmd){
    if(cmd == ENABLE){ 
        SPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }else{
        SPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}
void Transfer(SPIx_t* SPIx, uint8_t* tx, uint8_t* rx, uint8_t len){
    while(len > 0){
		while(!(SPIx->SR & (1 << SPI_SR_TXE)));
		SPIx->DR = *tx;
        ++tx;
		while(!(SPIx->SR & (1 << SPI_SR_RXNE)));
		*rx = SPIx->DR;
        ++rx;
        --len;
	}
    // hang while SPI is not busy
	while(SPIx->SR & SPI_SR_BSY);

}
void SPI_ReceiveMsg(SPIx_t* SPIx, uint8_t* buffer, uint8_t len){
    while(len > 0){
		while(!(SPIx->SR & (1 << SPI_SR_RXNE)));
		*buffer = SPIx->DR;
        ++buffer;
        --len;
	}
	while(SPIx->SR & SPI_SR_BSY);

}
void SPI_SendMsg(SPIx_t* SPIx, uint8_t* msg, uint8_t len){
	while(len > 0){
		while(!(SPIx->SR & (1 << SPI_SR_TXE)));
		SPIx->DR = *msg;
        ++msg;
        --len;

	}
	while(SPIx->SR & SPI_SR_BSY);
}

uint8_t SPI_ReceiveIT(SPIx_Handler_t* SPI, uint8_t* msg, uint32_t len){
    uint8_t bsy = ((SPI->SPIx->SR >> SPI_SR_BSY) >> 0x1);
    if(bsy == SPI_FREE){
       SPI->RxLen = len;
       SPI->RxBuffer = msg;
       SPI->BusyState = SPI_BSY_RX;

       SPI->SPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
    }
    return bsy;
}
uint8_t SPI_SendIT(SPIx_Handler_t* SPI, uint8_t* msg, uint32_t len){
    uint8_t bsy = ((SPI->SPIx->SR >> SPI_SR_BSY) >> 0x1);
    if(bsy == SPI_FREE){
       SPI->TxLen = len;
       SPI->TxBuffer = msg;
       SPI->BusyState = SPI_BSY_TX;

       SPI->SPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    }
    return bsy;
}

void SPI_CloseSend(SPIx_Handler_t* SPI){
    SPI->TxLen = 0;
    SPI->TxBuffer = 0;
    SPI->BusyState = SPI_FREE;

    SPI->SPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
}
void SPI_CloseReceive(SPIx_Handler_t* SPI){
    SPI->RxLen = 0;
    SPI->RxBuffer = 0;
    SPI->BusyState = SPI_FREE;

    SPI->SPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
}

void SPI_HandleTx(SPIx_Handler_t * SPI){
    SPI->SPIx->DR = *(SPI->TxBuffer);
    SPI->TxLen--;
    if(SPI->TxLen == 0){
       SPI_CloseSend(SPI);
    } else {
        SPI->TxBuffer++;
    }

}
void SPI_HandleRx(SPIx_Handler_t* SPI){
    *(SPI->RxBuffer) = SPI->SPIx->DR;
    SPI->RxLen--;
    if(SPI->RxLen == 0){
        SPI_CloseReceive(SPI);
    }else {
        SPI->RxBuffer++;
    }
}

void SPI_IRQ_Handling(SPIx_Handler_t* SPI){
    uint8_t temp1 = ((SPI->SPIx->CR2 >> SPI_CR2_TXEIE) & 0x1);

    uint8_t temp2 = ((SPI->SPIx->SR >> SPI_SR_TXE) & 0x1);
    
    if(temp2 && temp1){
        SPI_HandleTx(SPI);
    } 
    temp1 = ((SPI->SPIx->CR2 >> SPI_CR2_RXNEIE) & 0x1);
    temp2 = ((SPI->SPIx->SR >> SPI_SR_RXNE) & 0x1);

    if(temp1 && temp2){
        SPI_HandleRx(SPI);
    }
}

void SPI_ITControl(uint8_t PeriInterrupt, uint8_t cmd){
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

void SPI_Control(SPIx_t* SPIx, uint8_t cmd){
    if(cmd == ENABLE){
        SPIx->CR1 |= (1 << SPI_CR1_SPE);
    }else {
	    SPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	    print("SPI DISABLED\r\n");
    }
}
