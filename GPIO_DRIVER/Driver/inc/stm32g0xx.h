/*
 * stm32g0xx.h
 *
 *  Created on: Jul 30, 2025
 *      Author: Avinash Kumar
 */

#ifndef INC_STM32G0XX_H_
#define INC_STM32G0XX_H_

#include "stdint.h"
#include "stddef.h"
#include "string.h"

/****************** PROCESSOR SPECIFIC DETAILS   CORTEX M0+ ****************************************/

#define NVIC_ISER 	 ((volatile uint32_t *)0xE000E100U)
#define NVIC_ICER 	 ((volatile uint32_t *)0xE000E180U)
#define NVIC_ISPR 	 ((volatile uint32_t *)0xE000E200U)
#define	NVIC_ICPR 	 ((volatile uint32_t *)0xE000E280U)
#define NVIC_IPR0    ((volatile uint32_t *)0xE000E400U)
#define NVIC_IPR1    ((volatile uint32_t *)0xE000E404U)
#define NVIC_IPR2    ((volatile uint32_t *)0xE000E408U)
#define NVIC_IPR3    ((volatile uint32_t *)0xE000E40CU)
#define NVIC_IPR4    ((volatile uint32_t *)0xE000E410U)
#define NVIC_IPR5    ((volatile uint32_t *)0xE000E414U)
#define NVIC_IPR6    ((volatile uint32_t *)0xE000E418U)
#define NVIC_IPR7    ((volatile uint32_t *)0xE000E41CU)

#define NVIC_IPR_BASE_ADDR  ((volatile uint32_t*)0xE000E400U)
#define NO_PR_BITS_IMPLEMENTED		4

#define FLASH_BASEADDR		0x80000000
//#define SRAM1_BASEADDR		0x20010000
#define SRAM_BASEADDR		0x20000000

#define AHB_BASEADDR		0x40020000
//#define AHB2_BASEADDR		0x50000000
//#define AHB3_BASEADDE		0x60000000
#define APB1_BASEADDR		0x40010000
#define APB2_BASEADDR		0x40000000
#define IOPORT_BASEADDR		0x50000000
#define __vol volatile


#define GPIOA_BASEADDR		(IOPORT_BASEADDR + 0x0000)
#define GPIOB_BASEADDR		(IOPORT_BASEADDR + 0x0400)
#define GPIOC_BASEADDR		(IOPORT_BASEADDR + 0x0800)
#define GPIOD_BASEADDR		(IOPORT_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR		(IOPORT_BASEADDR + 0x1000)
#define GPIOF_BASEADDR		(IOPORT_BASEADDR + 0x1400)

#define RCC_BASEADDR        (AHB_BASEADDR + 0x1000)
#define EXTI_BASEADDR		(AHB_BASEADDR + 0x1800)
#define SYSCONFIG_BASEADDR	(APB1_BASEADDR + 0x0000)


#define SPI1_BASEADDR		(APB1_BASEADDR + 0x3000)
#define SPI2_BASEADDR		(APB2_BASEADDR + 0x3800)
#define SPI3_BASEADDR		(APB2_BASEADDR + 0x3C00)


#define USART1_BASEADDR  	(APB1_BASEADDR + 0x3800)
#define USART6_BASEADDR  	(APB1_BASEADDR + 0x3C00)

#define USART2_BASEADDR  	(APB2_BASEADDR + 0x4400)
#define USART3_BASEADDR  	(APB2_BASEADDR + 0x4800)
#define USART4_BASEADDR  	(APB2_BASEADDR + 0x4C00)
#define USART5_BASEADDR  	(APB2_BASEADDR + 0x5000)


#define I2C1_BASEADDR  	(APB2_BASEADDR + 0x5400)
#define I2C2_BASEADDR  	(APB2_BASEADDR + 0x5800)
#define USB_BASEADDR  	(APB1_BASEADDR + 0x5C00)


#define TIMER1_BASEADDR  	(APB1_BASEADDR + 0x2C00)
#define TIMER15_BASEADDR  	(APB1_BASEADDR + 0x4000)
#define TIMER16_BASEADDR  	(APB1_BASEADDR + 0x4400)
#define TIMER17_BASEADDR  	(APB1_BASEADDR + 0x4800)


