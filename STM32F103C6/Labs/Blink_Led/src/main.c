/*
 * main.c
 *
 *  Created on: Aug 13, 2020
 *      Author: asss5
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "TIMER_interface.h"

void main(void)
{
	RCC_voidInitSysClock();
	TIMER_voidInit();
	RCC_voidEnableClock(RCC_APB2,2);
	RCC_voidEnableClock(RCC_APB1 , 1);
	DIO_voidSetDirection(GPIOA,0,OUTPUT_PP_10MHZ);

	//DIO_voidSetDirection(GPIOA,9,INPUT_PP_PD);
	/* for pull up */
	//DIO_voidSetValue(GPIOA , 0 , GPIO_HIGH);
	//int w=800;
	while(1)
	{
		/*if(DIO_u8GEtValue(GPIOA , 9)==0)
		{
			DIO_voidSetValue(GPIOA , 8 , GPIO_HIGH);
		}
		else
		{
			DIO_voidSetValue(GPIOA , 8 , GPIO_LOW);
		}*/
		DIO_voidSetValue(GPIOA , 0 , GPIO_HIGH);
		TIMER_voidSetBusyWait(TIM3 , 1000000);
		DIO_voidSetValue(GPIOA , 0 , GPIO_LOW);
		TIMER_voidSetBusyWait(TIM3 , 1000000);



	}
}
