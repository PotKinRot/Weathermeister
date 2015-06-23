/*
 * StateFncs.c

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
#include "LEDM.h"


uint8_t time[6];
volatile int bu;
volatile int bd;
volatile int bs;
volatile int bf;
int cnt = 0;
volatile weather1 weather; //BEHINDERTE DRECKSKACKESCHEISSE
volatile int issetup =0;
extern double pressureData[5];
extern volatile state my_state;


/* 
Description: State of Welcome message 
State from Diagram: S01
*/
state do_WELCOME()
{
	GotoLCD_Location(1,1);
	Send_String("Welcome to the");
	GotoLCD_Location(1,2);
	Send_String("Weathermeister");
	_delay_ms(3000*2);
	clear_display();
	return DISP_TEMP;

	
}


/*
Description: Home state, displaying date, time and temperature
State from Diagram: S02
*/
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
		Send_String("Temp.: ");
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


/*
Description: Pressure state, displaying date, time and pressure
State from Diagram: S03
*/	
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
		Send_String("Pres: ");	
		Send_Double(weather.pres,2,4);
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


/*
Description: Humidity state, displaying date, time and humidity
State from Diagram: S04
*/	
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
		Send_String("Humidity: ");	
		Send_Int(weather.hum);
		Send_String("%");
		
		if(my_state != DISP_HUM)	//if any interrupt has changed the destination state, shut up.
			return my_state;	
			
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


/*
Description: Light state, displaying date, time and light
State from Diagram: S05
*/	
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
	
	
/*
Description: Sleep state, Display off, backlight off, prox activation and button activation
State from Diagram: S06
*/	
state do_SLEEP()
{
	clear_display();
	
	if (bd || bu || bf || bs)
		{bd=0;
		bu=0;
		bs=0;
		bf=0;
		return WELCOME;}
	else
		return SLEEP;
}


/*
Description: Forecast state + Calculation of forecast
State from Diagram: S07
*/
state do_DISP_FC()
{
	int averagePressure = 0;
	
	for (int i=0; i<5; i++)
	averagePressure += pressureData[i];
	
	averagePressure /= 5; //TODO: should all this be floats?ich		
	
	if (pressureData[3] > averagePressure && pressureData[4] > averagePressure)
	{
		GotoLCD_Location(1,1);
		Send_String("Forecast: Good");
		GotoLCD_Location(1,2);
		Send_String("Weather Expected");
	}
	else
	{
		GotoLCD_Location(1,1);
		Send_String("Forecast: Bad");
		GotoLCD_Location(1,2);
		Send_String("Weather Expected");
	}
	
	_delay_ms(10000);
	_delay_ms(10000);
	clear_display();
	return DISP_TEMP;
}	


/*
Description: First Setup state, Adjusting hour
State from Diagram: S08
*/
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


/*
Description: Setup state, Adjusting minute
State from Diagram: S09
*/	
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


/*
Description: Setup state, Adjusting Day
State from Diagram: S10
*/	
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


/*
Description: Setup state, Adjusting Month
State from Diagram: S11
*/	
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


/*
Description: Setup state, Adjusting Year
State from Diagram: S12
*/	
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


/*
Description: End of Setup, Store changed data to RTC and display end message
State from Diagram: S13
*/	
state do_DISP_SETUP_MSG()
{
	GotoLCD_Location(1,1);
	Send_String("Time&Date Set!");
	ds1307_setdate(time[0],time[1],time[2],time[3],time[4],0);
	_delay_ms(10000);
	clear_display();
	issetup=0;
	return DISP_TEMP;
}


/*
Button debounce Routine

*/
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


/*
Summarization of all Sensor Readouts + RTC
*/
void Get_Weather_Data()
{
if (issetup==0)
	ds1307_getdate(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);			
	if (my_state == DISP_TEMP) weather.temp = bmp085_gettemperature()-2.4;			//Calibration	
	if (my_state == DISP_PRESS)														//problem with i2c Communication, if temperature and pressure are readout after each other => bljad
	{
		weather.pres = bmp085_getpressure();
		weather.pres = (weather.pres/100000)+0.16;									//Calibration
	}
	weather.hum = Get_Hum();
	
}

state proxyDistance()
{


	//Wait for raising edge on Echo Input
	while(1)
	{
		
		PINC |= (1 << PINC3);  //TODO: Correct pin?
		//Stay high for at least 10us
		_delay_us(150);
		//Disable output again
		PINC &= (1 << PINC3);  //TODO: Correct pin?		
		if( PIND & (1 << PIND2)) //TODO: Correct pin?
		break;
		_delay_us(500);
	}
	//wait for 500us
	_delay_us(500); //sound travels 340m/s, so 500us=17cm=8,5cm object-sensor
	if( !(PIND & (1 << PIND2)) ) //TODO: Correct pin?
	return WELCOME;
	else
	return SLEEP;
	
}	