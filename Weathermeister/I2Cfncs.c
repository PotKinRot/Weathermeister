/*
 * I2Cfncs.c
 *
 * Created: 19.06.2015 16:25:46
 *  Author: Schewis Laptop
 */ 


#include <inttypes.h>
#include <compat/twi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include "I2Cfncs.h"
#include "avr/pgmspace.h"




/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  10000L


/*
 * days per month
 */
const uint8_t ds1307_daysinmonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };


/*************************************************************************
 Initialization of the I2C bus interface. Need to be called only once
*************************************************************************/
void i2c_init(void)
{
  /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
  
  TWSR = 0;                         /* no prescaler */
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */

}/* i2c_init */


/*************************************************************************	
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
*************************************************************************/
unsigned char i2c_start(unsigned char address)
{
    uint8_t   twst;

	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

	// send device address
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;

}/* i2c_start */


/*************************************************************************
 Issues a start condition and sends address and transfer direction.
 If device is busy, use ack polling to wait until device is ready
 
 Input:   address and transfer direction of I2C device
*************************************************************************/


void i2c_start_wait(unsigned char address)
{
    uint8_t   twst;


    while ( 1 )
    {
	    // send START condition
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    
    	// wait until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
    
    	// send device address
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    
    	// wail until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) ) 
    	{    	    
    	    /* device busy, send stop condition to terminate write operation */
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        
	        // wait until stop condition is executed and bus released
	        while(TWCR & (1<<TWSTO));
	        
    	    continue;
    	}
    	//if( twst != TW_MT_SLA_ACK) return 1;
    	break;
     }

}/* i2c_start_wait */


/*************************************************************************
 Issues a repeated start condition and sends address and transfer direction 

 Input:   address and transfer direction of I2C device
 
 Return:  0 device accessible
          1 failed to access device
*************************************************************************/
unsigned char i2c_rep_start(unsigned char address)
{
    return i2c_start( address );

}/* i2c_rep_start */


/*************************************************************************
 Terminates the data transfer and releases the I2C bus
*************************************************************************/
void i2c_stop(void)
{
    /* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));

}/* i2c_stop */


/*************************************************************************
  Send one byte to I2C device
  
  Input:    byte to be transfered
  Return:   0 write successful 
            1 write failed
*************************************************************************/
unsigned char i2c_write( unsigned char data )
{	
    uint8_t   twst;
    
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;

}/* i2c_write */


/*************************************************************************
 Read one byte from the I2C device, request more data from device 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;

}/* i2c_readAck */


/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;

}/* i2c_readNak */


/*
 * BMP180 COMMUNICATION
 */


void bmp085_writemem(uint8_t reg, uint8_t value) {
	i2c_start_wait(BMP085_ADDR | I2C_WRITE);
	i2c_write(reg);
	i2c_write(value);
	i2c_stop();
}

/*
 * i2c read
 */
void bmp085_readmem(uint8_t reg, uint8_t buff[], uint8_t bytes) {
	uint8_t i =0;
	i2c_start_wait(BMP085_ADDR | I2C_WRITE);
	i2c_write(reg);
	i2c_rep_start(BMP085_ADDR | I2C_READ);
	for(i=0; i<bytes; i++) {
		if(i==bytes-1)
			buff[i] = i2c_readNak();
		else
			buff[i] = i2c_readAck();
	}
	i2c_stop();
}


#if BMP085_FILTERPRESSURE == 1
#define BMP085_AVARAGECOEF 21
static long k[BMP085_AVARAGECOEF];
long bmp085_avaragefilter(long input) {
	uint8_t i=0;
	long sum=0;
	for (i=0; i<BMP085_AVARAGECOEF; i++) {
		k[i] = k[i+1];
	}
	k[BMP085_AVARAGECOEF-1] = input;
	for (i=0; i<BMP085_AVARAGECOEF; i++) {
		sum += k[i];
	}
	return (sum /BMP085_AVARAGECOEF) ;
}
#endif

/*
 * read calibration registers
 */
