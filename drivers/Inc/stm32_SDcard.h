/*
 * stm32_SDcard.h
 *
 *  Created on: 10-Jan-2022
 *      Author: pro
 */

#ifndef INC_STM32_SDCARD_H_
#define INC_STM32_SDCARD_H_


void readBlockSingle(uint32_t blockIndex ) ;
void writeBlockSingle(uint32_t blockIndex , uint8_t data) ;
void readBlockMultiple(uint32_t blockIndex ) ;
void writeBlockMultiple() ;
void stopTransfer() ;

#endif /* INC_STM32_SDCARD_H_ */
