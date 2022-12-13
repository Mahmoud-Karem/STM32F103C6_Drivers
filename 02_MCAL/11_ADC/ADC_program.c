/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 3/9/2021
 *  Version : V01
 *  Layer   : MCAL
 * 
 */ 
 
//=====================================================================================================================
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"


#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static u16* ADC1_pu16Reading= NULL;
static void (*ADC1_pvCallBackNotificationFunc)(void)=NULL;
u8 ADC1_u8BusyState= IDLE;

static u16* ADC2_pu16Reading= NULL;
static void (*ADC2_pvCallBackNotificationFunc)(void)=NULL;
u8 ADC2_u8BusyState= IDLE;



static u16* ADC3_pu16Reading= NULL;
static void (*ADC3_pvCallBackNotificationFunc)(void)=NULL;
u8 ADC3_u8BusyState= IDLE;




//=====================================================================================================================
/**********************************************   For ADC1        ****************************************************/
//=====================================================================================================================
/*
	Hint : We will Initialize ADC1 & Channel 0 (PA0)
*/

void ADC1_voidInit(void)
{
/* ADC1 Enable Condition    */
#if ADC1_STATUS == ADC_ENABLE
	
	/* Enable ADC Peripheral */
	SET_BIT( ADC1_CR2 , ADC1_CR2_ADON );

	/***********************************************************************************/
	/*************************  ADC1 Config  *******************************************/
	/***********************************************************************************/
	
	/* Conversion Mode */
	#if ADC1_CON_MODE == ADC_SINGLE_CON_MODE
		CLR_BIT( ADC1_CR2 , ADC1_CR2_CONT );

	#elif ADC1_CON_MODE == ADC_CONTINUOUS_CON_MODE
		SET_BIT( ADC1_CR2 , ADC1_CR2_CONT );

	#endif
	/*******************/
	
	/* Set conversion sequence length to 1 L[3:0]*/
	ADC1_SQR1 = 0 ;
	/*******************/
	
	/*  Set start of conversion sequence to ch 0 (PA0)*/
	ADC1_SQR3 = 0 ;
	/*******************/
	
	/* Enable DMA */
	#if DMA_STATUS == DMA_DISABLE
		CLR_BIT( ADC1_CR2 , ADC1_CR2_DMA );

	#elif DMA_STATUS == DMA_ENABLE
		SET_BIT( ADC1_CR2 , ADC1_CR2_DMA );

	#endif
	/*******************/
	
	
	
	/***********************************************************************************/
	
/* ADC1 Disable Condition    */
#elif ADC1_STATUS == ADC_DISABLE
	
	/* Disable ADC1 Peripheral */
	CLR_BIT( ADC1_CR2 , ADC1_CR2_ADON );
	
#endif

	
}

/*
	Hint : We will Initialize ADC1 & Channel 0 (PA0)
*/

