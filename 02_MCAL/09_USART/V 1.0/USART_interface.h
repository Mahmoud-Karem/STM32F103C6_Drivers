/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_interface.h  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 11/7/2021
 *  Version : V01
 *  Layer   : MCAL
 *
 */
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H



void MUSART1_voidInit(void);
void MUSART1_voidTransmit(char* arr);
u8   MUSART1_u8Receive (u32 Copy_u32timeout);

#endif
