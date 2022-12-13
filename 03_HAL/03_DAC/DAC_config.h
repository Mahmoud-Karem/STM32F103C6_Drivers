/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DAC_config.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 9/7/2021
 *  Vertion : V01
 *  Layer   : HAL
 * 
 */ 
 
#ifndef DAC_CONFIG_H_
#define DAC_CONFIG_H_

//==============================================================================================================


/**************************************************************************************************************/
/*                                                                                                            */
/*                             The Connection of The Circuit                                                  */
/*                                                                                                            */
/**************************************************************************************************************/
/*                                                                                                            */
/*                                                                                    O--SpeaKer              */
/*                                                                                    |                       */
/*                                                                                    |                       */
/*                                                                                    @                       */
/*               ###################                 ###################         ##### ######                 */
/*               #                 #                 #                 #         #          #                 */
/*               #       MC        #                 #       DAC       #         #    Z     #                 */
/*               #                 #                 #                 #         #          #                 */
/*               #             A0 -#-----------------#- BIT0           #         # L  G  R  #                 */
/*               #             .  -#-----------------#-  .             #         ##|##|##|###                 */
/*               #             .  -#-----------------#-  .             #           |  |  |                    */
/*               #             .  -#-----------------#-  .             #           |  |  |                    */
/*               #             .  -#-----------------#-  .             #           |  |  |                    */
/*               #             .  -#-----------------#-  .         OUT-#-----------O--|--O                    */
/*               #             .  -#-----------------#-  .             #              |                       */
/*               #             A7 -#-----------------#- BIT7       GND-#--------------O----------GND          */
/*               #                 #                 #                 #            (Ground of the circuit)   */
/*               #                 #                 #                 #                                      */
/*               #                 #                 #                 #                                      */
/*               #                 #                 #                 #                                      */
/*               #                 #                 #                 #                                      */
/*               ###################                 ###################                                      */
/*                                                                                                            */
/*                                                                                                            */
/*  $ Hint : WE have to add an amplifier (LM386) with voltage devider                                         */
/*            to make the sound higher without losing the signal                                              */
/*                                                                                                            */
/**************************************************************************************************************/

#define DAC_PORT      DIOA
#define DAC_PORT_LH   DIO_LOW


//==============================================================================================================
#endif /* DAC_CONFIG_H_ */
