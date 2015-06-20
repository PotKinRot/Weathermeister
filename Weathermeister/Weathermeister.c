/*
 * Weathermeister.c
 *
 * Created: 09.06.2015 14:37:49
 *  Author: Tilmann
 */ 

#define F_CPU 8000000UL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "I2Cfncs.h"
#include "LCD.h"
#include "Lighttemphum.h"


int main(void) {
	int l;
	uint8_t time[6];
	bmp085_init();
	ds1307_init();
	Initialize_LCD();
	l = Get_Hum();
	
	
	
	//main loop
	
	while(1)
	{
		ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
		GotoLCD_Location(1,1);
	
	
		Send_String("Time:");
		Send_Int(time[0]);
		Send_String(" ");
		Send_Int(time[1]);
		Send_String(" ");
		Send_Int(time[2]);
		GotoLCD_Location(1,2);
		Send_Int(time[3]);
		Send_String(" ");
		Send_Int(time[4]);
		Send_String(" ");
		Send_Int(time[5]);
		Send_String(" ");
		Send_Int(l);
		
	}
	
	return 0;
}