typedef struct
{
	__vol uint32_t MODER;
	__vol uint32_t OTYPER;
	__vol uint32_t OSPEEDR;
	__vol uint32_t PUPDR;
	__vol uint32_t IDR;
	__vol uint32_t ODR;
	__vol uint32_t BSRR;
	__vol uint32_t LCKR;
	__vol uint32_t AFR[2];
	__vol uint32_t BRR;

}GPIO_RegDef_t;


typedef struct
{
	__vol uint32_t CR;
	__vol uint32_t ICSCR;
	__vol uint32_t CFGR;
	__vol uint32_t PLL_CFGR;
	__vol uint32_t Reserved;
	__vol uint32_t Reserved1;
	__vol uint32_t CIER;
	__vol uint32_t CIFR;
	__vol uint32_t CICR;
	__vol uint32_t IOPRSTR;
	__vol uint32_t AHBRSTR;
	__vol uint32_t APB2RSTR;
	__vol uint32_t APB1RSTR;
	__vol uint32_t IOPENR;
	__vol uint32_t AHBENR;
	__vol uint32_t APBENR1;
	__vol uint32_t APBENR2;
	__vol uint32_t IOPSMENR;
	__vol uint32_t AHBSMENR;
	__vol uint32_t APBSMENR1;
	__vol uint32_t APBSMENR2;
	__vol uint32_t CCIPR;
	__vol uint32_t CCIPR2;
	__vol uint32_t BDCR;
	__vol uint32_t CSR;


}RCC_CLK_EN;

typedef struct
{
	__vol uint32_t EXTI_RSTR1;
	__vol uint32_t EXTI_FTSR1;
	__vol uint32_t EXTI_SWIER1;
	__vol uint32_t EXTI_RPR1;
	__vol uint32_t EXTI_FPR1;
	uint32_t RESERVED1[3];   /*!< Reserved 1,                                                0x14 -- 0x1C */
	uint32_t RESERVED2[5];   /*!< Reserved 2,                                                0x20 -- 0x30 */
	uint32_t RESERVED3[11];  /*!< Reserved 3,                                                0x34 -- 0x5C */
	__vol uint32_t EXTI_EXTI_CR1[4];
	uint32_t EXTI_RSRVD[4];
	__vol uint32_t EXTI_IMR1;
	__vol uint32_t EXTI_EMR1;
}EXTI_REG_DEF;


typedef struct
{
	__vol uint32_t CFGR1;          /*!< SYSCFG configuration register 1,                   Address offset: 0x00 */
   uint32_t RESERVED0[5];   /*!< Reserved,                                                   0x04 --0x14 */
   __vol uint32_t CFGR2;          /*!< SYSCFG configuration register 2,                   Address offset: 0x18 */
   uint32_t RESERVED1[25];  /*!< Reserved                                                           0x1C */
   __vol uint32_t IT_LINE_SR[32]; /*!< SYSCFG configuration IT_LINE register,             Address offset: 0x80 */
} SYSCFG_TypeDef;


typedef struct
{
	__vol uint32_t CR1;      /*!< SPI Control register 1 (not used in I2S mode),       Address offset: 0x00 */
	__vol uint32_t CR2;      /*!< SPI Control register 2,                              Address offset: 0x04 */
	__vol uint32_t SR;       /*!< SPI Status register,                                 Address offset: 0x08 */
	__vol uint32_t DR;       /*!< SPI data register,                                   Address offset: 0x0C */
	__vol uint32_t CRCPR;    /*!< SPI CRC polynomial register (not used in I2S mode),  Address offset: 0x10 */
	__vol uint32_t RXCRCR;   /*!< SPI Rx CRC register (not used in I2S mode),          Address offset: 0x14 */
	__vol uint32_t TXCRCR;   /*!< SPI Tx CRC register (not used in I2S mode),          Address offset: 0x18 */
	__vol uint32_t I2SCFGR;  /*!< SPI_I2S configuration register,                      Address offset: 0x1C */
	__vol uint32_t I2SPR;    /*!< SPI_I2S prescaler register,                          Address offset: 0x20 */
} SPI_RegDef_t;


