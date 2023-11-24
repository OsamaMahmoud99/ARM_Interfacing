/********************************************************************/
/* Author	: OsamaMahmoud			           				 	 	*/
/* Date		: 16/10/2020                                            */
/* Version	: V01                                                	*/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include<string.h>
#include<stdio.h>

#include "USART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

char Closing[]	 = "\r\n"	;

u8 Local_u8Response[100] ={0};

u8 hexFileData[50] = {0};// record in hex file
char arr[4] = {0};// will be returned from intToStr()

void HESP_voidInit(void)
{
	u8 Local_u8ValidFlag = 0;

	while(Local_u8ValidFlag == 0)
	{
		/*Stop Echo*/
		MUSART1_voidTransmit("ATE0\r\n");
		/*	Check command is done right
			ATE0 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(ECHO_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;
	
	while(Local_u8ValidFlag == 0)
	{
		/*Set ESP station mode*/
		MUSART1_voidTransmit("AT+CWMODE=1\r\n");
		/*	Check command is done right
			AT+CWMODE=1 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(MODE_TIMEOUT);
	}
}


void HESP_voidConnctToRouter(u8* Copy_u8StrSsid, u8* Copy_u8StrPassword)
{
	u8 Local_u8ValidFlag = 0;
	char Router_Command[50];
	
	sprintf(Router_Command,"%s%s%s%s%s","AT+CWJAP_CUR=\"",Copy_u8StrSsid,"\",\"",Copy_u8StrPassword,"\"\r\n");
	
	while(Local_u8ValidFlag == 0)
	{
		/*Connect to WiFi of name Copy_u8StrSsid and password Copy_u8StrPassword*/
		MUSART1_voidTransmit(Router_Command);
		/*	Check command is done right
			AT+CWJAP_CUR="SSID","Pass" returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(ROUTER_TIMEOUT);
	}
}

void HESP_voidConnectToServer( u8* Copy_u8StrIP, u8* Copy_u8StrPort)
{
	u8 Local_u8ValidFlag = 0;
	char Server_Command[42];

	
	sprintf(Server_Command,"%s%s%s%s%s","AT+CIPSTART=\"TCP\",\"", Copy_u8StrIP,"\",",Copy_u8StrPort,"\r\n");
	while(Local_u8ValidFlag == 0)
	{
		/*	Connect to Server of IP Copy_u8StrIP with Copy_u8StrMode potocol
			Either TCP or UDP and on Port Copy_u8StrPort*/
		MUSART1_voidTransmit(Server_Command);
		/*	Check command is done right
			AT+CIPSTART="MODE","IP",PORT returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(SERVER_TIMEOUT);
	}
}

void GetString(u8 *string , u8 *from , u8 index1 , u8 *to , u8 index2 , u8 *get_text)
{
	u8 *p1;
	u8 *p2;
	u8 length = 0;
	p1 = strstr(string , from ) + index1;

	p2 = strstr(p1 , to) + index2;

	length = p2 - p1;
	strncpy(get_text , p1, length);
	get_text[length] = '\0';
}

u8 * get_data(void)
{

	GetString(Local_u8Response , ":" , 1 , "C" , 0 , hexFileData);
	return hexFileData;

}
/*u8* ESP_u8pGetHexData(void)
{
	u8 i = 0; // counter
	u8 j = 0;// counter
	while(Local_u8Response[i] != 255)
	{
		if(Local_u8Response[i] == ':')
		{
			if( (Local_u8Response[i-1] == '1' ) || (Local_u8Response[i+1] == '1') )
			{
				return &Local_u8Response[i+1];
			}
			else if(Local_u8Response[i-1] >= '1')
			{
				while(Local_u8Response[i] != '\n')
				{
					hexFileData[j] = Local_u8Response[i+1];//copy hex record
					i++; j++;
				}
				return hexFileData ;
			}
		}
		i++;
	}
	return 'E';
}*/
u8 * HESP_u8ExecuteRequest(u8* Copy_u8StrRequest , u8 Cpy_u8CommandSize , u16 Cpy_u16LineNum)
{
	u8 Local_u8ValidFlag = 0;
	u8 Loc_u8SendDataCmd[17]="AT+CIPSEND=";

	//char Send_Command[15];
	//u8 * HexLink = Copy_u8StrRequest;

	//u8 NumberLetter = (strlen(HexLink) + 2);

	//char Request_Command[200];
	//char Temp_str[2];

	//strcpy( Copy_u8StrRequest , intToStr(Copy_u16LineNum));

	//strcpy(Send_Command, "AT+CIPSEND=");

	/* calculate request length and add 2 for \r\n */
	//u8 NumberOfLetters = strlen(Copy_u8StrRequest) + 2;
	/*Convert the number of the request letters to String*/
	//sprintf(Temp_str, "%i", NumberOfLetters);
	
	//strcat(Send_Command, Temp_str);
	
	//strcat(Send_Command, Closing);


	//u8 *P  = intToStr((u16)Cpy_u8CommandSize);
	//u8 *pt = intToStr(Cpy_u16LineNum);

	if(Cpy_u16LineNum <10)// 1 digit
	{

	    strcat(Loc_u8SendDataCmd , intToStr((u16)Cpy_u8CommandSize));

	}
	else if(Cpy_u16LineNum <100)// 2 digits
	{

			Cpy_u8CommandSize++;
			strcat(Loc_u8SendDataCmd , intToStr((u16)Cpy_u8CommandSize));
	}
	else if(Cpy_u16LineNum <1000) // 3 digits
	{

			Cpy_u8CommandSize+=2;
			strcat(Loc_u8SendDataCmd , intToStr((u16)Cpy_u8CommandSize));
	}
	else if(Cpy_u16LineNum <10000) // 4 digits
	{

			Cpy_u8CommandSize+=3;
			strcat(Loc_u8SendDataCmd , intToStr((u16)Cpy_u8CommandSize));
	}

	/*Concatinate all the CMDs*/
	    //strcpy(request, "");
		strcat(Copy_u8StrRequest,intToStr(Cpy_u16LineNum));
		strcat(Copy_u8StrRequest, Closing);
		strcat(Loc_u8SendDataCmd,Closing);

	
	while(Local_u8ValidFlag == 0)
	{
		/*	Send number of letter from the coming request*/
		MUSART1_voidTransmit(Loc_u8SendDataCmd);
		/*	Check command is done right
			AT+CIPSEND=NUMBER returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(PREREQUEST_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;

	/*strcpy(Copy_u8StrRequest, "");
	strcat(Copy_u8StrRequest, Copy_u8StrRequest );
	strcat(Copy_u8StrRequest, Closing);*/
	
	while(Local_u8ValidFlag == 0)
	{
		/*	Send number of letter from the coming request*/
		MUSART1_voidTransmit(Copy_u8StrRequest);
		/*	Check command is done right
			AT+CIPSEND=NUMBER returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(REQUEST_TIMEOUT);
	}
	
	/*u8 Temp_char;*/
	/* When we receive data from server it would be in the form +IPD,NUMBER_OF_LETTERS_RECIEVED;DATA*/

			/*Return data in the 6th position after the I*/
			//Temp_char = Local_u8Response[i+6];

	for(u8 i=0; i<100; i++)
	{
		if(Local_u8Response[i] == 'I' && Local_u8Response[i+1] == 'P' && Local_u8Response[i+2] == 'D')
		{
			 return get_data();
		}
	}



	/*if(Temp_char == '1')
		Temp_char = 1;
	else if (Temp_char == '0')
		Temp_char = 0;
	return Temp_char;*/
}

u8 u8ValidateCmd(u32 Copy_u32timeout)
{
	u8 Local_u8ValidFlag = 0;
	u8 Counter = 0;
	u8 Temp_char = 0;

	/*for(u8 i = 0; i < 100; i++)
	{
		Local_u8Response[i] = 0;
	}*/

	/*Make sure that the MC is not receiving any more data from the ESP*/
	while (Temp_char != 255)
	{
		Temp_char = MUSART1_u8Receive(Copy_u32timeout);
		Local_u8Response[Counter] = Temp_char;
		Counter++;
	}

	/*	Deleting last element as it is always 255 for stop receiving data	*/
	Local_u8Response[Counter-1] = 0;


	for(u8 i = 0; i < 100; i ++)
	{
		if(Local_u8Response[i] == 'O' && Local_u8Response[i+1] == 'K')
		{
			Local_u8ValidFlag = 1;
			break;
		}

	}
	return Local_u8ValidFlag;
}

const char* intToStr(u16 num)
{
	char a7ad   = 0;
	char a4rat  = 0;
	char m2at   = 0;
	char alaaf  = 0;

	if(num < 10)// 1 digit
	{
		arr[0] = (char)(num + 48);
		return arr;
	}
	else if(num < 100)// 2 digits
	{
		/* get each digit in a variable */
		a4rat = num / 10;
		a7ad  = num - a4rat*10 ;

		/* covert digits of num into char */
		arr[0] = (char)(a4rat + 48);
		arr[1] = (char)(a7ad + 48);
		return arr;
	}
	else if(num < 1000)// 3 digits
	{
		/* get each digit in a variable */
		m2at  = num / 100;
		a4rat = (num-(m2at*100) ) / 10;
		a7ad  = (num-(m2at*100) ) -	(a4rat*10) ;

		/* covert digits of num into char */
		arr[0] = (char)(m2at  + 48);
		arr[1] = (char)(a4rat + 48);
		arr[2] = (char)(a7ad  + 48);
		return arr;

	}
	else if(num < 10000)// 4 digits
	{
		/* get each digit in a variable */
		alaaf = num / 1000;
		m2at  = (num-(alaaf*1000)) / 100;
		a4rat = (num-(m2at*100 + alaaf*1000) ) / 10;
		a7ad  = (num-(m2at*100 + alaaf*1000 + a4rat*10) );

		/* covert digits of num into char */
		arr[0] = (char)(alaaf + 48);
		arr[1] = (char)(m2at  + 48);
		arr[2] = (char)(a4rat + 48);
		arr[3] = (char)(a7ad  + 48);
		return arr;
	}
	return 0;
}
