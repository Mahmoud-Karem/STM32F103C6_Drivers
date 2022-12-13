/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    HLEDMAT_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 7/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 

 
//==============================================================================================================
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "HLEDMAT_interface.h"
#include "HLEDMAT_private.h"
#include "HLEDMAT_config.h"


//==============================================================================================================


void HLEDMAT_voidInit(void)
{
	MDIO_voidSetPinDirection(HLEDMAT_ROW_0,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_1,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_2,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_3,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_4,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_5,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_6,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_ROW_7,OUTPUT_SPEED_2MHZ_PP);
	
	
	MDIO_voidSetPinDirection(HLEDMAT_COL_0,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_1,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_2,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_3,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_4,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_5,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_6,OUTPUT_SPEED_2MHZ_PP);
	MDIO_voidSetPinDirection(HLEDMAT_COL_7,OUTPUT_SPEED_2MHZ_PP);
}


//==============================================================================================================

void HLEDMAT_voidDisplayFrame(u8 *Copy_u8Frame)
{
	for (u8 i=0 ; i<8 ; i++ )
		{
			DisableAllCols();
			SetRowsValue  (Copy_u8Frame[i]);
			ActivateColumn(i);
			MSTK_voidSetBusyWait(2500);
		}
}

//==============================================================================================================


//<<<<<<<<<<<<<<<<<<<<    " Private Functions Called in HLEDMAT_voidDisplayFrame  "   >>>>>>>>>>>>>>>>>>>>>>>>>>>

void DisableAllCols(void)
{
	MDIO_voidSetPinValue(HLEDMAT_COL_0,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_1,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_2,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_3,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_4,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_5,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_6,DIO_HIGH);
	MDIO_voidSetPinValue(HLEDMAT_COL_7,DIO_HIGH);
}


//--------------------------------------------------------------------------------------------------------------


void SetRowsValue  (u8 Copy_u8Value)
{

	MDIO_voidSetPinValue(HLEDMAT_ROW_0,GET_BIT(Copy_u8Value,0));
	MDIO_voidSetPinValue(HLEDMAT_ROW_1,GET_BIT(Copy_u8Value,1));
	MDIO_voidSetPinValue(HLEDMAT_ROW_2,GET_BIT(Copy_u8Value,2));
	MDIO_voidSetPinValue(HLEDMAT_ROW_3,GET_BIT(Copy_u8Value,3));
	MDIO_voidSetPinValue(HLEDMAT_ROW_4,GET_BIT(Copy_u8Value,4));
	MDIO_voidSetPinValue(HLEDMAT_ROW_5,GET_BIT(Copy_u8Value,5));
	MDIO_voidSetPinValue(HLEDMAT_ROW_6,GET_BIT(Copy_u8Value,6));
	MDIO_voidSetPinValue(HLEDMAT_ROW_7,GET_BIT(Copy_u8Value,7));
	
}


//--------------------------------------------------------------------------------------------------------------

void ActivateColumn(u8 Copy_u8Col)
{
	/* Enable the desired pin only */
	switch (Copy_u8Col)
	{
		case 0: MDIO_voidSetPinValue(HLEDMAT_COL_0,DIO_LOW); break;
		case 1: MDIO_voidSetPinValue(HLEDMAT_COL_1,DIO_LOW); break;
		case 2: MDIO_voidSetPinValue(HLEDMAT_COL_2,DIO_LOW); break;
		case 3: MDIO_voidSetPinValue(HLEDMAT_COL_3,DIO_LOW); break;
		case 4: MDIO_voidSetPinValue(HLEDMAT_COL_4,DIO_LOW); break;
		case 5: MDIO_voidSetPinValue(HLEDMAT_COL_5,DIO_LOW); break;
		case 6: MDIO_voidSetPinValue(HLEDMAT_COL_6,DIO_LOW); break;
		case 7: MDIO_voidSetPinValue(HLEDMAT_COL_7,DIO_LOW); break;
	}
}

//==============================================================================================================
