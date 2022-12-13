/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TFT_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 12/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	MDIO_voidSetPinValue(TFT_RST_PIN,DIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MDIO_voidSetPinValue(TFT_RST_PIN,DIO_LOW);
	MSTK_voidSetBusyWait(1);
	MDIO_voidSetPinValue(TFT_RST_PIN,DIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MDIO_voidSetPinValue(TFT_RST_PIN,DIO_LOW);
	MSTK_voidSetBusyWait(100);
	MDIO_voidSetPinValue(TFT_RST_PIN,DIO_HIGH);
	MSTK_voidSetBusyWait(120000); //120 ms
	
	/* Sleep Out Command */
	voidWriteCommand(SLPOUT);
	
	/* Wait 150 ms */
	MSTK_voidSetBusyWait(150000);
	
	/* Color Mode Command */
	voidWriteCommand(COLMOD);
	voidWriteData   (COLMOD_P);
	
	/* Display On Command */
	voidWriteCommand(DISPON);
	MSTK_voidSetBusyWait(1000);
	
	/* Remap TFT addresses ( x = 0 , y = 0 Start From The Left Top Of The TFT ) */
	voidWriteCommand( MADCTL );
	voidWriteData   ( 0xC0 );
	
}


void HTFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	voidWriteCommand(CASET);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(XSIZE-1);
	
	/* Set Y Address */
	voidWriteCommand(RASET);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(YSIZE-1);

	/* RAM Write */
	voidWriteCommand(RAMWR);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the DIO_HIGH byte */
		voidWriteData(Data);
		/* Write the DIO_LOW byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}


void HTFT_voidFillColor (u16 Copy_u16Color)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	voidWriteCommand(CASET);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(XSIZE-1);
	
	/* Set Y Address */
	voidWriteCommand(RASET);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(YSIZE-1);

	/* RAM Write */
	voidWriteCommand(RAMWR);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_u16Color >> 8;

		/* Write the DIO_HIGH byte */
		voidWriteData(Data);
		/* Write the DIO_LOW byte */
		Data = Copy_u16Color & 0x00ff;
		voidWriteData(Data);
	}


}

void HTFT_voidDrawHLine ( u8 Xaxis , u8 Yaxis , u8 Copy_u8Length , u16 Copy_u8Color )
 {

	for ( ; Copy_u8Length > 0 ; Copy_u8Length-- ){

		voidWriteCommand( CASET ); // set column range (x0,x1)

		voidWriteData   ( Xaxis );
		voidWriteData   ( Xaxis );

		voidWriteCommand( RASET ); // set row range (y0,y1)

		voidWriteData   ( Yaxis );
		voidWriteData   ( Yaxis );

		voidWriteCommand( RAMWR ); // memory write

		voidWriteData ( Copy_u8Color >> 8   ); // write hi byte
		voidWriteData ( Copy_u8Color & 0xFF ); // write lo byte

		Xaxis++;

	}

}

void HTFT_voidDrawVLine ( u8 Xaxis , u8 Yaxis , u8 Copy_u8Length , u16 Copy_u8Color )
 {

	for ( ; Copy_u8Length > 0 ; Copy_u8Length-- ){

		voidWriteCommand( CASET ); // set column range (x0,x1)

		voidWriteData   ( Xaxis );
		voidWriteData   ( Xaxis );

		voidWriteCommand( RASET ); // set row range (y0,y1)

		voidWriteData   ( Yaxis );
		voidWriteData   ( Yaxis );

		voidWriteCommand( RAMWR ); // memory write

		voidWriteData ( Copy_u8Color >> 8   ); // write hi byte
		voidWriteData ( Copy_u8Color & 0xFF ); // write lo byte

		Yaxis++;

	}

}

void HTFT_voidDrawRectangle ( u8 Copy_u8Height , u8 Copy_u8Width , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color )
{

	HTFT_voidDrawHLine ( Xaxis , Yaxis , Copy_u8Width  , Copy_u8Color                 );
	HTFT_voidDrawVLine ( Xaxis , Yaxis , Copy_u8Height , Copy_u8Color                 );
	HTFT_voidDrawHLine ( Xaxis , Copy_u8Height + Yaxis , Copy_u8Width  , Copy_u8Color );
	HTFT_voidDrawVLine ( Copy_u8Width + Xaxis , Yaxis , Copy_u8Height , Copy_u8Color  );

}


/*   This is as same as the previous func using another mathod  */
void HTFT_voidDrawRect (u8 x1 , u8 x2 , u8 y1 , u8 y2 ,u16 Copy_u16Color)
{
	u16 counter;
	u8 Data;
	
	u16 size = (x2-x1) * (y2-y1) ;


	/* Set X Address */
	voidWriteCommand(CASET);
	voidWriteData(0);
	voidWriteData(x1);   // LOW byte for Start
	voidWriteData(0);
	voidWriteData(x2);   // LOW byte for End
	
	/* Set Y Address */
	voidWriteCommand(RASET);
	voidWriteData(0);
	voidWriteData(y1);
	voidWriteData(0);
	voidWriteData(y2);

	/* RAM Write */
	voidWriteCommand(RAMWR);

	for(counter = 0; counter< size ;counter++)
	{
		Data = Copy_u16Color >> 8;

		/* Write the DIO_HIGH byte */
		voidWriteData(Data);
		/* Write the DIO_LOW byte */
		Data = Copy_u16Color & 0x00ff;
		voidWriteData(Data);
	}


}





void HTFT_voidWriteChar( u8 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color )
{

	u8  LOC_u8Mask = 0x01 ;
	u8  LOC_u8DataMasked  ;
	u16 LOC_u8Pixel       ;

	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 5 ; LOC_u8Iterator1++ ){

		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 7 ; LOC_u8Iterator2++ ){

			/* Set The Position Of 5x7 Character */
			voidWriteCommand( CASET ); // set column range (x0,x1)

			voidWriteData( Xaxis +  LOC_u8Iterator1 );
			voidWriteData( Xaxis +  LOC_u8Iterator1 );

			voidWriteCommand( RASET ); // set row range (y0,y1)

			voidWriteData( Yaxis +  LOC_u8Iterator2 );
			voidWriteData( Yaxis +  LOC_u8Iterator2 );

			voidWriteCommand( RAMWR ); // memory write

			LOC_u8DataMasked = Cop_u8Char[ LOC_u8Iterator1 ] & LOC_u8Mask ;

			if( LOC_u8DataMasked == 0  ) { LOC_u8Pixel = 0x0000       ; }
			else                         { LOC_u8Pixel = Copy_u8Color ; }

			voidWriteData ( LOC_u8Pixel >> 8   ); // write hi byte
			voidWriteData ( LOC_u8Pixel & 0xFF ); // write lo byte

			LOC_u8Mask <<= 1 ;

		}

		LOC_u8Mask = 0x01 ;

	}

}





/***************************************************************/

static void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp; // return result for SPI
	
	/* Set A0 Pin to DIO_LOW */
	MDIO_voidSetPinValue(TFT_A0_PIN,DIO_LOW);
	
	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Command,&Local_u8Temp);
}

static void voidWriteData   (u8 Copy_u8Data)
{
	u8 Local_u8Temp; // return result for SPI
	
	/* Set A0 Pin to DIO_HIGH */
	MDIO_voidSetPinValue(TFT_A0_PIN,DIO_HIGH);
	
	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Data,&Local_u8Temp);
}






