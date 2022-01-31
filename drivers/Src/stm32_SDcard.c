/*
 * stm32_SDcard.c
 *
 *  Created on: 29-Jan-2022
 *      Author: pro
 */

#include "stm32_SDcard.h"


void deselectSDcard(){GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10, SET);}
void selectSDcard(){GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_10, RESET);}

static void sdPowerUp(){
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;
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

static void sdInitSeq(){
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;
	uint8_t res7 = 0 ;
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

static void readOCR() {
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;

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

static void sd_final_Init(){
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;

	SPI_PeripheralControl(SPI2, DISABLE) ;
	deselectSDcard();
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;//generates sclk of 8MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

	SPI_Init(&SPI2handle);

	SPI_SSIConfig(SPI2, ENABLE) ;	// mandate for software slave management
	// enable the spi peripheral
	SPI_PeripheralControl(SPI2, ENABLE) ; // enable spi2 for communiation

uint8_t res1 = 0xff ;
while(res1 != 0x00){

printf("CMD55 \n") ;
Data[0] = 	0x77 ;
Data[1] = 	0x00 ;
Data[2] = 	0x00 ;
Data[3] = 	0x00 ;
Data[4] = 	0x00 ;
Data[5] =   (0x00 | 0x01);

SPI_Send(SPI2, &dummyByte, 1) ;
// delay some time
for (uint16_t i = 0;  i < 1000; i++) {}
selectSDcard() ;
SPI_Send(SPI2, &dummyByte, 1) ;

//ACMD55
SPI_Send(SPI2, Data, 6);

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &res1, 1) ;
printf("1 %p \n" , res1) ;

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &res1, 1) ;
printf("1 %p \n" , res1) ;


SPI_Send(SPI2, &dummyByte, 1) ;
// delay some time
for (uint16_t i = 0;  i < 1000; i++) {}
deselectSDcard();
SPI_Send(SPI2, &dummyByte, 1) ;

printf("ACMD41 \n") ;
Data[0] = 	0x69 ;
Data[1] = 	0x40 ;
Data[2] = 	0x00 ;
Data[3] = 	0x00 ;
Data[4] = 	0x00 ;
Data[5] =   (0x00 | 0x01);

SPI_Send(SPI2, &dummyByte, 1) ;
// delay some time
for (uint16_t i = 0;  i < 1000; i++) {}
selectSDcard() ;
SPI_Send(SPI2, &dummyByte, 1) ;

//ACMD41
SPI_Send(SPI2, Data, 6);

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &res1, 1) ;
printf("1 %p \n" , res1) ;

SPI_Send(SPI2, &dummyByte, 1) ;
SPI_Read(SPI2, &res1, 1) ;
printf("1 %p \n" , res1) ;


SPI_Send(SPI2, &dummyByte, 1) ;
// delay some time
for (uint16_t i = 0;  i < 1000; i++) {}
deselectSDcard();
SPI_Send(SPI2, &dummyByte, 1) ;

  }
printf("Init Success \n ") ;
}

static void prepReadWrite(){
	SPI_PeripheralControl(SPI2, DISABLE) ;
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

}

void readBlockSingle(uint32_t blockIndex , uint8_t *buffAddr){
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;
	uint8_t dummyReadByte = 0xff ;
uint8_t res1 = 0xff ;
	printf("CMD17\n") ;
	Data[0] = 	0x51 ;
	Data[1] = 	(blockIndex >> 24) ;
	Data[2] = 	(blockIndex >> 16) ;
	Data[3] = 	(blockIndex >> 8) ;
	Data[4] = 	(blockIndex >> 0) ;
	Data[5] =   (0x00 | 0x01);

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	selectSDcard() ;
	SPI_Send(SPI2, &dummyByte, 1) ;

	SPI_Send(SPI2, Data, 6);

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res1, 1) ;
	printf("1 %p \n" , res1) ;

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res1, 1) ;
	printf("1 %p \n" , res1) ;

	for (uint16_t j = 0; j < 515; j++) {
		SPI_Send(SPI2, &dummyByte, 1) ;
		SPI_Read(SPI2, &dummyReadByte, 1) ; // dummy reaad
		if (dummyReadByte == 0xFE) {
			for (uint16_t i = 0;  i < 514; i++) {
		SPI_Send(SPI2, &dummyByte, 1) ;
		SPI_Read(SPI2, buffAddr, 1) ; // dummy read
		if (i == 510) {
			printf("1 signature is %p \n" , *buffAddr) ;
		}else if (i == 511) {
			printf("2 signature is %p \n" , *buffAddr) ;
		}else if (i == 512) {
			printf("2 CRC is %p \n" , *buffAddr) ;
		}else if (i == 513) {
			printf("2 CRC is %p \n" ,*buffAddr) ;
			return ;
		}

		buffAddr++ ;
			}
	    }
	}

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;
}


void writeBlockSingle(uint32_t blockIndex , uint8_t *buffAddr){
	uint8_t Data [] = {0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,} ;
	uint8_t dummyByte = 0xff ;
	uint8_t dummyReadByte = 0xff ;
	uint8_t res1 = 0xff ;
	printf("CMD24\n") ;
	Data[0] = 	0x58 ;
	Data[1] = 	(blockIndex >> 24) ;
	Data[2] = 	(blockIndex >> 16) ;
	Data[3] = 	(blockIndex >> 8) ;
	Data[4] = 	(blockIndex >> 0) ;
	Data[5] =   (0x00 | 0x01);

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	selectSDcard() ;
	SPI_Send(SPI2, &dummyByte, 1) ;

	SPI_Send(SPI2, Data, 6);

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res1, 1) ;
	printf("1 %p \n" , res1) ;

	SPI_Send(SPI2, &dummyByte, 1) ;
	SPI_Read(SPI2, &res1, 1) ;
	printf("1 %p \n" , res1) ;

		if (res1 == 0) {
		dummyByte = 0xFE ;
		SPI_Send(SPI2, &dummyByte, 1) ;
		dummyByte = 0xff ;
		}
			for (uint16_t i = 0;  i < 512; i++) {
		SPI_Send(SPI2, buffAddr, 1) ;
		buffAddr++;
			}
			SPI_Send(SPI2, &dummyByte, 1) ;
			SPI_Read(SPI2, &dummyReadByte, 1) ;

			while((dummyReadByte & 0x0F) != 0x05){
			SPI_Send(SPI2, &dummyByte, 1) ;
			SPI_Read(SPI2, &dummyReadByte, 1) ;
			}
			   SPI_Send(SPI2, &dummyByte, 1) ;
						SPI_Read(SPI2, &dummyReadByte, 1) ;

			while(dummyReadByte == 0x00 ){
		    SPI_Send(SPI2, &dummyByte, 1) ;
			SPI_Read(SPI2, &dummyReadByte, 1) ;
			}

	SPI_Send(SPI2, &dummyByte, 1) ;
	// delay some time
	for (uint16_t i = 0;  i < 1000; i++) {}
	deselectSDcard();
	SPI_Send(SPI2, &dummyByte, 1) ;

}

void SD_init(){
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

	// perepare for read and write
	prepReadWrite();
}

