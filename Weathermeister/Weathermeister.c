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
#include "StateFncs.h"
#include "Setup.h"
	
volatile state my_state = WELCOME;	//Declare state variable (volatile, since interrupts may change it)

extern volatile int bu;
extern volatile int bd;
extern volatile int bs;
extern volatile int bf;
volatile int timer1s=0, timer3s=0, timer10s=0, timer180s=0;


int main(void) {
	//int l;
	//	l = Get_Hum();
	
	Setup();
	while(1)
	{
	  	Get_Weather_Data();
		
		timer180s_reset();	//reset timeout to sleep timer after user input
		  
		switch (my_state)
		{
			case WELCOME:                         //welcome msg
				my_state = do_WELCOME();
				break;
			
			case DISP_TEMP:
				my_state = do_DISP_TEMP();
				break;
			
			case DISP_PRESS:
				my_state = do_DISP_PRESS();                   
				break;
			
			case DISP_HUM:                           
				my_state = do_DISP_HUM();
				break;
			
			case DISP_LIGHT:
				my_state = do_DISP_LIGHT();
				break;
			
			case SLEEP:
				my_state = do_SLEEP();             //Sleep mode, state transition in interrupt below
				break;
			
			case DISP_FC:
				my_state = do_DISP_FC();                   //Forecast mode
				break;
			
			case SET_HOUR:                             //set hours
				my_state = do_SET_HOUR();
				break;
			
			case SET_MIN:                             //set minutes
				my_state = do_SET_MIN();
				break;
			
			case SET_DAY:                             //set day
				my_state = do_SET_DAY();
				break;
			
			case SET_MONTH:                            //set month
				my_state = do_SET_MONTH();
				break;
			
			case SET_YEAR:                              //set year
				my_state = do_SET_YEAR();
				break;
			
			case DISP_SETUP_MSG:                       // Display "Time and Date Set"
				my_state = do_DISP_SETUP_MSG();
				break;
			
			default:
				my_state = DISP_TEMP;
				break;
			
		}
		
		
		
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

ISR (TIMER0_OVF_vect)
{
  /* Interrupt Aktion alle
  (8000000/1024)/256 Hz = 30,51 Hz
  bzw.
  1/488,28125 s = 32,768 ms  
  */
  	Debounce();
	  
  	if (timer1s >= 31)	//1s timer ticks after 31 interrupts
	{
		timer1s = 0;
		timer3s++;
		timer10s++;
		timer180s++;
		timer1s_tick();
	}
	if (timer3s >= 3)	//3s timer is depending on 1s timer
	{
		timer3s = 0;
		timer3s_tick();
	}
	if (timer10s >= 10)	//10s timer is depending on 1s timer
	{
		timer10s = 0;
		timer10s_tick();
	}
	if (timer180s >= 180)	//18s timer is depending on 1s timer
	{
		timer180s = 0;
		timer180s_tick();
	}
	timer1s++;
}

void timer1s_tick()
{
	if (my_state == SLEEP)
		ProxyDetect();
}

void timer3s_tick()
{
	
}

void timer10s_tick()
{
	
}

void timer180s_tick()
{
	my_state = SLEEP;
}

void timer180s_reset()
{
	if (bu || bd || bs || bf)
	{
		timer180s = 0;
	}
}