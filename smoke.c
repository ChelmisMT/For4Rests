/*
 * smoke.c
 *
 *  Created on: Dec 15, 2016
 *      Author: chelmis
 */

#include "smoke.h"
#include "ADC0.h"
#include "WAIT1.h"

//variables
static uint16_t smvalue;
float smvalue2, smval;
/*float smconvert()	{
	smvalue2= smvalue/65535;
	return smvalue2;
}*/

int GetSmoke() {
	ADC0_MeasureChan(TRUE,1);
	ADC0_GetChanValue16(1, &smvalue);
/*====================================================================================
    The commented out section below is to display the values from the sensor on a terminal
	/*Term1_SendNum(smvalue);
	if (smvalue>30000)	{
		Term1_SendStr("Smoke_sensor: High");
	}
	else	{
		Term1_SendStr("Smoke_sensor: Safe");
	}
		Term1_SendStr("\r\n");
		WAIT1_Waitms(1000);
 ==================================================================================*/
	return smvalue;
   }



