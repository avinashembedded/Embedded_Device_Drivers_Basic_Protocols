/*
 * i2c.h
 *
 *  Created on: Jul 8, 2026
 *      Author: shiva
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_
#include <stm32g0xx.h>
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t I2C_DeviceAddress;
	//uint8_t I2C_AckControl;
	//uint16_t I2C_FMDutyCycle;
}I2C_Config_t;


typedef struct
{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxRxState;
	uint32_t Rxsize;
	uint8_t DevAddr;
	uint8_t Sr;     //Repeated Start
}I2C_Handle_t;


#define I2C_READY		0
#define I2C_BUSY_IN_RX	1
#define I2C_BUSY_IN_TX	2


/*
 * @I@C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM	100000     //100Khz
#define I2C_SCL_SPEED_FM4K	400000     //400Khz
#define I2C_SCL_SPEED_FM2k	200000     //200Khz

/*
 * @I@C_ACKControl
 */
#define I2C_ACK_EN			1
#define I2C_ACK_DIS			0

/*
 * @I@C_FMDutyCycle
 */

#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1

#define I2C_TIMING_16MHZ_100KHZ   0x00303D5B
#define I2C_TIMING_16MHZ_400KHZ   0x0010061A

#define I2C_DISABLE_SR    0
#define I2C_ENABLE_SR     1

#define I2C_EVENT_TRANSFER_COMPLETE   1
#define I2C_ERROR_NACK				  2

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t  EnorDi);
void I2C_ENControl(I2C_RegDef_t *pI2Cx,uint8_t EnORDi);
/*
 * Init and Deinit SPI Setup
 */

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint32_t Len,uint8_t SlaveAddr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint32_t Len,uint8_t SlaveAddr);

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint32_t Len,uint8_t SlaveAddr,uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint32_t Len,uint8_t SlaveAddr,uint8_t Sr);

void I2C_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnORDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint32_t Priority);

uint8_t I2C_Get_FLagStatus(I2C_RegDef_t *pI2Cx,uint8_t FlagName);
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv);


#endif /* INC_I2C_H_ */