typedef struct
{
	__vol uint32_t USART_CR1;                  /* Address offset:  0x00 */
	__vol uint32_t USART_CR2;					/* Address offset: 0x04 */
	__vol uint32_t USART_CR3;					/* Address offset: 0x08 */
	__vol uint32_t USART_BRR;					/* Address offset: 0x0C */
	__vol uint32_t USART_GTPR;					/* Address offset: 0x10 */
	__vol uint32_t USART_RTOR;					/* Address offset: 0x14 */
	__vol uint32_t USART_RQR;					/* Address offset: 0x18 */
	__vol uint32_t USART_ISR;					/* Address offset: 0x1C */
	__vol uint32_t USART_ICR;					/* Address offset: 0x20 */
	__vol uint32_t USART_RDR;					/* Address offset: 0x24 */
	__vol uint32_t USART_TDR;					/* Address offset: 0x28 */
	__vol uint32_t USART_PRESC;					/* Address offset: 0x2C */
}USART_RegDef_t;

typedef struct
{
	__vol uint32_t I2C_CR1;
	__vol uint32_t I2C_CR2;
	__vol uint32_t I2C_OAR1;
	__vol uint32_t I2C_OAR2;
	__vol uint32_t I2C_TIMINGR;
	__vol uint32_t I2C_TIMEOUTR;
	__vol uint32_t I2C_ISR;
	__vol uint32_t I2C_ICR;
	__vol uint32_t I2C_PECR;
	__vol uint32_t I2C_RXDR;
	__vol uint32_t I2C_TXDR;
}I2C_RegDef_t;
/*
 * Peripheral definitions (Peripherals base address type casted to xxx_Reg_Def_t
 */

#define GPIOA                  	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                  	((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                  	((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                  	((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                  	((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                	((GPIO_RegDef_t*)GPIOF_BASEADDR)


#define RCC                    	((RCC_CLK_EN*)RCC_BASEADDR)

#define EXTI 					((EXTI_REG_DEF*)EXTI_BASEADDR)

#define SYSCONFIG				((SYSCFG_TypeDef*)SYSCONFIG_BASEADDR)

#define SPI1					((SPI_RegDef_t*)SPI1_BASEADDR)

#define SPI2					((SPI_RegDef_t*)SPI2_BASEADDR)

#define SPI3					((SPI_RegDef_t*)SPI3_BASEADDR)

#define USART1					((USART_RegDef_t*)USART1_BASEADDR)
#define USART2					((USART_RegDef_t*)USART2_BASEADDR)
#define USART3					((USART_RegDef_t*)USART3_BASEADDR)
#define USART4					((USART_RegDef_t*)USART4_BASEADDR)
#define USART5					((USART_RegDef_t*)USART5_BASEADDR)
#define USART6					((USART_RegDef_t*)USART6_BASEADDR)

#define I2C1					((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2					((I2C_RegDef_t*)I2C2_BASEADDR)


/*
 *         Enabling and disabling macro clock for different peripheral  , GPIOS , SPI ,UASRT and I2C
 */


/*
 * Enabling clock for the GPIOS peripheral
 */

#define GPIOA_PCLK_EN()   (RCC->IOPENR |= (1 <<0 ))   //match it once with Reference manual
#define GPIOB_PCLK_EN()   (RCC->IOPENR |= (1 <<1 ))
#define GPIOC_PCLK_EN()   (RCC->IOPENR |= (1 <<2 ))
#define GPIOD_PCLK_EN()   (RCC->IOPENR |= (1 <<3 ))
#define GPIOE_PCLK_EN()   (RCC->IOPENR |= (1 <<4 ))
#define GPIOF_PCLK_EN()   (RCC->IOPENR |= (1 <<5 ))


#define SYSCONFIG_PCLK_EN()			(RCC->APBENR2 |= (1<<0))
#define SYSCONFIG_PCLK_DIS()		(RCC->APBRTS2 |= (1<<0))

#define EXTI_PCLK_EN()
#define EXTI_PCLK_DIS()


/*
 * Enabling & Disabling clock for the SPI peripheral
 */
#define 	SPI1_PCLK_EN()      (RCC->APBENR2 |= (1 <<12))
#define 	SPI1_PCLK_DIS()		(RCC->APB2RSTR |= (1<<12))


#define 	SPI2_PCLK_EN()		(RCC->APBENR1 |= (1 <<14 ))
#define 	SPI2_PCLK_DIS()		(RCC->APB1RSTR |= (1 <<14))


#define 	SPI3_PCLK_EN()      (RCC->APBENR1 |= (1 <<12))
#define 	SPI3_PCLK_DIS()		(RCC->APB1RSTR |= (1<<12))


/*
 * Enabling clock for the UART peripheral
 */

