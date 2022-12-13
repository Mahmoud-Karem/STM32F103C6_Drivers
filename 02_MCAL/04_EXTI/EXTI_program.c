/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 6/7/2021
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"
//==============================================================================================================

#define NULL		(void * )0


static void (* EXTI0_CallBack) (void) = NULL ;

//==============================================================================================================

void MEXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI -> IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI -> IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI -> IMR , EXTI_LINE2 );
	#elif	EXTI_LINE == EXTI_LINE3
			SET_BIT(EXTI -> IMR , EXTI_LINE3 );
	#elif	EXTI_LINE == EXTI_LINE4
			SET_BIT(EXTI -> IMR , EXTI_LINE4 );
	#elif	EXTI_LINE == EXTI_LINE5
			SET_BIT(EXTI -> IMR , EXTI_LINE5 );
	#elif	EXTI_LINE == EXTI_LINE6
			SET_BIT(EXTI -> IMR , EXTI_LINE6 );
	#elif	EXTI_LINE == EXTI_LINE7
			SET_BIT(EXTI -> IMR , EXTI_LINE7 );
	#elif	EXTI_LINE == EXTI_LINE8
			SET_BIT(EXTI -> IMR , EXTI_LINE8 );
	#elif	EXTI_LINE == EXTI_LINE9
			SET_BIT(EXTI -> IMR , EXTI_LINE9 );
	#elif	EXTI_LINE == EXTI_LINE10
			SET_BIT(EXTI -> IMR , EXTI_LINE10 );
	#elif	EXTI_LINE == EXTI_LINE11
			SET_BIT(EXTI -> IMR , EXTI_LINE11 );
	#elif	EXTI_LINE == EXTI_LINE12
			SET_BIT(EXTI -> IMR , EXTI_LINE12 );
	#elif	EXTI_LINE == EXTI_LINE13
			SET_BIT(EXTI -> IMR , EXTI_LINE13 );
	#elif	EXTI_LINE == EXTI_LINE14
			SET_BIT(EXTI -> IMR , EXTI_LINE14 );
	#elif	EXTI_LINE == EXTI_LINE15
			SET_BIT(EXTI -> IMR , EXTI_LINE15 );
	
	#else
		#error ("Wrong Externl Interrupt Line !")
	#endif
	
	
	#if		EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
			/*  Fore more speed  ==> (EXTI -> FTSR) |= (1 <<  EXTI_LINE);  */
	#elif	EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else
		#error ("Wrong Externl Interrupt Sense Mode !")
	#endif
	
	
}


//==============================================================================================================

void MEXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode)
{	
	switch(Copy_u8EXTISenseMode)
	{
		case	RISING_EDGE		:	SET_BIT(EXTI -> RTSR , EXTI_LINE);	break;
		case	FALLING_EDGE	:	SET_BIT(EXTI -> FTSR , EXTI_LINE);	break;
		case	ON_CHANGE		:	SET_BIT(EXTI -> RTSR , EXTI_LINE);	
									SET_BIT(EXTI -> FTSR , EXTI_LINE);	break;
	}
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
}


//==============================================================================================================

void MEXTI_voidEnableEXTI(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
}


//==============================================================================================================

void MEXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI -> IMR , Copy_u8EXTILine);
	
}


//==============================================================================================================

void MEXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI -> SWIER , Copy_u8EXTILine);
}



//==============================================================================================================

//////////////////////////////////////////////////// ISR 0 /////////////////////////////////////////////////////

void MEXTI0_voidSetCallBack(void (*ptr) (void))
{
		EXTI0_CallBack = ptr ;
}

void	EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();  // Calling the func @ main
	
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 0);
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==============================================================================================================

