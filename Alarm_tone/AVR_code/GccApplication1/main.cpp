#define SPEAKER_PORT PORTD
#define SPEAKER_DDR DDRD
#define SPEAKER_PIN 0
 
#define F_CPU 1000000L // CPU clock speed 1 MHz
#include <avr/io.h>
#include <util/delay.h> 
#include "IncFile1.h"
#include <stdlib.h>


int snooze=0,alarm_status=0;
void playMelody();
void playNote(float duration, float frequency);
void ring_alarm(int song[]);

void setup(){
	DDRB = 0b00000000;    // set the push button pins as input mode
	PORTB = 0b00111100;
	DDRD = 0b00011111;    // set the led /speaker connecting pins as an output mode
	PORTD =0b00000000;    // set all the pins on off mode
}

void my_delay_ms(double ms){
	while (0 < ms){
		_delay_ms(1);
		--ms;
	}
}

int main(void){
	setup();
    while(1) {
		if(!(PINB & (1<<5))){
			alarm_status=1;
		    ring_alarm(melody1);}
		else if(!(PINB & (1<<4))){
			alarm_status=1;
			ring_alarm(melody2);}
    }
}

 
 
void playNote(double duration, float frequency){
    long int i,cycles;
    double half_period;                // assigning the necessary variables
    float wavelength;
 
    wavelength=(1/frequency)*1000;    // find the wave length of the pulse from frequency
    cycles=duration/wavelength;       // The number of cycles.
    half_period = wavelength/2;       // The time between each toggle.
    
    SPEAKER_DDR |= (1 << SPEAKER_PIN);
 
    for (i=0;i<cycles;i++){
        my_delay_ms(half_period);                              // Wait 1 half wavelength.
        SPEAKER_PORT |= (1 << SPEAKER_PIN);                    // Output 5 V to port Pin 7.
        my_delay_ms(half_period);                              // Wait 1 half wavelength.
        SPEAKER_PORT &= ~(1 << SPEAKER_PIN);                   // 0 V at port pin 7.
    }
 
    return; 
}

void ring_alarm(int song[]){
	int notes=song[0];
	int tempo=song[1];
	int wholenote = (60000 * 4) / tempo;                                 // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
	int divider = 0;
	double noteDuration = 0;
	/* iterate over the notes of the melody.*/
	while(1){
	for (int thisNote = 2; thisNote < notes * 2; thisNote = thisNote + 2) {
		divider = song[thisNote + 1];                                    // calculates the duration of each note
		if (divider > 0) {
		noteDuration = (wholenote) / divider;}                           // regular note, just proceed
		else if (divider < 0) {
			noteDuration = (wholenote) / abs(divider);                   // dotted notes are represented with negative durations!!
		noteDuration *= 1.5;}                                            // increases the duration in half for dotted notes
		if (!(PINB & (1<<3))){
			alarm_status=0;snooze=0;
			return;}
		else if((!(PINB & (1<<2))) && snooze<3 ){
			break;}
		else if((!(PINB & (1<<2))) && snooze==3 ){
			snooze=0;alarm_status=0;
			return;}
		playNote( noteDuration * 0.9, song[thisNote]);                   // we only play the note for 90% of the duration, leaving 10% as a pause
		my_delay_ms(noteDuration);                                       // Wait for the specif duration before playing the next note.
		playNote(1.0, 0);                                                // stop the waveform generation before the next note.
	}
	if (snooze>=0 && snooze<3 && alarm_status==1){
		snooze=snooze+1;
		my_delay_ms(5000);
		}
	else if(snooze==3 && alarm_status==1){
		alarm_status=0;snooze=0;
		return;}
	}
}