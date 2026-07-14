/*
 * gpio.c
 *
 *  Created on: Aug 14, 2025
 *      Author: Avinash Kumar
 */


#include <stm32g0xx.h>
#include "gpio.h"


/*
 * Peripheral clock Setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t  EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx== GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx== GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx== GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx== GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx== GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx== GPIOF)
		{
			GPIOF_PCLK_EN();
		}


	}
	else
	{
		if(EnorDi == DISABLE)
		{
			if(pGPIOx==GPIOA)
			{
				GPIOA_PCLK_DIS();
			}
			else if(pGPIOx==GPIOB)
			{
				GPIOB_PCLK_DIS();
			}
			else if(pGPIOx==GPIOC)
			{
				GPIOC_PCLK_DIS();
			}
			else if(pGPIOx==GPIOD)
			{
				GPIOD_PCLK_DIS();
			}
			else if(pGPIOx==GPIOE)
			{
				GPIOE_PCLK_DIS();
			}
			else if(pGPIOx==GPIOF)
			{
				GPIOF_PCLK_DIS();
			}
		}
	}

}


/*
 * Init and Deinit GPIO Setup
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;  //temp register

	// 1. Configure mode of the GPIO pins
	if(pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode  <= GPIO_MODE_ANALOG)
	{
		//For the non-interrupt
		temp = (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode  << (2* pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
		//pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));  // CLearing
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2* pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));  // CLearing
		pGPIOHandle->pGPIOx->MODER |= temp;  // setting
	}
	else
	{
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
		if(pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. configure the FTSR
			EXTI->EXTI_FTSR1 |= (1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);
			EXTI->EXTI_RSTR1 &= ~(1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//2. Configure the RTSR
			EXTI->EXTI_RSTR1 |= (1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);
			EXTI->EXTI_FTSR1 &= ~(1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//3. configure the FTSR and RSTR
			EXTI->EXTI_RSTR1 |= (1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);
			EXTI->EXTI_FTSR1 |= (1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);

		}

//		//Configure the GPIO_Port selection in SYSCFG_EXTICR
//		uint8_t temp1=pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber /4;
//		uint8_t temp2=pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber %4 ;
//		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
//		SYSCONFIG_PCLK_EN();
//		SYSCONFIG->IT_LINE_SR[temp1]= portcode << (temp2* 4);

		// Configure the GPIO Port selection in EXTI_EXTICR

		uint8_t temp1 = pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

		SYSCONFIG_PCLK_EN();
		// Clear previous port selection
		EXTI->EXTI_EXTI_CR1[temp1] &= ~(0xFF << (temp2 * 8));

		// Write new port selection
		EXTI->EXTI_EXTI_CR1[temp1] |= (portcode << (temp2 * 8));




		//3 enable the EXTI interrupt delivery using IMR
		EXTI->EXTI_IMR1 |=  1<< pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber;

	}

	//configure the speed for the pin
	temp=0;
	temp = (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinSpeed  << (2* pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;


	temp=0;
	temp = (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	temp=0;
	temp = (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;


	//configure the alt functionality
	if(pGPIOHandle->GPIO_PinCOnfig.GPIO_PinMode  == GPIO_MODE_ALTFN)
	{
		uint8_t temp1,temp2;
		temp1 = pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber/8;
		temp2 = pGPIOHandle->GPIO_PinCOnfig.GPIO_PinNumber %8;

		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinCOnfig.GPIO_PinALtFunMode << (4 * temp2));

	}


}



void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx== GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx== GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx== GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx== GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx== GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx== GPIOF)
	{
		GPIOF_REG_RESET();
	}

}

uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	uint8_t Value;
	Value = (uint8_t )((pGPIOx->IDR >> PinNumber ) & 0x00000001);
	return Value;

}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t Value;
	Value = (uint16_t )(pGPIOx->IDR) ;
	return Value;

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);

	}
	else
	{
		pGPIOx->ODR |= ~(1 << PinNumber);

	}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t value)
{
	pGPIOx->ODR =value;


}


void GPIO_ToggleOutoutPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	pGPIOx->ODR ^= ( 1 << PinNumber);
}


void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi)
{
	if(EnorDi== ENABLE)
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

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	// Lets find out the ipr register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber% 4;

	uint8_t shift_amount = (8 *iprx_section ) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE_ADDR + (iprx)) |= (IRQPriority << (8 * shift_amount));


}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// Clear the EXTI PR Register corresponding to the Pin No.
	if(EXTI->EXTI_RPR1 & (1 << PinNumber))
	{
	    EXTI->EXTI_RPR1 |= (1 << PinNumber);
	}

	if(EXTI->EXTI_FPR1 & (1 << PinNumber))
	{
	    EXTI->EXTI_FPR1 |= (1 << PinNumber);
	}


}


