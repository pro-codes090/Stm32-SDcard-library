/*
 * stm32f407XX_spi_driver.c
 *
 *  Created on: 03-Nov-2021
 *      Author: pro
 */


#include "stm32f407xx_spi_driver.h"

// spi peripheral clock control

void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx , uint8_t EnorDi) {

	if (EnorDi == ENABLE) {

		if (pSPIx == SPI1) {

			SPI1_CLOCK_ENABLE();

		}else if (pSPIx == SPI2) {

			SPI2_CLOCK_ENABLE();

		}else if (pSPIx == SPI3) {

			SPI3_CLOCK_ENABLE();

		}


	}else{

		if (pSPIx == SPI1) {

			SPI1_CLOCK_DISABLE();

		}else if (pSPIx == SPI2){

			SPI2_CLOCK_DISABLE();

		}else if (pSPIx == SPI3) {

			SPI3_CLOCK_DISABLE();

		}

	}

}
// init and deinit apis
void SPI_Init(SPI_Handle_t *pSPIHandle) {

	// enable the clock
	SPI_PeripheralClockControl(pSPIHandle->pSPIx, ENABLE ) ;

// first configure the spi_cr1 register

	uint32_t tempreg = 0 ;

		// configure the the spi device mode
		tempreg |=  ( pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR) ;

	// configure the bus config
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD) {

		// BIDIMODE should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE) ;

	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD) {

		// BIDIMODE should be set
		tempreg |=  ( 1 << SPI_CR1_BIDIMODE) ;

	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY) {

		// BIDIMODE should be cleared ;
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE) ;

		// RXOONLY bit should be set
		tempreg |=  ( 1 << SPI_CR1_RXONLY) ;

	}

	// configure spi clock speed
	tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR) ;

	// configure spi dff mode
	tempreg |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF) ;

	// configure spi cpol
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL) ;

	// configure spi cpha
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPHA) ;

	// configure spi ssm
	tempreg |= (pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM) ;

	pSPIHandle->pSPIx->CR1 = tempreg ;

}
void SPI_DeInit(SPI_RegDef_t *pSPIx) {

	if (pSPIx == SPI1) {
		SPI1_REG_RESET() ;
	}else if (pSPIx == SPI2) {
		SPI2_REG_RESET() ;
	}else if (pSPIx == SPI3) {
		SPI3_REG_RESET() ;
	}


}
// Spi send and receive apis
void SPI_Send(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer , uint32_t length) {

	while(length > 0 ) {

		// check for tx buffer empty state
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET) {

		}

		if ((pSPIx->CR1 & (1 << SPI_CR1_DFF))) {

			// 16 bit data format
			// load 16 bit of data into DR
			pSPIx->DR = *((uint16_t*)pTxBuffer) ;
			length-- ;
			length-- ;
			(uint16_t*)pTxBuffer++ ;

		} else {
			// load 8 bit data into DR
			pSPIx->DR = *pTxBuffer ;
			length-- ;
			pTxBuffer++ ;
//			printf("s \n ") ;

		}
	}

}
void SPI_Read(SPI_RegDef_t *pSPIx , uint8_t *pRxBuffer , uint32_t length) {

	while(length > 0 ) {

		// check for rx buffer empty state
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET) {

		}

		if ((pSPIx->CR1 & (1 << SPI_CR1_DFF))) {

			// 16 bit data format
			// read 16 bit of data into DR
			 *((uint16_t*)pRxBuffer) = pSPIx->DR ;
			length-- ;
			length-- ;
			(uint16_t*)pRxBuffer++ ;

		} else {
			// load 8 bit data into DR
			*pRxBuffer = pSPIx->DR ;
			length-- ;
			pRxBuffer++ ;

		}
     }
  }

//spi get flag status
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName ){

	if ((pSPIx->SR &  (FlagName))) {

		return FLAG_SET ;
	}

	return FLAG_RESET ;
}

// Spi peripheral enable

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SPE);
	}


}

// Spi SSI configuration

void  SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SSI);
	}


}

// Spi SSOE configuration

void  SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |=  (1 << SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &=  ~(1 << SPI_CR2_SSOE);
	}


}


// spi interrupt configuration

