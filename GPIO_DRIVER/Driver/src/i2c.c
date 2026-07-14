/*
 * i2c.c
 *
 *  Created on: Jul 8, 2026
 *      Author: shiva
 */

#include "i2c.h"
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr,uint8_t Len);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr,uint8_t Len);
static void I2C_MasterHandleTXISInterrupt(I2C_Handle_t *pHandle);

static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pHandle);
static void I2C_MasterHandleTCInterrupt(I2C_Handle_t *pHandle);
static void I2C_MasterHandleSTOPInterrupt(I2C_Handle_t *pHandle);
static void I2C_MasterHandleNACKInterrupt(I2C_Handle_t *pHandle);


void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t  EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}
	}
	else if(EnorDi == DISABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DIS();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_DIS();
		}
	}
}

void I2C_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnORDi)
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

void I2C_ENControl(I2C_RegDef_t *pI2Cx,uint8_t EnORDi)
{
	if(EnORDi==ENABLE)
	{
		pI2Cx->I2C_CR1 |= (1<<I2C_CR1_PERIPH_EN);

	}
	else
	{
		pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_PERIPH_EN);

	}
}
void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority)
{

}

uint8_t I2C_Get_FLagStatus(I2C_RegDef_t *pI2Cx,uint8_t FlagName)
{
	return ((pI2Cx->I2C_ISR & FlagName)!=0);
}

/*
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg=0;

	tempreg |= (pI2CHandle->I2C_Config.I2C_AckControl<<10);

	pI2CHandle->pI2Cx->I2C_CR1 = tempreg;

	temp=0;

	tempreg=RCC_GetPCLK1Value()/100000;   // SYSCLK will be 16 Mhz

	pI2CHandle->pI2Cx->I2C_CR2 = (tempreg & 0x3F);

	//Program the Device own Address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress <<1;
	tempreg |= (1<<14);
	pI2CHandle->pI2Cx->I2C_OAR1 = tempreg ;

	tempreg=0;

	//CCR Calculations
	uint16_t ccr_value=0;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed==I2C_SCL_SPEED_SM)
	{
		// Mode is Standard
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= ccr_value & 0xFFF;

	}
	else
	{
		//Mode is fast mode
		tempreg |= (1<<15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle<<14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{

			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
			tempreg |= ccr_value & 0xFFF;
		}
		else
		{
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
			tempreg |= ccr_value & 0xFFF;
		}
	}

	pI2CHandle->pI2Cx->CCR = tempreg;
}
*/
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;

    /*---------------------------------------------------
      Disable I2C before configuration
    ---------------------------------------------------*/
    pI2CHandle->pI2Cx->I2C_CR1 &= ~(1U << 0);

    /*---------------------------------------------------
      Configure Own Address
    ---------------------------------------------------*/

    tempreg = 0;

    tempreg |= (pI2CHandle->I2C_Config.I2C_DeviceAddress << 1);

    pI2CHandle->pI2Cx->I2C_OAR1 = tempreg;

    /* Enable Own Address */

    pI2CHandle->pI2Cx->I2C_OAR1 |= (1U << 15);

    /*---------------------------------------------------
      Configure Timing Register
    ---------------------------------------------------*/

    if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM)
    {
        /*
            Example value

            I2C Clock = 16 MHz
            Bus Speed = 100 kHz
        */

        pI2CHandle->pI2Cx->I2C_TIMINGR = I2C_TIMING_16MHZ_100KHZ;
    }
    else if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_FM4K)
    {
        /*
            Example value

            I2C Clock =16 MHz
            Bus Speed =400 kHz
        */

        pI2CHandle->pI2Cx->I2C_TIMINGR = I2C_TIMING_16MHZ_400KHZ;
    }

    /*---------------------------------------------------
      Enable Peripheral
    ---------------------------------------------------*/

//    pI2CHandle->pI2Cx->CR1 |= (1U << 0);
}
//void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uin32_t Len,uint8_t SlaveAddr)
//{
//	//1. Generate Start Condition
//	I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);
//	//Check SB Flag
//	while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB));
//
//	// Send Addr of Slave with r/w bit
//	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx);
//
//	//4.
//	while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR));
//
//	while(Len>0)
//	{
//		while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,I2C_ISR_TXE));
//		pI2CHandle->pI2Cx->I2C_TXDR = *pTxBuffer;
//		pTxBuffer++;
//		Len--;
//
//	}
//
//	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
//}

