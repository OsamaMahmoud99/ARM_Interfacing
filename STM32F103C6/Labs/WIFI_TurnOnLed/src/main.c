/*
 * main.c
 *
 *  Created on: Oct 2, 2020
 *      Author: asss5
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"

#include "ESP_interface.h"



void main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, IOPA_EN);		/* Enable GPIOA clock*/
	RCC_voidEnableClock(RCC_APB2, IOPB_EN);		/* Enable GPIOB clock*/
	RCC_voidEnableClock(RCC_APB2, 14);		/* Enable USART1 Clock */

	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	DIO_voidSetDirection(GPIOA, 9, OUTPUT_AF_PP_50MHZ);
	/* Setting A10:RX pin as input floating */
	DIO_voidSetDirection(GPIOA, 10, INPUT_FLOATING);

	DIO_voidSetDirection(GPIOA, 0, OUTPUT_PP_2MHZ);

	DIO_voidSetDirection(GPIOB, 0, OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOB, 1, OUTPUT_PP_2MHZ);
	DIO_voidSetDirection(GPIOB, 2, OUTPUT_PP_2MHZ);

	USART1_voidInit();

	ESP_voidInit();
	/* Connect to Router, sending name and password as strings*/
	ESP_voidConnctToRouter("osama2222", "011283740934093");

	u8  Led_Status = 0;
    u8  arr[2]={0x03,0x02};
	while(1)
	{
		/*Connecting to server, sending data transmit mode UDP or TCP and IP of server and port number as strings*/
		/* We connect each time as my server is free one and disconnects automatically, if you got a server yourself you don't
		 * have to do so
		 */
		ESP_voidConnectToServer("162.253.155.226", "80");
		/* Send the reqest as string*/
		Led_Status = ESP_u8ExecuteRequest("GET http://osamamahmoud.freevar.com/status.txt");

		DIO_voidSetPort(GPIOB , arr[Led_Status]);
	}
}
