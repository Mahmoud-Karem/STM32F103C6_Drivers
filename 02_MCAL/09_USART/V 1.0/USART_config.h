/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_config.h  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 11/7/2021
 *  Version : V01
 *  Layer   : MCAL
 *
 */

#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/*
	Baud rate to be implemented

	For 8MHz:-
	9600-> 52.083 :-
	F=1
	M=34
	0x134

	115200-> 4.34 :-
	F=5
	M=4
	0x54

*/

/*	$ Options:-
		1-BAUD_9600
		2-BAUD_115200
*/
#define BAUD_RATE		BAUD_115200


/*	$ Options:-
		1-USART_8_BIT_WORD
		2-USART_9_BIT_WORD
*/
#define USART1_WORD		USART_8_BIT_WORD 

/*	$ Options:-
		1-USART_PARITY_DISABLED
		2-USART_PARITY_ENABLED
*/
#define USART1_PARITY	 	USART_PARITY_DISABLED	

/*	$ Options:-
		1-USART_EVEN_PARITY
		2-USART_ODD_PARITY
*/
#define PARITY	USART_EVEN_PARITY

/*	$ Options:-
 * Parity error interrupt enable state:
		1-USART_PE_DISABLED
        2-USART_PE_ENABLED
*/
#define PARITY_ERROR_INTERRUPT		USART_PE_DISABLED


#endif
