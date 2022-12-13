/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DMA_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 10/7/2021
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 


/*Preprocessor File Guard*/
#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

/* struct for every channel */
typedef struct{

	volatile u32 CCR       ;//0x000
	volatile u32 CNDTR     ;//0x004
	volatile u32 CPAR      ;//0x008
	volatile u32 CMAR      ;//0x00C
	volatile u32 RESERVED  ;//0x010

}DMACHANNEL;

typedef struct{

	volatile u32 ISR  ;//0x000
	volatile u32 IFCR ;//0x004
	DMACHANNEL CHANNEL[7];//0x008

}DMA;

#define DMA	((volatile DMA *)0x40020000)

#endif