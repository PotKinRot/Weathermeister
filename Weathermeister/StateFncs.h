/*
 * StateFncs.h
 *
 * Created: 20.06.2015 16:07:42
 *  Author: Schewi
 */ 


#ifndef STATEFNCS_H_
#define STATEFNCS_H_
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

typedef struct  
{double temp; long pres;int hum;int lux;
} weather1;


extern state do_WELCOME();
extern state do_DISP_TEMP();
extern state do_DISP_PRESS();
extern state do_DISP_HUM();
extern state do_DISP_LIGHT();
extern state do_SLEEP();
extern state do_DISP_FC();
extern state do_SET_HOUR();
extern state do_SET_MIN();
extern state do_SET_DAY();
extern state do_SET_MONTH();
extern state do_SET_YEAR();
extern state do_DISP_SETUP_MSG();
void Debounce();
void Get_Weather_Data();



#endif /* STATEFNCS_H_ */