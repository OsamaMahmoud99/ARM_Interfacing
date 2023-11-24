/*
 * main.c
 *
 *  Created on: Aug 25, 2020
 *      Author: Osama
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "SYSTICK_interface.h"


volatile u8   u8StartFlag       = 0;
volatile u32  u32FrameData[50]  = {0};
volatile u8   u8EdgeCounter     = 0;
volatile u8   u8Data            = 0;



void voidPlay(void)
{
	switch (u8Data)
	{
		case 70:
			         for(int i=0;i<4;i++)
				      {
					     LED_pingpong();
				      }
			//DIO_voidSetValue(GPIOA, 0 , GPIO_HIGH);
		break;
		case 12:
			         for(int i=0;i<4;i++)
			          {
			    	     LED_IN_OUT();
			          }
		break;
		case 24:     for(int i=0;i<8;i++)
	                  {
	    	             LED_Flashing();
	                  }
		break;
	}
}

void voidTakeAction(void)
{
	u8 i;
	u8Data = 0;

	if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 14000) )
	{
		for (i=0;i<8;i++)
		{
			if (  (u32FrameData[17+i] >= 2000) && (u32FrameData[17+i] <=2300) )
			{
				SET_BIT(u8Data,i);
			}

			else
			{
				CLR_BIT(u8Data,i);
			}
		}

		voidPlay();
	}

	else
	{
		/* Invalid Frame */
	}

	u8StartFlag     = 0;
	u32FrameData[0] = 0;
	u8EdgeCounter   = 0;
}

void voidGetFrame(void)
{
	if (u8StartFlag == 0)
	{
		/* Start Timer */
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8StartFlag = 1;
	}

	else
	{
		u32FrameData[u8EdgeCounter] = MSTK_u32GetElapsedTime();
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8EdgeCounter++;
	}
}
void LED_pingpong();
void LED_IN_OUT();
void LED_Flashing();
int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2); // GPIOA
    RCC_voidEnableClock(RCC_APB2,3); // GPIOB


	DIO_voidSetDirection(GPIOA,0,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,1,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,2,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,3,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,4,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,5,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,6,OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOA,7,OUTPUT_PP_2MHZ);

	DIO_voidSetDirection(GPIOB,1,INPUT_FLOTING);  // Pin 1 Input Floating

	EXTI_voidSetCallBack(LINE1 , voidGetFrame);
	EXTI_voidSetSignalLatch(LINE1 , FALLING);

	MNVIC_voidInit();
	NVIC_voidEnableInterrupt(7);   //EXTI1

	MSTK_voidInit();



	while(1)
	{



	}
}

void LED_pingpong()
{
	 for(int i=1; i<=128; i*=2)
	   {
	        	DIO_voidSetPort(GPIOA,i);
	        	MSTK_voidSetBusyWait(200000);   // 200 ms
	   }
	 for(int i=128; i>=1; i/=2)
	   {
	        	DIO_voidSetPort(GPIOA,i);
	        	MSTK_voidSetBusyWait(200000);
	   }
}
void LED_IN_OUT()
{
	DIO_voidSetPort(GPIOA,0x18);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x3C);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x7E);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0xFF);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x7E);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x3C);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x18);
	MSTK_voidSetBusyWait(200000);
	DIO_voidSetPort(GPIOA,0x00);
	MSTK_voidSetBusyWait(200000);
}
void LED_Flashing()
{
	DIO_voidSetPort(GPIOA,0xFF);
	MSTK_voidSetBusyWait(500000);  //500 ms
	DIO_voidSetPort(GPIOA,0x00);
	MSTK_voidSetBusyWait(500000);
}

