/*
 * main.c
 *
 *  Created on: Aug 24, 2020
 *      Author: asss5
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"

int main(void)
{
	/* Initialize Clock*/
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);

	/* Pin Mode */
	DIO_voidSetDirection(GPIOA,0,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,1,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,4,OUTPUT_PP_2MHZ);

	/* Initialize NVIC */
	MNVIC_voidInit();

	MNVIC_voidSetPriority(6,0b01000000);  /* EXTI0 Group 1 sub 0 */
	MNVIC_voidSetPriority(7,0b00110000);  /* EXTI1 Group 0 sub 3 */
	NVIC_voidEnableInterrupt(6); /* EXTI0 */
	NVIC_voidEnableInterrupt(7); /* EXTI1 */

	NVIC_voidSetPendingFlag(6);
	while(1)
	{

	}
}

void EXTI0_IRQHandler(void)
{
	DIO_voidSetValue(GPIOA,0,GPIO_HIGH);
	NVIC_voidSetPendingFlag(7);
	DIO_voidSetValue(GPIOA,1,GPIO_HIGH);
}
void EXTI1_IRQHandler(void)
{
	DIO_voidSetValue(GPIOA,4,GPIO_HIGH);
}

