#pragma once

/* Include files */
#include "Lcd_16X2.h"
#include "Alarm.h"
#include "RTC_DS3232.h"
#include "Keys.h"
#include "Tone_Notes.h"


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


/* functions */
int alarm_Time_Set(int);
void A_Sort();
void Repeat_Handle(int);
int Alarm_Time();
void Delete_Alarm(int);
void Day_Increament(int);
int Compare(int, int);
int Time_Compare(Alarm, Alarm);
int Alarm_State();
int Edit_Alarm(int);
int  A_Abort();

void Alarm_setting(int *, int *);
void Alarm_Time_Functionality();
