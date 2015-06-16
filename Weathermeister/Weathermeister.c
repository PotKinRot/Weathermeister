/*
 * Weathermeister.c
 *
 * Created: 09.06.2015 14:37:49
 *  Author: Tilmann
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

#include "bmp085/bmp085.h"

int main(void) {
	long l;
	double d;
	char printbuff[10];
	DDRA=0xff;
	PORTA=0x00;

	//init interrupt
	sei();

	//init bmp085
	bmp085_init();

	//main loop
	for (;;)
	{
		//get temperature
		d = bmp085_gettemperature();
		dtostrf(d, 10, 2, printbuff);
		PORTA= l;

		//get pressure
		l = bmp085_getpressure();
		ltoa(l, printbuff, 10);
		

		//get altitude
		d = bmp085_getaltitude();
		dtostrf(d, 10, 2, printbuff);
		

		_delay_ms(3000);
	}
	
	return 0;
}
