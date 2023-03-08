/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/owenschwab/Documents/IoT/smartRoom/speakerTesting/src/speakerTesting.ino"
/*
 * Project speakerTesting
 * Description: trying to use tone() to play tones on speaker, that may correcpond to readout on screen
 * Author: Owen S
 * Date: 3/6/2023
 */

//#include "application.h"




// TonePlayer tonePlayer;

void setup();
void loop();
#line 15 "/Users/owenschwab/Documents/IoT/smartRoom/speakerTesting/src/speakerTesting.ino"
const int SPKPIN = A1;

int freq1 = 1000;
int freq2 = 2000;
int freq3 = 4000;
int duration = 1000;


SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pinMode(A1, OUTPUT);
  // tonePlayer.Begin();
}


void loop() {
  // tonePlayer.process();
  tone(SPKPIN, freq1, duration);
  delay(1000);
  noTone(SPKPIN);
  tone(SPKPIN, freq2, duration);
  delay(1000);
  noTone(SPKPIN);
  tone(SPKPIN, freq3, duration);
  delay(1000);
  noTone(SPKPIN);
  delay(1000);
}