void SPI_IRQInterruptConfig(uint8_t IRQ_Number , uint8_t EnorDi ) {



	if (EnorDi == ENABLE ) {

		if (IRQ_Number <= 31) {
			// configure iser 0 register
			*NVIC_ISER0 |= ( 1 << IRQ_Number) ;

		} else if (IRQ_Number > 31 && IRQ_Number < 64){
			// configure iser 1 register
			*NVIC_ISER1 |= ( 1 << ( IRQ_Number % 32 )) ;

		} else if (IRQ_Number >= 64 && IRQ_Number < 96){
			// configure iser 2 register
			*NVIC_ISER2 |= ( 1 << ( IRQ_Number % 64 )) ;

	 }
   }else {

		if (IRQ_Number <= 31) {
			// configure iser 0 register
		*NVIC_ICER0 |= ( 1 << IRQ_Number) ;

		} else if (IRQ_Number > 31 && IRQ_Number < 64){
			// configure iser 1 register
			*NVIC_ICER1 |= ( 1 << ( IRQ_Number % 32 ) ) ;

		} else if (IRQ_Number > 64 && IRQ_Number < 96){
			// configure iser 2 register
			*NVIC_ICER2 |= ( 1 << ( IRQ_Number % 64 )) ;

	 }
  }


}


uint8_t SPI_SendIT(SPI_Handle_t *pSPIHandle , uint8_t *pTxBuffer , uint32_t length) {

	uint8_t state = pSPIHandle->TxState ;

	if (state != SPI_BUSY_IN_TX) {

		// save the buffer address and len in some global variable
		pSPIHandle->pTxBuffer = pTxBuffer ;	// saving the buffer address
		pSPIHandle->TxLen = length        ;	// saving the buffer length

		// Set the spi state is busy in transmission
		pSPIHandle->TxState = SPI_BUSY_IN_TX ;

		// enable the txeie bit to get an interrupt when the txe flag is set in sr
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE) ;

		// data transmission will happen in ISR handler
	}

	return state ;
}


void SPI_CloseTransmissionIT(SPI_Handle_t *pSPIHandle ) {

	// deactiivate the txe interrupt
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE) ;

		//  reset the tx buffer
		pSPIHandle->pTxBuffer = NULL ;

		// reset the tx length to zero 0
		pSPIHandle->TxLen = 0 ;

		// reset the tx state to spi_ready
		pSPIHandle->TxState = SPI_READY ;

}

void SPI_CloseRecptionIT(SPI_Handle_t *pSPIHandle ) {


	// deactivate the rxne interrupt
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE) ;

	//  reset the tx buffer
	pSPIHandle->pRxBuffer= NULL ;

	// reset the tx length to zero 0
	pSPIHandle->RxLen = 0 ;

	// reset the tx state to spi_ready
	pSPIHandle->RxState = SPI_READY ;


}


// spi txe interrupt handler
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle){

	if ((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))) {

		// 16 bit data format
		// load 16 bit of data into DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)(pSPIHandle->pTxBuffer)) ;
		pSPIHandle->TxLen -- ;
		pSPIHandle->TxLen -- ;
		((uint16_t*)(pSPIHandle->pTxBuffer)++) ;

	 } else {
		// load 8 bit data into DR
		 pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer) ;
		 pSPIHandle->TxLen --;
		 (pSPIHandle->pTxBuffer)++ ;

	}

	if (pSPIHandle->TxLen <= 0) {

		// tx len is zero , communication needs to be closed and inform the application transmission is over

		// deactiivate the txe interrupt
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE) ;

		//  reset the tx buffer
		pSPIHandle->pTxBuffer = NULL ;

		// reset the tx length to zero 0
		pSPIHandle->TxLen = 0 ;

		// reset the tx state to spi_ready
		pSPIHandle->TxState = SPI_READY ;

		// inform the application about the data transfer event completion
		SPI_ApplicationEventCallBack(pSPIHandle , SPI_EVENT_TX_CMPLT) ;


	}

}

