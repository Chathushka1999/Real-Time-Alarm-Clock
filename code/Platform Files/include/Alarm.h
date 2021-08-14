#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

//#define F_CPU 8000000UL

#define SPEAKER_PORT PORTD                                        // defining the speaker connected port/register /pin number
#define SPEAKER_DDR DDRD
#define SPEAKER_PIN 2
                                           

void playNote(double duration, float frequency);                  // generate voltage pulse wave according to the given frequency,time duration
int  ring_alarm(int song[]);                                      // play the tone 
void my_delay_ms(double ms);                                      // delay the time given ms seconds