void bmp085_getcalibration() {
	uint8_t buff[2];
	memset(buff, 0, sizeof(buff));

	bmp085_readmem(BMP085_REGAC1, buff, 2);
	bmp085_regac1 = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGAC2, buff, 2);
	bmp085_regac2 = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGAC3, buff, 2);
	bmp085_regac3 = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGAC4, buff, 2);
	bmp085_regac4 = ((unsigned int)buff[0] <<8 | ((unsigned int)buff[1]));
	bmp085_readmem(BMP085_REGAC5, buff, 2);
	bmp085_regac5 = ((unsigned int)buff[0] <<8 | ((unsigned int)buff[1]));
	bmp085_readmem(BMP085_REGAC6, buff, 2);
	bmp085_regac6 = ((unsigned int)buff[0] <<8 | ((unsigned int)buff[1]));
	bmp085_readmem(BMP085_REGB1, buff, 2);
	bmp085_regb1 = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGB2, buff, 2);
	bmp085_regb2 = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGMB, buff, 2);
	bmp085_regmb = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGMC, buff, 2);
	bmp085_regmc = ((int)buff[0] <<8 | ((int)buff[1]));
	bmp085_readmem(BMP085_REGMD, buff, 2);
	bmp085_regmd = ((int)buff[0] <<8 | ((int)buff[1]));
}

/*
 * get raw temperature as read by registers, and do some calculation to convert it
 */
void bmp085_getrawtemperature() {
	uint8_t buff[2];
	memset(buff, 0, sizeof(buff));
	long ut,x1,x2;

	//read raw temperature
	bmp085_writemem(BMP085_REGCONTROL, BMP085_REGREADTEMPERATURE);
	_delay_ms(5); // min. 4.5ms read Temp delay
	bmp085_readmem(BMP085_REGCONTROLOUTPUT, buff, 2);
	ut = ((long)buff[0] << 8 | ((long)buff[1])); //uncompensated temperature value

	//calculate raw temperature
	x1 = ((long)ut - bmp085_regac6) * bmp085_regac5 >> 15;
	x2 = ((long)bmp085_regmc << 11) / (x1 + bmp085_regmd);
	bmp085_rawtemperature = x1 + x2;
}

/*
 * get raw pressure as read by registers, and do some calculation to convert it
 */
void bmp085_getrawpressure() {
	uint8_t buff[3];
	memset(buff, 0, sizeof(buff));
	long up,x1,x2,x3,b3,b6,p;
	unsigned long b4,b7;

	#if BMP085_AUTOUPDATETEMP == 1
	bmp085_getrawtemperature();
	#endif

	//read raw pressure
	bmp085_writemem(BMP085_REGCONTROL, BMP085_REGREADPRESSURE+(BMP085_MODE << 6));
	_delay_ms(2 + (3<<BMP085_MODE));
	bmp085_readmem(BMP085_REGCONTROLOUTPUT, buff, 3);
	up = ((((long)buff[0] <<16) | ((long)buff[1] <<8) | ((long)buff[2])) >> (8-BMP085_MODE)); // uncompensated pressure value

	//calculate raw pressure
	b6 = bmp085_rawtemperature - 4000;
	x1 = (bmp085_regb2* (b6 * b6) >> 12) >> 11;
	x2 = (bmp085_regac2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((long)bmp085_regac1) * 4 + x3) << BMP085_MODE) + 2) >> 2;
	x1 = (bmp085_regac3 * b6) >> 13;
	x2 = (bmp085_regb1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (bmp085_regac4 * (uint32_t)(x3 + 32768)) >> 15;
	b7 = ((uint32_t)up - b3) * (50000 >> BMP085_MODE);
	p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	bmp085_rawpressure = p + ((x1 + x2 + 3791) >> 4);

	#if BMP085_FILTERPRESSURE == 1
	bmp085_rawpressure = bmp085_avaragefilter(bmp085_rawpressure);
	#endif
}

/*
 * get celsius temperature
 */
