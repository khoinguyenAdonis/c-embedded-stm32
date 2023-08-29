/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

  /* ADC1 interrupt Init */
  NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(ADC_IRQn);

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_UNITARY_CONV);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_VREFINT);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_VREFINT, LL_ADC_SAMPLINGTIME_3CYCLES);
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_VREFINT);
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/* USER CODE BEGIN 1 */
static uint32_t DMABuffer = 0;
extern uint8_t adc_done;
uint32_t data;
void start_adc(void)
{
  LL_ADC_EnableIT_EOCS(ADC1);
  LL_ADC_Enable(ADC1);
  Hal_Delay(10);
  LL_ADC_REG_StartConversionSWStart(ADC1);
  while (!adc_done){};
  return LL_ADC_REG_ReadConversionData12(ADC1);
}

void change_conver(void)
{
  data = start_adc();
}
void DMA_Start(void)
{
   LL_ADC_REG_SetDMATransfer(ADC1,LL_ADC_REG_DMA_TRANSFER_LIMITED);
}
void ADC_config_DMA(void)
{
  // disable dma
  LL_DMA_DisableStream(DMA2,LL_DMA_STREAM_0);
  
  //get address pheria
  LL_DMA_SetPeriphAddress(DMA2,LL_DMA_STREAM_0,LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA));
  // set memory address 
  LL_DMA_SetMemoryAddress(DMA2,LL_DMA_STREAM_0,(uint32_t)&DMABuffer);
  // configure number of data 
  LL_DMA_SetDataLength(DMA2,LL_DMA_STREAM_0,0xFFFFFFFF);
  // select channel DMA
  LL_DMA_SetChannelSelection(DMA2,LL_DMA_STREAM_0,LL_DMA_CHANNEL_0);
  // select stream priority level
  LL_DMA_SetStreamPriorityLevel(DMA2,LL_DMA_STREAM_0,LL_DMA_PRIORITY_LOW);
  // configure FIFO 
  LL_DMA_DisableFifoMode(DMA2,LL_DMA_STREAM_0);
  // direction data stranfer
  LL_DMA_SetDataTransferDirection(DMA2,LL_DMA_STREAM_0,LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  //peripheral and memory incremented/fixed mode
  LL_DMA_SetMode(DMA2,LL_DMA_STREAM_0,LL_DMA_MODE_NORMAL);
  LL_DMA_SetPeriphIncMode(DMA2,LL_DMA_STREAM_0,LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(DMA2,LL_DMA_STREAM_0,LL_DMA_MEMORY_NOINCREMENT);
  LL_DMA_SetPeriphSize(DMA2,LL_DMA_STREAM_0,LL_DMA_PDATAALIGN_HALFWORD);
  LL_DMA_GetMemorySize(DMA2,LL_DMA_STREAM_0,LL_DMA_PDATAALIGN_HALFWOR);
  // single or burst transactions
  LL_DMA_SetMemoryBurstxfer(DMA2,LL_DMA_STREAM_0,LL_DMA_MBURST_SINGLE);
  // enable interup
  LL_DMA_EnableIT_TE(DMA2,LL_DMA_STREAM_0);
  //enable dma
  LL_DMA_EnableStream(DMA2,LL_DMA_STREAM_0);}
  void adc_demo_test(void)
{
  static uint16_t  adc_raw = 0;
  static uint16_t  adc_v = 0;
  while ()

  adc_raw = __adc_single_convert();
  adc_v = (float)(adc_raw) * (float)(ADC_CONV_RATIO);
}
/* USER CODE END 1 */
