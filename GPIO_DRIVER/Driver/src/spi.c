/*
 * spi.c
 *  Created on: Aug 17, 2025
 *      Author: Avinash Kumar
 */


#include "spi.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_overan_error_interrupt_handle(SPI_Handle_t *pSPIHandle);

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t  EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else if(EnorDi == DISABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DIS();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DIS();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DIS();
		}
	}
}



void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t temp=0;

	//First configure the Device Mode
	temp=pSPIHandle->SPIConfig.SPI_DEVICEMODE<<2;

	if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_FULL_DUPLEX)
	{
		//Bidi Mode should be cleared
		temp &= ~(1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_HALF_DUPLEX)
	{
		//Bidi Mode should be SET
		temp |= (1<<15);

	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_RX_ONLY)
	{
		//Bidi Mode should be cleared
		//RX only Mode will be set
		temp &= ~(1<<15);
		temp |= (1<<10);

	}

	//3. Configure the SPI Serial Clock Speed(Buad Rate
	temp |= pSPIHandle->SPIConfig.SPI_SCLKSPEED <<3;

	//4. Configure the CPOL

	temp |= pSPIHandle->SPIConfig.SPI_CPOL <<1;

	//5. Configure the CPHASE

	temp |= pSPIHandle->SPIConfig.SPI_CPHASE <<0;

	pSPIHandle->pSPIx->CR1 = temp;

	//6. COnfigure the DFF
	temp=0;

	temp |= pSPIHandle->SPIConfig.SPI_DataSize<<3;

	pSPIHandle->pSPIx->CR2 = temp;

}
uint8_t SPI_Get_FLagStatus(SPI_RegDef_t *pSPIx,uint8_t FlagName)
{
	return ((pSPIx->SR & FlagName)!=0);
}
void SPI_ENControl(SPI_RegDef_t *pSPIx,uint8_t EnORDi)
{
	if(EnORDi==ENABLE)
	{
		pSPIx->CR1 |= (1<<6);

	}
	else
	{
		pSPIx->CR1 &= ~(1<<6);

	}
}
void SPI_Transmit(SPI_RegDef_t *pSPIx,uint8_t *Datap,uint32_t Len)
{
	while(Len>0)
	{
		while((pSPIx->SR & (1<<1))==0);

		if( ((pSPIx->CR2 & SPI_CR2_DS_MASK) >> 8) == SPI_DFF16BITS )
		{
			//16 bit Data MOde
			pSPIx->DR = *((uint16_t*)Datap);
			Len -= 2;
			Datap += 2;
		}
		else
		{
			//8 Bit Data Mode
			pSPIx->DR = *Datap;
			Datap++;
			Len--;
		}

	}
	while((pSPIx->SR & (1<<7))!=0);

}

void SPI_Receive(SPI_RegDef_t *pSPIx,uint8_t *Datap,uint32_t Len)
{
	while(Len>0)
	{

		if( ((pSPIx->CR2 & SPI_CR2_DS_MASK) >> 8) == SPI_DFF16BITS )
		{
			while((pSPIx->SR & (1<<1))==0);
			pSPIx->DR = 0xFFFF;
			//16 bit Data MOde
			while((pSPIx->SR & (1<<0))==0);
			*((uint16_t*)Datap)=pSPIx->DR;
			Len -= 2;
			Datap += 2;
		}
		else
		{
			while((pSPIx->SR & (1<<1))==0);
			pSPIx->DR = 0xFF;
			//16 bit Data MOde
			while((pSPIx->SR & (1<<0))==0);
			pSPIx->DR = 0xFF;
			//8 Bit Data Mode
			*Datap=(uint8_t)pSPIx->DR;
			Datap++;
			Len--;
		}

	}

}

uint8_t SPI_TransmitIT(SPI_Handle_t *pSPIHandle,uint8_t *Datap,uint32_t Len)
{
	uint8_t State=pSPIHandle->TxState;

	if(State != SPI_BUSY_IN_TX)
	{
		//1. Save TX Buffer Address and Length into Global Variable
		pSPIHandle->PTxBuffer=Datap;
		pSPIHandle->TxLen=Len;
		//2. Mark the SPI State Busy in Transmission so that no other code take over SAME SPI

		pSPIHandle->TxState=SPI_BUSY_IN_TX;
		//3. Enable TXEIE Bit to Get Interrupt whenever TXE Flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1<<7);  // 7 Pos SPI_CR2_TXEIE
		//4. Data Transmission Will Be handled by ISR Code

	}

	return State;
}

