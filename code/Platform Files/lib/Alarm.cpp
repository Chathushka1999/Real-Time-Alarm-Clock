


/*#include "Tone_Notes.h"*/
                    

#include "Alarm.h"


void my_delay_ms(double ms){
	while (0 < ms){
		_delay_ms(1);
		--ms;
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

int ring_alarm(int song[]){
	
	int notes=song[0];
	int tempo=song[1];
	int wholenote = (60000 * 4) / tempo;                                     //  calculates the duration of a whole note in ms (60s/tempo)*4 beats
	int divider = 0;
	double noteDuration = 0;
	/* iterate over the notes of the melody.*/
	for (int thisNote = 2; thisNote < notes * 2; thisNote = thisNote + 2) {
		divider = song[thisNote + 1];                                    // calculates the duration of each note
		if (divider > 0) {
		noteDuration = (wholenote) / divider;}                           // regular note, just proceed
		else if (divider < 0) {
			noteDuration = (wholenote) / abs(divider);                   // dotted notes are represented with negative durations!!
		noteDuration *= 1.5;}                                            // increases the duration in half for dotted notes
		
		if (!(PINB & (1<<5))){                                               // stop the alarm------------------->>>>>
			return 1;}
		else if (!(PINB & (1<<2))){                                          // snooze the alarm------------------->>>>>
			return 0;}
		
		playNote( noteDuration * 0.9, song[thisNote]);                   // play the note for 90% of the duration, leaving 10% as a pause
		my_delay_ms(noteDuration);                                       // Wait for the specif duration before playing the next note.
		playNote(1.0, 0);                                                // stop the waveform generation before the next note.
	}
	
	return 1;
}