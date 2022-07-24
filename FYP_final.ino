//.............PROJECT INFORMATION..............//
//..... FYP final code for Faizan Projects....///
//...... Institue of Electronics..............////
//.......University of Peshawar..............////
//.............................................//
//---------------------------------------------//
//---------------------IMPORTANT Header Files---------------------//
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <WiFi.h>

//---------------------IMPORTANT Header Files---------------------//

//-----------------DS1820-------------------//
// GPIO where the DS18B20 is connected to
const int oneWireBus = 23;  
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
   

//---------------------BMP180---------------------//
Adafruit_BMP085 bmp;
//---------------------BMP180---------------------//

/////////////////////////////////////////////////////////
//--------------------DHT11-----------------------//

#define DHTPIN 13     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//--------------------DHT11-----------------------//
///////////////////////////////////////////////////////
//--------------------Air Quality -----------------//
#define MQ135_THRESHOLD_1 1000 // Fresh Air threshold

  
void setup() {
  //--------------Serial Ports ----------------------//
    Serial.begin(115200);
    sensors.begin();
   //Serial.print(“********** ESP32 publishes DS18B20 data “);    //---------------------DS18B20---------------------//
  // Serial.print(“********** ESP32 publishes BMP180 data “);  //--------------------- BMP180---------------------//
  // Serial.print(“********** ESP32 publishes DHT11 data “);     //---------------------DHT11---------------------//
  // Serial.print(“********** ESP32 publishes MQ-135 data “);   //---------------------MQ-135---------------------//
  if (!bmp.begin()) 
  {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  while (1) {  }
  }
}
  
void loop() {

//------------------DS18B20-------------------------------//
 // Serial.println(“********** ESP32 publishes DS18B20 data “);    //---------------------DS18B20---------------------//
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  delay(3000);
//  Serial.println(“\n“);    //---------------------NEWLINE---------------------//
//------------------------------------------------------//
// Serial.println(“********** ESP32 publishes BMP180 data “);
// Serial.println(“\n“);
//------------------BMP180---------------------------//
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
    
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
  
  delay(500);
  
//  Serial.println(“\n“);    //---------------------NEWLINE---------------------//
// Serial.println(“********** ESP32 publishes DHT11 data “); 
//------------------DHT11---------------------------//

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
}
//---------------AIR Quality-------------------//






//////////////////////////////////////////////////////////////
