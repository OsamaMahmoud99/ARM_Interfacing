/*
 * main.c
 *
 *  Created on: Sep 20, 2020
 *      Author: Osama
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "SPI_interface.h"

void main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , IOPA_EN);
	RCC_voidEnableClock(RCC_APB2 , IOPB_EN);

	DIO_voidSetDirection(GPIOB , 0 , OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOB, 1 , INPUT_PP_PD);
	DIO_voidSetValue(GPIOB , 1 , GPIO_HIGH);
    SPI1_voidInitMaster();

    u8 x;

	while(1)
	{
	   u8 Data = DIO_u8GetValue(GPIOB , 1);

       x= SPI1_voidSendReceiveSynch(Data);


	}
}

