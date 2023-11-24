/*
 * APP.c
 *
 *  Created on: Sep 10, 2020
 *      Author: asss5
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "RCC_interface.h"
#include "SYSTICK_interface.h"

#include "LEDMRX_interface.h"

/* Osama */
u8 MY_Name[38]={0, 0, 24, 36, 36, 24, 0, 0,
		        0,0, 0, 38, 42, 50, 0, 0 ,
		        0, 124, 18, 18, 18, 124, 0, 0,
				0, 0,28, 2, 30, 2, 28,0,
				0, 124, 18, 18, 18, 124, 0,0 };


/* Osama Mahmoud */
u8 FullMyName[]={0, 56, 68, 68, 68, 56, 0,
		  0, 92, 84, 84, 116, 0, 0, 120, 36, 36, 36, 120, 0, 120, 4, 124, 4, 120, 0, 120, 36, 36, 120,
		  0, 120, 4, 124, 4, 120, 0, 120, 36, 36, 120, 0, 126, 8, 120, 0, 120, 4, 124, 4, 120, 0, 56, 68, 56, 0, 60, 64, 64, 60};
int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 3);

	MSTK_voidInit();

	LEDMRX_voidInit();



	LEDMRX_voidDisplayName(MY_Name);

	while(1);

	return 0;
}

