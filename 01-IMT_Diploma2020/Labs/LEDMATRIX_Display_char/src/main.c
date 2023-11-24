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

u8 MY_Name[38]={0, 0, 24, 36, 36, 24, 0, 0, 0, 0, 0, 38, 42, 50,
		        0, 0 , 0, 124, 18, 18, 18, 124, 0, 0 , 0, 0, 28,
				2, 30, 2, 28, 0,0, 124, 18, 18, 18, 124, 0, 0 };


u8 FirstChar[8] = {0, 60, 66, 66, 66, 66, 60, 0};

int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 3);

	MSTK_voidInit();

	LEDMRX_voidInit();



	LEDMRX_voidDispaly(FirstChar);

	while(1);

	return 0;
}