double bmp085_gettemperature() {
	bmp085_getrawtemperature();
	double temperature = ((bmp085_rawtemperature + 8)>>4);
	temperature = temperature /10;
	return temperature;
}

/*
 * get pressure
 */
int32_t bmp085_getpressure() {
	bmp085_getrawpressure();
	return bmp085_rawpressure + BMP085_UNITPAOFFSET;
}

/*
 * get altitude
 */
double bmp085_getaltitude() {
	bmp085_getrawpressure();
	return ((1 - pow(bmp085_rawpressure/(double)101325, 0.1903 )) / 0.0000225577) + BMP085_UNITMOFFSET;
}

/*
 * init bmp085
 */
void bmp085_init() {
	#if BMP085_I2CINIT == 1
	//init i2c
	i2c_init();
	_delay_us(10);
	#endif

	bmp085_getcalibration(); //get calibration data
	bmp085_getrawtemperature(); //update raw temperature, at least the first time

	#if BMP085_FILTERPRESSURE == 1
	//initialize the avarage filter
	uint8_t i=0;
	for (i=0; i<BMP085_AVARAGECOEF; i++) {
		bmp085_getrawpressure();
	}
	#endif
}


// RTC Fncs


/*
 * initialize the accellerometer
 */
void ds1307_init() {
	#if DS1307_I2CINIT == 1
	//init i2c
	i2c_init();
	_delay_us(10);
	#endif
}

/*
 * transform decimal value to bcd
 */
uint8_t ds1307_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}

/*
 * transform bcd value to deciaml
 */
static uint8_t ds1307_bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

/*
 * get number of days since 2000/01/01 (valid for 2001..2099)
 */
static uint16_t ds1307_date2days(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t days = d;
	for (uint8_t i = 1; i < m; ++i)
		days += pgm_read_byte(ds1307_daysinmonth + i - 1);
	if (m > 2 && y % 4 == 0)
		++days;
	return days + 365 * y + (y + 3) / 4 - 1;
}

/*
 * get day of a week
 */
uint8_t ds1307_getdayofweek(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t day = ds1307_date2days(y, m, d);
	return (day + 6) % 7;
}

/*
 * set date
 */
uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
	//sanitize data
	if (second < 0 || second > 59 ||
		minute < 0 || minute > 59 ||
		hour < 0 || hour > 23 ||
		day < 1 || day > 31 ||
		month < 1 || month > 12 ||
		year < 0 || year > 99)
		return 8;

	//sanitize day based on month
	if(day > pgm_read_byte(ds1307_daysinmonth + month - 1))
		return 0;

	//get day of week
	uint8_t dayofweek = ds1307_getdayofweek(year, month, day);

	//write date
	i2c_start_wait(DS1307_ADDR | I2C_WRITE);
	i2c_write(0x00);//stop oscillator
	i2c_write(ds1307_dec2bcd(second));
	i2c_write(ds1307_dec2bcd(minute));
	i2c_write(ds1307_dec2bcd(hour));
	i2c_write(ds1307_dec2bcd(dayofweek));
	i2c_write(ds1307_dec2bcd(day));
	i2c_write(ds1307_dec2bcd(month));
	i2c_write(ds1307_dec2bcd(year));
	i2c_write(0x00); //start oscillator
	i2c_stop();

	return 1;
}

/*
 * get date
 */
void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second) {
	i2c_start_wait(DS1307_ADDR | I2C_WRITE);
	i2c_write(0x00);//stop oscillator
	i2c_stop();

	i2c_rep_start(DS1307_ADDR | I2C_READ);
	*second = ds1307_bcd2dec(i2c_readAck() & 0x7F);
	*minute = ds1307_bcd2dec(i2c_readAck());
	*hour = ds1307_bcd2dec(i2c_readAck());
	i2c_readAck();
	*day = ds1307_bcd2dec(i2c_readAck());
	*month = ds1307_bcd2dec(i2c_readAck());
	*year = ds1307_bcd2dec(i2c_readNak());
	i2c_stop();
}


