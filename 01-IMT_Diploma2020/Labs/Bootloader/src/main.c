#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <string.h>
#include <stdio.h>
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "STK_interface.h"
#include "FPEC_interface.h"
#include "ESP_interface.h"
#include "Parser.h"

u8* HexData; // contain record of hex file
volatile u8  u8TimeOutFlag   = 0;
volatile u8  u8BLWriteReq    = 1;
volatile u8  u8RecCounter    = 0;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void toApp(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002000;

	addr_to_call = *(Function_t*)(0x08002008);
	addr_to_call();
}

void main(void)
{
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2, IOPA);		/* Enable GPIOA clock*/
	MRCC_voidEnableClock(APB2, IOPB);		/* Enable GPIOB clock*/
	MRCC_voidEnableClock(APB2, USART1);		/* Enable USART1 Clock */
	MRCC_voidEnableClock(AHB,4);   /* FPEC   */

	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_voidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);

	/*MGPIO_voidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_2MHZ_PP);

	MGPIO_voidSetPinDirection(GPIOB, PIN0, OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOB, PIN1, OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOB, PIN2, OUTPUT_SPEED_2MHZ_PP);*/

	MUSART1_voidInit();

	HESP_voidInit();
	/* Connect to Router, sending name and password as strings*/
	HESP_voidConnctToRouter("osama2222", "011283740934093");

	/*u8  Led_Status = 0;
    u8  arr[2]={0x03,0x02};*/

	u8 arr[200]={"GET http://khaledmohsen1400-001-site1.gtempurl.com/WeatherForecast/api/receive/DIO_V03.hex/"};
	u16 LineNum = 0;
	u8* PTR = 0;

	while( u8TimeOutFlag  == 0)
	{
		/*Connecting to server, sending data transmit mode UDP or TCP and IP of server and port number as strings*/
		/* We connect each time as my server is free one and disconnects automatically, if you got a server yourself you don't
		 * have to do so
		 */

		HESP_voidConnectToServer("205.144.171.124", "80");
				/* Send the reqest as string*/
		PTR =  HESP_u8ExecuteRequest(arr ,  94 ,LineNum );

		Parser_voidParseRecord(PTR);

		LineNum++;

		/*if(HexData[0] == ':')
		{

			if (u8BLWriteReq == 1)
			{
				FPEC_voidEraseAppArea();
				u8BLWriteReq = 0;
			}

			if(HexData[u8RecCounter] == '\n')
			{
				toApp();
				Parser_voidParseRecord(HexData);
				u8RecCounter = 0;
				LineNum++;
			}
			else
			{
				u8RecCounter ++ ;
			}


		}*/




	}
}
