/*
 * gprsv3.c
 *
 *  Created on: Dec 15, 2016
 *      Author: lexy
 */

#include "Term1.h"
#include "gprsv3.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "Bit1_BLUE.h"
#include "Bit2_GREEN.h"
#include "Bit3_RED.h"

#define apiKey			"ZPJSNZXPVHHNR34U"
//thignspeak channel write api key

/*#define TEMP_FIELD			"field1"
TS field for temp*/

#define SMOKE_FIELD			"field3"
#define SOUND_FIELD			"field4"

void initialize_gprs(void){
	Bit1_BLUE_SetVal();
	Bit2_GREEN_SetVal();
	Bit3_RED_SetVal();
	Term1_SendStr("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");
	WAIT1_Waitms(5000);
	Term1_SendStr("AT+SAPBR=3,1,\"APN\",\"CMNET\"\r\n"); //setting the apn in bearer 1
	WAIT1_Waitms(5000);
	Term1_SendStr("AT+SAPBR=1,1 \r\n");
	WAIT1_Waitms(5000);
	Bit1_BLUE_NegVal();
	Bit2_GREEN_NegVal();
	Bit3_RED_NegVal();
	Term1_SendStr("AT+HTTPINIT \r\n");
	WAIT1_Waitms(5000);
}
void sendtoTS(int smoke, int sound){

/*uint8_t cmd_read[64]; read the reply.*/

/* Below are the data buffers. Theys should be the same as the data size that you want
 * to send otherwise the data will be sent incompletely.
 * Pay attention to the num32string, you need to accont for the 32 characters (coz of 32bits)
 */
uint8_t csound[160];		
uint8_t csmoke[160];		

//create string writing to array csound
//AT+HTTPPARA="URL","api.thingspeak.com/update?key=apiKey&SMOKE_FIELD=90"
UTIL1_strcpy(csmoke, sizeof(csmoke), "AT+HTTPPARA=");
UTIL1_chcat(csmoke, sizeof(csmoke),'\"');
UTIL1_strcat(csmoke, sizeof(csmoke),"URL");
UTIL1_chcat(csmoke, sizeof(csmoke),'\"');
UTIL1_chcat(csmoke, sizeof(csmoke),',');
UTIL1_chcat(csmoke, sizeof(csmoke),'\"');
UTIL1_strcat(csmoke, sizeof(csmoke),"api.thingspeak.com/update?key=");
UTIL1_strcat(csmoke, sizeof(csmoke), apiKey);
UTIL1_chcat(csmoke, sizeof(csmoke), '&');
UTIL1_strcat(csmoke, sizeof(csmoke), SMOKE_FIELD);
UTIL1_chcat(csmoke, sizeof(csmoke), '=');
UTIL1_strcatNum32s(csmoke, sizeof(csmoke), smoke); //copythe value of smoke here.
UTIL1_chcat(csmoke, sizeof(csmoke),'\"');
UTIL1_strcat(csmoke, sizeof(csmoke), "\r\n");

/* Sending smoke to thingspeak*/
Bit1_BLUE_SetVal();
Term1_SendStr(csmoke);
WAIT1_Waitms(7000);
Term1_SendStr("AT+HTTPACTION=0\r\n");
Bit1_BLUE_NegVal();
WAIT1_Waitms(7000);


//create string. writing to array csound.
//AT+HTTPPARA="URL","api.thingspeak.com/update?key=apiKey&SOUND_FIELD=90\r\n
UTIL1_strcpy(csound, sizeof(csound), "AT+HTTPPARA=");
UTIL1_chcat(csound, sizeof(csound),'\"');
UTIL1_strcat(csound, sizeof(csound),"URL");
UTIL1_chcat(csound, sizeof(csound),'\"');
UTIL1_chcat(csound, sizeof(csound),',');
UTIL1_chcat(csound, sizeof(csound),'\"');
UTIL1_strcat(csound, sizeof(csound),"api.thingspeak.com/update?key=");
UTIL1_strcat(csound, sizeof(csound), apiKey);
UTIL1_chcat(csound, sizeof(csound), '&');
UTIL1_strcat(csound, sizeof(csound), SOUND_FIELD);
UTIL1_chcat(csound, sizeof(csound), '=');
UTIL1_strcatNum32s(csound, sizeof(csound), sound); //copythe value of smoke here.
UTIL1_chcat(csound, sizeof(csound),'\"');
UTIL1_strcat(csound, sizeof(csound), "\r\n");

/*sending sound data to thingspeak*/
Bit2_GREEN_SetVal();
Term1_SendStr(csound);
WAIT1_Waitms(7000);
Term1_SendStr("AT+HTTPACTION=0\r\n");
Bit2_GREEN_NegVal();
WAIT1_Waitms(7000);


}

void send_sms(void){
//set module to text mode
char end[2];
end[0]= 0x1a;
end[1]='\0';
Term1_SendStr("AT+CMGF=1\r\n");
Term1_SendStr("AT+CMGS=\"+254710446128\"\r\n");
Term1_SendStr("WARNING!! Smoke detected");
Term1_SendStr(end);
WAIT1_Waitms(3000);
}




