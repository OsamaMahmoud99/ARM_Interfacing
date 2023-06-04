/*********************************************************************************************/
/*  Author   :    OsamaMahmoud                                                               */
/*  Date     :    3/10/2020                                                                  */
/*********************************************************************************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H


/*Options for word size:
		USART_8_BIT_WORD
		USART_9_BIT_WORD
						*/
#define USART1_WORD		USART_8_BIT_WORD

/*Options for parity:
		USART_PARITY_DISABLED
		USART_PARITY_ENABLED
							*/
#define USART1_PARITY	 	USART_PARITY_DISABLED

/*Parity:
		USART_EVEN_PARITY
		USART_ODD_PARITY
						*/
#define PARITY	USART_EVEN_PARITY

/*Parity error interrupt enable state:
		USART_PE_DISABLED
        USART_PE_ENABLED
									*/
#define PARITY_ERROR_INTERRUPT		USART_PE_DISABLED


#define   BAUD_RATE           BAUD_RATE_115200_8MHZ



#endif
