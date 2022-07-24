/*
# the approximate moisture levels for the sensor reading
# 0 to 300 dry soil
# 300 to 700 humid soil
# 700 to 950 in water
*/

#include <OneWire.h>
#include <DallasTemperature.h>

# define ledPin 15
# define sensorPin 36 
// GPIO where the DS18B20 is connected to
const int oneWireBus = 23;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
int trigger = 300; // set the level

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn off LED
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop()
{

Serial.print("Moisture Sensor Value:");
Serial.println(analogRead(sensorPin)); // read the value from the sensor
/////////////////////////////////////////////////////////////////////////////
Serial.print("\n");
   sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  
   delay(1000);
  
}
