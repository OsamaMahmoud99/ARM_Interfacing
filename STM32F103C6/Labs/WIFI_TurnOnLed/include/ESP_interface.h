/********************************************************************/
/* Author	: MOHAMED ABDELNABY								 	 	*/
/* Date		: 30 Sep 2020                                           */
/* Version	: V01                                                	*/
/********************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

void ESP_voidInit(void);
void ESP_voidConnctToRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword);
void ESP_voidConnectToServer(char* Copy_u8StrIP, char* Copy_u8StrPort);
u8   ESP_u8ExecuteRequest(char* Copy_u8StrRequest);

#endif
