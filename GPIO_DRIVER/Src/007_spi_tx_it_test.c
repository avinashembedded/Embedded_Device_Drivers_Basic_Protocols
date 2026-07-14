/*
 * 007_spi_tx_it_test.c
 *
 *  Created on: Jul 7, 2026
 *      Author: shiva
 */

#include "spi.h"
#include "stm32g0xx.h"
#include "string.h"
GPIO_Handle_t SPI_GPIO;
SPI_Handle_t SPI1_Handle;

void SPI1_GPIOInit(void)
{
	SPI_GPIO.pGPIOx = GPIOA;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_1;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
	SPI_GPIO.GPIO_PinCOnfig.GPIO_PinALtFunMode = AF0;

	GPIO_PeriClockControl(GPIOA,ENABLE);
    // PA1 -> SCLK
    GPIO_Init(&SPI_GPIO);

    // PA2 -> MOSI
    SPI_GPIO.GPIO_PinCOnfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&SPI_GPIO);
    //PA3->MISO
    SPI_GPIO.GPIO_PinCOnfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&SPI_GPIO);

}

void SPI_INIT(void)
{
	SPI1_Handle.pSPIx=SPI1;
	SPI1_Handle.SPIConfig.SPI_DEVICEMODE=SPI_DEVICE_MASTER_MODE;
	SPI1_Handle.SPIConfig.SPI_BusConfig=SPI_FULL_DUPLEX;
	SPI1_Handle.SPIConfig.SPI_CPOL=SPI_CPOL_HIGH;
	SPI1_Handle.SPIConfig.SPI_CPHASE=SPI_CPHA_HIGH;
	SPI1_Handle.SPIConfig.SPI_DataSize=SPI_DFF8BITS;
	SPI1_Handle.SPIConfig.SPI_SCLKSPEED=SPI_SCLK_SPEED_DIV4;
	SPI1_Handle.SPIConfig.SPI_SSM=SPI_SSM_SW;


	SPI_Init(&SPI1_Handle);
	//SPI1_Handle.pSPIx->CR1 |= (1 <<6);  //Enable the SPI Peripheral
	SPI_ENControl(SPI1,ENABLE);

}
uint8_t count=0;

int main()
{
	//char user_data[]="Hello World";
	uint8_t Data[11]={0x01,0x02,0x03,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB};
	SPI1_GPIOInit();
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_INIT();
	SPI_IRQInterruptConfig(SPI1_IRQn,ENABLE);
	//SPI_IRQPriorityConfig(SPI1_IRQn,32);

	//SPI_Transmit(SPI1,(uint8_t *)user_data,strlen(user_data));
	SPI_TransmitIT(&SPI1_Handle,Data,11);

	while(1);
	return 0;
}


void SPI1_IRQHandler(void)
{

	SPI_IRQHandling(&SPI1_Handle);
	count++;
	if(count==10)
	{
		count=0;
	}

}
