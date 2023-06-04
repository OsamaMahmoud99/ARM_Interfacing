/*********************************************************************************************/
/*  Author   :    OsamaMahmoud                                                               */
/*  Date     :    3/10/2020                                                                  */
/*********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void USART1_voidInit(void)
{
	
	#if   BAUD_RATE  ==  BAUD_RATE_9600_8MHZ
	USART1 -> BRR = 0x341;
	#elif BAUD_RATE  ==  BAUD_RATE_115200_8MHZ
	USART1 -> BRR = 0x45;
	#endif
	
#if USART1_WORD == USART_8_BIT_WORD
		CLR_BIT(USART1 -> CR1, M);
	#elif USART1_WORD == USART_9_BIT_WORD
		SET_BIT(USART1 -> CR1, M);
	#endif

	#if USART1_PARITY == USART_PARITY_DISABLED
		CLR_BIT(USART1 -> CR1, PCE);
	#elif USART1_PARITY == USART_PARITY_ENABLED
		SET_BIT(USART1 -> CR1, PCE);

		#if PARITY == USART_EVEN_PARITY
			CLR_BIT(USART1 -> CR1, PS);
		#elif PARITY == USART_ODD_PARITY
			SET_BIT(USART1 -> CR1, PS);
		#endif

		#if PARITY_ERROR_INTERRUPT == USART_PE_DISABLED
			CLR_BIT(USART1 -> CR1, PEIE);
		#elif PARITY_ERROR_INTERRUPT == USART_PE_ENABLED
			SET_BIT(USART1 -> CR1, PEIE);
		#endif
	#endif

	
	SET_BIT(USART1 -> CR1 , 2);     /* Enable Receiver */
	SET_BIT(USART1 -> CR1 , 3);     /* Enable Transmitter */
	SET_BIT(USART1 -> CR1 , 13);    /* Enable USART */
	
	USART1 -> SR = 0;              /* clear status register */
}
void USART1_voidTransmit(u8 *data)
{
	u8 Local_u8CurrentLetter = 0;
	while(data[Local_u8CurrentLetter] !='\0')
	{
		USART1 -> DR = data[Local_u8CurrentLetter];
		while( GET_BIT(USART1 -> SR , TC) == 0 );
		Local_u8CurrentLetter++;
	}
}
u8 USART1_u8ReceiveTimeOut(u32 Copy_u32TimeOut)
{
	u16 timeout = 0;
	s8 Local_u8ReceiveData = 0;
	while( GET_BIT(USART1 -> SR , RXNE) == 0 )
	{
		timeout++;
		if(timeout == Copy_u32TimeOut)
		{
			Local_u8ReceiveData = 255;
			break;
		}
	
	}
	if(Local_u8ReceiveData == 0)
	{
		Local_u8ReceiveData = USART1 -> DR;
	}
	return Local_u8ReceiveData;
}

u8 USART1_u8ReceiveNoBlock(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;
	if(GET_BIT(USART1->SR , RXNE) == 1)
	{
		*Copy_u8Data = USART1 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}
	
	return Local_u8Result;
  	
}
