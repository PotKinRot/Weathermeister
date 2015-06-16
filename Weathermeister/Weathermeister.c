/*
 * Weathermeister.c
 *
 * Created: 09.06.2015 14:37:49
 *  Author: Tilmann
 */ 

# define F_CPU 16000000UL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "bmp085.h"
#include "ds1307.h"
#include "LCD.h"

int main(void) {
	long l;
	double d;
	char printbuff[10];
	uint8_t time[6];
	DDRA=0xff;
	PORTA=0x00;
	
	//init bmp085
	bmp085_init();
	ds1307_init();
	Initialize_LCD();
	
	

	//main loop
	while(1)
	{
	
		Send_String("Test");



		
		
		/*ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
		PORTA=time[5];
*/
		
		
	}
	
	return 0;
}
