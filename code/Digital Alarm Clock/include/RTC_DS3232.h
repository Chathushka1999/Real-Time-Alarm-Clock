#pragma once


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "stdutils.h"

//#define F_CPU 8000000UL


struct rtc_t{ 
	uint8_t sec;                         //allocating int memory for storing seconds
	uint8_t min;                         //allocating int memory for storing minutes
	uint8_t hour;                        //allocating int memory for storing hours
	uint8_t weekDay;                     //allocating int memory for storing weekday
	uint8_t date;                        //allocating int memory for storing date
	uint8_t month;                       //allocating int memory for storing month
	uint8_t year;                        //allocating int memory for storing year
};

#define Ds3232ReadMode 0xD1u                    // DS3232 ID
#define Ds3232WriteMode 0xD0u                   // DS3232 ID
#define Ds3232SecondRegAddress  0x00u           // Address to access Ds3232 SEC register
#define Ds3232DateRegAddress     0x04u          // Address to access Ds3232 DATE register
#define Ds3232ControlRegAddress  0x07u          // Address to access Ds3232 Control register

                                                                  

uint8_t encode(uint8_t value);
uint8_t	decode(uint8_t value);
void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t v_i2cData_u8);
uint8_t I2C_Read(uint8_t v_ackOption_u8);
void RTC_Initialize(void);
void RTC_Set_Time(rtc_t *rtc);                  				// set the given time to rtc module
void RTC_Get_Time(rtc_t *rtc);                  				// get the current keep track time in rtc