//
//static void I2C_Generate_Start_Condition(I2C_RegDef_t *pI2Cx)
//{
//	pI2Cx->I2C_CR1 |= (1 <<I2C_CR2_START);
//
//}
//
//static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr)
//{
//	SlaveAddr = SlaveAddr <<1;
//	SlaveAddr &= ~(1);    // SlaveAddr + r/w bit
//	pI2Cx->I2C_TXDR = SlaveAddr;
//}
//static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr)
//{
//	pI2Cx->I2C_CR1 |= (1 <<I2C_CR2_STOP);
//}


void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint32_t Len,uint8_t SlaveAddr)
{
    /* Configure Address + NBYTES + START */

	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr,Len);

    while(Len > 0)
    {
        /* Wait until TXDR is empty */

        //while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,(1 << I2C_ISR_TXIS)));
        while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,(1<<I2C_ISR_TXE)));

        pI2CHandle->pI2Cx->I2C_TXDR = *pTxBuffer;

        pTxBuffer++;

        Len--;
    }

    /* Wait until STOP is generated */

    while(!(pI2CHandle->pI2Cx->I2C_ISR & (1 << 5)));   // STOPF

    /* Clear STOP Flag */

    pI2CHandle->pI2Cx->I2C_ICR |= (1 << 5);            // STOPCF
}


static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr,uint8_t Len)
{
    uint32_t temp = 0;

    temp |= (SlaveAddr << 1);          // SADD[7:1]

    temp |= (Len << I2C_CR2_NBYTES);   // Number of bytes

    // Write Operation
    temp &= ~(1 << I2C_CR2_RD_WRN);

    // Auto STOP after last byte
    temp |= (1 << I2C_CR2_AUTOEND);

    // Generate START
    temp |= (1 << I2C_CR2_START);

    pI2Cx->I2C_CR2 = temp;
}
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr,uint8_t Len)
{
    uint32_t temp = 0;

    temp |= (SlaveAddr << 1);          // SADD[7:1]

    temp |= (Len << I2C_CR2_NBYTES);   // Number of bytes

    // Write Operation
    temp |= (1 << I2C_CR2_RD_WRN);

    // Auto STOP after last byte
    temp |= (1 << I2C_CR2_AUTOEND);

    // Generate START
    temp |= (1 << I2C_CR2_START);

    pI2Cx->I2C_CR2 = temp;
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint32_t Len,uint8_t SlaveAddr)
{
	/* Configure Address + NBYTES + START */

	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,SlaveAddr,Len);

	while(Len > 0)
	{
		/* Wait until TXDR is empty */

		//while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,(1 << I2C_ISR_TXIS)));
		while(!I2C_Get_FLagStatus(pI2CHandle->pI2Cx,(1<<I2C_ISR_RXNE)));

		*pRxBuffer=pI2CHandle->pI2Cx->I2C_RXDR;

		pRxBuffer++;

		Len--;
	}

	/* Wait until STOP is generated */

	while(!(pI2CHandle->pI2Cx->I2C_ISR & (1 << 5)));   // STOPF

	/* Clear STOP Flag */

	pI2CHandle->pI2Cx->I2C_ICR |= (1 << 5);            // STOPCF

}


uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint32_t Len,uint8_t SlaveAddr,uint8_t Sr)
{
	uint8_t busystate = pI2CHandle->TxRxState;
	uint32_t temp;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		//pI2CHandle->pI2Cx->I2C_CR2 |= (1 << I2C_CR2_START);

        /* Configure CR2 */
	    temp |= (SlaveAddr << 1);          // SADD[7:1]
	    temp |= (Len << I2C_CR2_NBYTES);   // Number of bytes
	    // Write Operation
	    temp |= (1 << I2C_CR2_RD_WRN);
	    // Auto STOP after last byte
	    temp |= (1 << I2C_CR2_AUTOEND);
	    pI2CHandle->pI2Cx->I2C_CR2 = temp;

        /* Enable Interrupts */

        /* TXIS Interrupt */
        pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_TXEI);

        /* Transfer Complete */
        pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_TCIE);

        /* STOP Detection */
        pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_STOPIE);

        /* NACK Detection */
        pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_NACKIE);

        /* Error Interrupt */
        //pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_ERRIE);

        pI2CHandle->pI2Cx->I2C_CR2 |= (1 << I2C_CR2_START);


	}

	return busystate;

}

uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint32_t Len,uint8_t SlaveAddr,uint8_t Sr)
{
	uint8_t busystate = pI2CHandle->TxRxState;
    uint32_t temp = 0;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxLen = Len; //Rxsize is used in the ISR code to manage the data reception
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

	    temp |= (SlaveAddr << 1);          // SADD[7:1]
	    temp |= (Len << I2C_CR2_NBYTES);   // Number of bytes
	    // Write Operation
	    temp |= (1 << I2C_CR2_RD_WRN);
	    // Auto STOP after last byte
	    temp |= (1 << I2C_CR2_AUTOEND);


	    pI2CHandle->pI2Cx->I2C_CR2 = temp;
		/* Enable Interrupts */

		/* RXNE Interrupt */
		pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_RXEI);

		/* Transfer Complete */
		pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_TCIE);

		/* STOP Detection */
		pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_STOPIE);

		/* NACK Detection */
		pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_NACKIE);

		/* Error Interrupt */
		//pI2CHandle->pI2Cx->I2C_CR1 |= (1 << I2C_CR1_ERRIE);

		pI2CHandle->pI2Cx->I2C_CR2 |= (1 <<I2C_CR2_START);
	}

	return busystate;

}




void I2C_IRQHandling(I2C_Handle_t *pHandle)
{
    uint32_t isr = pHandle->pI2Cx->I2C_ISR;
    uint32_t cr1 = pHandle->pI2Cx->I2C_CR1;

    /*---------------------- TXIS ----------------------*/

    if((isr & I2C_ISR_TXIS) &&
       (cr1 & I2C_CR1_TXEI))
    {
        I2C_MasterHandleTXISInterrupt(pHandle);
    }

    /*---------------------- RXNE ----------------------*/

    if((isr & I2C_ISR_RXNE) &&
       (cr1 & I2C_CR1_RXEI))
    {
        I2C_MasterHandleRXNEInterrupt(pHandle);
    }

    /*---------------------- TC ----------------------*/

    if((isr & I2C_ISR_TC) &&
       (cr1 & I2C_CR1_TCIE))
    {
        I2C_MasterHandleTCInterrupt(pHandle);
    }

    /*---------------------- STOP ----------------------*/  //SLAVE MODE

    if((isr & I2C_ISR_STOPF) &&
       (cr1 & I2C_CR1_STOPIE))
    {
        I2C_MasterHandleSTOPInterrupt(pHandle);
    }

    /*---------------------- NACK ----------------------*/

    if((isr & I2C_ISR_NACKF) &&
       (cr1 & I2C_CR1_NACKIE))
    {
        I2C_MasterHandleNACKInterrupt(pHandle);
    }

    /*---------------------- Errors ----------------------*/

//    if(cr1 & I2C_CR1_ERRIE)
//    {
//        if(isr & I2C_ISR_BERR)
//        {
//            // Bus Error
//        }
//
//        if(isr & I2C_ISR_ARLO)
//        {
//            // Arbitration Lost
//        }
//
//        if(isr & I2C_ISR_OVR)
//        {
//            // Overrun
//        }
//    }
}

static void I2C_MasterHandleTXISInterrupt(I2C_Handle_t *pHandle)
{
    pHandle->pI2Cx->I2C_TXDR = *(pHandle->pTxBuffer);

    pHandle->pTxBuffer++;

    pHandle->TxLen--;
}

static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pHandle)
{
    *(pHandle->pRxBuffer) = pHandle->pI2Cx->I2C_RXDR;

    pHandle->pRxBuffer++;

    pHandle->RxLen--;
}

static void I2C_MasterHandleTCInterrupt(I2C_Handle_t *pHandle)
{
    if(pHandle->Sr == I2C_DISABLE_SR)
    {
        /* Generate STOP */

        pHandle->pI2Cx->I2C_CR2 |= (1<<I2C_CR2_STOP);
    }
    else
    {
        /* Application will generate another START */
    }
}


static void I2C_MasterHandleSTOPInterrupt(I2C_Handle_t *pHandle)
{
    /* Clear STOP flag */

    pHandle->pI2Cx->I2C_ICR |= (1<<5);

    /* Disable interrupts */

    pHandle->pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_TXEI);
    pHandle->pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_RXEI);
    pHandle->pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_TCIE);
    pHandle->pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_STOPIE);
    pHandle->pI2Cx->I2C_CR1 &= ~(1<<I2C_CR1_NACKIE);

    pHandle->TxRxState = I2C_READY;

    pHandle->TxLen = 0;

    pHandle->RxLen = 0;

    pHandle->pTxBuffer = NULL;

    pHandle->pRxBuffer = NULL;

    I2C_ApplicationEventCallback(pHandle,I2C_EVENT_TRANSFER_COMPLETE);
}

static void I2C_MasterHandleNACKInterrupt(I2C_Handle_t *pHandle)
{
    /* Clear NACK */

    pHandle->pI2Cx->I2C_ICR |= (1<<4);

    /* Generate STOP */

    pHandle->pI2Cx->I2C_CR2 |= (1<<I2C_CR2_STOP);

    I2C_ApplicationEventCallback(pHandle,I2C_ERROR_NACK);
}
