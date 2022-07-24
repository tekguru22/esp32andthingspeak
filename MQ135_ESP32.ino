#include "MQ135.h"
#include <SPI.h>

























//--------------------------------------------------//
/*
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;

// variable for storing the potentiometer value
int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(500);
}*/

/*
MQ135 gasSensor = MQ135(33);
int val;
int sensorPin = 33;
int sensorValue = 0;
void setup()
{
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
 
}

void loop() {
  val = analogRead(33);
  Serial.print ("raw = ");
  Serial.println (val);
 // float zero = gasSensor.getRZero();
 // Serial.print ("rzero: ");
  //Serial.println (zero);
  float ppm = gasSensor.getPPM();
  Serial.print ("ppm: ");
  Serial.println (ppm);
  
  delay(2000);
}

*/