// spi rxne interrupt handler
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle){

	if ((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))) {

		// 16 bit data format
		// read 16 bit of  data from DR
		*((uint16_t*)(pSPIHandle->pRxBuffer)) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen -- ;
		pSPIHandle->RxLen -- ;
		((uint16_t*)(pSPIHandle->pRxBuffer)++) ;

	 } else {
		// Read 8 bit data from DR
		 *(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR ;
		 pSPIHandle->RxLen --;
		 (pSPIHandle->pRxBuffer)++ ;

	}

	if (pSPIHandle->RxLen <= 0) {

		// Rx len is zero , communication needs to be closed and inform the application Recption is over

		// deactivate the rxne interrupt
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE) ;

		//  reset the tx buffer
		pSPIHandle->pRxBuffer= NULL ;

		// reset the tx length to zero 0
		pSPIHandle->RxLen = 0 ;

		// reset the tx state to spi_ready
		pSPIHandle->RxState = SPI_READY ;

		// inform the application about the data transfer event completion
		SPI_ApplicationEventCallBack(pSPIHandle , SPI_EVENT_RX_CMPLT) ;


	}



}

static void spi_error_interrupt_handle(SPI_Handle_t *pSPIHandle){

	uint8_t temp ;
	// clear the over flag

	/* directly readign the DR register causes the ovr flag to reset but the value in the DR may be required
	 * by the application thats why we read the dr to clear the ovr flag only when spi is not transmitting because
	 *  we receive data only when there is clock and clock only happens when master is transmitting */
	if (pSPIHandle->TxState != SPI_BUSY_IN_TX) {

		// read operation to dr register
		temp = pSPIHandle->pSPIx->DR ;

		// read operation to sr register
		temp = pSPIHandle->pSPIx->SR;

	}
	(void)temp ;

	// inform the application about the error
	SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_OVR_ERR) ;

}

uint8_t SPI_ReadIT(SPI_Handle_t *pSPIHandle , uint8_t *pRxBuffer , uint32_t length) {

	uint8_t state = pSPIHandle->RxState ;

	if (state != SPI_BUSY_IN_RX) {

		// save the buffer address and len in some global variable
		pSPIHandle->pRxBuffer = pRxBuffer ;	// saving the buffer address
		pSPIHandle->RxLen = length        ;	// saving the buffer length

		// Set the spi state is busy in transmission
		pSPIHandle->RxState = SPI_BUSY_IN_RX ;

		// enable the txeie bit to get an interrupt when the txe flag is set in sr
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE) ;

		// data transmission will happen in ISR handler
	}

	return state ;

}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){

	uint8_t temp ;
	temp = pSPIx->DR ;
	temp = pSPIx->SR ;
	(void)temp ; /// suppress complier warnings

}

void SPI_IRQPriorityConfig(uint8_t IRQ_Number , uint32_t Interrupt_Prority ) {

	// find the appropriate ipr register


	uint8_t iprx = IRQ_Number / 4 ;
	uint8_t iprx_section = IRQ_Number % 4 ;
	uint8_t shift_ammount = (8 * iprx_section) + NO_PR_BITS_IMPLEMENTED ;
	*(NVIC_IPR_BASE_ADDR + iprx) |= (Interrupt_Prority << shift_ammount) ;


}
void SPI_IRQHandling (SPI_Handle_t *pSPIHandle) {

	uint8_t temp1 , temp2 ;

	// check for txe

	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_TXE) ;
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE) ;

	if (temp1 && temp2) {
		// handling txe interrupt
		spi_txe_interrupt_handle(pSPIHandle) ;
	}

	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE) ;
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE) ;

	if (temp1 && temp2) {
		// handling rxne  interrupt

		spi_rxne_interrupt_handle(pSPIHandle) ;
	}

	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_OVR) ;
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE) ;

	if (temp1 && temp2) {
		// handling the error interrupt
		spi_error_interrupt_handle(pSPIHandle) ;
	}

}


__attribute__((weak))void SPI_ApplicationEventCallBack(SPI_Handle_t *pSPIHandle , uint8_t eventcode) {

	// This is weak implementation of application callback function

	if (eventcode == SPI_EVENT_TX_CMPLT) {
		printf("transmission completed \n") ;
	} else if(eventcode == SPI_EVENT_RX_CMPLT){
		printf("Reception completed \n") ;
	}else if (eventcode == SPI_EVENT_OVR_ERR) {
		printf("OVR error has occurred clearing now \n") ;
	}else if (eventcode == SPI_EVENT_CRC_ERR) {
		printf("CRC Error has occurred \n ") ;
	}

}


