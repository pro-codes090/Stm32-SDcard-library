/*
 * stm32f407xx.h
 *
 *  Created on: Oct 23, 2021
 *      Author: pro
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#define __vo volatile
// base address of flash and ram memories
#define FLASH_BASEADDR	0x08000000U
#define SRAM1_BASEADDR	0x20000000U	// 112kb of sram1
#define SRAM2_BASEADDR	0x20001C00U	// 16 kb of sram2
#define ROM_BASEADDR	0x1FFF0000U	// 30kb of  system memory
#define SRAM 			SRAM1_BASEADDR

#define ENABLE  1
#define DISABLE 0
#define SET		ENABLE
#define RESET 	DISABLE
#define FLAG_RESET	RESET
#define FLAG_SET	SET


////////////////////////////////////Processor specific details ///////////////////////////////////
/* Arm cortex Mx NVIC register addresses */
	 // stm32f407vgt6 has only 80 interrupts implemented by the vendor itself
#define NVIC_ISER0				(__vo uint32_t*)0xE000E100
#define NVIC_ISER1				(__vo uint32_t*)0xE000E104
#define NVIC_ISER2				(__vo uint32_t*)0xE000E108

#define NVIC_ICER0				(__vo uint32_t*)0xE000E180
#define NVIC_ICER1				(__vo uint32_t*)0xE000E184
#define NVIC_ICER2				(__vo uint32_t*)0xE000E188

#define NVIC_IPR_BASE_ADDR			(__vo uint32_t *)0xE000E400
#define NO_PR_BITS_IMPLEMENTED 		4

////////////////////////////////////////////////////////////////////////////////////////////////

// base address for various bus domains
#define PERIPPH_BASE	0x40000000U
#define AHB1PERIPH_BASE	0x40020000U
#define AHB2PERIPH_BASE	0x50000000U
#define APB1ERIPH_BASE	0x40000000U
#define APB2ERIPH_BASE	0x40010000U


// peripheral base address macros of AHB1 bus

#define GPIOA_BASEADDR	(AHB1PERIPH_BASE + 0x00)
#define GPIOB_BASEADDR	(AHB1PERIPH_BASE + 0x400)
#define GPIOC_BASEADDR	(AHB1PERIPH_BASE + 0x800)
#define GPIOD_BASEADDR	(AHB1PERIPH_BASE + 0xC00)
#define GPIOE_BASEADDR	(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR	(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR	(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR	(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR	(AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASEADDR	(AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASEADDR	(AHB1PERIPH_BASE + 0x2800)
#define RCC_BASEADDR 	(AHB1PERIPH_BASE + 0x3800)

// peripheral base address macros of APB1 bus

// I2C peripheral base address
#define I2C1_BASEADDR 	(APB1ERIPH_BASE + 0x5400 )
#define I2C2_BASEADDR 	(APB1ERIPH_BASE + 0x5800 )
#define I2C3_BASEADDR 	(APB1ERIPH_BASE + 0x5C00 )

// SPI peripheral base address
#define SPI2_BASEADDR	(APB1ERIPH_BASE + 0x3800)
#define SPI3_BASEADDR	(APB1ERIPH_BASE + 0x3C00)

//USART peripheral base address
#define	USART2_BASEADDR	(APB1ERIPH_BASE + 0x4400)
#define	USART3_BASEADDR	(APB1ERIPH_BASE + 0x4800)

// UART peripheral base address
#define UART4_BASEADDR		(APB1ERIPH_BASE + 0x4C00)
#define UART5_BASEADDR		(APB1ERIPH_BASE + 0x5000)

// peripheral base address macros of APB2 bus
#define EXTI_BASEADDR		(APB2ERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR		(APB2ERIPH_BASE + 0x3000)
#define USART1_BASEADDR		(AHB2PERIPH_BASE+ 0x1000)
#define USART6_BASEADDR		(APB2ERIPH_BASE + 0x1400)
#define SYSCFG_BASEADDR		(APB2ERIPH_BASE + 0x3800)

