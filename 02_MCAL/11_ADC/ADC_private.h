/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 3/9/2021
 *  Version : V01
 *  Layer   : MCAL
 * 
 */

#ifndef ADC_PRIVATE
#define ADC_PRIVATE


/* Register Definitions For ADC1 */  /* P:51,252 (Reg Des) */
#define ADC1_SR                *( (volatile u32*) (0x40012400 + 0x00) )
#define ADC1_SR_EOC    1

#define ADC1_CR1               *( (volatile u32*) (0x40012400 + 0x04) )
#define ADC1_CR1_EOCIE     5

#define ADC1_CR2               *( (volatile u32*) (0x40012400 + 0x08) )
#define ADC1_CR2_ADON      0
#define ADC1_CR2_CONT      1
#define ADC1_CR2_DMA       8
#define ADC1_CR2_SWSTART   22

#define ADC1_SMPR1             *( (volatile u32*) (0x40012400 + 0x0C) )
#define ADC1_SMPR2             *( (volatile u32*) (0x40012400 + 0x10) )
#define ADC1_JOFR1             *( (volatile u32*) (0x40012400 + 0x14) )
#define ADC1_JOFR2             *( (volatile u32*) (0x40012400 + 0x18) )
#define ADC1_JOFR3             *( (volatile u32*) (0x40012400 + 0x1C) )
#define ADC1_JOFR4             *( (volatile u32*) (0x40012400 + 0x20) )
#define ADC1_HTR               *( (volatile u32*) (0x40012400 + 0x24) )
#define ADC1_LTR               *( (volatile u32*) (0x40012400 + 0x28) )
#define ADC1_SQR1              *( (volatile u32*) (0x40012400 + 0x2C) )
#define ADC1_SQR2              *( (volatile u32*) (0x40012400 + 0x30) )
#define ADC1_SQR3              *( (volatile u32*) (0x40012400 + 0x34) )
#define ADC1_JSQR              *( (volatile u32*) (0x40012400 + 0x38) )
#define ADC1_JDR1              *( (volatile u32*) (0x40012400 + 0x3C) )
#define ADC1_JDR2              *( (volatile u32*) (0x40012400 + 0x40) )
#define ADC1_JDR3              *( (volatile u32*) (0x40012400 + 0x44) )
#define ADC1_JDR4              *( (volatile u32*) (0x40012400 + 0x48) )
#define ADC1_DR                *( (volatile u32*) (0x40012400 + 0x4C) )




/* Register Definitions For ADC2 */  
#define ADC2_SR                *( (volatile u32*) (0x40012800 + 0x00) )
#define ADC2_SR_EOC    1

#define ADC2_CR1               *( (volatile u32*) (0x40012800 + 0x04) )
#define ADC2_CR1_EOCIE     5

#define ADC2_CR2               *( (volatile u32*) (0x40012800 + 0x08) )
#define ADC2_CR2_ADON      0
#define ADC2_CR2_CONT      1
#define ADC2_CR2_DMA       8
#define ADC2_CR2_SWSTART   22

#define ADC2_SMPR1             *( (volatile u32*) (0x40012800 + 0x0C) )
#define ADC2_SMPR2             *( (volatile u32*) (0x40012800 + 0x10) )
#define ADC2_JOFR1             *( (volatile u32*) (0x40012800 + 0x14) )
#define ADC2_JOFR2             *( (volatile u32*) (0x40012800 + 0x18) )
#define ADC2_JOFR3             *( (volatile u32*) (0x40012800 + 0x1C) )
#define ADC2_JOFR4             *( (volatile u32*) (0x40012800 + 0x20) )
#define ADC2_HTR               *( (volatile u32*) (0x40012800 + 0x24) )
#define ADC2_LTR               *( (volatile u32*) (0x40012800 + 0x28) )
#define ADC2_SQR1              *( (volatile u32*) (0x40012800 + 0x2C) )
#define ADC2_SQR2              *( (volatile u32*) (0x40012800 + 0x30) )
#define ADC2_SQR3              *( (volatile u32*) (0x40012800 + 0x34) )
#define ADC2_JSQR              *( (volatile u32*) (0x40012800 + 0x38) )
#define ADC2_JDR1              *( (volatile u32*) (0x40012800 + 0x3C) )
#define ADC2_JDR2              *( (volatile u32*) (0x40012800 + 0x40) )
#define ADC2_JDR3              *( (volatile u32*) (0x40012800 + 0x44) )
#define ADC2_JDR4              *( (volatile u32*) (0x40012800 + 0x48) )
#define ADC2_DR                *( (volatile u32*) (0x40012800 + 0x4C) )




/* Register Definitions For ADC3 */  
#define ADC3_SR                *( (volatile u32*) (0x40013C00 + 0x00) )
#define ADC3_SR_EOC    1

#define ADC3_CR1               *( (volatile u32*) (0x40013C00 + 0x04) )
#define ADC3_CR1_EOCIE     5

#define ADC3_CR2               *( (volatile u32*) (0x40013C00 + 0x08) )
#define ADC3_CR2_ADON      0
#define ADC3_CR2_CONT      1
#define ADC3_CR2_DMA       8
#define ADC3_CR2_SWSTART   22

#define ADC3_SMPR1             *( (volatile u32*) (0x40013C00 + 0x0C) )
#define ADC3_SMPR2             *( (volatile u32*) (0x40013C00 + 0x10) )
#define ADC3_JOFR1             *( (volatile u32*) (0x40013C00 + 0x14) )
#define ADC3_JOFR2             *( (volatile u32*) (0x40013C00 + 0x18) )
#define ADC3_JOFR3             *( (volatile u32*) (0x40013C00 + 0x1C) )
#define ADC3_JOFR4             *( (volatile u32*) (0x40013C00 + 0x20) )
#define ADC3_HTR               *( (volatile u32*) (0x40013C00 + 0x24) )
#define ADC3_LTR               *( (volatile u32*) (0x40013C00 + 0x28) )
#define ADC3_SQR1              *( (volatile u32*) (0x40013C00 + 0x2C) )
#define ADC3_SQR2              *( (volatile u32*) (0x40013C00 + 0x30) )
#define ADC3_SQR3              *( (volatile u32*) (0x40013C00 + 0x34) )
#define ADC3_JSQR              *( (volatile u32*) (0x40013C00 + 0x38) )
#define ADC3_JDR1              *( (volatile u32*) (0x40013C00 + 0x3C) )
#define ADC3_JDR2              *( (volatile u32*) (0x40013C00 + 0x40) )
#define ADC3_JDR3              *( (volatile u32*) (0x40013C00 + 0x44) )
#define ADC3_JDR4              *( (volatile u32*) (0x40013C00 + 0x48) )
#define ADC3_DR                *( (volatile u32*) (0x40013C00 + 0x4C) )


#endif
