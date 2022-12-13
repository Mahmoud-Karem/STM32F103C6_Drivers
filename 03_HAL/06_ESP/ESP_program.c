/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ESP_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mahmoud Karem Zamel
 *  Date    : 13/7/2021
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */

//=====================================================================================================================

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include<string.h>
#include<stdio.h>

#include "USART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

char Quotes	[]	 = "\""		;
char Comma 	[]	 = {","};
char Closing[]	 = "\r\n"	;

u8 Local_u8Response[100] ={0};

void HESP_voidInit(void)
{
	u8 Local_u8ValidFlag = 0;

	while(Local_u8ValidFlag == 0)
	{
		/*Stop Echo*/
		MUSART1_voidTransmit("ATE0\r\n");
		/*	Check command is done right
			ATE0 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(ECHO_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;
	
	while(Local_u8ValidFlag == 0)
	{
		/*Set ESP station mode*/
		MUSART1_voidTransmit("AT+CWMODE=1\r\n");
		/*	Check command is done right
			AT+CWMODE=1 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(MODE_TIMEOUT);
	}
}


void HESP_voidConnctToRouter(char* Copy_u8StrSsid, char* Copy_u8StrPassword)
{
	u8 Local_u8ValidFlag = 0;
	char Router_Command[50];
	
	/* Empty the pointer that strcat was using last time as it saves at the same location and data may interference*/
	strcpy(Router_Command, "");

	/*catenating strings to be : "AT+CWJAP_CUR="Copy_u8StrSsid","Copy_u8StrPassword""*/
	strcat(Router_Command, "AT+CWJAP_CUR=");

	strcat(Router_Command, Quotes);
	strcat(Router_Command, Copy_u8StrSsid);
	strcat(Router_Command, Quotes);
	
	strcat(Router_Command, Comma);
	
	strcat(Router_Command, Quotes);
	strcat(Router_Command, Copy_u8StrPassword);
	strcat(Router_Command, Quotes);
	
	strcat(Router_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{
		/*Connect to WiFi of name Copy_u8StrSsid and password Copy_u8StrPassword*/
		MUSART1_voidTransmit(Router_Command);
		/*	Check command is done right
			AT+CWJAP_CUR="SSID","Pass" returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(ROUTER_TIMEOUT);
	}
}

void HESP_voidConnectToServer(char* Copy_u8StrMode, char* Copy_u8StrIP, char* Copy_u8StrPort)
{
	u8 Local_u8ValidFlag = 0;
	char Server_Command[42];

	/* Empty the pointer that strcat was using last time as it saves at the same location and data may interference*/
	strcpy(Server_Command, "");

	/*catenating strings to be : "AT+CIPSTART="Copy_u8StrMode","Copy_u8StrIP",Copy_u8StrPort"
	 	 Example "AT+CIPSTART="TCP","162.154.13.54",80"    */
	strcat(Server_Command, "AT+CIPSTART=");
	
	strcat(Server_Command, Quotes);
	strcat(Server_Command, Copy_u8StrMode);
	strcat(Server_Command, Quotes);
	
	strcat(Server_Command, Comma);
	
	strcat(Server_Command, Quotes);
	strcat(Server_Command, Copy_u8StrIP);
	strcat(Server_Command, Quotes);
	
	strcat(Server_Command, Comma);
	
	strcat(Server_Command, Copy_u8StrPort);
	
	strcat(Server_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{
		/*	Connect to Server of IP Copy_u8StrIP with Copy_u8StrMode potocol
			Either TCP or UDP and on Port Copy_u8StrPort*/
		MUSART1_voidTransmit(Server_Command);
		/*	Check command is done right
			AT+CIPSTART="MODE","IP",PORT returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(SERVER_TIMEOUT);
	}
}

void HESP_u8ExecuteHttpRequest(char* Copy_u8StrRequest , char* Copy_u8Return )
{
	u8 Local_u8ValidFlag = 0;
	char Send_Command[14];
	char Request_Command[(strlen(Copy_u8StrRequest) + 2)];
	char Temp_str[2];

	/* Empty the pointer that strcat was using last time as it saves at the same location and data may interference*/
	strcpy(Send_Command, "AT+CIPSEND=");

	/* calculate request length and add 2 for \r\n */
	u8 NumberOfLetters = strlen(Copy_u8StrRequest) + 2;
	/*Convert the number of the request letters to String*/
	sprintf(Temp_str, "%i", NumberOfLetters);
	
	strcat(Send_Command, Temp_str);
	
	strcat(Send_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{
		/*	Send number of letter from the coming request*/
		MUSART1_voidTransmit(Send_Command);
		/*	Check command is done right
			AT+CIPSEND=NUMBER returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(PREREQUEST_TIMEOUT);
	}
	
	Local_u8ValidFlag = 0;
	strcpy(Request_Command, "");
	strcat(Request_Command, Copy_u8StrRequest);
	strcat(Request_Command, Closing);
	
	while(Local_u8ValidFlag == 0)
	{
		/*	Send number of letter from the coming request*/
		MUSART1_voidTransmit(Request_Command);
		/*	Check command is done right
			AT+CIPSEND=NUMBER returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(REQUEST_TIMEOUT);
	}
	
	u8 Temp_char;
	/* When we receive data from server it would be in the form +IPD,NUMBER_OF_LETTERS_RECIEVED;DATA*/
	for(u8 i = 0; i < 98; i++)
	{
		/*Checking that the data recieved have IPD*/
		if(Local_u8Response[i] == 'I' && Local_u8Response[i+1] == 'P' && Local_u8Response[i+2] == 'D')
		{
			/*Return data in the 6th postion after the I*/
			Temp_char = Local_u8Response[i+6];
		}
	}

	(* Copy_u8Return) = Temp_char ;
	/*if(Temp_char == '1')
		Temp_char = 1;
	else if (Temp_char == '0')
		Temp_char = 0;
	return Temp_char;*/
}

u8 u8ValidateCmd(u32 Copy_u32timeout)
{
	u8 Local_u8ValidFlag = 0;
	u8 Counter = 0;
	u8 Temp_char = 0;

	for(u8 i = 0; i < 100; i++)
	{
		Local_u8Response[i] = 0;
	}

	/*Make sure that the MC is not receiving any more data from the ESP*/
	while (Temp_char != 255)
	{
		Temp_char = MUSART1_u8Receive(Copy_u32timeout);
		Local_u8Response[Counter] = Temp_char;
		Counter++;
	}

	/*	Deleting last element as it is always 255 for stop receiving data	*/
	Local_u8Response[Counter-1] = 0;

	/*Strcmp returns 0 if the two strings are iqentical*/
	//Local_u8ValidFlag = strcmp(Copy_u8StrCmd, Local_u8Response);

	/* Checks if any of the received data contains the word "OK" meaning the command is done successfully*/
	for(u8 i = 0; i < Counter - 2; i ++)
	{
		if(Local_u8Response[i] == 'O' && Local_u8Response[i+1] == 'K')
		{
			Local_u8ValidFlag = 1;
		}
	}
	return Local_u8ValidFlag;
}