//RCC structure definition

typedef struct {
	__vo  uint32_t	CR 			;
	__vo  uint32_t	PLLCFGR 	;
	__vo  uint32_t	CFGR		;
	__vo  uint32_t	CIR			;
	__vo  uint32_t	AHB1RSTR	;
	__vo  uint32_t	AHB2RSTR	;
	__vo  uint32_t	AHB3RSTR	;
	__vo  uint32_t	RESERVED1	;
	__vo  uint32_t	APB1RSTR	;
	__vo  uint32_t	APB2RSTR	;
	__vo  uint32_t	RESERVED2[2];
	__vo  uint32_t	AHB1ENR 	;
	__vo  uint32_t	AHB2ENR 	;
	__vo  uint32_t	AHB3ENR 	;
	__vo  uint32_t	RESERVED3 	;
	__vo  uint32_t	APB1ENR 	;
	__vo  uint32_t	APB2ENR 	;
	__vo  uint32_t	RESERVED4[2];
	__vo  uint32_t	AHB1LPENR 	;
	__vo  uint32_t	AHB2LPENR 	;
	__vo  uint32_t	AHB3LPENR 	;
	__vo  uint32_t	RESERVED5 	;
	__vo  uint32_t	APB1LPENR 	;
	__vo  uint32_t	APB2LPENR 	;
	__vo  uint32_t	RESERVED6[2];
	__vo  uint32_t	BDCR 		;
	__vo  uint32_t	CSR 		;
	__vo  uint32_t	RESERVED7[2];
	__vo  uint32_t	SSCGR 		;
	__vo  uint32_t	PLLI2SCFGR 	;

}RCC_RegDef_t;

// GPIO structure definition

typedef struct {
	__vo uint32_t MODER  ;	// gpio mode register at 				0x00
	__vo uint32_t OTYPER ;	// gpio output type register at 		0x04
	__vo uint32_t OSPEEDR;	// gpio output speed register at 		0x08
	__vo uint32_t PUPDR	 ;	// gpio pull up pull down register at 	0x0c
	__vo uint32_t IDR	 ;	// gpio input data register at 			0x10
	__vo uint32_t ODR	 ;	// gpio output data register at 		0x14
	__vo uint32_t BSRR	 ;	// gpio bit set reset regisetr at 		0x18
	__vo uint32_t LCKR	 ;	// gpio lock register at 				0x1c
	__vo uint32_t AFR[2] ;	/* gpio alternate function high and
								   low register at 						0x20 and
																		0x24*/
}GPIO_RegDef_t;

//EXTI structure definition
typedef struct {
	__vo uint32_t IMR  ;
	__vo uint32_t EMR  ;
	__vo uint32_t RTSR ;
	__vo uint32_t FTSR ;
	__vo uint32_t SWIER;
	__vo uint32_t PR   ;

}EXTI_RegDef_t;

//SYSCFG structure definition
typedef struct {
__vo uint32_t MEMRMP ;
__vo uint32_t PMC    ;
__vo uint32_t EXTICR[4] ;
__vo uint32_t RESERVED[2] ;
__vo uint32_t CMPCR	  ;

}SYSCFG_RegDef_t;

// Spi structure definition

typedef struct {
	__vo uint32_t CR1 	;
	__vo uint32_t CR2 	;
	__vo uint32_t SR 	;
	__vo uint32_t DR 	;
	__vo uint32_t CRCPR	;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFG;
	__vo uint32_t I2SPR	;

}SPI_RegDef_t ;


// I2C structure definition

typedef struct {
	__vo uint32_t CR1 	;
	__vo uint32_t CR2 	;
	__vo uint32_t OAR1 	;
	__vo uint32_t OAR2 	;
	__vo uint32_t DR	;
	__vo uint32_t SR1	;
	__vo uint32_t SR2   ;
	__vo uint32_t CCR	;
	__vo uint32_t TRISE	;
	__vo uint32_t FLTR	;

}I2C_RegDef_t ;


