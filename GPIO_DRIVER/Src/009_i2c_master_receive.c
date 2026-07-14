/*
 * 009_i2c_master_receive.c
 *
 *  Created on: Jul 13, 2026
 *      Author: shiva
 */

#include "stm32g0xx.h"

#define 		DIS   0
#define 		USER_BUTTON   DIS

I2C_Handle_t I2C_Handle;
GPIO_Handle_t I2C_GPIO;

uint8_t some_data[]="Sending Data on I2C Slave\n";
uint8_t I2CRxBuffer[20];
uint8_t Command =0x51;
void delay(void)
{
	for(uint32_t i=0; i<=500000;i++);
}
void GPIO_INIT_()
{
	//I2C_SCL
	GPIO_PeriClockControl(GPIOA,ENABLE);
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
int main(void)
{
	I2C_PeriClockControl(I2C1,ENABLE);
	GPIO_INIT_();
	I2C_Init_GPIO();

	I2C_ENControl(I2C1,ENABLE);

	I2C_MasterSendData(&I2C_Handle,&Command,1,0x06);

	I2C_MasterReceiveData(&I2C_Handle,I2CRxBuffer,1,0x06);


	while(1)
	{

	}
	return 0;
}
