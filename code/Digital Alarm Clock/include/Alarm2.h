#pragma once

/* Include files */
#include "Lcd_16X2.h"
#include "Alarm.h"
#include "RTC_DS3232.h"
#include "Keys.h"
#include "Tone_Notes.h"

/* variables */
//keep the track of number of true alarms
int alarm_t=0;
//snooze time
int snooze_time = 1;
//index reference for the first alarm
int ha_count=0;


//alarm parameters
char alarm_names[6][12] = {"MORNING", "EVENING", "NIGNT", "NAP-ALARM", "WORK-ALARM", "NOISY"};
char alarm_tones[5][12] = {"MELODY", "STRANGE", "LOVELY", "ROCK", "POP"};
char repeat_state[4][12] = {"ONCE", "DAILY", "WEEKLY"};

// define alarm struct for alarm attributes handling
struct Alarm
{
    int Name;
    int A_Time[2];
    int Date[3];
    int Tone;
    int Repeat_state;
    int Alarm_state;
};
//getting reference time from rtc
rtc_t a_rtc;

//keeping track of current time in alarm format
Alarm c_time;
//reference for the first alarm
Alarm h_alarm;
//Creating Alarm class for Handling six alarms
Alarm alarms[6];

/* functions */
int alarm_Time_Set(int);
void A_Sort();
void Repeat_Handle(int);
int Alarm_Time();
void Delete_Alarm(int);
void Day_Increament(int);
int Compare(int, int);
int Time_Compare(Alarm, Alarm);
int Edit_Alarm(int);
int  A_Abort();

void Alarm_setting(int *, int *);
void Alarm_Time_Functionality();
