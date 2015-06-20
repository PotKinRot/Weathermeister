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
volatile int bu;
volatile int bd;
volatile int bs;
volatile int bf;
int cnt = 0;
volatile weather1 weather;
volatile int issetup =0;

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
		
		
		Send_Int(time[2]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[0]);
		
		GotoLCD_Location(1,2);
		Send_String("Temp.:");
		Send_Double(weather.temp,2,1);
		Send_String("C");
		
		if(my_state != DISP_TEMP)	//if any interrupt has changed the destination state, shut up.
			return my_state;
			

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
		
		if (bs==1)
		{
			clear_display();
			bs=0;
			issetup=1;
			return SET_HOUR;
		}		
		
		if (bf==1)
		{
			clear_display();
			bf=0;
			return DISP_FC;
		}
		

			return DISP_TEMP;

	
		
		
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
		
		
		Send_Int(time[2]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[0]);
		
		GotoLCD_Location(1,2);
		Send_String("Pressure:");	
		Send_Int(weather.pres);
		Send_String("bar");	
		
		if(my_state != DISP_PRESS)	//if any interrupt has changed the destination state, shut up.
			return my_state;
		

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
			
		if (bs==1)
		{
			clear_display();
			issetup=1;
			bs=0;
			return SET_HOUR;
		}
		if (bf==1)
		{
			clear_display();
			bf=0;
			return DISP_FC;
		}		

			return DISP_PRESS;
	

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
		
		
		Send_Int(time[2]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[0]);
		
		GotoLCD_Location(1,2);
		Send_String("Humidity:");	
		Send_Int(weather.hum);
		Send_String("%");
		
		if(my_state != DISP_HUM)	//if any interrupt has changed the destination state, shut up.
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
		if (bs==1)
		{
			clear_display();
			issetup=1;
			bs=0;
			return SET_HOUR;
		}
		if (bf==1)
		{
			clear_display();
			bf=0;
			return DISP_FC;
		}		
		
			return DISP_HUM;
		
		
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
		
		
		Send_Int(time[2]);
		Send_String(".");
		Send_Int(time[1]);
		Send_String(".");
		Send_Int(time[0]);
		
		GotoLCD_Location(1,2);
		Send_String("Light:");	
		Send_Int(weather.lux);
		
		if(my_state != DISP_LIGHT)	//if any interrupt has changed the destination state, shut up.
			return my_state;		
		

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
		if (bs==1)
		{
			clear_display();
			bs=0;
			return SET_HOUR;
		}
		if (bf==1)
		{
			clear_display();
			issetup=1;
			bf=0;
			return DISP_FC;
		}		
		

		

			return DISP_LIGHT;	
}
	
state do_SLEEP()
{
	clear_display();
	
	if (bd || bu || bf || bs)
		{bd=0;
		bu=0;
		bs=0;
		bf=0;
		return DISP_TEMP;}
	else
		return SLEEP;
}

state do_DISP_FC()
{
	return DISP_FC;
}
	
state do_SET_HOUR()
{
		GotoLCD_Location(1,1);
		Send_String("Set Hour:");
		GotoLCD_Location(1,2);
		Send_Int(time[3]);
		
		
		if (bu==1)
		{
			clear_display();
			bu=0;
			if (time[3]<=22)
			time[3]++;
			else time[3]=0;
		}
		if (bd==1)
		{
			bd=0;
			clear_display();
			if (time[3]>=1)
			time[3]--;
			else time[3]=23;
		}
		

		if (bs==1)
		{
			clear_display();
			bs=0;
			issetup=0;
			return DISP_TEMP;
		}
		if (bf==1)
		{
			clear_display();
			bf=0;
			return SET_MIN;
		}
		
	return SET_HOUR;
}
	
state do_SET_MIN()
{
	GotoLCD_Location(1,1);
	Send_String("Set Minute:");
	GotoLCD_Location(1,2);
	Send_Int(time[4]);
	
	
		if (bu==1)
		{
			clear_display();
			bu=0;
			if (time[4]<=58)
			time[4]++;
			else time[4]=0;
		}
		if (bd==1)
		{
			bd=0;
			clear_display();
			if (time[4]>=1)
			time[4]--;
			else time[4]=59;
		}
		

	if (bs==1)
	{
		clear_display();
		bs=0;
		issetup=0;
		return DISP_TEMP;
	}
	if (bf==1)
	{
		clear_display();
		bf=0;
		return SET_DAY;
	}
		
	return SET_MIN;
}
	
state do_SET_DAY()
{
	GotoLCD_Location(1,1);
	Send_String("Set Day:");
	GotoLCD_Location(1,2);
	Send_Int(time[2]);
	
	
	if (bu==1)
	{
		clear_display();
		bu=0;
		if (time[2]<=30)
		time[2]++;
		else time[2]=1;
	}
	if (bd==1)
	{
		bd=0;
		clear_display();
		if (time[2]>=2)
		time[2]--;
		else time[2]=31;
	}
	

	if (bs==1)
	{
		clear_display();
		bs=0;
		issetup=0;
		return DISP_TEMP;
	}
	if (bf==1)
	{
		clear_display();
		bf=0;
		return SET_MONTH;
	}
		
	return SET_DAY;
}
	
state do_SET_MONTH()
{
	GotoLCD_Location(1,1);
	Send_String("Set Month:");
	GotoLCD_Location(1,2);
	Send_Int(time[1]);
	
	
	if (bu==1)
	{
		clear_display();
		bu=0;
		if (time[1]<=11)
		time[1]++;
		else time[1]=1;
	}
	if (bd==1)
	{
		bd=0;
		clear_display();
		if (time[1]>=2)
		time[1]--;
		else time[1]=12;
	}
	

	if (bs==1)
	{
		clear_display();
		bs=0;
		issetup=0;
		return DISP_TEMP;
	}
	if (bf==1)
	{
		clear_display();
		bf=0;
		return SET_YEAR;
	}	
	return SET_MONTH;
}
	
state do_SET_YEAR()
{
	GotoLCD_Location(1,1);
	Send_String("Set Year:");
	GotoLCD_Location(1,2);
	Send_Int(time[0]);
	
	
	if (bu==1)
	{
		clear_display();
		bu=0;
		if (time[0]<=99)
		time[0]++;
		else time[0]=14;
	}
	if (bd==1)
	{
		bd=0;
		clear_display();
		if (time[0]>=15)
		time[0]--;
		else time[0]=99;
	}
	

	if (bs==1)
	{
		clear_display();
		bs=0;
		issetup=0;
		return DISP_TEMP;
	}
	if (bf==1)
	{
		clear_display();
		bf=0;
		return DISP_SETUP_MSG;
	}	
	return SET_YEAR;
}
	
state do_DISP_SETUP_MSG()
{
	
	ds1307_setdate(time[0],time[1],time[2],time[3],time[4],0);
	_delay_ms(3000);
	issetup=0;
	return DISP_TEMP;
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
	if (issetup==0)
	ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
	
	weather.temp = bmp085_gettemperature();
	weather.pres = bmp085_getpressure();
	weather.hum = Get_Hum();
	
}

	
	