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

typedef enum {	//Define state machine states
	WELCOME,
	DISP_TEMP,
	DISP_PRESS,
	DISP_HUM,
	DISP_LIGHT,
	SLEEP,
	DISP_FC,
	SET_HOUR,
	SET_MIN,
	SET_DAY,
	SET_MONTH,
	SET_YEAR,
	DISP_SETUP_MSG
	} state;
	
volatile state my_state = WELCOME;	//Declare state variable (volatile, since interrupts may change it)


int main(void) {
	int l;
	uint8_t time[6];
	bmp085_init();
	ds1307_init();
	Initialize_LCD();
	l = Get_Hum();
	
	while(1)
	{
		switch (my_state)
		{
			case WELCOME:                         //welcome msg
				//my_state = do_welcome();
				break;
			
			case DISP_TEMP:

				break;
			
			case DISP_PRESS:
				//my_state = DISPTP();                    
				break;
			
			case DISP_HUM:                           
				//my_state = DISPTH();
				break;
			
			case DISP_LIGHT:
				//my_state = DISPTL();
				break;
			
			case SLEEP:
				//my_state = SLEEP();                 //Sleep mode
				break;
			
			case DISP_FC:
				//my_state = DISPFC();                   //Forecast mode
				break;
			
			case SET_HOUR:                             //set hours
				//my_state = SETH();
				break;
			
			case SET_MIN:                             //set minutes
				//my_state = SETMI();
				break;
			
			case SET_DAY:                             //set day
				//my_state = SETD();
				break;
			
			case SET_MONTH:                            //set month
				//my_state = SETMO();
				break;
			
			case SET_YEAR:                              //set year
				//my_state = SETY();
				break;
			
			case DISP_SETUP_MSG:                       // Display "Time and Date Set"
				//my_state = DISPMSG();
				break;
			
			default:
			
				break;
			
		}
		
		
		
		/*ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
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
		Send_Int(l); */
		
	}
	
	return 0;
}

ISR(INT0_vect)	//needs to be in this file b/c it needs access to my_state global var!
{
	if (my_state == SLEEP)		//error prevention - this must only trigger when we are sleeping
	{
		_delay_us(500);			//wait 500µs - time for the signal to travel ~10cm and back
		if ( !(PIND & (1<<PIND3)) )	//if signal is gone by now, an object is present
		my_state == DISP_TEMP;	//change state
	}
}