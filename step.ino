#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif
#define LED_PIN 6
#define sensorPin1 7
#define sensorPin2 13
#define LED_COUNT 18
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int calibrationTime = 20;
int sensorValue1 =0;
int sensorValue2 =0;
int sensorstatus = 0;
int sensor = 0; 
int ranValue = 0;
void colourSelection()
{   sensorstatus = 1;
if (ranValue == 1 ) {
 RGBColor(0, 0, 255);  
}
 else if (ranValue == 2 ) {
 RGBColor(0, 255, 255); 
}
 else if (ranValue == 3 ) {
 RGBColor(0, 127, 255);  
}
 else if (ranValue == 4 ) {
 RGBColor(0, 255, 127); 
} else if (ranValue == 5 ) {
  RGBColor(0, 255, 0);  
} else if (ranValue == 6 ) {
 RGBColor(255, 0, 255);  
} else if (ranValue == 7 ) {
   RGBColor(255, 255, 0); 
} else if (ranValue == 8 ) {
 RGBColor(255, 0, 127);  
} else if (ranValue == 9 ) {
   RGBColor(255, 0, 0);  
} else if (ranValue == 10 ) {
  RGBColor(244, 233, 140);  
} else if (ranValue == 11 ) {
  RGBColor(255, 166, 0);
} else if (ranValue == 12 ) {
 RGBColor(252, 78, 3);
} else {
RGBColor(255, 127, 0); 
}
   
}



void colorWipe(uint32_t color, int wait)
{
  for (int i = 0; i < strip.numPixels(); i++)
  { //Serial.println(sensorstatus);
    if(sensorstatus == 0){
        sensorValue1 = digitalRead(sensorPin1);
        sensorValue2 = digitalRead(sensorPin2);
           if (sensorValue1 == 1 || sensorValue2 == 1)  {
            
              //Serial.println("seroa");
              break;
           } 
      }
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
void colorWipere(uint32_t color, int wait)
{

  for (int i = strip.numPixels(); i >= 0; i--)
  { 
    //Serial.println(sensorstatus);
   if(sensorstatus == 0){
    sensorValue1 = digitalRead(sensorPin1);
        sensorValue2 = digitalRead(sensorPin2);
     if (sensorValue1 == 1 || sensorValue2 == 1)  {
     // Serial.println("seroa");
              break;
           } 
        
      }
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
void RGBColor(int Rcolor, int Gcolor, int Bcolor)
{ 
  
  if (sensorValue1 == 1) {
    sensor = 1;
    colorWipe(strip.Color(Rcolor, Gcolor, Bcolor),500);
  } 
  if (sensorValue2 == 1) {
     sensor = 2; 
   colorWipere(strip.Color(Rcolor, Gcolor, Bcolor),500);
  }
 
}
void setup() {
  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255
  //Serial.begin(9600);
  
  pinMode(LED_PIN,OUTPUT);
  pinMode(sensorPin1,INPUT); 
  pinMode(sensorPin2,INPUT); 
}

void loop() {
  sensorValue1 = digitalRead(sensorPin1);
  sensorValue2 = digitalRead(sensorPin2);
  
  if (ranValue == 13) {
       ranValue = 0;
  }
  if (sensorValue1 == 1 || sensorValue2 == 1) {
    sensorstatus = 1;
   colourSelection();
  ranValue =  ranValue +1 ;
  for(int i = 0; i < calibrationTime; i++){ delay(1000); } 
  } 
   if (sensorValue1 == 0 && sensor == 1) {
     sensorstatus = 0;
    colorWipe(strip.Color(0,0,0),400);
    sensor = 0;
  } 
   if (sensor == 2 && sensorValue2 == 0) {
     sensorstatus = 0;
    colorWipere(strip.Color(0,0,0),400);
    sensor = 0;
  } 
}
