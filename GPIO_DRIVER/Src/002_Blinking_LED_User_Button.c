/*
 * 002_Blinking_LED_User_Button.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Avinash Kumar
 */



#include "stm32g0xx.h"
//#include "gpio.h"
#define 		DIS   0
#define 		USER_BUTTON   DIS


void delay(void)
{
	for(uint32_t i=0; i<=500000;i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed,Gpio_User_Button;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_5;
	GpioLed.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_PIN_NO_PUPD;


	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_PeriClockControl(GPIOC,ENABLE);



	GPIO_Init(&GpioLed);
	Gpio_User_Button.pGPIOx = GPIOC;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_13;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpio_User_Button.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_PIN_NO_PUPD;

	GPIO_Init(&Gpio_User_Button);


	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13)== USER_BUTTON)
		{
			delay();
			GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
		}
	}

	return 0;
}
