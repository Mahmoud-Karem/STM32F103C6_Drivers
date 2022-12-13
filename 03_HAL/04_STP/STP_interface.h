/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STP_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 10/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
 
#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H


void HSTP_voidInit( void );
void HSTP_voidSendByteSynchronus    (u8  Copy_u8DataToSend );
void HSTP_voidSendTwoBytesSynchronus(u16 Copy_u8DataToSend );


#endif