uint8_t SPI_ReceiveIT(SPI_Handle_t *pSPIHandle,uint8_t *Datap,uint32_t Len)
{
	uint8_t State=pSPIHandle->RxState;

	if(State != SPI_BUSY_IN_RX)
	{
		//1. Save TX Buffer Address and Length into Global Variable
		pSPIHandle->pRxBuffer=Datap;
		pSPIHandle->Rxlen=Len;
		//2. Mark the SPI State Busy in Transmission so that no other code take over SAME SPI

		pSPIHandle->RxState=SPI_BUSY_IN_RX;
		//3. Enable TXEIE Bit to Get Interrupt whenever TXE Flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1<<6);  // 6 Pos SPI_CR2_RXEIE
		//4. Data Transmission Will Be handled by ISR Code

	}

	return State;
}
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnORDi)
{
	if(EnORDi== ENABLE)
	{
		if(IRQNumber<=31)
		{
			//Program the ISER Register
			*NVIC_ISER |= (1<< IRQNumber);
		}
	}
	else
	{
		if(IRQNumber<=31)
		{
			//Program the ISER Register
			*NVIC_ICER |= (1<< IRQNumber);
		}
	}

}
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority)
{

}




void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint32_t temp1,temp2;
	//Lets Check for the TXE & TXEIE
	temp1 = pHandle->pSPIx->SR  & (1 <<SPI_SR_TXE_FLAG);
	temp2 = pHandle->pSPIx->CR2 & (1<<SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		//Handle TXE
		spi_txe_interrupt_handle(pHandle);
	}


	//Check for RXNE and RXEIE
	temp1 = pHandle->pSPIx->SR &  (1 <<SPI_SR_RXNE_FLAG);
	temp2 = pHandle->pSPIx->CR2 & (1<<SPI_CR2_RXEIE);

	if(temp1 && temp2)
	{
		//Handle RXE
		spi_rxe_interrupt_handle(pHandle);
	}

	// check for the Overran
	temp1= pHandle->pSPIx->SR & (1<<6);  // OVERRAN FLAG SPI_SR_OVERAN  6
	temp2=pHandle->pSPIx->CR2 & (1<<5);  // ERROR_ENABLE SPI_CR2_ERROR_ENABLE_IT 5

	if(temp1 && temp2 )
	{
		spi_overan_error_interrupt_handle(pHandle);
	}

}



static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if( ((pSPIHandle->pSPIx->CR2 & SPI_CR2_DS_MASK) >> 8) == SPI_DFF16BITS )
	{
		//16 bit Data MOde
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->PTxBuffer);
		pSPIHandle->TxLen -= 2;
		//(uint16_t*)pSPIHandle->PTxBuffer++;
		pSPIHandle->PTxBuffer += 2;
	}
	else
	{
		//8 Bit Data Mode
		pSPIHandle->pSPIx->DR = *(pSPIHandle->PTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->PTxBuffer++;
	}

	if(!pSPIHandle->TxLen)
	{
		//Close the SPI when the Application is Txlen is Zero
		pSPIHandle->pSPIx->CR2 &= ~(1 <<SPI_CR2_TXEIE);
		pSPIHandle->PTxBuffer=NULL;
		pSPIHandle->TxLen=0;
		pSPIHandle->TxState=SPI_READY;
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CPLT);

	}
}
static void spi_rxe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if( ((pSPIHandle->pSPIx->CR2 & SPI_CR2_DS_MASK) >> 8) == SPI_DFF16BITS )
	{
		pSPIHandle->pSPIx->DR = 0xFFFF;
		//16 bit Data MOde
		*((uint16_t*)pSPIHandle->pRxBuffer)=(uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->Rxlen -= 2;
		pSPIHandle->pRxBuffer += 2;
	}
	else
	{
		pSPIHandle->pSPIx->DR = 0xFF;
		//8 bit Data MOde
		pSPIHandle->pSPIx->DR = 0xFF;
		//8 Bit Data Mode
		*(pSPIHandle->pRxBuffer)=(uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->Rxlen--;
		pSPIHandle->pRxBuffer++;
	}

	if(!pSPIHandle->Rxlen)
	{
		pSPIHandle->pSPIx->CR2 &= ~(1 <<SPI_CR2_RXEIE);
		pSPIHandle->pRxBuffer=NULL;
		pSPIHandle->Rxlen=0;
		pSPIHandle->RxState=SPI_READY;
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CPLT);
	}



}
static void spi_overan_error_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp=0;
	if(pSPIHandle->TxState !=SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;

	}
	(void)temp;
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERROR);



}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{
	//This is Weak implementation

}
