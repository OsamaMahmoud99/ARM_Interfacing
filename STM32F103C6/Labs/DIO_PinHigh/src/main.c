/*
 * main.c
 *
 *  Created on: Sep 4, 2020
 *      Author: asss5
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "RCC_interface.h"


int main(void)
{
    RCC_voidInitSysClock();
    RCC_voidEnableClock(RCC_APB2 , 2);
    RCC_voidEnableClock(RCC_APB2 , 3);
	DIO_Init();
  while(1)
  {
     DIO_WritePin(PINA0 , HIGH);
  }

	return 0;
}