// GPIO struct macos

#define GPIOA	((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC	((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD	((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE	((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF	((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG	((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH	((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI	((GPIO_RegDef_t *)GPIOI_BASEADDR)
#define GPIOJ	((GPIO_RegDef_t *)GPIOJ_BASEADDR)
#define GPIOK	((GPIO_RegDef_t *)GPIOK_BASEADDR)

// RCC struct macro
#define RCC 	((RCC_RegDef_t *)RCC_BASEADDR)

// EXTI struct macro
#define EXTI	((EXTI_RegDef_t *)EXTI_BASEADDR)

//SYSCFG struct macro

#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

// SPIx struct macro

#define SPI1	((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2	((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3	((SPI_RegDef_t*)SPI3_BASEADDR)

// I2Cx struct macro

#define I2C1	((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2	((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3	((I2C_RegDef_t*)I2C3_BASEADDR)


// Peripheral clock enable macros

	// clock enable macros for GPIOx
	#define GPIOA_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 0) )
	#define GPIOB_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 1) )
	#define GPIOC_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 2) )
	#define GPIOD_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 3) )
	#define GPIOE_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 4) )
	#define GPIOF_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 5) )
	#define GPIOG_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 6) )
	#define GPIOH_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 7) )
	#define GPIOI_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 8) )
	#define GPIOJ_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 9) )
	#define GPIOK_CLOCK_ENABLE()	(RCC->AHB1ENR  |= (1 << 10) )

	// clock enable macros for I2Cx
	#define I2C1_CLOCK_ENABLE()			(RCC->APB1ENR |= (1 << 21) )
	#define I2C2_CLOCK_ENABLE()			(RCC->APB1ENR |= (1 << 22) )
	#define I2C3_CLOCK_ENABLE()			(RCC->APB1ENR |= (1 << 23) )

	// clock enable macros for spix
	#define SPI1_CLOCK_ENABLE()			(RCC->APB2ENR |= (1 << 12) )
	#define SPI2_CLOCK_ENABLE()			(RCC->APB1ENR |= (1 << 14) )
	#define SPI3_CLOCK_ENABLE()			(RCC->APB1ENR |= (1 << 15) )
	#define SPI4_CLOCK_ENABLE()			(RCC->APB2ENR |= (1 << 13) )

	//clock enable macros for usartx and uartx
	#define USART1_CLOCK_ENABLE()		(RCC->APB2ENR |= (1 << 4 ) )
	#define USART2_CLOCK_ENABLE()		(RCC->APB1ENR |= (1 << 17) )
	#define USART3_CLOCK_ENABLE()		(RCC->APB1ENR |= (1 << 18) )
	#define UART4_CLOCK_ENABLE()		(RCC->APB1ENR |= (1 << 19) )
	#define UART5_CLOCK_ENABLE()		(RCC->APB1ENR |= (1 << 20) )
	#define USART6_CLOCK_ENABLE()		(RCC->APB2ENR |= (1 << 5 ) )

	// clock enable macro for syscfg
	#define SYSCFG_CLOCK_ENABLE()			(RCC->APB2ENR |= (1 << 14) )

