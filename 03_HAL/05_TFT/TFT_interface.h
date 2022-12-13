/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TFT_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 12/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

/************************************************/

// ST7735 ROUTINES
#define SWRESET  0x01 // software reset
#define SLPOUT   0x11 // sleep out
#define DISPOFF  0x28 // display off
#define DISPON   0x29 // display on
#define CASET    0x2A // column(x) address set
#define RASET    0x2B // row(y) address set
#define RAMWR    0x2C // RAM write
#define MADCTL   0x36 // axis control
#define COLMOD   0x3A // color mode ID
#define COLMOD_P 0x05 // color mode parameter

// 1.8" TFT display constants
#define XSIZE 128
#define YSIZE 160
#define XMAX XSIZE-1
#define YMAX YSIZE-1

// Color constants
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x0400
#define LIME     0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

/*************************************************************************************************************/


void HTFT_voidInitialize    (void                                                                         );
void HTFT_voidDisplayImage  (const u16* Copy_Image                                                        );
void HTFT_voidFillColor     (u16 Copy_u16Color                                                            );

void HTFT_voidDrawHLine     ( u8 Xaxis , u8 Yaxis , u8 Copy_u8Length , u16 Copy_u8Color                   );
void HTFT_voidDrawVLine     ( u8 Xaxis , u8 Yaxis , u8 Copy_u8Length , u16 Copy_u8Color                   );

void HTFT_voidDrawRectangle ( u8 Copy_u8Height , u8 Copy_u8Width , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color );
void HTFT_voidDrawRect      (u8 x1 , u8 x2 , u8 y1 , u8 y2 ,u16 Copy_u16Color                             );

void HTFT_voidWriteChar     ( u8 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color                    );

/*************************************************************************************************************/

#endif