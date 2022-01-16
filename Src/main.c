/*
 * spi_tx_testing.c
 *
 *  Created on: 03-Nov-2021
 *      Author: pro
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"

uint8_t res7 = 0 ;
uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
uint8_t dummyByte = 0xff ;
uint8_t dummyReadByte = 0xff ;
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
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;//generates sclk of 8MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}

void deselectSDcard(){GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10, SET);}
void selectSDcard(){GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10, RESET);}

void sdPowerUp(){
	deselectSDcard();

	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	// sending 80 clock cycles
	uint8_t R1_Response = 0x0f; // store the R1 response for CMD 0
	SPI_Send(SPI2, Data, 10) ;

	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;
	// send CMD0 with CRC
	Data[0] = 0x40 ;
	Data[1] = 0x00 ;
	Data[2] = 0x00 ;
	Data[3] = 0x00 ;
	Data[4] = 0x00 ;
	Data[5] = 0x95 ;

		SPI_Send(SPI2, &dummyByte, 1) ;
		// delay some time
		for (uint16_t i = 0;  i < 1000; i++) {}
		selectSDcard() ;
		SPI_Send(SPI2, &dummyByte, 1) ;

	// send CMD0 wait for 1 byte R1 response
	SPI_Send(SPI2, Data, 6) ;
	// send some clock to get the R1 response towards master

	while (R1_Response != 0x01) {
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &R1_Response, 1) ;
	printf("%d\n" , R1_Response) ;
	}

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;
		printf("CMD0 r1 ideal \n") ;

}

void sdInitSeq(){

	printf("CMD8 \n ") ;
	Data[0] = 0x48 ;
	Data[1] = 0x00 ;
	Data[2] = 0x00 ;
	Data[3] = 0x01 ;
	Data[4] = 0xAA ;
	Data[5] = (0x86 | 0x01) ;

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	selectSDcard() ;
	SPI_Send(SPI2, &dummyByte, 1) ;

	SPI_Send(SPI2, Data, 6);

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("1 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("2 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("3 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("4 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("5 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("6 %p \n" , res7) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res7, 1) ;
	printf("7 %p \n" , res7) ;

	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;

}

void readOCR() {
uint8_t res3 ;
	printf("CMD58 \n ") ;
	Data[0] = 0x7A ;
	Data[1] = 0x00 ;
	Data[2] = 0x00 ;
	Data[3] = 0x00 ;
	Data[4] = 0x00 ;
	Data[5] = (0x00 | 0x01) ;

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	selectSDcard() ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Send(SPI2, Data, 6) ;

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("1 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("2 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("3 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("4 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("5 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("6 %p \n" , res3) ;
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res3, 1) ;
	printf("7 %p \n" , res3) ;

	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;

}

void sd_final_Init(uint8_t cardType){
	uint8_t R1_Response = 0xff ;
while(R1_Response != 0x00){

printf("CMD55 \n") ;
Data[0] = 	0x77 ;
Data[1] = 	0x00 ;
Data[2] = 	0x00 ;
Data[3] = 	0x00 ;
Data[4] = 	0x00 ;
Data[5] =   (0x00 | 0x01);

SPI_Send(SPI2, Data, 6);	// we are sending an application specific command
SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy reaad

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &R1_Response, 1) ;	// read the response for CMD55
printf("%d \n" , R1_Response ) ;

for (uint16_t i = 0; i <20000  ; i++) {}

printf("ACMD41 \n") ;
Data[0] = 	0x69 ;
Data[1] = 	0x40 ;
Data[2] = 	0x00 ;
Data[3] = 	0x00 ;
Data[4] = 	0x00 ;
Data[5] =   (0x00 | 0x01);

SPI_Send(SPI2, Data, 6);	// sending ACMD41
SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy reaad

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &R1_Response, 1) ;	// read the response for CMD55
printf("%d \n" , R1_Response ) ;

for (uint16_t i = 0; i <20000  ; i++) {}

   }
printf("Init Success \n ") ;
}

void readBlockSingle(uint32_t blockIndex ){

	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;//generates sclk of 8MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

	SPI_Init(&SPI2handle);

	SPI_SSIConfig(SPI2, ENABLE) ;	// mandate for software slave management
	// enable the spi peripheral
	SPI_PeripheralControl(SPI2, ENABLE) ; // enable spi2 for communiation

uint8_t R1_Response = 0xff ;
	printf("CMD17\n") ;
	Data[0] = 	0x51 ;
	Data[1] = 	(blockIndex >> 24) ;
	Data[2] = 	(blockIndex >> 16) ;
	Data[3] = 	(blockIndex >> 8) ;
	Data[4] = 	(blockIndex >> 0) ;
	Data[5] =   (0x00 | 0x01);

	SPI_Send(SPI2, Data, 6);	// sending ACMD41
	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy reaad

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &R1_Response, 1) ;	// read the response for CMD55
	printf("%d \n" , R1_Response ) ;

	for (uint16_t i = 0; i < 515; i++) {
		SPI_Send(SPI2, &dummyByte, 1) ;
		SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy reaad
		if (dummyReadByte == 0xFE) {
			for (uint16_t i = 0;  i < 515; i++) {
		SPI_Send(SPI2, &dummyByte, 1) ;
		SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy read
		printf("%p ", dummyReadByte) ;		// @needs to change
		if (i >= 514 ) {
			return ;
		}
			}
	    }
	}
}

int main (void ){
	printf("application running \n") ;

	SPI2_GPIOInits(); 	// setup the gpio pins for spi communication
	deselectSDcard();
	SPI2_Inits();		// spi2 initialization like sclk speed and cpol and cpha
	//spi ssi config
	SPI_SSIConfig(SPI2, ENABLE) ;	// mandate for software slave management
	// enable the spi peripheral
	SPI_PeripheralControl(SPI2, ENABLE) ; // enable spi2 for communiation
	// send data over spi

	// start up sequence of sdcard
	sdPowerUp();

	// sd card init sequence like voltage verification
	sdInitSeq();

	// read OCR CCS field
	readOCR();

	// send ACMD41
	 sd_final_Init(1);

	// read OCR CCS field again
	 readOCR();

	SPI_PeripheralControl(SPI2, DISABLE) ;
	deselectSDcard();
	 // read block of data , data at block 0

	SPI_PeripheralControl(SPI2, ENABLE)  ;
	selectSDcard() ;
	 readBlockSingle(0x0000ffff) ;

	//close the communication by disabling the peripherals


	while(1);

	return 0;
}

