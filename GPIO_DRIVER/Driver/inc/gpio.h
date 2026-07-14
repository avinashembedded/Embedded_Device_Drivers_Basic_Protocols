/*
 * gpio.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Avinash Kumar
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


#include <stm32g0xx.h>


/*
 * @GPIO_Pin_Modes
 * GPIO Pins Possible Modes
 */

#define GPIO_MODE_IN 							0
#define GPIO_MODE_OUT 							1
#define GPIO_MODE_ALTFN 						2
#define GPIO_MODE_ANALOG 						3
#define GPIO_MODE_IT_FT							4
#define GPIO_MODE_IT_RT          				5
#define GPIO_MODE_IT_RFT                        6


/*
 * @GPIO_Pin_Output_Type
 * GPIO Pins Possible Output Type
 */

#define GPIO_OP_TYPE_PP							0
#define GPIO_OP_TYPE_OD							1


/*
 * @GPIO_Pin_Speed
 * GPIO Pins Possible Output Speed
 */

#define GPIO_SPEED_LOW							0
#define GPIO_SPEED_MED							1
#define GPIO_SPEED_HIGH							2
#define GPIO_SPEED_FAST							3

/*
 * @GPIO_Pin_Pullup_PullDown_Mode
 * GPIO Pins Pull up & Pull down Configuration
 */

#define GPIO_PIN_NO_PUPD						0
#define GPIO_PIN_PU								1
#define GPIO_PIN_PD								2



/*
 * @GPIO_Pin_Number
 * GPIO Pins No.
 */

#define GPIO_PIN_NO_0							0
#define GPIO_PIN_NO_1             				1
#define GPIO_PIN_NO_2             				2
#define GPIO_PIN_NO_3             				3
#define GPIO_PIN_NO_4             				4
#define GPIO_PIN_NO_5             				5
#define GPIO_PIN_NO_6             				6
#define GPIO_PIN_NO_7             				7
#define GPIO_PIN_NO_8             				8
#define GPIO_PIN_NO_9             				9
#define GPIO_PIN_NO_10             				10
#define GPIO_PIN_NO_11             				11
#define GPIO_PIN_NO_12             				12
#define GPIO_PIN_NO_13             				13
#define GPIO_PIN_NO_14             				14
#define GPIO_PIN_NO_15             				15


#define AF0				0
#define AF1				1
#define AF2				2
#define AF3				3
#define AF4				4
#define AF5				5
#define AF6				6
#define AF7				7


typedef struct
{
	uint8_t GPIO_PinNumber;			/*@GPIO_Pin_Number     */
	uint8_t GPIO_PinMode;      		/*@GPIO_Pin_Modes     */
	uint8_t GPIO_PinSpeed;			/*@GPIO_Pin_Speed     */
	uint8_t GPIO_PinPuPdControl;	/*@GPIO_Pin_Pullup_PullDown_Mode     */
	uint8_t GPIO_PinOPType;			/*@GPIO_Pin_Output_Type     */
	uint8_t GPIO_PinALtFunMode;		/*@GPIO_Pin_Alternate_Functionality     */
}GPIO_PinConfig_t;


typedef struct
{
	GPIO_RegDef_t *pGPIOx;     /*|<This holds the base address of the GPIO port to which the pin belongs>*/
	GPIO_PinConfig_t GPIO_PinCOnfig;

}GPIO_Handle_t;


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t  EnorDi);

/*
 * Init and Deinit GPIO Setup
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Read and Write From GPIOS
 */
uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t value);
void GPIO_ToggleOutoutPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);


/*
 * Read and Write From GPIOS
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi); // Processor Side Coding
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);





#endif /* INC_GPIO_H_ */
