/*********************************************************************************************/
/*  Author   :    OsamaMahmoud                                                               */
/*  Date     :    3/10/2020                                                                  */
/*********************************************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GRPR;
}UART_Register;

#define   USART1      ((volatile UART_Register*)0x40013800)

#define UE 		13	/*USART enable*/
#define M 		12 	/*WORD length*/
#define PCE 	10 	/*Parity control Enable*/
#define PS 		9	/*Parity selection*/
#define PEIE	8	/*Parity interrupt enable*/
#define TXEIE	7	/*TXE Interrupt enable*/
#define TCIE	6	/*RX Interrupt enable*/
#define RXNEIE  5	/*RCNE interrupt enable*/
#define TE 		3	/*TX enabled*/
#define RE		2	/*RX enabled*/

#define TXE 	7	/*Transmistion data register empty*/
#define TC 		6	/*Transimation complete*/
#define RXNE 	5	/*Read data register not empty*/
#define IDLE	4	/*Idle Line*/

#define USART_8_BIT_WORD			0
#define USART_9_BIT_WORD			1

#define USART_PARITY_DISABLED		0
#define USART_PARITY_ENABLED		1

#define USART_EVEN_PARITY			0
#define USART_ODD_PARITY			1

#define USART_PE_DISABLED			0
#define USART_PE_ENABLED			1

/* status register (USART_SR)  Pins  */
//#define   RXNE      5                  this bit is set when data transferred to USART_DR
                                        /* and interrupt generated if RXNEIE=1 in USART_CR1  */
										   
//#define   TC        6                 /* this bit is set by hardware when transmission is complete and if
                                         /*TXE is set . interrupt is generated if TCIE=1 in USART_CR1 */
										 
//#define   TXE       7

#define   BAUD_RATE_9600_8MHZ       0
#define   BAUD_RATE_115200_8MHZ     1

#endif
