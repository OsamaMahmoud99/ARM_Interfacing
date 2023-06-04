/*
 * main.c
 *
 *  Created on: Oct 1, 2020
 *      Author: Osama
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"


void main(void)
{

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , IOPA_EN);
	RCC_voidEnableClock(RCC_APB2 , USART1_EN);

	DIO_voidSetDirection(GPIOA , 9 , OUTPUT_PP_50MHZ);  // TX
	DIO_voidSetDirection(GPIOA , 10 , INPUT_FLOATING);  // RX
	DIO_voidSetDirection(GPIOA , 0 ,OUTPUT_PP_2MHZ);

	USART1_voidInit();

	u8 x;
	while(1)
	{
        USART1_voidTransmit("7");
        x=USART1_u8Receive();

        if(x == '5')
        {
        	DIO_voidSetValue(GPIOA , 0 ,GPIO_HIGH);
        }
        else if(x == 'R')
        {
        	DIO_voidSetValue(GPIOA , 0 ,GPIO_LOW);
        }
	}
}

