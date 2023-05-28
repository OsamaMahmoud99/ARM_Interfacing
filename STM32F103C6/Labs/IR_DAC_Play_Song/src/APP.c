/*
 * APP.c
 *
 *  Created on: Sep 10, 2020
 *      Author: asss5
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Delay.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "SYSTICK_interface.h"
#include "AFIO_interface.h"
#include "LEDMRX_interface.h"

#include "IR_interface.h"
#include "Hello.h"
#include "Help.h"
#include "Hungry.h"
#include "Water.h"
#include "Amr.h"
#include "Dance.h"

volatile u16 i=0;
volatile u16 j=0;
volatile u16 f=0;
volatile u16 k=0;

#define Num_Frames   3

/*u8 Frames[Num_Frames][8]={{0, 0, 86, 62, 86, 0, 0, 0},
		                  {0, 8, 86, 62, 86, 8, 0, 0},
						  {0, 32, 86, 62, 86, 32, 0, 0}};*/

/*#define  FramesNum  11

u8 Frames[FramesNum][8] ={
		{24, 203, 63, 75 , 88 , 32, 0, 0},
		{24, 203, 63, 75 , 152, 16, 0, 0},
		{0,  219, 63, 219, 0  , 8 , 0, 0},
		{0,  219, 63, 219, 0  , 4 , 0, 0},
		{0,  219, 63, 219, 0  , 2 , 0, 0},
		{0,  219, 63, 219, 0  , 1 , 0, 0},
		{0,  219, 63, 219, 0  , 2 , 0, 0},
		{0,  219, 63, 219, 0  , 4 , 0, 0},
		{0,  219, 63, 219, 0  , 8 , 0, 0},
		{24, 203, 63, 75 , 152, 16, 0, 0},
		{24, 203, 63, 75 , 88 , 32, 0, 0}
};*/

void Hello(void)
{

	    DIO_voidSetPort(GPIOA , Hello_Raw[i]);
	    i++;
	    if(i == 8636)
	    {
	    	i=0;
	    }


}
void Help(void)
{

	 DIO_voidSetPort(GPIOA , Help_raw[j]);
	 j++;
	  if(j == 4916)
	  {
		j = 0;
	  }
}
void Hungry(void)
{

	 DIO_voidSetPort(GPIOA , Hungry_raw[f]);
	 f++;
	  if(f == 8686)
	  {
		f = 0;
	  }
}
void water(void)
{

	 DIO_voidSetPort(GPIOA , Water_raw[k]);
	 k++;
	  if(k == 6860)
	  {
		k = 0;
	  }
}

void Amr(void)
{
	 DIO_voidSetPort(GPIOA , Amr_raw[k]);
		 k++;
		  if(k == 37014)
		  {
			k = 0;
		  }

}

/*void Dance(void)
{
	DIO_voidSetPort(GPIOA , Dance_raw[k]);
			 k++;
			  if(k == 32245)
			  {
				k = 0;
			  }
}*/
void Task1(u8 Key)
{
	switch(Key)
	{
	   case ZERO :   MSTK_voidSetIntervalPeriodic(125 , Hello);
	   break;


	   case ONE :  MSTK_voidSetIntervalPeriodic(125 , Help);
	   break;

	   case TWO :
		   MSTK_voidSetIntervalPeriodic(125 , Hungry);

		          break;

	   case FOUR :
		   MSTK_voidSetIntervalPeriodic(125 , water);
		   		           break;

	}
}

int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 3);
	RCC_voidEnableClock(RCC_APB2 , 0);  /* AFIO*/

	AFIO_voidSetEXTIConfig(LINE0 , PB);
	DIO_voidSetDirection(GPIOB , 0 , INPUT_FLOATING );

	DIO_voidSetDirection(GPIOA , 0,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 1,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 2,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 3,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 4,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 5,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 6,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA , 7,OUTPUT_PP_2MHZ);


	EXTI_voidSetCallBack(LINE0 , IR_voidGetFrame);
	EXTI_voidEnable(LINE0);
	EXTI_voidInit();


	MNVIC_voidInit();              /* Priority */
	MNVIC_voidEnableInterrupt(6);  /* Enable EXTI0  */
	MSTK_voidInit();               /* Select Clock */
    //LEDMRX_voidInit();
	IR_voidSetCallBack(Task1);



while(1)
{
}




}


