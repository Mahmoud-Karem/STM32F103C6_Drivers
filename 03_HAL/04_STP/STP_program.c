/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STP_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 10/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"
#include "RCC_interface.h"

#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"

void HSTP_voidInit( void ){ 

	RCC_voidEnablePeripheralClock (  APB2_BUS , DIOA_RCC  );

	MDIO_voidSetPinDirection( HSTP_SERIAL_DATA , OUTPUT_SPEED_2MHZ_PP );
	MDIO_voidSetPinDirection( HSTP_SHIFT_CLOCK , OUTPUT_SPEED_2MHZ_PP );
	MDIO_voidSetPinDirection( HSTP_STORE_CLOCK , OUTPUT_SPEED_2MHZ_PP );

}

void HSTP_voidSendByteSynchronus(u8 Copy_u8DataToSend)
{
	s8 Local_s8Counter;
	u8 Local_u8Bit;
	for (Local_s8Counter = 7; Local_s8Counter >=0; Local_s8Counter--)
	{
		/* Send bit by bit strating from MSb */
		Local_u8Bit =  GET_BIT(Copy_u8DataToSend,Local_s8Counter);
		
		MDIO_voidSetPinValue(HSTP_SERIAL_DATA,Local_u8Bit);
		
		/* Send Pulse to Shift Clock */
		MDIO_voidSetPinValue(HSTP_SHIFT_CLOCK,DIO_HIGH);
		MSTK_voidSetBusyWait(1);
		MDIO_voidSetPinValue(HSTP_SHIFT_CLOCK,DIO_LOW);
		MSTK_voidSetBusyWait(1);
	}
	
			/* Send Pulse to Shift Clock */
	MDIO_voidSetPinValue(HSTP_STORE_CLOCK,DIO_HIGH);
	MSTK_voidSetBusyWait(1);
	MDIO_voidSetPinValue(HSTP_STORE_CLOCK,DIO_LOW);
	MSTK_voidSetBusyWait(1);
	
}

void HSTP_voidSendTwoBytesSynchronus(u16 Copy_u8DataToSend)
{
	s8 Local_s8Counter;
	u8 Local_u8Bit;
	for (Local_s8Counter = 15 ; Local_s8Counter >=0; Local_s8Counter--)
	{
		/* Send bit by bit strating from MSb */
		Local_u8Bit =  GET_BIT(Copy_u8DataToSend,Local_s8Counter);
		
		MDIO_voidSetPinValue(HSTP_SERIAL_DATA,Local_u8Bit);
		
		/* Send Pulse to Shift Clock */
		MDIO_voidSetPinValue(HSTP_SHIFT_CLOCK,DIO_HIGH);
		MSTK_voidSetBusyWait(1);
		MDIO_voidSetPinValue(HSTP_SHIFT_CLOCK,DIO_LOW);
		MSTK_voidSetBusyWait(1);
	}
	
			/* Send Pulse to Shift Clock */
	MDIO_voidSetPinValue(HSTP_STORE_CLOCK,DIO_HIGH);
	MSTK_voidSetBusyWait(1);
	MDIO_voidSetPinValue(HSTP_STORE_CLOCK,DIO_LOW);
	MSTK_voidSetBusyWait(1);
	
}