// Peripheral clock disable macros

	// clock disable macros for GPIOx
	#define GPIOA_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 0) )
	#define GPIOB_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 1) )
	#define GPIOC_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 2) )
	#define GPIOD_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 3) )
	#define GPIOE_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 4) )
	#define GPIOF_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 5) )
	#define GPIOG_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 6) )
	#define GPIOH_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 7) )
	#define GPIOI_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 8) )
	#define GPIOJ_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 9) )
	#define GPIOK_CLOCK_DISABLE()	(RCC->AHB1ENR  &= ~(1 << 10) )

	// clock disable macros for I2Cx
	#define I2C1_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1 << 21) )
	#define I2C2_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1 << 22) )
	#define I2C3_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1 << 23) )

	// clock disable macros for spix
	#define SPI1_CLOCK_DISABLE()			(RCC->APB2ENR &= ~(1 << 12) )
	#define SPI2_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1 << 14) )
	#define SPI3_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1 << 15) )
	#define SPI4_CLOCK_DISABLE()			(RCC->APB2ENR &= ~(1 << 13) )

	//clock disable macros for usartx and uartx
	#define USART1_CLOCK_DISABLE()		(RCC->APB2ENR &= ~(1 << 4 ) )
	#define USART2_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1 << 17) )
	#define USART3_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1 << 18) )
	#define UART4_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1 << 19) )
	#define UART5_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1 << 20) )
	#define USART6_CLOCK_DISABLE()		(RCC->APB2ENR &= ~(1 << 5 ) )

	// clock disable macro for syscfg
	#define SYSCFG_CLOCK_DISABLE()			(RCC->APB2ENR &= ~(1 << 14) )

// GPIOx peripheral reset
#define GPIOA_REG_RESET()			do {(RCC->AHB1RSTR |=(1 <<  0)); (RCC->AHB1RSTR &= ~(1 <<  0));}while(0)
#define GPIOB_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  1)); (RCC->AHB1RSTR &= ~(1 <<  1));}while(0)
#define GPIOC_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  2)); (RCC->AHB1RSTR &= ~(1 <<  2));}while(0)
#define GPIOD_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  3)); (RCC->AHB1RSTR &= ~(1 <<  3));}while(0)
#define GPIOE_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  4)); (RCC->AHB1RSTR &= ~(1 <<  4));}while(0)
#define GPIOF_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  5)); (RCC->AHB1RSTR &= ~(1 <<  5));}while(0)
#define GPIOG_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  6)); (RCC->AHB1RSTR &= ~(1 <<  6));}while(0)
#define GPIOH_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  7)); (RCC->AHB1RSTR &= ~(1 <<  7));}while(0)
#define GPIOI_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  8)); (RCC->AHB1RSTR &= ~(1 <<  8));}while(0)
#define GPIOJ_REG_RESET()           do {(RCC->AHB1RSTR |=(1 <<  9)); (RCC->AHB1RSTR &= ~(1 <<  9));}while(0)
#define GPIOK_REG_RESET()           do {(RCC->AHB1RSTR |=(1 << 10)); (RCC->AHB1RSTR &= ~(1 << 10));}while(0)

#define GPIO_BASEADDR_TO_CODE(x)  ( (x == GPIOA) ? 0 :\
									(x == GPIOB) ? 1 :\
									(x == GPIOC) ? 2 :\
									(x == GPIOD) ? 3 :\
									(x == GPIOE) ? 4 :\
									(x == GPIOF) ? 5 :\
									(x == GPIOG) ? 6 :\
									(x == GPIOH) ? 7 :\
									(x == GPIOI) ? 8 :\
									(x == GPIOJ) ? 9 :\
									(x == GPIOK) ? 0xA :0 )


//SPI peripheral reset macro

#define SPI1_REG_RESET()		   do {(RCC->APB2RSTR |=(1 <<  12)); (RCC->APB2RSTR &= ~(1 << 12));}while(0)
#define SPI2_REG_RESET()           do {(RCC->APB1RSTR |=(1 <<  14)); (RCC->APB1RSTR &= ~(1 << 14));}while(0)
#define SPI3_REG_RESET()           do {(RCC->APB1RSTR |=(1 <<  15)); (RCC->APB1RSTR &= ~(1 << 15));}while(0)


//SPI peripheral reset macro

