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
#include "NVIC_interface.h"
#include "EXTI_interface.h"

#include "IR_interface.h"
#include "LEDMRX_interface.h"

u8 MY_Name[38]={0, 0, 24, 36, 36, 24, 0, 0, 0, 0, 0, 38, 42, 50, 0, 0 , 0, 124, 18, 18, 18, 124, 0, 0 , 0, 0, 28, 2, 30, 2, 28, 0,0, 124, 18, 18, 18, 124, 0, 0};

//u8 Name[8]={0, 0, 24, 36, 36, 24, 0, 0};

void Task1(u8 Key)
{
	switch(Key)
	{
	  case MODE :    LEDMRX_voidStopAnimation(); break;
	  case ZERO :    LEDMRX_voidResumeAnimation(); break;
	  case ONE  :    LEDMRX_voidSpeedUp(); break;
	  case TWO  :    LEDMRX_voidSpeedDown(); break;
 	}
}
int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 3);

	DIO_voidSetDirection(GPIOA , 0 , INPUT_FLOATING);
	DIO_voidSetDirection(GPIOA , 9 , OUTPUT_PP_2MHZ);


	EXTI_voidSetCallBack(LINE0 , IR_voidGetFrame);
	EXTI_voidEnable(LINE0);
	EXTI_voidInit();

   /* Enable EXTI0  */
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6);

	MSTK_voidInit();

	LEDMRX_voidInit();
	IR_voidSetCallBack(Task1);

	LEDMRX_voidAnimation(MY_Name);


}

