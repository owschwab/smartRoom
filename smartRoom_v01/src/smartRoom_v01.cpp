/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/owenschwab/Documents/IoT/smartRoom/smartRoom_v01/src/smartRoom_v01.ino"
/*
 * Project smartRoom_v01
 * Description: Emotional room controll that you need to tell nice things to get to work.
 * Author: Owen S
 * Date: 3/6/2023
 */

#include <math.h>
#include <Encoder.h>
#include <neopixel.h>
#include "IoTClassroom_CNM.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "colors.h"

void setup();
void loop();
#line 16 "/Users/owenschwab/Documents/IoT/smartRoom/smartRoom_v01/src/smartRoom_v01.ino"
const int SRVPIN = A3;
const int SPKRPIN = A2;
//ENCODER
const int PINA = A5;
const int PINB = A4;
//LED
const int PIXPIN = D8;
//BUTTONS
const int BT1PIN = D2;
const int BT2PIN = D3;
const int BT3PIN = D4;
const int BT4PIN = D5;
const int BT5PIN = D6;
const int ENBPIN = 12;
//WEMO
const int WEMO1 = 1;
const int WEMO2 = 2;
const int NUMBULBS = 1;
const int BULB = 2;

int color;
int encValue;
int brightness;

// float button1, button2, button3, button4, button5, button6;
// bool other1, other2, other3, other4, other5, other6;
bool onOFF1, onOFF2, onOFF3, onOFF4, onOFF5, onOFFE;

Button button1(BT1PIN);
Button button2(BT2PIN);
Button button3(BT3PIN);
Button button4(BT4PIN);
Button button5(BT5PIN);
Button buttonE(ENBPIN);


Servo myServo;
IoTTimer timer;

void wemoSwitch(int oF, int wM);

Encoder myEnc(PINA,PINB);

SYSTEM_MODE(MANUAL);

void setup() {

    myServo.attach(SRVPIN);

    pinMode(SPKRPIN, OUTPUT);
    pinMode(PIXPIN, OUTPUT);
    pinMode(ENBPIN, INPUT_PULLDOWN);

    Serial.begin(9600);
    waitFor(Serial.isConnected,10000);

    WiFi.on();
    WiFi.setCredentials("IoTNetwork");
    WiFi.connect();

    while(WiFi.connecting()) {
        Serial.printf(",");
    }
    delay(1000);
    Serial.printf("\n\n");
}


void loop() {
    
    if(button1.isClicked()) {
        onOFF1 = !onOFF1;
    }
    wemoSwitch(onOFF1, WEMO1);

    if(button2.isClicked()) {
        onOFF2 = !onOFF2;
    }
    wemoSwitch(onOFF2, WEMO2); 

    if(button3.isClicked()) {
        color++;
    }

    encValue = myEnc.read();

     if(encValue >= 95) {
        myEnc.write(95);
        encValue = 95;
    }
    if(encValue <= 0) {
        myEnc.write(0);
        encValue = 0;
    }

    brightness = map(encValue,0,95,0,255);

    if(buttonE.isClicked()) {
        onOFFE = !onOFFE;
    }

    if(onOFFE) {
        // if(timer.isTimerReady()) {
            Serial.printf("setting color of bulb %i to color %06i\n", BULB, HueRainbow[color%7]);
            setHue(BULB,true,HueRainbow[color%7],brightness,255);
            // timer.startTimer(5000);
        // }
    }

    if(!onOFFE) {
        Serial.printf("SHUT ER DOWN\n");
        setHue(BULB,false,0,0,0);
    }
}

void wemoSwitch(int oF, int wM) {
    if(oF) {
        switchON(wM);
       // Serial.printf("turn on Wemo %d\n", wM);
    }

    if(!oF) {
        switchOFF(wM);
        //Serial.printf("turn off Wemo %d\n", wM);
    } 
}