#define USART1_PCLK_EN()      (RCC->APBENR2 |= (1 <<14 ))
#define USART1_PCLK_DIS()     (RCC->APB2RSTR |= (1 <<14))


#define USART2_PCLK_EN()	  (RCC->APBENR1 |= (1 <<17 ))
#define USART2_PCLK_DIS()     (RCC->APB1RSTR |= (1 <<17))

#define USART3_PCLK_EN()	  (RCC->APBENR1 |= (1 <<18 ))
#define USART3_PCLK_DIS()     (RCC->APB1RSTR |= (1 <<18))


#define USART4_PCLK_EN()	  (RCC->APBENR1 |= (1 <<19 ))
#define USART4_PCLK_DIS()     (RCC->APB1RSTR |= (1 <<19))


#define USART5_PCLK_EN()	  (RCC->APBENR1 |= (1 <<8 ))
#define USART5_PCLK_DIS()     (RCC->APB1RSTR |= (1 <<8))

#define USART6_PCLK_EN()	  (RCC->APBENR1 |= (1 <<9 ))
#define USART6_PCLK_DIS()     (RCC->APB1RSTR |= (1 <<9))




/*
 * Enabling clock for the TIMER peripheral
 */

#define TIM2_PCLK_EN()        	(RCC->APBENR1 |= (1 <<0 ))
#define TIM3_PCLK_EN()			(RCC->APBENR1 |= (1 <<1 ))
#define TIM6_PCLK_EN()			(RCC->APBENR1 |= (1 <<4 ))
#define TIM7_PCLK_EN()			(RCC->APBENR1 |= (1 <<5 ))


/*
 * Enabling clock for the I2C peripheral
 */
#define I2C1_PCLK_EN()			(RCC->APBENR1 |= (1 <<21 ))
#define I2C2_PCLK_EN()			(RCC->APBENR1 |= (1 <<22 ))

/*
 * Disabling clock for the GPIOS peripheral
 */
#define GPIOA_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<0 ))
#define GPIOB_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<1 ))
#define GPIOC_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<2 ))
#define GPIOD_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<3 ))
#define GPIOE_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<4 ))
#define GPIOF_PCLK_DIS()      (RCC->IOPENR &= ~(1 <<5 ))



/*
 * Disabling clock for the SPI peripheral
 */

//#define SPI1_PCLK_DIS()      (RCC->APB2ENR &= ~(1 <<12 ))
//#define SPI2_PCLK_DIS()		 (RCC->APB1ENR &= ~(1 <<14 ))


/*
 * Disabling clock for the UART peripheral
 */

//#define USART1_PCLK_DIS()      (RCC->APB2ENR &= ~(1 <<14 ))
//#define USART2_PCLK_DIS()	   (RCC->APB1ENR &= ~(1 <<17 ))
//#define USART4_PCLK_DIS()	   (RCC->APB1ENR &= ~(1 <<19 ))
//#define USART5_PCLK_DIS()	   (RCC->APB1ENR &= ~(1 <<20 ))
//#define LPUART1_PCLK_DIS()	   (RCC->APB1ENR &= ~(1 <<18 ))

/*
 * Disabling clock for the TIMERS peripheral
 */


#define TIM2_PCLK_DIS()        	(RCC->APB1ENR &= ~(1 <<0 ))
#define TIM3_PCLK_DIS()			(RCC->APB1ENR &= ~(1 <<1 ))
#define TIM6_PCLK_DIS()			(RCC->APB1ENR &= ~(1 <<4 ))
#define TIM7_PCLK_DIS()			(RCC->APB1ENR &= ~(1 <<5 ))


/*
 * Disabling clock for the I2C peripheral
 */


#define I2C1_PCLK_DIS()			(RCC->APB1RSTR &= ~(1 <<21 ))
#define I2C2_PCLK_DIS()			(RCC->APB1RSTR &= ~(1 <<22 ))






//Some Generic Macros

#define ENABLE 						1
#define DISABLE 					0
#define SET                       	ENABLE
#define RESET						DISABLE
#define GPIO_PIN_SET				SET
#define GPIO_PIN_RESET				RESET



