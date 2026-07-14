/*
 * 008_I2C_master_tx.c
 *
 *  Created on: Jul 12, 2026
 *      Author: shiva
 */


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

I2C_Handle_t I2C_Handle;
void delay(void)
{
	for(uint32_t i=0; i<=500000;i++);
}
void GPIO_INIT_()
{
	GPIO_Handle_t GpioLed,Gpio_User_Button,I2C_GPIO;

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

	//I2C_SCL
	I2C_GPIO.pGPIOx = GPIOA;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_9;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinALtFunMode = AF6;

	GPIO_Init(&I2C_GPIO);
	//I2C_SDA
	I2C_GPIO.GPIO_PinCOnfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&I2C_GPIO);


}
void I2C_Init_GPIO()
{
	I2C_Handle.pI2Cx = I2C1;
	I2C_Handle.I2C_Config.I2C_DeviceAddress=0x06;
	I2C_Handle.I2C_Config.I2C_SCLSpeed=I2C_SCL_SPEED_SM;

	I2C_Init(&I2C_Handle);


}

uint8_t some_data[]="Sending Data on I2C Slave\n";

int main(void)
{
	I2C_PeriClockControl(I2C1,ENABLE);
	GPIO_INIT_();
	I2C_Init_GPIO();

	I2C_ENControl(I2C1,ENABLE);


	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13)== USER_BUTTON)
		{
			delay();
			GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
			I2C_MasterSendData(&I2C_Handle,some_data,sizeof(some_data),0x06);
		}
	}

	return 0;
}
