/*
 * 011_usart_IT_with_Button_Interrupt.c
 *
 *  Created on: Jul 9, 2026
 *      Author: shiva
 */



#include "stm32g0xx.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"
void delay(void)
{
	for(uint32_t i=0; i<=500000/2;i++);
}

GPIO_Handle_t USART_GPIO;
USART_Handle_t Usart2_Handle;
//uint8_t msg[20]="Hello AVINASH";
uint8_t msg[] = "Hello AVINASH";

uint8_t UART_RX[10]={0};

void USART2_GPIOInit(void)
{
	//GPIO_Handle_t USART;
	USART_GPIO.pGPIOx = GPIOA;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_2;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
	USART_GPIO.GPIO_PinCOnfig.GPIO_PinALtFunMode = AF1;

	GPIO_PeriClockControl(GPIOA,ENABLE);
    // PA2 -> TX
    //USART_GPIO.GPIO_PinCOnfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&USART_GPIO);

    // PA3 -> RX
    USART_GPIO.GPIO_PinCOnfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&USART_GPIO);

}

void Push_Button_Interrupt()
{
	GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinCOnfig.GPIO_PinNumber =GPIO_PIN_NO_5;
	GpioLed.GPIO_PinCOnfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinCOnfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinCOnfig.GPIO_PinPuPdControl=GPIO_PIN_NO_PUPD;
	GpioLed.GPIO_PinCOnfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;


	GPIO_PeriClockControl(GPIOA,ENABLE);



	GPIO_Init(&GpioLed);
	GPIO_Handle_t Gpio_User_Button;
	//GPIO_Init(&GpioLed);
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
}

void USART(void)
{
	Usart2_Handle.pUSARTx=USART2;
	Usart2_Handle.USART_Config.USART_Baud=USART_STD_BUAD_115200;
	Usart2_Handle.USART_Config.USART_Mode=USART_MODE_TXRX;
	Usart2_Handle.USART_Config.USART_HWFlowControl=USART_HW_FLOW_CTRL_NONE;
	Usart2_Handle.USART_Config.USART_NoofStopBits=USART_STOPBITS_1;
	Usart2_Handle.USART_Config.USART_ParityControl=USART_PARITY_DISABLE;
	Usart2_Handle.USART_Config.USART_WordLength=USART_WORDLEN_8BITS;


	USART_Init(&Usart2_Handle);
	Usart2_Handle.pUSARTx->USART_CR1 |= (1 <<0);



}

int main(void)
{
	Push_Button_Interrupt();
	USART2_GPIOInit();
	USART_PeriClockControl(USART2,ENABLE);
	USART();
	USART_IRQInterruptConfig(USART2_IRQn,ENABLE);
	//USART_IRQPriorityConfig(USART2_IRQn,);
	//USART_SendDataIT(&Usart2_Handle,msg,11);

	//USART_PeriClockControl(USART2,ENABLE);
	//USART_SendData(&Usart2_Handle,(uint8_t *)msg,13);
	//USART_SendData(&Usart2_Handle, msg, strlen((char *)msg));
	//USART_ReceiveData(&Usart2_Handle,(uint8_t *)UART_RX,sizeof(UART_RX));

	while(1)
	{
		//USART_SendData(&Usart2_Handle,(uint8_t *)msg,sizeof(msg));
		//USART_ReceiveData(&Usart2_Handle,(uint8_t *)UART_RX,sizeof(UART_RX));

		//GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
		//delay();
	}

	return 0;
}

void USART2_IRQHandler()
{
	USART_IRQHandling(&Usart2_Handle);
}

volatile uint32_t exti_count = 0;
void EXTI4_15_IRQHandler(void)
{
	exti_count++;
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutoutPin(GPIOA,GPIO_PIN_NO_5);
	USART_SendDataIT(&Usart2_Handle,msg,11);
}
