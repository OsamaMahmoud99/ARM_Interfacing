/********************************************************************/
/* Author	: MOHAMED ABDELNABY								 	 	*/
/* Date		: 30 Sep 2020                                           */
/* Version	: V01                                                	*/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include<string.h>
#include<stdio.h>

#include "UART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

char Quotes	[]	 = "\""		;
char Comma 	[]	 = {","};
char Closing[]	 = "\r\n"	;

u8 Local_u8Response[100] ={0};

void ESP_voidInit(void)
{
	u8 Local_u8ValidFlag = 0;

	while(Local_u8ValidFlag == 0)
	{

		USART1_voidTransmit("ATE0\r\n");

		Local_u8ValidFlag = u8ValidateCmd(ECHO_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;
	
	while(Local_u8ValidFlag == 0)
	{

		USART1_voidTransmit("AT+CWMODE=1\r\n");

		Local_u8ValidFlag = u8ValidateCmd(MODE_TIMEOUT);
	}
}


void ESP_voidConnctToRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword)
{
	u8 Local_u8ValidFlag = 0;
	char Router_Command[50];
	
	sprintf(Router_Command,"%s%s%s%s%s","AT+CWJAP_CUR=\"",Copy_u8StrSsid,"\",\"",Copy_u8StrPassword,"\"\r\n");
	
	while(Local_u8ValidFlag == 0)
	{

		USART1_voidTransmit(Router_Command);

		Local_u8ValidFlag = u8ValidateCmd(ROUTER_TIMEOUT);
	}
}

void ESP_voidConnectToServer( char* Copy_u8StrIP, char* Copy_u8StrPort)
{
	u8 Local_u8ValidFlag = 0;
	char Server_Command[42];
	
	sprintf(Server_Command,"%s%s%s%s%s","AT+CIPSTART=\"TCP\",\"", Copy_u8StrIP,"\",",Copy_u8StrPort,"\r\n");
	
	while(Local_u8ValidFlag == 0)
	{
		USART1_voidTransmit(Server_Command);

		Local_u8ValidFlag = u8ValidateCmd(SERVER_TIMEOUT);
	}
}

u8 ESP_u8ExecuteRequest(char* Copy_u8StrRequest)
{
	u8 Local_u8ValidFlag = 0;
	char Send_Command[14];
	char Request_Command[(strlen(Copy_u8StrRequest) + 2)];
	char Temp_str[2];


	strcpy(Send_Command, "AT+CIPSEND=");


	u8 NumberOfLetters = strlen(Copy_u8StrRequest) + 2;

	sprintf(Temp_str, "%i", NumberOfLetters);
	
	strcat(Send_Command, Temp_str);
	
	strcat(Send_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{

		USART1_voidTransmit(Send_Command);

		Local_u8ValidFlag = u8ValidateCmd(PREREQUEST_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;
	strcpy(Request_Command, "");
	strcat(Request_Command, Copy_u8StrRequest);
	strcat(Request_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{

		USART1_voidTransmit(Request_Command);

		Local_u8ValidFlag = u8ValidateCmd(REQUEST_TIMEOUT);
	}
	
	u8 Temp_char;

	for(u8 i = 0; i < 98; i++)
	{
		/*Checking that the data received have IPD*/
		if(Local_u8Response[i] == 'I' && Local_u8Response[i+1] == 'P' && Local_u8Response[i+2] == 'D')
		{
			/*Return data in the 6th position after the I*/
			Temp_char = Local_u8Response[i+6];
		}
	}

	if(Temp_char == '1')
		Temp_char = 1;
	else if (Temp_char == '0')
		Temp_char = 0;
	return Temp_char;
}

u8 u8ValidateCmd(u32 Copy_u32timeout)
{
	u8 Local_u8ValidFlag = 0;
	u8 Counter = 0;
	u8 Temp_char = 0;

	for(u8 i = 0; i < 100; i++)
	{
		Local_u8Response[i] = 0;
	}


	while (Temp_char != 255)
	{
		Temp_char = USART1_u8ReceiveTimeOut(Copy_u32timeout);
		Local_u8Response[Counter] = Temp_char;
		Counter++;
	}


	Local_u8Response[Counter-1] = 0;

	for(u8 i = 0; i < Counter - 2; i ++)
	{
		if(Local_u8Response[i] == 'O' && Local_u8Response[i+1] == 'K')
		{
			Local_u8ValidFlag = 1;
		}
	}
	return Local_u8ValidFlag;
}
