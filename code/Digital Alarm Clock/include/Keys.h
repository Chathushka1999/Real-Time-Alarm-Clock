#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd_16X2.h"


#define RETURN_PIN 6                           //#define KEYS_PIN PINB
#define SELECT_PIN 5
#define UP_PIN 3
#define DOWN_PIN 2
#define SNOOZE_PIN 4


void Key_Setup();                              // Set the push up button pins as Input pull up Mode
int Key_Pressed();                             // Find the key pressing state and pressing key
void Key_handle(int n);                        // handle level, items of the level value according to the key pressing