void ADC1_voidChangeCh(u8 Copy_u8Channel)
{

	/*  Set start of conversion sequence to ch 0 (PA0)*/
	ADC1_SQR3 = Copy_u8Channel ;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC1_u8GetResultSync( u16* Copy_pu16Result )
{

	u8 LOC_u8ErrorState = OK ;
	
	u32 LOC_u32Counter = 0 ;
	
	if (ADC1_u8BusyState == IDLE)
	{

			/*
				Hint:
					=> We may config the channel here and take it as an argument from the user in this func
					   if we had many channels
					=> In This App we config this for Ch1 @ ADC1_voidInit
			*/
			/*Start conversion*/
			SET_BIT(ADC1_CR2,ADC1_CR2_SWSTART);


			/***********************************************************************************************************************/
			/* Polling (Busy Waiting) until The conversion complete (EOC flag is set) OR  LOC_u32Counter reached ADC_TIMEOUT */

			while( ( GET_BIT( ADC1_SR , ADC1_SR_EOC ) == 0 ) && ( LOC_u32Counter != ADC_TIMEOUT) )
			{
				LOC_u32Counter ++ ;
			}
			/* Check The reason of breaking the loop   */
			if (LOC_u32Counter == ADC_TIMEOUT)
			{
				/* Loop is broken because time_out is reached */
				LOC_u8ErrorState = NOK ;
			}
			else
			{
				/* Loop is broken because Flag is raised */

				/*
					Clear the conversion complete flag
				    CLR_BIT( ADC1_SR , ADC1_SR_EOC ); we will clear it by reading ADC1_DR
				*/

				/* Return The Reading & Clear EOC flag */
				* Copy_pu16Result = ADC1_DR ;

				/*ADC is finished, return it to IDLE*/
				ADC1_u8BusyState= IDLE;
			}
	}
	else
	{
		LOC_u8ErrorState= BUSY_STATE;
	}


	/***********************************************************************************************************************/

	return LOC_u8ErrorState ;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC1_u8StartConversionAsynch( u16* Copy_pu16Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	/*Check on the ADC state to avoid overwrite on the convertion */
	if(ADC1_u8BusyState== IDLE)
	{
		/* Check Null Pointer  */
		if((Copy_pu16Reading ==NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC1_u8BusyState= BUSY;

			/*************************************************************************************************************************/
			/*
				We should make the address of the Global Pointers as the same as the local which return the result to user
			*/

			/*Initialize the reading variable globally*/
			ADC1_pu16Reading = Copy_pu16Reading;

			/*Initialize the callback notification function globally*/
			ADC1_pvCallBackNotificationFunc= Copy_pvNotificationFunc;

			/*************************************************************************************************************************/

			/*
				Hint:
					=> We maay config the channel here and take it as an argument from the user in this func
					   if we had many channels 
					=> In This App we config this for Ch1 @ ADC1_voidInit
			*/

			/*Start conversion*/
			SET_BIT(ADC1_CR2,ADC1_CR2_SWSTART);

			/*ADC interrupt enable*/
			SET_BIT(ADC1_CR1,ADC1_CR1_EOCIE);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_STATE;
	}

	return Local_u8ErrorState;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC1_voidEnableInterrupt(void)
{
	SET_BIT(ADC1_CR1,ADC1_CR1_EOCIE);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC1_voidDisableInterrupt(void)
{
	  CLR_BIT(ADC1_CR1,ADC1_CR1_EOCIE);
}







//=====================================================================================================================
/**********************************************   For ADC2        ****************************************************/
//=====================================================================================================================
/*
	Hint : We will Initialize ADC1 & Channel 0 (PA0)
*/

void ADC2_voidInit(void)
{
/* ADC1 Enable Condition    */
#if ADC2_STATUS == ADC_ENABLE

	/* Enable ADC Peripheral */
	SET_BIT( ADC2_CR2 , ADC2_CR2_ADON );

	/***********************************************************************************/
	/*************************  ADC1 Config  *******************************************/
	/***********************************************************************************/

	/* Conversion Mode */
	#if ADC2_CON_MODE == ADC_SINGLE_CON_MODE
		CLR_BIT( ADC2_CR2 , ADC2_CR2_CONT );

	#elif ADC2_CON_MODE == ADC_CONTINUOUS_CON_MODE
		SET_BIT( ADC2_CR2 , ADC2_CR2_CONT );

	#endif
	/*******************/

	/* Set conversion sequence length to 1  L[3:0]*/
	ADC2_SQR1 = 0 ;
	/*******************/

	/*  Set start of conversion sequence to ch 0 (PA0)*/
	ADC2_SQR3 = 0 ;
	/*******************/

	/* Enable DMA */
	#if DMA_STATUS == DMA_DISABLE
		CLR_BIT( ADC2_CR2 , ADC2_CR2_DMA );

	#elif DMA_STATUS == DMA_ENABLE
		SET_BIT( ADC2_CR2 , ADC2_CR2_DMA );

	#endif
	/*******************/



	/***********************************************************************************/

/* ADC1 Disable Condition    */
#elif ADC2_STATUS == ADC_DISABLE

	/* Disable ADC1 Peripheral */
	CLR_BIT( ADC2_CR2 , ADC2_CR2_ADON );

#endif


}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC2_u8GetResultSync( u16* Copy_pu16Result )
{

	u8 LOC_u8ErrorState = OK ;

	u32 LOC_u32Counter = 0 ;

	if (ADC2_u8BusyState == IDLE)
	{

			/*
				Hint:
					=> We may config the channel here and take it as an argument from the user in this func
					   if we had many channels
					=> In This App we config this for Ch1 @ ADC2_voidInit
			*/
			/*Start conversion*/
			SET_BIT(ADC2_CR2,ADC2_CR2_SWSTART);

		
			/***********************************************************************************************************************/
			/* Polling (Busy Waiting) until The conversion complete (EOC flag is set) OR  LOC_u32Counter reached ADC_TIMEOUT */

			while( ( GET_BIT( ADC2_SR , ADC2_SR_EOC ) == 0 ) && ( LOC_u32Counter != ADC_TIMEOUT) )
			{
				LOC_u32Counter ++ ;
			}
			/* Check The reason of breaking the loop   */
			if (LOC_u32Counter == ADC_TIMEOUT)
			{
				/* Loop is broken because time_out is reached */
				LOC_u8ErrorState = NOK ;
			}
			else
			{
				/* Loop is broken because Flag is raised */
				
				/*
					Clear the conversion complete flag 
				    CLR_BIT( ADC2_SR , ADC2_SR_EOC ); we will clear it by reading ADC2_DR
				*/
				
				/* Return The Reading & Clear EOC flag */
				* Copy_pu16Result = ADC2_DR ;
				
				/*ADC is finished, return it to IDLE*/
				ADC2_u8BusyState= IDLE;
			}
	}
	else
	{
		LOC_u8ErrorState= BUSY_STATE;
	}

	
	/***********************************************************************************************************************/

	return LOC_u8ErrorState ;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC2_u8StartConversionAsynch( u16* Copy_pu16Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	
	/*Check on the ADC state to avoid overwrite on the convertion */
	if(ADC2_u8BusyState== IDLE)
	{
		/* Check Null Pointer  */
		if((Copy_pu16Reading ==NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC2_u8BusyState= BUSY;
			
			/*************************************************************************************************************************/
			/* 
				We should make the address of the Global Pointers as the same as the local which return the result to user
			*/

			/*Initialize the reading variable globally*/
			ADC2_pu16Reading = Copy_pu16Reading;

			/*Initialize the callback notification function globally*/
			ADC2_pvCallBackNotificationFunc= Copy_pvNotificationFunc;
			
			/*************************************************************************************************************************/
			
			/*
				Hint:
					=> We maay config the channel here and take it as an argument from the user in this func
					   if we had many channels 
					=> In This App we config this for Ch1 @ ADC2_voidInit
			*/

			/*Start conversion*/
			SET_BIT(ADC2_CR2,ADC2_CR2_SWSTART);

			/*ADC interrupt enable*/
			SET_BIT(ADC2_CR1,ADC2_CR1_EOCIE);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_STATE;
	}

	return Local_u8ErrorState;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC2_voidEnableInterrupt(void)
{
	SET_BIT(ADC2_CR1,ADC2_CR1_EOCIE);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC2_voidDisableInterrupt(void)
{
	  CLR_BIT(ADC2_CR1,ADC2_CR1_EOCIE);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC1_2_IRQHandler(void)
{

	/* Check for the source ADC1 or ADC2 (state or EOC bit)  */
	if (( GET_BIT( ADC1_SR , ADC1_SR_EOC ) == 1 ) )
	{
			/*Read ADC result*/
		*ADC1_pu16Reading= ADC1_DR;
	
		/*Make ADC state be IDLE because it finished*/
		ADC1_u8BusyState=IDLE;
	
		/*Invoke the callback notification function*/
		ADC1_pvCallBackNotificationFunc();
	
	
		/*  Disable ADC conversion complete interrupt */
		ADC1_voidDisableInterrupt();
	
	}
	else if (( GET_BIT( ADC2_SR , ADC2_SR_EOC ) == 1 ) )
	{
			/*Read ADC result*/
		*ADC2_pu16Reading= ADC2_DR;
	
		/*Make ADC state be IDLE because it finished*/
		ADC2_u8BusyState=IDLE;
	
		/*Invoke the callback notification function*/
		ADC2_pvCallBackNotificationFunc();
	
	
		/*  Disable ADC conversion complete interrupt */
		ADC2_voidDisableInterrupt();
	}
	

}



//=====================================================================================================================
/**********************************************   For ADC3        ****************************************************/
//=====================================================================================================================
/*
	Hint : We will Initialize ADC1 & Channel 0 (PA0)
*/

void ADC3_voidInit(void)
{
/* ADC1 Enable Condition    */
#if ADC3_STATUS == ADC_ENABLE

	/* Enable ADC Peripheral */
	SET_BIT( ADC3_CR2 , ADC3_CR2_ADON );

	/***********************************************************************************/
	/*************************  ADC1 Config  *******************************************/
	/***********************************************************************************/

	/* Conversion Mode */
	#if ADC3_CON_MODE == ADC_SINGLE_CON_MODE
		CLR_BIT( ADC3_CR2 , ADC3_CR2_CONT );

	#elif ADC3_CON_MODE == ADC_CONTINUOUS_CON_MODE
		SET_BIT( ADC3_CR2 , ADC3_CR2_CONT );

	#endif
	/*******************/

	/* Set conversion sequence length to 1  L[3:0]*/
	ADC3_SQR1 = 0 ;
	/*******************/

	/*  Set start of conversion sequence to ch 0 (PA0)*/
	ADC3_SQR3 = 0 ;
	/*******************/

	/* Enable DMA */
	#if DMA_STATUS == DMA_DISABLE
		CLR_BIT( ADC3_CR2 , ADC3_CR2_DMA );

	#elif DMA_STATUS == DMA_ENABLE
		SET_BIT( ADC3_CR2 , ADC3_CR2_DMA );

	#endif
	/*******************/



	/***********************************************************************************/

/* ADC1 Disable Condition    */
#elif ADC3_STATUS == ADC_DISABLE

	/* Disable ADC1 Peripheral */
	CLR_BIT( ADC3_CR2 , ADC3_CR2_ADON );

#endif


}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC3_u8GetResultSync( u16* Copy_pu16Result )
{

	u8 LOC_u8ErrorState = OK ;

	u32 LOC_u32Counter = 0 ;

	if (ADC3_u8BusyState == IDLE)
	{

			/*
				Hint:
					=> We may config the channel here and take it as an argument from the user in this func
					   if we had many channels
					=> In This App we config this for Ch1 @ ADC3_voidInit
			*/
			/*Start conversion*/
			SET_BIT(ADC3_CR2,ADC3_CR2_SWSTART);

		
			/***********************************************************************************************************************/
			/* Polling (Busy Waiting) until The conversion complete (EOC flag is set) OR  LOC_u32Counter reached ADC_TIMEOUT */

			while( ( GET_BIT( ADC3_SR , ADC3_SR_EOC ) == 0 ) && ( LOC_u32Counter != ADC_TIMEOUT) )
			{
				LOC_u32Counter ++ ;
			}
			/* Check The reason of breaking the loop   */
			if (LOC_u32Counter == ADC_TIMEOUT)
			{
				/* Loop is broken because time_out is reached */
				LOC_u8ErrorState = NOK ;
			}
			else
			{
				/* Loop is broken because Flag is raised */
				
				/*
					Clear the conversion complete flag 
				    CLR_BIT( ADC3_SR , ADC3_SR_EOC ); we will clear it by reading ADC3_DR
				*/
				
				/* Return The Reading & Clear EOC flag */
				* Copy_pu16Result = ADC3_DR ;
				
				/*ADC is finished, return it to IDLE*/
				ADC3_u8BusyState= IDLE;
			}
	}
	else
	{
		LOC_u8ErrorState= BUSY_STATE;
	}

	
	/***********************************************************************************************************************/

	return LOC_u8ErrorState ;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC3_u8StartConversionAsynch( u16* Copy_pu16Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	
	/*Check on the ADC state to avoid overwrite on the convertion */
	if(ADC3_u8BusyState== IDLE)
	{
		/* Check Null Pointer  */
		if((Copy_pu16Reading ==NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_u8ErrorState= NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order not to work until being idle*/
			ADC3_u8BusyState= BUSY;
			
			/*************************************************************************************************************************/
			/* 
				We should make the address of the Global Pointers as the same as the local which return the result to user
			*/

			/*Initialize the reading variable globally*/
			ADC3_pu16Reading = Copy_pu16Reading;

			/*Initialize the callback notification function globally*/
			ADC3_pvCallBackNotificationFunc= Copy_pvNotificationFunc;
			
			/*************************************************************************************************************************/
			
			/*
				Hint:
					=> We may config the channel here and take it as an argument from the user in this func
					   if we had many channels 
					=> In This App we config this for Ch1 @ ADC3_voidInit
			*/

			/*Start conversion*/
			SET_BIT(ADC3_CR2,ADC3_CR2_SWSTART);

			/*ADC interrupt enable*/
			SET_BIT(ADC3_CR1,ADC3_CR1_EOCIE);
		}
	}
	else
	{
		Local_u8ErrorState= BUSY_STATE;
	}

	return Local_u8ErrorState;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC3_voidEnableInterrupt(void)
{
	SET_BIT(ADC3_CR1,ADC3_CR1_EOCIE);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC3_voidDisableInterrupt(void)
{
	  CLR_BIT(ADC3_CR1,ADC3_CR1_EOCIE);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC3_IRQHandler(void)
{

	/*Read ADC result*/
	*ADC3_pu16Reading= ADC3_DR;

	/*Make ADC state be IDLE because it finished*/
	ADC3_u8BusyState=IDLE;

	/*Invoke the callback notification function*/
	ADC3_pvCallBackNotificationFunc();


	/*  Disable ADC conversion complete interrupt */
	ADC3_voidDisableInterrupt();

}

