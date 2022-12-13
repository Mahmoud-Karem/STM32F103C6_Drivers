/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DAC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 9/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
//==============================================================================================================
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "DAC_interface.h"
#include "DAC_private.h"
#include "DAC_config.h"

#include "arr.h"

//==============================================================================================================

volatile u32 Song_Counter = 0;

//==============================================================================================================
void DAC_CALLBACK( void ){

	MDIO_voidSetPortValue( DAC_PORT , DAC_PORT_LH , Array[ Song_Counter ] );
	Song_Counter++;

	if( Song_Counter == Arr_Length ){
		Song_Counter = 0;
	}

}

//==============================================================================================================

void MDAC_voidInit( void ){

	MDIO_voidSetPortDirection( DAC_PORT , DAC_PORT_LH , OUTPUT_SPEED_10MHZ_PP );
	MSTK_voidInit();

}


//--------------------------------------------------------------------------------------------------------------

void MDAC_voidPlay( void ){

	MSTK_voidSetIntervalPeriodic(125,DAC_CALLBACK);
	//MSTK_voidSetCallBack( DAC_CALLBACK );
	//MSTK_voidSetBusyWait( 125 );

}

//==============================================================================================================

