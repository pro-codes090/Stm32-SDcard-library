/*
 * stm32_SDcard.h
 *
 *  Created on: 10-Jan-2022
 *      Author: pro
 */

#ifndef INC_STM32_SDCARD_H_
#define INC_STM32_SDCARD_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"

void readBlockSingle(uint32_t blockIndex ) ;
void writeBlockSingle(uint32_t blockIndex , uint8_t data) ;

#endif /* INC_STM32_SDCARD_H_ */
