/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    IR_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 9/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
 
#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

#define TIMER_VALUE              150000UL
#define END_OF_CODE              (u8)33

#define DATA_COMMEND_START_EDGE  17
#define DATA_COMMEND_END_EDGE    25

#define LOGIC1_RANGE             2000


#define POWER_BUTTON             (u8)69
#define MODE_BUTTON              (u8)70
#define MUTE_BUTTON              (u8)71
#define PLAY_BUTTON              (u8)68
#define LEFT_BUTTON              (u8)64
#define RIGHT_BUTTON             (u8)67
#define EQ_BUTTON                (u8)7
#define VOL_DOWN_BUTTON          (u8)21
#define VOL_UP_BUTTON            (u8)9
#define ZER0_BUTTON              (u8)22
#define RPT_BUTTON               (u8)25
#define USD_BUTTON               (u8)13
#define ONE_BUTTON               (u8)12
#define TWO_BUTTON               (u8)24
#define THREE_BUTTON             (u8)94
#define FOUR_BUTTON              (u8)8
#define FIVE_BUTTON              (u8)28
#define SIX_BUTTON               (u8)90
#define SEVEN_BUTTON             (u8)66
#define EIGHT_BUTTON             (u8)82
#define NINE_BUTTON              (u8)74


void IR_voidInit          ( void );
u8 IR_u8GetCode          ( void );

void Read_CodeCallBack   ( void );
void Timer_ResetCallBack ( void );

#endif /* IR_INTERFACE_H_ */
