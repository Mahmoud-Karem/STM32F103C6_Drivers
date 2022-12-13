/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 3/9/2021
 *  Version : V01
 *  Layer   : MCAL
 * 
 */
 
#ifndef ADC_CONFIG
#define ADC_CONFIG

/*
	$ Options:-
		1- ADC_ENABLE
		2- ADC_DISABLE
*/
#define ADC1_STATUS  ADC_ENABLE
#define ADC2_STATUS  ADC_ENABLE
#define ADC3_STATUS  ADC_DISABLE


/*
	$ Options:-
		1- ADC_SINGLE_CON_MODE
		2- ADC_CONTINUOUS_CON_MODE
*/
#define ADC1_CON_MODE   ADC_CONTINUOUS_CON_MODE
#define ADC2_CON_MODE   ADC_CONTINUOUS_CON_MODE
#define ADC3_CON_MODE   ADC_CONTINUOUS_CON_MODE

/*
	$ Options:-
		1- DMA_ENABLE
		2- DMA_DISABLE
*/
#define DMA_STATUS  DMA_DISABLE 

/* TIMEOUT to avoid infinite loops in Busy waiting */
#define  ADC_TIMEOUT      50000


#endif
