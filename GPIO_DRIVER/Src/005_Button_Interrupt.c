/*
 * 005_Button_Interrupt.c
 *
 *  Created on: Jul 5, 2026
 *      Author: shiva
 */

#include "stm32g0xx.h"


GPIO_Handle_t GpioLed,Gpio_User_Button;

int main()
{
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_5;
	GpioLed.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinCOnfig.GPIO_PinPuPdControl=GPIO_PIN_NO_PUPD;
	GpioLed.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;


	GPIO_PeriClockControl(GPIOA,ENABLE);



	GPIO_Init(&GpioLed);
	Gpio_User_Button.pGPIOx = GPIOC;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_13;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;


	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&Gpio_User_Button);

	//IRQ_Configuration
	//GPIO_IRQPriorityConfig(EXTI4_15_IRQn,NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(EXTI4_15_IRQn,ENABLE);

	while(1);



	return 0;
}


void EXTI4_15_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
}
