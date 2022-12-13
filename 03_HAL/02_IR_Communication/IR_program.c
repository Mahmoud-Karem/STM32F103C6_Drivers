/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    IR_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
#include "NVIC_interface.h"
#include "AFIO_interface.h"
#include "EXTI_interface.h"

#include "IR_interface.h"
#include "IR_config.h"

//==============================================================================================================

volatile u8  Start           =   0   ;
volatile u8  Counter         =   0   ;
volatile u32 CodeSample[100] = { 0 } ;
volatile u8  Data            =   0   ;
volatile u8  Iterator        =   0   ;

void Read_CodeCallBack ( void ){

	if ( Start == 0 ){

		MSTK_voidStart( TIMER_VALUE );
		Start = 1;

	}
	else if ( Start == 1 ){

		CodeSample[ Counter ] = MSTK_u32GetRemainingTime();
		Counter++ ;
		MSTK_voidSetBusyWait( TIMER_VALUE );

	}
	if( Counter == END_OF_CODE ){

		for( Iterator = 0 ; Iterator < END_OF_CODE ; Iterator++ ){

			CodeSample[ Iterator ] = TIMER_VALUE - CodeSample[ Iterator ];

		}

		for( Iterator = DATA_COMMEND_START_EDGE ; Iterator < DATA_COMMEND_END_EDGE ; Iterator++ ){

			if( CodeSample[ Iterator ] >= LOGIC1_RANGE ){

				SET_BIT( Data , ( Iterator - DATA_COMMEND_START_EDGE ) );

			}

		}

		MNVIC_voidDisableInterrupt( EXTI0 );

		Start   = 2 ;

	}

}


void Timer_ResetCallBack ( void ){

	MSTK_voidStopInterval();
	Start  = 0 ;
	Counter = 0 ;
	Data    = 0 ;

}

void IR_voidInit( void ){

	MDIO_voidSetPinDirection       ( IR_PORT , IR_PIN , INPUT_FLOATING     );

	MNVIC_voidSetPriority          ( EXTI0 ,  1 , NO_SUB_PRIORITY , GROUP3 );
	MNVIC_voidEnableInterrupt      ( EXTI0                                 );

	MAFIO_voidSetEXTIConfiguration ( EXTI_LINE0 , IR_PORT                  );
	MEXTI0_voidSetCallBack         ( Read_CodeCallBack                     );
	MEXTI_voidInit                 ( EXTI_LINE0 , FALLING_EDGE             );
 
	MEXTI0_voidSetCallBack         ( Timer_ResetCallBack                   );
	MEXTI_voidInit                 (                                       );

}

u8 IR_u8GetCode ( void ){

	u8 LOC_u8Data = 0 ;

	while( Start != 2 );

	LOC_u8Data = Data ;

	Start   = 0 ;
	Counter = 0 ;
	Data    = 0 ;

	MNVIC_voidEnableInterrupt   ( EXTI0 );

	return LOC_u8Data ;
}

