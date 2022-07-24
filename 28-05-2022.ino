#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>



/// GPIO where the DS18B20 is connected to
const int oneWireBus = 23;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
//----------------------------------------------//
#define DHTPIN 13        // Digital pin connected to the DHT sensor //  use pins 3, 4, 5, 12, 13 or 14 --//
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.
//--------------------------------------------//
Adafruit_BMP085 bmp;

//------------Air Quality (MQ135)----------//
#define MQ135_THRESHOLD_1 1000 // Fresh Air threshold



void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println(F("Serial ..........!"));
  // Start the DS18B20 sensor
  sensors.begin();
//--------------------------------//
Serial.println(F("DHTxx test!"));
dht.begin();

//-------------BMP180----------------------//
if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  //while (1) //{}
}}

//----------------------------------------//


void loop() {
  //----------------------DS18B20--------------------//
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  //Serial.print(temperatureF);
 // Serial.println("ºF");
  Serial.println();
  delay(3000);
//-------------------------------------------------//
//--------------DHT11-----------------------------//
//------------------------------------------------//
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(3000);
Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  Serial.println();
  delay(3000);
  
 //-------------------------------------BMP180----------------------//   
   float BrPressure;       //04
   BrPressure = bmp.readPressure();
   Serial.print("Pressure = ");
   Serial.print(BrPressure);                                        // thingspeak value 3  Barometeric Pressure
   Serial.println(" Pa");
 // Serial.print("Pressure = ");
  //Serial.print(bmp.readPressure());
 // Serial.println(" Pa");
    
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(102000));
  Serial.println(" meters");
    
  Serial.println();
  delay(3000);


//----------------AIR Quality(MQ-135)----------------------------//
int MQ135_data = analogRead(36);

Serial.print("AirQua=");
Serial.print(MQ135_data, DEC);               // prints the value read
Serial.println(" PPM");
/*
if(MQ135_data < MQ135_THRESHOLD_1){
Serial.print('Fresh Air: ');
} else {
Serial.print('Poor Air:');
}
Serial.print(MQ135_data); // analog data
Serial.print('PPM'); // Unit = part per million */
Serial.println();
delay(3000);
/////////////////////////////////////////////////////////

}
