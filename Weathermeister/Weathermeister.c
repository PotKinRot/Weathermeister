/*
 * Weathermeister.c
 *
 * Created: 09.06.2015 14:37:49
 *  Author: Schewi
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
#include "LEDM.h"
	
extern volatile state my_state = WELCOME;	//Declare state variable (volatile, since interrupts may change it)
extern volatile int iswelcome;		
extern volatile int bu;
extern volatile int bd;
extern volatile int bs;
extern volatile int bf;
extern volatile int issetup;
extern volatile int isforecast;
extern volatile int howistheweather;


volatile double pressureData[5];	//Data array for pressure storage for forecast
int togglesetup; //Variable to toggle setup Blink
int timerblink; //timer for blinken LED Matrix
int cnt1; //counter for statemachine call

volatile int timer1s=0, timer3s=0, timer5s=0, timer10s=0, timer180s=0;		//Checkvariables for Timer


int main(void)								//Main Loop
{	
	iswelcome = 1;	//Startup, Welcome state
	Setup();		//Calling Setup Routine
	while(1)
	{
	cnt1++;			//Counter for state machine call (once a hundert cycles)

switch (my_state)		//State machine for LED Matrix
	{
		case WELCOME:
		Show_W();
		break;
		
		case DISP_TEMP:
		Show_T();
		break;
		
		case DISP_PRESS:
		Show_P();
		break;
		
		case DISP_LIGHT:
		Show_L();
		break;
		
		case DISP_HUM:
		Show_H();
		break;
		
		case DISP_FC:
		if (howistheweather==0)
		Show_SadFace();
		if (howistheweather==1)
		Show_Smiley();
		break;
		
		
	}
	
	if (issetup == 1 && togglesetup ==1)		//easier solution than creating the same code for every setup state
	Light_All();

	

	
	
	if (cnt1==100)
		{
			
		
		timer180s_reset();	//reset timeout to sleep timer after user input
		  
		switch (my_state)
		{
			case WELCOME:                         //welcome Message
				my_state = do_WELCOME();
				break;
			
			case DISP_TEMP:						//Displaying Temperature
				my_state = do_DISP_TEMP();
				break;
			
			case DISP_PRESS:					//Displaying Pressure
				my_state = do_DISP_PRESS();                   
				break;
			
			case DISP_HUM:						//Displaying Humidity
				my_state = do_DISP_HUM();
				break;
			
			case DISP_LIGHT:					//Displaying Light Intensity
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
				my_state = DISP_TEMP;					//In Case of wrong data => Home Screen
				break;
			
		}
		cnt1=0;
		}
	}
	
	return 0;
}


ISR(INT0_vect)					//External Interrupt for Proximity Sensor
{
	if (my_state == SLEEP)		//error prevention - this must only trigger when we are sleeping
	{
		_delay_us(500);			//wait 500µs - time for the signal to travel ~9cm and back
		if ( !(PIND & (1<<PIND3)) )	//if signal is gone by now, an object is present
		my_state == DISP_TEMP;	//change state
	}
}				

ISR (TIMER0_OVF_vect)
{
  /* Interrupt:
		(8000000/1024)/256 Hz = 30,51 Hz
	
		1/488,28125 s = 32,768 ms  
  */
  	Debounce();
	Get_Weather_Data();	//weather data aquisition
	//clear_display(); //reset display in case of not used numbers on display
	
	if (timerblink >= 15)	//1s timer ticks after 31 interrupts
	{
		timerblink = 0;
		if (togglesetup==0)
		togglesetup=1;
		else
		togglesetup=0;
	}  
	  
	  
	  
  	if (timer1s >= 31)	//1s timer ticks after 31 interrupts
	{
		timer1s = 0;
		timer3s++;
		timer5s++;
		timer10s++;
		timer180s++;
		timer1s_tick();
	}
	if (timer3s >= 3)	//3s timer is depending on 1s timer
	{
		timer3s = 0;
		timer3s_tick();
	}
	if (timer5s >= 5)	//3s timer is depending on 1s timer
	{
		timer5s = 0;
		timer5s_tick();
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
	timerblink++;
}

void timer1s_tick()			//Interrupt after one Second
{
	if (my_state == SLEEP)
		ProxyDetect();
}

void timer3s_tick()			//Interrupt after three Seconds
{
if (iswelcome==1)	
iswelcome=0;
}

void timer5s_tick()			//Interrupt after seven Seconds
{
if (isforecast==1)
isforecast=0;
}

void timer10s_tick()		//Interrupt after ten Seconds
{
 //left shift of pressure data array
 for (int i = 1; i < 5; i++)
 pressureData[i-1] = pressureData[i];		 
 //save new data
 pressureData[4] = bmp085_getpressure();
}

void timer180s_tick()		//Interrupt after 180 Seconds
{
 my_state = SLEEP;		//AUF 180 ÄNDERN!!!!!!!!!!!!!!111111111111111einseinself
}

void timer180s_reset()		//Reset Sleep Counter
{

	if (bu || bd || bs || bf)
	{
		timer180s = 0; //AUF 180 ÄNDERN!!!!!!!!!!!!!!111111111111111einseinself
	}
}