#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd_16X2.h"


#define RETURN_PIN 6                           //#define KEYS_PIN PINB
#define SELECT_PIN 5
#define UP_PIN 3
#define DOWN_PIN 2
#define SNOOZE_PIN 4


void Key_Setup();                              
int Key_Pressed();                             
void Key_handle(int,int *,int *);