#define I2C1_REG_RESET()		   do {(RCC->APB1RSTR |=(1 <<  21)); (RCC->APB2RSTR &= ~(1 << 21));}while(0)
#define I2C2_REG_RESET()           do {(RCC->APB1RSTR |=(1 <<  22)); (RCC->APB1RSTR &= ~(1 << 22));}while(0)
#define I2C3_REG_RESET()           do {(RCC->APB1RSTR |=(1 <<  23)); (RCC->APB1RSTR &= ~(1 << 23));}while(0)


// IRQ numbers definition macros

#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40
#define IRQ_NO_SPI1					35
#define IRQ_NO_SPI2					36
#define IRQ_NO_SPI3					51
#define IRQ_NO_I2C1_EV			    31
#define IRQ_NO_I2C2_EV			    33
#define IRQ_NO_I2C3_EV			    72
#define IRQ_NO_I2C1_ER			    32
#define IRQ_NO_I2C2_ER			    34
#define IRQ_NO_I2C3_ER			    73


/*
 * bit definition macros of spi peripheral
 * */
		//CR1 bit position definition
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15

	// CR2 bit position definition

#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7

	// SR bit position definition

#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8


/*
 * bit definition macros of i2c peripheral
 * */

		// CR1 bit position definition

#define I2C_CR1_PE			    0
#define I2C_CR1_SMBUS		    1
#define I2C_CR1_SMBTYPE		    3
#define I2C_CR1_ENARP		    4
#define I2C_CR1_ENPEC		    5
#define I2C_CR1_ENGC		    6
#define I2C_CR1_NOSTRETCH	    7
#define I2C_CR1_START		    8
#define I2C_CR1_STOP		    9
#define I2C_CR1_ACK		    	10
#define I2C_CR1_POS		    	11
#define I2C_CR1_PEC		    	12
#define I2C_CR1_ALERT		    13
#define I2C_CR1_SWRST		    15


		// CR2 bit position definition

#define I2C_CR2_FREQ			0
#define I2C_CR2_ITERREN		    8
#define I2C_CR2_ITEVTEN		    9
#define I2C_CR2_ITBUFEN		    10
#define I2C_CR2_DMAEN		    11
#define I2C_CR2_LAST		    12

		// OAR1 bit position definition

#define I2C_OAR1_ADD0			0
#define I2C_OAR1_ADD			1
#define I2C_OAR1_AD1			8
#define I2C_OAR1_ADDMODE		15

		// OAR2 bit position definition

#define I2C_OAR2_ENDUAL			0
#define I2C_OAR2_ADD2			1

		// DR bit position definition

#define I2C_DR_DR			0

		// SR1 bit position definition

#define I2C_SR1_SB			    0
#define I2C_SR1_ADDR		    1
#define I2C_SR1_BTF		    	2
#define I2C_SR1_ADD10		    3
#define I2C_SR1_STOPF		    4
#define I2C_SR1_RxNE		    6
#define I2C_SR1_TxE				7
#define I2C_SR1_BERR		    8
#define I2C_SR1_ARLO		    9
#define I2C_SR1_AF		    	10
#define I2C_SR1_OVR		    	11
#define I2C_SR1_PECERR		    12
#define I2C_SR1_TIMEOUT		    14
#define I2C_SR1_SMBALERT		15

		// SR2 bit position definition

#define I2C_SR2_MSL			    0
#define I2C_SR2_BUSY		    1
#define I2C_SR2_TRA				2
#define I2C_SR2_GENCALL			4
#define I2C_SR2_SMBDEFAULT		5
#define I2C_SR2_SMBHOST			6
#define I2C_SR2_DUALF			7
#define I2C_SR2_PEC				8

		// CCR bit position definition

#define I2C_CCR_CCR				0
#define I2C_CCR_DUTY			14
#define I2C_CCR_FS				15

		// TRISE bit position definition

#define I2C_TRISE_TRISE			0

		// FLTR bit position definition

#define I2C_FLTR_DNF			0
#define I2C_FLTR_ANOFF			4




#endif /* INC_STM32F407XX_H_ */
