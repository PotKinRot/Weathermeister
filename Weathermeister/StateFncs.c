/*
 * StateFncs.c
 *
 * Created: 20.06.2015 16:07:24
 *  Author: Schewi
 */ 

#include "StateFncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

uint8_t time[6];


state do_WELCOME()
{
	GotoLCD_Location(1,1);
	Send_String("Welcome to the");
	GotoLCD_Location(1,2);
	Send_String("Weathermeister");
	_delay_ms(3000*8);
	clear_display();
	return DISP_TEMP;
	//Transition: Timer = 3Secs;
	
}


state do_DISP_TEMP()
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
	//	Send_Int(l);
	
	
	return DISP_TEMP;}
	
state do_DISP_PRESS()
{}
	
state do_DISP_HUM()
{}
	
state do_DISP_LIGHT()
{}
	
state do_SLEEP()
{}

state do_DISP_FC()
{}
	
state do_SET_HOUR()
{}
	
state do_SET_MIN()
{}
	
state do_SET_DAY()
{}
	
state do_SET_MONTH()
{}
	
state do_SET_YEAR()
{}
	
state do_DISP_SETUP_MSG()
{}
	