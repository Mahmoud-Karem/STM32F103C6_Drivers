/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ESP_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 13/7/2021
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

void HESP_voidInit(void);
void HESP_voidConnctToRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword);
void HESP_voidConnectToServer(char* Copy_u8StrMode, char* Copy_u8StrIP, char* Copy_u8StrPort);
void HESP_u8ExecuteHttpRequest(char* Copy_u8StrRequest , char* Copy_u8Return );

#endif
