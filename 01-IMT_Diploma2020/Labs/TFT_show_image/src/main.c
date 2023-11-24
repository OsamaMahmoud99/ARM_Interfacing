/*
 * main.c
 *
 *  Created on: Sep 21, 2020
 *      Author: Osama
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"

#include "SYSTICK_interface.h"
#include "SPI_interface.h"
#include "TFT_interface.h"

#include "image.h"


void main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 12);

	DIO_voidSetDirection(GPIOA , 1 ,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 2 ,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 5 ,0b1001);
	DIO_voidSetDirection(GPIOA , 7 ,0b1001);

	MSTK_voidInit();
	SPI1_voidInit();
	TFT_voidInitialize();
    //TFT_voidDispalyImage(image);
	TFT_voidFillColor(0x0033);
	//TFT_voidDrawRect(20, 30 ,20 ,50 ,0xffff);
	while(1);
}

