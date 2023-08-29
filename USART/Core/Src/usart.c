/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#define CONFIG_UART_USE_DMA         (1)
#if CONFIG_UART_USE_DMA == 0
    #define CONFIG_UART_USE_IT     (1)
#endif
/* USER CODE END 0 */

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART2 DMA Init */

  /* USART2_TX Init */
  LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_6, LL_DMA_CHANNEL_4);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_6, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_6, LL_DMA_PRIORITY_MEDIUM);

  LL_DMA_SetMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_6, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_6, LL_DMA_MDATAALIGN_BYTE);

  LL_DMA_DisableFifoMode(DMA1, LL_DMA_STREAM_6);

  /* USART2_RX Init */
  LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_5, LL_DMA_CHANNEL_4);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_5, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_5, LL_DMA_PRIORITY_MEDIUM);

  LL_DMA_SetMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_5, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_5, LL_DMA_MDATAALIGN_BYTE);

  LL_DMA_EnableFifoMode(DMA1, LL_DMA_STREAM_5);

  LL_DMA_SetFIFOThreshold(DMA1, LL_DMA_STREAM_5, LL_DMA_FIFOTHRESHOLD_1_4);

  LL_DMA_SetMemoryBurstxfer(DMA1, LL_DMA_STREAM_5, LL_DMA_MBURST_SINGLE);

  LL_DMA_SetPeriphBurstxfer(DMA1, LL_DMA_STREAM_5, LL_DMA_PBURST_SINGLE);

  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(USART2_IRQn);

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_8;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/* USER CODE BEGIN 1 */

   
extern uint8_t RXbuffer[128U];
void config_UART(void)
{
  /* Enable the USART by writing the UE bit in USART_CR1 register to 1.*/
  LL_USART_Enable(USART2);
}
uint8_t Databuffer[128U] = {0};
volatile uint32_t buf_ptr = 0;
static void inline _USART_Put_Char(uint8_t c)
{
  if (buf_ptr>128U){
    buf_ptr = 0U;
  }
  Databuffer[buf_ptr] = c;
  __disable_irq();
  buf_ptr +=1;
  __enable_irq();
}
#if CONFIG_UART_USE_IT
void send_data(const char* str, uint32_t len)
{
  if (str == 0 ){return ;}; // 
  while (!LL_USART_IsActiveFlag_TC(USART2)){};
  while(len--) // check null
  {
    _USART_Put_Char(*str++);
   
  }
  /*===========================TX==configure====================*/
    LL_USART_EnableDirectionTx(USART2);
  #if CONFIG_UART_USE_IT
    LL_USART_EnableIT_TXE(USART2);
  #endif
void UART_RX_Data(void)
{
  /*===========================RX==configure====================*/
  /* Set bit RE USART_>CR1*/
  LL_USART_EnableDirectionRx(USART2);
  /* Use Interrup*/
  #if CONFIG_UART_USE_IT
    LL_USART_EnableIT_RXNE(USART2);
  #endif
}
}
#else
void send_data(const char* str, uint32_t len)
{
  memcpy(Databuffer,str,len);
  USART_DMA_Trans(Databuffer,len)
}
void  UART_RX_Data(void)
{
  RX_DMA();
}
#endif


void USART_DMA_Enable(void)
{

}
void USART_DMA_Trans(const char* user_buf, uint32_t  user_len )
{
  // disable stream
  LL_DMA_DisableStream(DMA1,LL_DMA_STREAM_6);
  // set PeriphAddress
  LL_DMA_SetPeriphAddress(DMA1,LL_DMA_STREAM_6,LL_USART_DMA_GetRegAddr(USART2));
  // set mmraddress
  LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_6,(uint32_t)user_buf);
  // set data total number
  LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_6,user_len);
  // Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR register. init
  // 
  LL_USART_EnableDMAReq_TX(USART2);
  LL_DMA_EnableIT_TC(DMA1,LL_DMA_STREAM_6);
  // enable stream 
  LL_DMA_EnableStream(DMA1,LL_DMA_STREAM_6);

} 
void RX_DMA()
 {
  LL_DMA_DisableStream(DMA1,LL_DMA_STREAM_5);
  LL_DMA_SetPeriphAddress(DMA1,LL_DMA_STREAM_5,LL_USART_DMA_GetRegAddr(USART2));
  LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_5,&RXbuffer);
  LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_5,user_len);
  LL_USART_EnableDMAReq_RX(USART2);
  LL_DMA_EnableIT_TC(DMA1,LL_DMA_STREAM_5);
  LL_DMA_EnableStream(DMA1,LL_DMA_STREAM_5);
}
/* USER CODE END 1 */
