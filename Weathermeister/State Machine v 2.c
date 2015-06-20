/*
 * State_Machine_v_2.c
 *
 * Created: 18-06-2015 23:31:53
 *  Author: Cloud Atlas
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

char day, month, year;                                       
int hour, minute, Day;
double weathertemp;                                           // Main function code declaration
int weatherlight;
int weatherhum ;
double weatherpress;

double GetTemp()
{
	//Temp code
}
double GetPressure()
{
	//Pressure code
}
int GetLight()
{
	//light Intensity code
}
int GetHum()
{
	//Humidity code
}
void bu()
{
	//Button up code
}
void bf()
{ //Button Forecast code
	
}
void bd()
{
	//Button down code
}
void bs()
{
	//Button setup code
}
                                            
									
typedef enum {Welcome,DispTT,DispTP,DispTH,DispTL,Sleep,DispFC,SetH,SetMi,SetD,SetMo,SetY,DispSMsg} state;    //State Machine Definition
state my_state = Welcome;
 
  void SLEEP()                                                      // Sleep State as a function                                              
  {  switch (my_state)
	 { case: Sleep
	    {
			//sleep code
		}
	  if ( //button_pressed || proxy_sensor
	  )
	  { state : Welcome;
	  }
	  else
		  state : Sleep;
	  
	  break;
	 }
  }
  
  void Forecast()                                         // Forecast State as a function   
  {  switch (my_state)
	 { case : DispFC
		 {
			 //Forecast display code
		 }
		 
	  if ( bf()
	  )
	  { 
		  state : DispFC;  //display forecast
	  }
	  else if ( //t5 or bs
	  )
	  {state : DispTT;
	  }
	  break;
 }
 }
 
 void GetWeather()                              // Weather data display as a function   
 {
	 {switch (my_state)
		 {
			 case : Welcome
			 //t5
			 state : DispTT;
			 break;
			 
			 case : DispTT
			 GetTemp();
			 if( bd();                                
			 )
			 {state : DispTP;}
			 break;
			 
			 case : DispTP
			 GetPressure();
			 if( bd();
			 )
			 {state : DispTH;}
			 else if ( bu();
			 )
			 state : DispTT;
			 break;
			 
			 case : DispTH
			 GetHum();
			 if( bd();
			 )
			 {state : DispTL;}
			 else if ( bu();
			 )
			 state : DispTP;
			 break;
			 
			 case : DispTL;
			 GetLight();
			 if( bu();
			 )
			 {state : DispTH;}
			 break;
		 }
	 
 }
			 }
			 
 void SetTime(tdarr)                                            //Time setup as a function   
 {
switch (my_state)
{
	
	
	case SetH                                                        //set hours 
	if(bd() or bu())
	{
		//set Hours
	} 
	else if (bf()) 
	state : SetMi;
	break;
	
	case SetMi                                                           //set Minutes
	if(bd() or bu() )
	{
		//set minutes
	}
	else if (bf())
	state : SetD;
	break;
	
	case SetD                                                             //set day
	if(bd() or bu()) 
	{
		 //set day 
	}
	else if(bf())
	state : SetMo;
	break;
	
	case SetMo                                                         //set Month
	if (bd() or bu())
	{
		//set Month
	}
	bf();
	state : SetY;
	break;
	
	case SetY                                                               //set Year
	 if(bd() or bu() )
	 {
		 //set year
	 }
	 else if(bf())
	state : DispSMsg;
	break;
	
	case  DispSMsg
	{
		//Time and date set
	}
	//t3
	state : DispTT;
	break;
}
}

void GetTime(tdarr)
{
	//Display Date and time
}

 
 
int main(void)                                 //main program
{
    while(1)
    void GetWeather();                        //timeout or no button pressed
	void GetTime(tdarr);                      
     if ( bs()                                  //if bs is pressed
		)
    {  void SetTime(tdarr);
    } 
    else if(  bf()
	)
    {  void DispForecast();                     //if bf is pressed     
    }
    else if ( //t180                                
	)
    {  void SLEEP();
    }
	else 
	{ void GetWeather();
     void GetTime(tdarr);		                       //timeout or no button pressed
	}
	}
	 
	 
