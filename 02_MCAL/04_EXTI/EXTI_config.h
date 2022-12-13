/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 6/7/2021
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

//==============================================================================================================

/*
 $ Options :-
			EXTI_LINE0
			EXTI_LINE1
			EXTI_LINE2
			.
			.
			.
			EXTI_LINE15

*/
#define	EXTI_LINE			EXTI_LINE0

//==============================================================================================================

/*
 $ Options :-
			FALLING_EDGE
			RISING_EDGE
			ON_CHANGE
*/
#define	EXTI_SENSE_MODE		FALLING_EDGE

//==============================================================================================================

#endif