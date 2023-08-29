/*
 * main.h
 *
 *  Created on: Jul 20, 2023
 *      Author: khoi7
 */

#ifndef MAIN_H_
#define MAIN_H_
#include<stdio.h>
#include<stdint.h>
#define ADDR_AHB1ENR 		((RCC_AHB1ENR*) 0x40023830)
#define ADDR_GPIOx_MODER 	((GPIOx_MODER*) 0x40020C00)
#define ADDR_GPIOX_ODR 		((GPIOX_ODR*)   0x40020C14)
#define CLOCK_ENABLE 		1
#define MOD_CONF_OUTP		1
#define PIN_STATE_HIGH		1
#define PIN_STATE_LOW		0
#define ANALOG_MOD			3
#define MOD_CPNF_INPUT		0
typedef struct
{
	uint32_t GPIOA_EN 		:1;
	uint32_t GPIOB_EN 		:1;
	uint32_t GPIOC_EN 		:1;
	uint32_t GPIOD_EN 		:1;
	uint32_t GPIOE_EN 		:1;
	uint32_t GPIOF_EN 		:1;
	uint32_t GPIOG_EN 		:1;
	uint32_t GPIOH_EN 		:1;
	uint32_t GPIOI_EN 		:1;
	uint32_t RESERVED1 		:3;
	uint32_t CREC 			:1;
	uint32_t RESERVED2 		:5;
	uint32_t BKPSR 			:1;
	uint32_t RESERVED3 		:1;
	uint32_t CCMAT 			:1;
	uint32_t DMA1EN 		:1;
	uint32_t DMA2EN 		:1;
	uint32_t RESERVED4 		:2;
	uint32_t ETHMACEN		:1;
	uint32_t ETHMATXEN 		:1;
	uint32_t ACRXEN			:1;
	uint32_t ACPTPEN 		:1;
	uint32_t OTGHSEN 		:1;
	uint32_t OTGHSULPIEN 	:1;
	uint32_t RESERVED5		:1;
}RCC_AHB1ENR;

typedef struct
{
	uint32_t pin_0 :2;
	uint32_t pin_1 :2;
	uint32_t pin_2 :2;
	uint32_t pin_3 :2;
	uint32_t pin_4 :2;
	uint32_t pin_5 :2;
	uint32_t pin_6 :2;
	uint32_t pin_7 :2;
	uint32_t pin_8 :2;
	uint32_t pin_9 :2;
	uint32_t pin_10 :2;
	uint32_t pin_11 :2;
	uint32_t pin_12 :2;
	uint32_t pin_13 :2;
	uint32_t pin_14 :2;
	uint32_t pin_15 :2;
}GPIOx_MODER;
typedef struct
{
	uint32_t pin_0 		:1;
	uint32_t pin_1 		:1;
	uint32_t pin_2 		:1;
	uint32_t pin_3 		:1;
	uint32_t pin_4 		:1;
	uint32_t pin_5 		:1;
	uint32_t pin_6 		:1;
	uint32_t pin_7 		:1;
	uint32_t pin_8 		:1;
	uint32_t pin_9 		:1;
	uint32_t pin_10 	:1;
	uint32_t pin_11 	:1;
	uint32_t pin_12 	:1;
	uint32_t pin_13 	:1;
	uint32_t pin_14 	:1;
	uint32_t pin_15 	:1;
	uint32_t REVERSER	:16;
}GPIOX_ODR;
#endif /* MAIN_H_ */
