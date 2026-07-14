/*
 * stm32f0xx_rcc_driver.c
 *
 *  Created on: Jul 3, 2026
 *      Author: shiva
 */
#include "stm32f0xx_rcc_driver.h"

uint32_t RCC_GetPLLOutputClock(void)
{
	return 0;
}


uint16_t AHB_Prescaler[8]={2,4,8,16,64,128,256};
uint8_t APB_Prescaler[4]={2,4,8,16};

uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;
	uint8_t clksrc,temp,ahbp,apb;

	clksrc = ((RCC->CFGR >>2 ) & 0x03);

	if(clksrc==0)
	{
		SystemClk=16000000;

	}
	else if(clksrc==1)
	{
		SystemClk=8000000;
	}
	else if(clksrc==2)
	{
		SystemClk=RCC_GetPLLOutputClock();
	}

	temp=((RCC->CFGR>>4)&0xF);

	if(temp<8)
	{
		ahbp=1;
	}
	else
	{
		ahbp=AHB_Prescaler[temp-8];
	}

	temp=((RCC->CFGR>>10)&0x7);

	if(temp<4)
	{
		apb=1;
	}
	else
	{
		apb=APB_Prescaler[temp-4];
	}

	pclk1= (SystemClk/ahbp)/apb;

	return pclk1;
}
