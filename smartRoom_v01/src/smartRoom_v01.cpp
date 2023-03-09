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
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "colors.h"

void setup();
void loop();
#line 17 "/Users/owenschwab/Documents/IoT/smartRoom/smartRoom_v01/src/smartRoom_v01.ino"
const int SRVPIN = A3;
const int SPKRPIN = A1;
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
const int BULB1 = 1;
//SCREEN
const int OLED_RESET = A0;
char POPPING;
//LED
const int PIXELPIN = D7;
const int PIXELCOUNT = 12;
int i;
//HUE


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

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_NeoPixel pixel(PIXELCOUNT, PIXELPIN, WS2812B);


Servo myServo;
IoTTimer timer;

void wemoSwitch(int oF, int wM);

void pixelFill(int startingPixel, int endingPixel, int color);
void oledWrite(int x, int y, int oO, char phrase);

Encoder myEnc(PINA,PINB);

SYSTEM_MODE(MANUAL);

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    pixel.begin();
    pixel.show();
    pixel.setBrightness(10);

    pinMode(SPKRPIN, OUTPUT);
    pinMode(PIXPIN, OUTPUT);
    pinMode(ENBPIN, INPUT_PULLDOWN);

    Serial.begin(9600);
    // waitFor(Serial.isConnected,10000);

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
    display.clearDisplay();

    if(button4.isClicked()) {
        onOFF4 = !onOFF4;
    }

    if(onOFF4 && !onOFF5) {
        // timer.startTimer(5000);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.printf("HELLO  LOVE\n]");
        display.display();
        pixelFill(0,16,0xFF0000);
        timer.startTimer(5000);
    }


    if(!onOFF4) {
        display.clearDisplay();
        display.display();
        pixelFill(0,16,0x000000);
    }

    if(button5.isClicked()) {
        onOFF5 = !onOFF5;
    }


    if(!onOFF5) {
        display.clearDisplay();
        display.display();
    }

    if(onOFF4 && onOFF5) {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,20);
        display.printf("WHAT DO U\n WANT");
        display.display();

        pixel.clear();
        pixelFill(0, 12, 0xFFFFFF);
        pixel.show();

        if(button1.isClicked()) {
            onOFF1 = !onOFF1;
        }
        wemoSwitch(onOFF1, WEMO1);
        oledWrite(0, 50, onOFF1, POPPING);

        if(button2.isClicked()) {
            onOFF2 = !onOFF2;
        }
        wemoSwitch(onOFF2, WEMO2); 



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

        if(button3.isClicked()) {
            color++;
        }

        if(buttonE.isClicked()) {
            onOFFE = !onOFFE;
        }

        if(onOFFE) {
            // if(timer.isTimerReady()) {
                Serial.printf("setting color of bulb %i to color %06i\n", BULB1, HueRainbow[color%7]);
                setHue(BULB1,true,HueRainbow[color%7],brightness,255);
                // timer.startTimer(5000);
            // }
        }

        if(!onOFFE) {
            Serial.printf("SHUT ER DOWN\n");
            setHue(BULB1,false,0,0,0);
        }
    }
}


///FUNCTION AREA

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


void oledWrite(int x, int y, int oO, char phrase) {
    if(oO) {
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(x,y);
        display.printf("%c", phrase);
        display.display();
    }

    if(!oO) {
        display.clearDisplay();
        display.display();
    }
}

void pixelFill(int startingPixel, int endingPixel, int color) {
    for(i=startingPixel; i<=endingPixel; i++) { 
        pixel.setPixelColor(i, color);
    }
    pixel.show();
}