#define 	GPIOA_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<0)); (RCC->IOPRSTR &= ~(1<<0)); }while(0)
#define 	GPIOB_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<1)); (RCC->IOPRSTR &= ~(1<<1)); }while(0)
#define 	GPIOC_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<2)); (RCC->IOPRSTR &= ~(1<<2)); }while(0)
#define 	GPIOD_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<3)); (RCC->IOPRSTR &= ~(1<<3)); }while(0)
#define 	GPIOE_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<4)); (RCC->IOPRSTR &= ~(1<<4)); }while(0)
#define 	GPIOF_REG_RESET()         do{ (RCC->IOPRSTR |= (1<<5)); (RCC->IOPRSTR &= ~(1<<5)); }while(0)

#define GPIO_BASEADDR_TO_CODE(x)       ((x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
										(x == GPIOE)?4:\
										(x == GPIOF)?5:0)


#define 		EXTI0_1_IRQn      5      /*!< EXTI 0 and 1 Interrupts                                           */
#define  		EXTI2_3_IRQn      6      /*!< EXTI Line 2 and 3 Interrupts                                      */
#define  		EXTI4_15_IRQn     7      /*!< EXTI Line 4 to 15 Interrupts                                      */

#define 		NVIC_IRQ_PRI15	15

#define 		I2C1_IRQn		23
#define 		I2C2_IRQn		24
#define 		I2C3_IRQn		24
#define 		SPI1_IRQn		25
#define 		SPI2_IRQn		26
#define 		SPI3_IRQn		26
#define 		USART1_IRQn		27
#define 		USART2_IRQn		28
#define 		USART3_IRQn		28
#define 		USART4_IRQn		28
#define 		USART5_IRQn		28
#define 		USART6_IRQn		28

/******************** BITS POSITION DEFINITION FOR SPI PERIPH************************/

//CR1

#define SPI_CR1_CPHA		0

/******************** BITS POSITION DEFINITION FOR I2C PERIPH************************/
#define 	I2C_CR1_PERIPH_EN			0
#define 	I2C_CR1_TXEI		1
#define 	I2C_CR1_RXEI		2
#define 	I2C_CR1_ADDRIE		3
#define 	I2C_CR1_NACKIE		4
#define 	I2C_CR1_STOPIE		5
#define 	I2C_CR1_TCIE		6
#define 	I2C_CR1ERRIE		7
#define 	I2C_CR1_DNF			8
#define 	I2C_CR1_ANFOFF		12
#define 	I2C_CR1_TXDMAEN		14
#define 	I2C_CR1_RXDMAEN		15
#define 	I2C_CR1_SSB			16
#define 	I2C_CR1_NOSTRETCH	17
#define 	I2C_CR1_WUPEN		18
#define 	I2C_CR1_GCEN		19
#define 	I2C_CR1_SMBHEN		20
#define 	I2C_CR1_SMBDEN		21
#define 	I2C_CR1_ALRETEN		22
#define 	I2C_CR1_PECEN		23

#define 	I2C_CR2_SADD		0
#define 	I2C_CR2_RD_WRN		10
#define 	I2C_CR2_ADD10		11
#define 	I2C_CR2_HEAD10R		11
#define 	I2C_CR2_START		13
#define 	I2C_CR2_STOP		14
#define 	I2C_CR2_NACK		15
#define 	I2C_CR2_NBYTES		16
#define 	I2C_CR2_RELOAD		24
#define 	I2C_CR2_AUTOEND		25
#define 	I2C_CR2_PECBYTES	26



#define 	I2C_TIMINGR_PRES		28
#define 	I2C_TIMINGR_SCLDEL		20
#define 	I2C_TIMINGR_SDADEL		16
#define 	I2C_TIMINGR_SCLH		8
#define 	I2C_TIMINGR_SCLL		0


#define 	I2C_ISR_TXE				0
#define 	I2C_ISR_TXIS			1
#define 	I2C_ISR_RXNE			2
#define 	I2C_ISR_ADDR			3
#define 	I2C_ISR_NACKF			4
#define 	I2C_ISR_STOPF			5
#define 	I2C_ISR_TC				6
#define 	I2C_ISR_TCR				7
#define 	I2C_ISR_BERR			8
#define 	I2C_ISR_ARLO			9
#define 	I2C_ISR_OVR				10
#define 	I2C_ISR_PECERR			11
#define 	I2C_ISR_TIMEOUT			12
#define 	I2C_ISR_ALERT			13
#define 	I2C_ISR_BUSY			15
#define 	I2C_ISR_DIR				16
#define 	I2C_ISR_ADDCODE			17

#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "stm32f0xx_rcc_driver.h"
#include "i2c.h"
#endif /* INC_STM32G0XX_H_ */
