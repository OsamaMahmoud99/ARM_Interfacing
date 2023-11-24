

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void USART1_voidInit(void)
{
	/* baud rate 9600 */
	USART1 -> BRR = 0x341;
	/* 115200 BRR= */
	
	SET_BIT(USART1 -> CR1 , 2);     /* Enable Receiver */
	SET_BIT(USART1 -> CR1 , 3);     /* Enable Transmitter */
	SET_BIT(USART1 -> CR1 , 13);    /* Enable USART */
	
	USART1 -> SR = 0;              /* clear status register */
}
void USART1_voidTransmit(u8 arr[])
{
	u8 i= 0;
 while(arr[i]!= '\0')
 {
	    USART1 -> DR =arr[i];
		while( GET_BIT(USART1 -> SR , 6) == 0);
		i++;
 }

}
u8 USART1_u8Receive(void)
{
	//u16 timeout = 0;
	u8 Local_u8ReceiveData=0;
	while( GET_BIT(USART1 -> SR , 5) == 0 );
	
	Local_u8ReceiveData = USART1 -> DR;
	return Local_u8ReceiveData;
}
