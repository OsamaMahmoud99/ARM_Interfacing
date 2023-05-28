/*
 * main.c
 *
 *  Created on: Sep 14, 2020
 *      Author: asss5
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "SYSTICK_interface.h"

#include "STP_interface.h"

u8 MY_Name[38]={0, 0, 24, 36, 36, 24, 0, 0, 0, 0, 0, 38, 42, 50, 0, 0 , 0, 124, 18, 18, 18, 124, 0, 0 , 0, 0, 28, 2, 30, 2, 28, 0,0, 124, 18, 18, 18, 124, 0, 0};

u8 Data[8]={0, 0, 24, 36, 36, 24, 0, 0};
void main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);

	DIO_voidSetDirection(GPIOA , 0 , OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 1 , OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 2 , OUTPUT_PP_2MHZ);

	MSTK_voidInit();

	u8 Local_u8column=1;

	while(1)
	{
		for(u8 j=0; j<30;j++)
		{
			u8 Data_u8Temp[8]={MY_Name[j],MY_Name[j+1], MY_Name[j+2],MY_Name[j+3],MY_Name[j+4],MY_Name[j+5],MY_Name[j+6],MY_Name[j+7]};
			for(u8 w=0 ;w<10;w++)
			{
		        for(u8 i=0; i<=7;i++)
		        {
			       u16 Local_u8DataToSend = (~Local_u8column <<8)|Data_u8Temp[i];

			       STP_voidSendSynchronus(Local_u8DataToSend , 2);
			       MSTK_voidSetBusyWait(2500);
			       Local_u8column = Local_u8column << 1;


		        }
			}
		}
		Local_u8column = 1;


	}

}

