/*
 * 001_LED_Toggle.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Avinash Kumar
 */


#include "stm32g0xx.h"
//#include "gpio.h"

void delay(void)
{
	for(uint32_t i=0; i<=500000/2;i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_5;
	GpioLed.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_PIN_NO_PUPD;


	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioLed);


	while(1)
	{

		GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
		delay();
	}

	return 0;
}
