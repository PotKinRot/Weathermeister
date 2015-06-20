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
#include "Proximity.h"
#include "I2Cfncs.h"

uint8_t time[6];
uint8_t timeset[6];
volatile int bu;
volatile int bd;
volatile int bs;
volatile int bf;
int cnt = 0;
volatile weather1 weather;

extern volatile state my_state;


state do_WELCOME()
{
	GotoLCD_Location(1,1);
	Send_String("Welcome to the");
	GotoLCD_Location(1,2);
	Send_String("Weathermeister");
	_delay_ms(3000*2);
	clear_display();
	return DISP_TEMP;
	//Transition: Timer = 3Secs;
	
}


state do_DISP_TEMP()
{
	
		GotoLCD_Location(1,1);
		if (time[3]<=9)
		{
			Send_String("0");
			Send_Int(time[3]);
		}
		else
		{
			Send_Int(time[3]);
		}
		Send_String(":");
		if (time[4]<=9)
		{
			Send_String("0");
			Send_Int(time[4]);
		}
		else
		{
			Send_Int(time[4]);
		}
		Send_String("  ");
		
		
		Send_Int(time[0]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[2]);
		
		GotoLCD_Location(1,2);
		Send_String("Temp.:");
		Send_Double(weather.temp,2,1);
		Send_String("C");
		
		if(my_state != DISP_TEMP)	//if any interrupt has changed the destination state, shut up.
			return my_state;
			
		if (bu==0 && bd == 0)
		{
			return DISP_TEMP;	
		}
		if (bd==1)
		{
			clear_display();
			bd=0;
			return DISP_HUM;
		}
		if (bu==1)
		{
			clear_display();
			bu=0;
			return DISP_LIGHT;
		}
		}
	
state do_DISP_PRESS()
{
	
		GotoLCD_Location(1,1);
		if (time[3]<=9)
		{
			Send_String("0");
			Send_Int(time[3]);
		}
		else
		{
			Send_Int(time[3]);
		}
		Send_String(":");
		if (time[4]<=9)
		{
			Send_String("0");
			Send_Int(time[4]);
		}
		else
		{
			Send_Int(time[4]);
		}
		Send_String("  ");
		
		
		Send_Int(time[0]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[2]);
		
		GotoLCD_Location(1,2);
		Send_String("Pressure:");	
		Send_Int(weather.pres);
		Send_String("bar");	
		
		if(my_state != DISP_TEMP)	//if any interrupt has changed the destination state, shut up.
			return my_state;
		
		if (bu==0 && bd == 0)
		{
			return DISP_PRESS;
		}
		if (bu==1)
		{
			clear_display();
			bu=0;
			return DISP_HUM;
		}
		if (bd==1)
		{
			clear_display();
			bd=0;
			return DISP_LIGHT;
		}		

}
	
state do_DISP_HUM()
{
			GotoLCD_Location(1,1);
		if (time[3]<=9)
		{
			Send_String("0");
			Send_Int(time[3]);
		}
		else
		{
			Send_Int(time[3]);
		}
		Send_String(":");
		if (time[4]<=9)
		{
			Send_String("0");
			Send_Int(time[4]);
		}
		else
		{
			Send_Int(time[4]);
		}
		Send_String("  ");
		
		
		Send_Int(time[0]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[2]);
		
		GotoLCD_Location(1,2);
		Send_String("Humidity:");	
		Send_Int(weather.hum);
		Send_String("%");
		
		if(my_state != DISP_TEMP)	//if any interrupt has changed the destination state, shut up.
			return my_state;	
			
		if (bu==0 && bd == 0)
		{
			return DISP_HUM;
		}
		if (bu==1)
		{
			clear_display();
			bu=0;
			return DISP_TEMP;
		}
		if (bd==1)
		{
			clear_display();
			bd=0;
			return DISP_PRESS;
		}		
}
	
state do_DISP_LIGHT()
{
			GotoLCD_Location(1,1);
		if (time[3]<=9)
		{
			Send_String("0");
			Send_Int(time[3]);
		}
		else
		{
			Send_Int(time[3]);
		}
		Send_String(":");
		if (time[4]<=9)
		{
			Send_String("0");
			Send_Int(time[4]);
		}
		else
		{
			Send_Int(time[4]);
		}
		Send_String("  ");
		
		
		Send_Int(time[0]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[2]);
		
		GotoLCD_Location(1,2);
		Send_String("Light:");	
		Send_Int(weather.lux);
		
		if(my_state != DISP_TEMP)	//if any interrupt has changed the destination state, shut up.
			return my_state;		
		
		if (bu==0 && bd == 0)
		{
			return DISP_LIGHT;
		}
		if (bu==1)
		{
			clear_display();
			bu=0;
			return DISP_PRESS;
		}
		if (bd==1)
		{
			bd=0;
			clear_display();
			return DISP_TEMP;
		}	
}
	
state do_SLEEP()
{
	if (bd || bu || bf || bs)
		return DISP_TEMP;
	else
		return SLEEP;
	//ProxyDetect();
}

state do_DISP_FC()
{
	return DISP_FC;
}
	
state do_SET_HOUR()
{
//	timeset = time;
	return SET_HOUR;
}
	
state do_SET_MIN()
{
	return SET_MIN;
}
	
state do_SET_DAY()
{
	return SET_DAY;
}
	
state do_SET_MONTH()
{
	return SET_MONTH;
}
	
state do_SET_YEAR()
{
	return SET_YEAR;
}
	
state do_DISP_SETUP_MSG()
{
	return DISP_SETUP_MSG;
}


void Debounce()
{
	cnt++;
	if (cnt==5)
	{
	if ( PINC & (1<<PINC7) ) {bu = 0;}
	else {bu=1;}
	if ( PINC & (1<<PINC6) ) {bd = 0;}
	else {bd=1;}
	if ( PINC & (1<<PINC5) ) {bs = 0;}
	else {bs=1;}
	if ( PINC & (1<<PINC4) ) {bf = 0;}
	else {bf=1;}
		cnt=0;
	}
	
}

void Get_Weather_Data()
{
	ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
	weather.temp = bmp085_gettemperature();
	weather.pres = bmp085_getpressure();
	weather.hum = Get_Hum();
	
}

	
	