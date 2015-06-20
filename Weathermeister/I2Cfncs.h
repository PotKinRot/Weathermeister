/*
 * I2Cfncs.h
 *
 * Created: 19.06.2015 16:26:01
 *  Author: Schewis Laptop
 */ 


#ifndef I2CFNCS_H_
#define I2CFNCS_H_


#ifndef _I2CMASTER_H
#define _I2CMASTER_H   1
#endif


#include <avr/io.h>
#define I2C_READ    1
#define I2C_WRITE   0

#define BMP085_ADDR (0x77<<1) //0x77 default I2C address
#define BMP085_I2CINIT 1 //init i2c

//registers
#define BMP085_REGAC1 0xAA
#define BMP085_REGAC2 0xAC
#define BMP085_REGAC3 0xAE
#define BMP085_REGAC4 0xB0
#define BMP085_REGAC5 0xB2
#define BMP085_REGAC6 0xB4
#define BMP085_REGB1 0xB6
#define BMP085_REGB2 0xB8
#define BMP085_REGMB 0xBA
#define BMP085_REGMC 0xBC
#define BMP085_REGMD 0xBE
#define BMP085_REGCONTROL 0xF4 //control
#define BMP085_REGCONTROLOUTPUT 0xF6 //output 0xF6=MSB, 0xF7=LSB, 0xF8=XLSB
#define BMP085_REGREADTEMPERATURE 0x2E //read temperature
#define BMP085_REGREADPRESSURE 0x34 //read pressure

//modes
#define BMP085_MODEULTRALOWPOWER 0 //oversampling=0, internalsamples=1, maxconvtimepressure=4.5ms, avgcurrent=3uA, RMSnoise_hPA=0.06, RMSnoise_m=0.5
#define BMP085_MODESTANDARD 1 //oversampling=1, internalsamples=2, maxconvtimepressure=7.5ms, avgcurrent=5uA, RMSnoise_hPA=0.05, RMSnoise_m=0.4
#define BMP085_MODEHIGHRES 2 //oversampling=2, internalsamples=4, maxconvtimepressure=13.5ms, avgcurrent=7uA, RMSnoise_hPA=0.04, RMSnoise_m=0.3
#define BMP085_MODEULTRAHIGHRES 3 //oversampling=3, internalsamples=8, maxconvtimepressure=25.5ms, avgcurrent=12uA, RMSnoise_hPA=0.03, RMSnoise_m=0.25

//autoupdate temperature enabled
#define BMP085_AUTOUPDATETEMP 1 //autoupdate temperature every read

//setup parameters
#define BMP085_MODE BMP085_MODEULTRAHIGHRES //define a mode
#define BMP085_UNITPAOFFSET 0 //define a unit offset (pa)
#define BMP085_UNITMOFFSET 0 //define a unit offset (m)

//avarage filter
#define BMP085_FILTERPRESSURE 1 //avarage filter for pressure

#define DS1307_ADDR (0x68<<1) //device address RTC

//variables
int bmp085_regac1, bmp085_regac2, bmp085_regac3, bmp085_regb1, bmp085_regb2, bmp085_regmb, bmp085_regmc, bmp085_regmd;
unsigned int bmp085_regac4, bmp085_regac5, bmp085_regac6;
long bmp085_rawtemperature, bmp085_rawpressure;




//i2C Functions

/**
 @brief initialize the I2C master interace. Need to be called only once 
 @param  void
 @return none
 */
extern void i2c_init(void);
/** 
 @brief Terminates the data transfer and releases the I2C bus 
 @param void
 @return none
 */
extern void i2c_stop(void);
/** 
 @brief Issues a start condition and sends address and transfer direction 
  
 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible 
 @retval   1   failed to access device 
 */
extern unsigned char i2c_start(unsigned char addr);
/**
 @brief Issues a repeated start condition and sends address and transfer direction 

 @param   addr address and transfer direction of I2C device
 @retval  0 device accessible
 @retval  1 failed to access device
 */
extern unsigned char i2c_rep_start(unsigned char addr);
/**
 @brief Issues a start condition and sends address and transfer direction 
   
 If device is busy, use ack polling to wait until device ready 
 @param    addr address and transfer direction of I2C device
 @return   none
 */
extern void i2c_start_wait(unsigned char addr);
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
extern unsigned char i2c_write(unsigned char data);
/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readAck(void);
/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readNak(void);
/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either i2c_readAck or i2c_readNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_read(unsigned char ack);
#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 

//BMP180
extern void bmp085_init();
extern int32_t bmp085_getpressure();
extern double bmp085_getaltitude();
extern double bmp085_gettemperature();


// RTC MODUL
extern void ds1307_init();
extern uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
extern void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);


#endif /* I2CFNCS_H_ */