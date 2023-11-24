/********************************************************************/
/* Author	: OsamaMahmoud							 	 	        */
/* Date		: 16/10/2020                                            */
/* Version	: V01                                                	*/
/********************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

void HESP_voidInit(void);
void HESP_voidConnctToRouter(u8* Copy_u8StrSsid, u8* Copy_u8StrPassword);
void HESP_voidConnectToServer(u8* Copy_u8StrIP, u8* Copy_u8StrPort);
//void HESP_u8ExecuteRequest(u8* Copy_u8StrRequest ,  u16 Copy_u16LineNum);
u8 * HESP_u8ExecuteRequest(u8* Copy_u8StrRequest , u8 Cpy_u8CommandSize , u16 Cpy_u16LineNum);

u8* ESP_u8pGetHexData(void);
const char* intToStr(u16 num);
#endif
