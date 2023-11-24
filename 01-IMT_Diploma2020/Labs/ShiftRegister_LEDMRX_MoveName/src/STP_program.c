/********************************************************/
/*  Author : OsamaMahmoud                               */
/*  Date   : 14/9/2020                                  */
/********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SYSTICK_interface.h"

#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"


void STP_voidSendSynchronus(u16 Copy_u8DataToSend , u8 Copy_u8NumberOfByte)
{    s8 Local_u8Counter;
     u8 Local_u8Bit;

     Local_u8Counter = Copy_u8NumberOfByte*8 - 1;
     for(; Local_u8Counter>=0;Local_u8Counter--)
	 {
    	 DIO_voidSetValue(STP_SERIAL_DATA , GPIO_HIGH);
	    /* Send bit by bit starting from MSb  */
		Local_u8Bit = GET_BIT(Copy_u8DataToSend,Local_u8Counter);
		DIO_voidSetValue(STP_SERIAL_DATA , Local_u8Bit);
		
		/* Send pulse to shift clock */
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_HIGH);
		MSTK_voidSetBusyWait(1);
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_LOW);
		MSTK_voidSetBusyWait(1);
	 }
	    DIO_voidSetValue(STP_STORE_CLOCK ,GPIO_HIGH);
		MSTK_voidSetBusyWait(1);
		DIO_voidSetValue(STP_STORE_CLOCK ,GPIO_LOW);
		MSTK_voidSetBusyWait(1);

}

void STP_voidShiftData(u8 *Copy_u8DataToShift)
{
	for(u8 j=0; j<30 ;j++)
	{
		for(u8 i=0; i<8; i++)
		{
			//STP_voidSetRow(Copy_u8DataToShift[j]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j]);
			/* enable col0 */
			STP_voidSetCol(0xFE);                      // 0b11111110
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+1]);
			STP_voidSetCol(0xFF);
            STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+1]);
			STP_voidSetCol(0xFD);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+2]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+2]);
			STP_voidSetCol(0xFB);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+3]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+3]);
			STP_voidSetCol(0xF7);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+4]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+4]);
			STP_voidSetCol(0xEF);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+5]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+5]);
			STP_voidSetCol(0xDF);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+6]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+6]);
			STP_voidSetCol(0xBF);
			MSTK_voidSetBusyWait(2500);

			//STP_voidSetRow(Copy_u8DataToShift[j+7]);
			STP_voidSetCol(0xFF);
			STP_voidSetCol(0xFF);
			STP_voidSetRow(Copy_u8DataToShift[j+7]);
			STP_voidSetCol(0x7F);
			MSTK_voidSetBusyWait(2500);
		}

	}
}

static void STP_voidSetRow(u8 Copy_u8Value)
{
	s8 Local_u8Counter;
    u8 Local_u8Bit;
	for(Local_u8Counter =7; Local_u8Counter>=0;Local_u8Counter--)
	{
	    /* Send bit by bit starting from MSb  */
		Local_u8Bit = GET_BIT(Copy_u8Value,Local_u8Counter);
		DIO_voidSetValue(STP_SERIAL_DATA , Local_u8Bit);

		/* Send pulse to shift clock */
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_HIGH);
		MSTK_voidSetBusyWait(1);
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_LOW);
		MSTK_voidSetBusyWait(1);
	}
}

static void STP_voidSetCol(u8 Copy_u8Value)
{
	s8 Local_u8Counter;
    u8 Local_u8Bit;
    for(Local_u8Counter =7; Local_u8Counter>=0;Local_u8Counter--)
	{
	    /* Send bit by bit starting from MSb  */
		Local_u8Bit = GET_BIT(Copy_u8Value,Local_u8Counter);
		DIO_voidSetValue(STP_SERIAL_DATA , Local_u8Bit);

		/* Send pulse to shift clock */
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_HIGH);
		MSTK_voidSetBusyWait(1);
		DIO_voidSetValue(STP_SHIFT_CLOCK,GPIO_LOW);
		MSTK_voidSetBusyWait(1);
	}
	    /* Send pulse to storage clock */
	DIO_voidSetValue(STP_STORE_CLOCK ,GPIO_HIGH);
	MSTK_voidSetBusyWait(1);
	DIO_voidSetValue(STP_STORE_CLOCK ,GPIO_LOW);
	MSTK_voidSetBusyWait(1);
}

