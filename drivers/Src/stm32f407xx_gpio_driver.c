/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: 25-Oct-2021
 *      Author: pro
 */

#include "stm32f407xx_gpio_driver.h"
#include <stdio.h>


// clock control api for gpio
void GPIO_PeripClockControl(GPIO_RegDef_t *pGPIOx , uint8_t EnorDi) {

	if(EnorDi == ENABLE){

		if (pGPIOx == GPIOA) {
			GPIOA_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOB) {
			GPIOB_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOC){
			GPIOC_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOD){
			GPIOD_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOE){
			GPIOE_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOF){
			GPIOF_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOG){
			GPIOG_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOH){
			GPIOH_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOI){
			GPIOI_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOJ){
			GPIOJ_CLOCK_ENABLE();
		}else if (pGPIOx == GPIOK){
			GPIOK_CLOCK_ENABLE();
		}

	}else{
		if (pGPIOx == GPIOA) {
			GPIOA_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOB) {
			GPIOB_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOC){
			GPIOC_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOD){
			GPIOD_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOE){
			GPIOE_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOF){
			GPIOF_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOG){
			GPIOG_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOH){
			GPIOH_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOI){
			GPIOI_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOJ){
			GPIOJ_CLOCK_DISABLE();
		}else if (pGPIOx == GPIOK){
			GPIOK_CLOCK_DISABLE();
		}
	}
}

// gpio init and deinit apis
void GPIO_Init(GPIO_Handle_t* pGPIOHandle) {
			uint32_t temp = 0 ;

//			// enable the peripheral clock
			GPIO_PeripClockControl(pGPIOHandle->pGPIOx, ENABLE) ;

	// configure the modes of a gpio pin
		// configuring non interrupt modes
		if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOGE ) {
			temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)) ;
			pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // @bug fix required
			pGPIOHandle->pGPIOx->MODER |= temp ;


		}else{
			// it is interrupt mode

			if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) {

				// configure the ftsr register
				EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
				// clear the rtsr bit
				EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;

			}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){

				// configure the rtsr register
				EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
				// clear the rtsr bit
				EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;

			}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
				// configure the rftsr register
				// configure the rtsr register
				EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
				// clear the rtsr bit
				EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;

			}

			// configure the gpio port selection in syscfg_exticr
				// syscfg SYSCFG_EXTICR[x] configures which pin of which port issues interrupt
			uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4  ;
			uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4  ;
			uint8_t portcode = (GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx)) ;
				// enabling the clock for syscfg before configuring the registers for syscfg
			SYSCFG_CLOCK_ENABLE() ;
			SYSCFG->EXTICR[temp1] |= (portcode << ( temp2 * 4) );

			// enable the interrupt delivery in exti
			EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;

		}
				temp = 0;

	// configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ) ;
	pGPIOHandle->pGPIOx->OSPEEDR  &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
	pGPIOHandle->pGPIOx->OSPEEDR  |= temp ;
	temp = 0 ;

	// configure the pupd control
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPUPDControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ) ;
	pGPIOHandle->pGPIOx->PUPDR  &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
	pGPIOHandle->pGPIOx->PUPDR  |= temp ;
	temp = 0 ;

	// configure the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ) ;
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
	pGPIOHandle->pGPIOx->OTYPER |= temp ;
	temp = 0 ;


	// configure the alternate functionality
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		// configure the alternate function registers
		uint8_t temp1 , temp2 ;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber  / 8 ;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8 ;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)) ;
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)) ;


	}

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx ) {

	if (pGPIOx == GPIOA) {
		GPIOA_REG_RESET() ;
	} else if (pGPIOx == GPIOB){
		GPIOB_REG_RESET() ;
	}else if (pGPIOx == GPIOC){
		GPIOC_REG_RESET() ;
	}else if (pGPIOx == GPIOD){
		GPIOD_REG_RESET() ;
	}else if (pGPIOx == GPIOE){
		GPIOE_REG_RESET() ;
	}else if (pGPIOx == GPIOF){
		GPIOF_REG_RESET() ;
	}else if (pGPIOx == GPIOG){
		GPIOG_REG_RESET() ;
	}else if (pGPIOx == GPIOH){
		GPIOH_REG_RESET() ;
	}else if (pGPIOx == GPIOI){
		GPIOI_REG_RESET() ;
	}else if (pGPIOx == GPIOJ){
		GPIOJ_REG_RESET() ;
	}else if (pGPIOx == GPIOK){
		GPIOK_REG_RESET() ;
	}


}

// gpio read and write to port ot pin
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber) {

	uint8_t value ;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber)& 0x00000001 );
	return value ;

}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx ) {

	uint16_t value ;
	value = (uint16_t)(pGPIOx->IDR ) ;
	return value ;

}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber , uint8_t Value) {

	if (Value == GPIO_PIN_SET) {
		// write 1 to the bit field corresponding pin number
		pGPIOx->ODR |= (1 << PinNumber) ;

	} else {
		// write 0  to the bit field corresponding pin number
		pGPIOx->ODR &= ~(1 << PinNumber) ;
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx ,uint16_t Value ) {

	pGPIOx->ODR = Value ;

}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber ) {

	pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber) ;

}

// gpio IRQ config and handling
void GPIO_IRQConfig(uint8_t IRQ_Number , uint8_t PinNumber , uint8_t EnorDi) {


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

void GPIO_IRQ_ProrityConfig(uint8_t IRQ_Number , uint32_t Interrupt_Prority ){

	// find the appropriate ipr register

	uint8_t iprx = IRQ_Number / 4 ;
	uint8_t iprx_section = IRQ_Number % 4 ;
	uint8_t shift_ammount = (8 * iprx_section) + NO_PR_BITS_IMPLEMENTED ;
	*(NVIC_IPR_BASE_ADDR + iprx) |= (Interrupt_Prority << shift_ammount) ;

}

void GPIO_IRQHandling(uint8_t PinNumber  ){

	//  clear the exti pr register corresponding to the pin number
	if (EXTI->PR & (1 << PinNumber)) {

		printf("inside isr handler \n") ;
		printf("pin no %d \n " , PinNumber) ;

		// clear the pr register and clear the interrupt
		EXTI->PR |= (1 << PinNumber) ;
	}

}
