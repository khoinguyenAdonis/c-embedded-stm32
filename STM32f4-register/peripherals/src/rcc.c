/*
 * rcc.c
 *
 *  Created on: Jul 25, 2023
 *      Author: khoi7
 */
#include "rcc.h"
void rcc_HSE_confid(void)
{
	/*  configuration - parameter --> clock tree
	 * hse = 8MHZ
	 * PLL_M = 9
	 * USB prescalar =1.5
	 * ahp prescalar = 1
	 * cortex prescalar = 1
	 * --> 72mhz system clock
	 *
	 * APB1 prescalar = 2 --> 36,72MHZ
	 * APB2 prescalar =1 --> 72MHZ
	 * ADC prescalar = 6 --> 12mhz
	 *
	 */
	// pll configuration
	// pll_m =9
	RCC-->CFGR
}
