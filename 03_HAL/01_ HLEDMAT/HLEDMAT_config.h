/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    HLEDMAT_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 7/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
#ifndef HLEDMAT_CONFIG_H
#define HLEDMAT_CONFIG_H


//==============================================================================================================

                             /*       Connection of Row AND Column Pins   */

/*    Please Write Row Pins Pair => DIOx,PINx      */
#define HLEDMAT_ROW_0      DIOA,PIN0
#define HLEDMAT_ROW_1      DIOA,PIN1
#define HLEDMAT_ROW_2      DIOA,PIN2
#define HLEDMAT_ROW_3      DIOA,PIN3
#define HLEDMAT_ROW_4      DIOA,PIN4
#define HLEDMAT_ROW_5      DIOA,PIN5
#define HLEDMAT_ROW_6      DIOA,PIN6
#define HLEDMAT_ROW_7      DIOA,PIN7

/*    Please Write Column Pins Pair => DIOx,PINx   */
#define HLEDMAT_COL_0      DIOB,PIN0
#define HLEDMAT_COL_1      DIOB,PIN1
#define HLEDMAT_COL_2      DIOB,PIN5
#define HLEDMAT_COL_3      DIOB,PIN6
#define HLEDMAT_COL_4      DIOB,PIN7
#define HLEDMAT_COL_5      DIOB,PIN8
#define HLEDMAT_COL_6      DIOB,PIN9
#define HLEDMAT_COL_7      DIOB,PIN10

//==============================================================================================================


#endif