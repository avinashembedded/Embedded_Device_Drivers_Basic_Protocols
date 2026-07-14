/*
 * spi.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Avinash Kumar
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <stm32g0xx.h>


typedef struct
{
  uint8_t SPI_DEVICEMODE;
  uint8_t SPI_BusConfig;
  uint8_t SPI_SCLKSPEED;
  uint8_t SPI_DataSize;
  uint8_t SPI_CPOL;
  uint8_t SPI_CPHASE;
  uint8_t SPI_SSM;
} SPI_Config_t;


typedef struct
{
	SPI_RegDef_t  *pSPIx;
	SPI_Config_t   SPIConfig;
	uint8_t 	   *PTxBuffer;
	uint8_t 		*pRxBuffer;
	uint32_t 		TxLen;
	uint32_t 		Rxlen;    /// Length of Receive Length
	uint8_t 		TxState;  // To Store Tx State
	uint8_t 		RxState;   // To Store Rx State
}SPI_Handle_t;


#define SPI_READY			0
#define SPI_BUSY_IN_RX		1
#define SPI_BUSY_IN_TX		2


#define SPI_EVENT_TX_CPLT	1
#define SPI_EVENT_RX_CPLT	2
#define SPI_EVENT_OVR_ERROR	3

/*
 * @SPI_DEVICEMODE
 */
#define SPI_DEVICE_MASTER_MODE			1
#define SPI_DEVICE_SLAVE_MODE			0

/*
 * @SPI_BusConfig
 */
#define SPI_FULL_DUPLEX		1
#define SPI_HALF_DUPLEX		2
#define SPI_TX_ONLY			3
#define SPI_RX_ONLY			4


/*
 * @SPI_SSM
 */

#define SPI_SSM_HW			0
#define SPI_SSM_SW			1

/*
 * @SPI_Buad_Rate
 */

#define 	SPI_SCLK_SPEED_DIV2			0
#define		SPI_SCLK_SPEED_DIV4			1
#define 	SPI_SCLK_SPEED_DIV8			2
#define		SPI_SCLK_SPEED_DIV16		3
#define 	SPI_SCLK_SPEED_DIV32		4
#define		SPI_SCLK_SPEED_DIV64		5
#define 	SPI_SCLK_SPEED_DIV2128		6
#define		SPI_SCLK_SPEED_DIV2256		7

#define __weak __attribute__((weak))

#define SPI_DFF8BITS		7
#define SPI_DFF16BITS		15


#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0

#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0


#define SPI_SR_TXE_FLAG			1
#define SPI_SR_RXNE_FLAG       	0
#define SPI_SR_CBUSY_FLAG		7

#define SPI_CR2_TXEIE		7
#define SPI_CR2_RXEIE		6

#define SPI_CR2_DS_MASK   (0xF << 8)

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t  EnorDi);
void SPI_ENControl(SPI_RegDef_t *pSPIx,uint8_t EnORDi);
/*
 * Init and Deinit SPI Setup
 */

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


void SPI_Transmit(SPI_RegDef_t *pSPIx,uint8_t *Datap,uint32_t Len);
void SPI_Receive(SPI_RegDef_t *pSPIx,uint8_t *Datap,uint32_t size);

uint8_t SPI_TransmitIT(SPI_Handle_t *pSPIHandle,uint8_t *Datap,uint32_t Len);
uint8_t SPI_ReceiveIT(SPI_Handle_t *pSPIHandle,uint8_t *Datap,uint32_t Len);


void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnORDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);


void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv);

#endif /* INC_SPI_H_ */
