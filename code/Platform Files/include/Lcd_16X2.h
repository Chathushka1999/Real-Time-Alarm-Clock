#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include "Functions.h"
#include "RTC_DS3232.h"

//#define F_CPU 8000000UL


#define LCD_Dir_00 DDRD                     // LCD display connected pins
#define LCDER_Port PORTD                    // LCD display connected pins I/O register
#define RSel PD0                            //RS Pin
#define ENable PD1                          //E Pin

void LCD_Commandgiver(unsigned char);
void LCD_Initializer (void);                //Initializes the LCD
void LCD_String(char *);                    //Send string to LCD
void LCD_Num (int);
void LCD_Character(unsigned char);
void LCD_Clear();                           //Clears the display
void LCD_SetCursor (char, char);            //Send string to LCD with XY position
void LCD_TwoDigit (int num);

void Display_Time();                        // print the Time and Date HH:MM:SS, DD:MM:YYYY format




