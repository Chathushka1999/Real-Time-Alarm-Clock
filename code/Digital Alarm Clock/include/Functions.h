#pragma once

#include "Lcd_16X2.h"
#include "RTC_DS3232.h"
#include "Keys.h"
#include <util/delay.h>


int * Time_Set(uint8_t hour, uint8_t min );                                       // update the time(alarm/clock) with buttons
int Date_Set();                                                                 // set and update the date
int  A_Abort();                                                                 // handling the unappropriated returning
int Edit_Alarm(int count);                                                // edit the alarm attributes
void Day_Increament(int count);                                                  // sum one day with given date
int Compare(int a, int b);                                                      
int Time_Compare(struct Alarm A, struct Alarm B);
void A_Sort();
void Repeat_Handle(int posi);
int Alarm_Time();                                                               // check current time is next alarm time or not
void Delete_Alarm(int count);                                                   // deactivate the given index alarm in the alarms array 





char  alarm_names[6][12]={"MORNING", "EVENING", "NIGNT" , "NAP-ALARM", "WORK-ALARM", "NOISY"};       // alarm names
char  alarm_tones[5][12]={"MELODY", "STRANGE", "LOVELY", "ROCK", "POP"};        					// alarm tones names
char  repeat_state[4][12]={"ONCE","DAILY","WEEKLY"};                            					// repeat mode variable names
	
int months[12]={31,29,31,30,31,30,31,31,30,31,30,31};                           			// the days count in months
	

int snooze_time=1;                                                              // snoozing time of the alarm


extern int ha_count;                                                                 // next alarm position

// define alarm struct for alarm attributes handling
struct Alarm{
	int Name;
	int A_Time[2];
	int Date[3];
	int Tone;
	int Repeat_state;
	int Alarm_state;
	
};                                                                                                        

Alarm c_time;                                                        // for storing current time in same format as the alarm
Alarm h_alarm;  													//Alarm class reference for the first alarm






