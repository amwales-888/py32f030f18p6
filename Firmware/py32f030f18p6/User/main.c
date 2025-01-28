/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "main.h"
#include "py32f0xx_ll_gpio.h"
#include "py32f0xx_ll_usart.h"


static void APP_SystemClockConfig(void);
static void APP_GPIOConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static int APP_UsartReceiveByte(USART_TypeDef *USARTx, uint8_t *ptr);
static int APP_UsartSendByte(USART_TypeDef *USARTx, uint8_t b);

static void outputMessage(void) {

	static uint8_t *msg = (uint8_t *)"hello world\r\n";
	static uint8_t i = 0;
	
	if (APP_UsartSendByte(USART1, msg[i]) != 0) {
		i++;
		if (msg[i] == '\0') {
			i = 0;
		}
	}	
}

int main(void)
{
  APP_SystemClockConfig();
  APP_GPIOConfig();
	
	APP_ConfigUsart(USART1);
	
	
  while (1)
  {
		outputMessage();
    LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_5);
    LL_mDelay(1000);
  }
}

static void APP_SystemClockConfig(void)
{
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1);

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS);

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  LL_SetSystemCoreClock(8000000);
}


static void APP_GPIOConfig(void)
{
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
}

void APP_ErrorHandler(void)
{
  while (1);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1);
}
#endif /* USE_FULL_ASSERT */


static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  if (USARTx == USART1) 
  {
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
  }
  else if (USARTx == USART2)
  {
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
  }
  
  LL_USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.BaudRate = 9600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  LL_USART_ConfigAsyncMode(USARTx);
  
  LL_USART_Enable(USARTx);
}


static int APP_UsartReceiveByte(USART_TypeDef *USARTx, uint8_t *ptr) {
	
	if (LL_USART_IsActiveFlag_RXNE(USARTx) == 1) {
		*ptr = LL_USART_ReceiveData8(USARTx);
		return 1;
	}
	
	return 0;
}

static int APP_UsartSendByte(USART_TypeDef *USARTx, uint8_t b) {
	
	if (LL_USART_IsActiveFlag_TXE(USARTx) == 1) {		
		LL_USART_TransmitData8(USARTx, b);
		return 1;
	}
	
	return 0;
}



