/*
 * sound.c
 *
 *  Created on: Dec 15, 2016
 *      Author: chelmis
 */
#include "sound.h"
#include "ADC1.h"
#include "WAIT1.h"
#include "Term1.h"
//variables
static uint16_t svalue;
float svalue2, sval;

int GetSound() {
	ADC1_Measure(TRUE);
	ADC1_GetValue16(&svalue);
/*====================================================================================
    The commented out section below is to display the values from the sensor on a terminal
	//Term1_SendStr("sValue1: ");
	//Term1_SendNum(svalue);

	/*if (svalue>12910)	{
		Term1_SendStr("Sound_sensor: Loud");
	}
	else	{
		Term1_SendStr("Sound_sensor: Safe");
	}

	Term1_SendStr("\r\n");
	WAIT1_Waitms(1000);
==================================================================================*/
return svalue;
   }

