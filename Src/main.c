/*
 * spi_tx_testing.c
 *
 *  Created on: 03-Nov-2021
 *      Author: pro
 */

// branch v1.2_reformat

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include "stm32_SDcard.h"
#include "fsfat32.h"

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

//	MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);


	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// pin for NSS pin
	SPIPins.pGPIOx = GPIOB ;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType= GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10 ;
	GPIO_Init(&SPIPins) ;

}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV64;//generates sclk of 8MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}


int main (void ){
	uint8_t SD_BUFFER [514] = "";	// last two bytes are for CRC and do not belong to thw data in the sector

	printf("application running \n") ;

	SPI2_GPIOInits(); 	// setup the gpio pins for spi communication
	deselectSDcard();
	SPI2_Inits();		// spi2 initialization like sclk speed and cpol and cpha
	//spi ssi config
	SPI_SSIConfig(SPI2, ENABLE) ;	// mandate for software slave management
	// enable the spi peripheral
	SPI_PeripheralControl(SPI2, ENABLE) ; // enable spi2 for communiation
	// send data over spi

	SD_init();

	readBPBandcompute(SD_BUFFER);

	while(1);

	return 0;
}

