#pragma once

/* including files */
#include "Lcd_16X2.h"
#include "RTC_DS3232.h"
#include "Keys.h"
#include <util/delay.h>

/* Functions */
int Time_Set();
int Date_Set();
void Date_Time(int *, int *);


