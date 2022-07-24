#include <math.h>
//#include <OneWire.h>
//#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <Wire.h>

#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>

#include <WiFi.h>
#include "ThingSpeak.h"




//////////////////////////////////////////////////////////////////
#define bdRate 115200
///////////////////////////Module 1 Pin Assigment///////////////////
#define AirTemp_DS18B20PIN  23
#define AirHumidityPIN      13
//#define BaroPressurePIN     (12c ~ SCL 22 ,SDA 21)
//#define LCD 4x20            (12c ~ SCL 22 ,SDA 21)
#define AirQaltyPIN         35
#define LuxMeterPIN         36
#define RainDetecPIN        39
//#define WindSpeedPIN      32
///////////////////////////////////////////////////////
// Replace with your network credentials (STATION)
const char* ssid = "MLT";   // your network SSID (name)
const char* password = "medi1234";   // your network password
WiFiClient  client;
unsigned long previousMillis = 0;
unsigned long interval = 30000;



////////////////////thingspeak channels///////////////////////
///////////////////////////////////////////////////////////////
unsigned long myChannelNumber1 = 1554312 ;
const char * myWriteAPIKey1 = "AEYCB9Z5ADL2HEU5";
///////////////////thingspeak Channek 2////////////////////////////////
unsigned long myChannelNumber2 = 1558532 ;
const char * myWriteAPIKey2 = "3O0NP5UV0JJDRI4O";
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Timer variables
unsigned long lastTime = 0;
//unsigned long timerDelay = 30000;
unsigned long timerDelay = 20000;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////Module_01_Sensor details////////////////
//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;
// GPIO where the DS18B20 is connected to
const int oneWireBus = AirTemp_DS18B20PIN;    
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
//----------------------------------------------//
#define DHTPIN AirHumidityPIN          // Digital pin connected to the DHT sensor //  use pins 3, 4, 5, 12, 13 or 14 --//
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor.
//--------------------------------------------//
Adafruit_BMP085 bmp;

//------------Air Quality (MQ135)----------//

#define MQ135_THRESHOLD_1 1000 // Fresh Air threshold
///////////////////////////////////////////////////////////////////////////////////////
/////////////////Lux Meter Values ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/* LDR Luximeter */
// Constants
#define VIN 3.3 // V power voltage, 3.3v in case of NodeMCU
#define R 10000 // Voltage devider resistor value
int LDR_Val; // Analog value from the LDR
int Iluminance; //Lux value
///////////////////////////////Module2 end//////////////////////////////////////

int rainPin = RainDetecPIN;

// you can adjust the threshold value
int thresholdValue = 500;
////////////////////////////////////////////////Lux conversion /////////////////////////
int conversion(int raw_val)
{
  // Conversion rule
  float Vout = float(raw_val) * (VIN / float(1023));// Conversion analog to voltage
  float RLDR = (R * (VIN - Vout))/Vout; // Conversion voltage to resistance
  int lux = 500/(RLDR/1000); // Conversion resitance to lumen
  return lux;
}
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////WindSpeed Module////////////////////////////////////
#define WindSensorPin (32) // The pin location of the anemometer sensor

volatile unsigned long Rotations; // cup rotation counter used in interrupt routine
volatile unsigned long ContactBounceTime; // Timer to avoid contact bounce in interrupt routine

float WindSpeed; // speed miles per hour
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////Function call by Windspeed inerrupt/////////////////////////
// This is the function that the interrupt calls to increment the rotation count
void isr_rotation ()
{

if ((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact.
Rotations++;
ContactBounceTime = millis();
}}

///////////////////////////////////////////////////////////

////////////wifi setting Function /////////
void initWiFi() {
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
  


/////////////////////////////////////////////////

void setup() {

//////////////////////////////////Module 01 //////////////////////////////
//////////////////PIN Definition////////////////////////
  pinMode(rainPin, INPUT);
  pinMode(WindSensorPin, INPUT);
 //////////// Start the Serial Monitor ////////////////////
  Serial.begin(bdRate);  //Initialize serial
  Serial.println("\n .....Serial Port ........");
 
////////////////////////////////////////////SetUP_END///////////////////////////////////////
 
///////////////////////WindSpeed /////////////////////////////////////////////
{

attachInterrupt(digitalPinToInterrupt(WindSensorPin), isr_rotation, FALLING);
Serial.println("....Wind Speed Test.........");
Serial.println("-----Rotations\tMPH------");}
///////////////////////////////////////////////////////////////////////////////
 
////////////// Start the DS18B20 sensor///////////////////////////////////////////
  sensors.begin();
//--------------------------------//
Serial.println(F("....DHTxx test!....."));
dht.begin();

//-------------BMP180----------------------//
if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  //while (1) //{}
}
//--------------------rain detect ---------------/
Serial.println(".........Rain Detector.......");
/////////////////////////////////Module 01 End ///////////////////////////////////////////

//////////////////wifi setUp//////////////////////////////////////

WiFi.mode(WIFI_STA);  
ThingSpeak.begin(client);  // Initialize ThingSpeak
initWiFi();
Serial.print("RSSI: ");
Serial.println(WiFi.RSSI());
/////////////////////////////wifi setUp End///////////////////////


}
///////////////////////////////////setUp END///////////////////////////////////////

void loop() 
{

if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED)
      {
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }}
//////--- WindSpeed---////////////
Rotations = 0; // Set Rotations count to 0 ready for calculations
sei(); // Enables interrupts
delay (3000); // Wait 3 seconds to average
cli(); // Disable interrupts
// convert to mp/h using the formula V=P(2.25/T)
// V = P(2.25/3) = P * 0.75
WindSpeed = Rotations * 0.75;
Serial.print(Rotations); Serial.print("\t\t");
Serial.println(WindSpeed);
////////////--DS18B20--//////////////////////
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);                          // Air Temperature thingspeak value 1
  Serial.println("ºC");
  //Serial.print(temperatureF);
 // Serial.println("ºF");
  delay(2000);
//-------------------------------------------------//
//--------------DHT11-----------------------------//
//------------------------------------------------//
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float humidity;    
  float humidity = dht.readHumidity();                                      // thingspeak value 2 " h = humidity"
  // Read temperature as Celsius (the default)
  float TempAir = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(TempAir) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(TempAir, humidity, false);

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(TempAir);
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
int MQ135_data = analogRead(AirQaltyPIN);

Serial.print("AirQua= ");
Serial.print(MQ135_data, DEC);               // prints the value read
Serial.println(" PPM");

if(MQ135_data < MQ135_THRESHOLD_1){
Serial.print("Fresh Air: ");
} else {
Serial.print("Poor Air:");
}
Serial.print(MQ135_data); // analog data
Serial.print("PPM"); // Unit = part per million
Serial.println();
delay(3000);
/////////////////////////////////////////////////////////////////////////////////////

///////////////////////////Lux value////////////////////////////////////////////////
{
   LDR_Val = analogRead(LuxMeterPIN);
  Iluminance = conversion(LDR_Val);
  Serial.print("Analog reading from sensor = ");
  Serial.println(LDR_Val); // between 0 -
  Serial.print("Iluminance value = ");
  Serial.print(Iluminance); // Converted value
  Serial.println(" Lux");
  delay(500);
}
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Rain detect & Values //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// read the input on analog pin :
  int sensorValue = analogRead(RainDetecPIN );
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
  Serial.println(".... - It's wet.........");
   
  }
  else {
    Serial.println(".......- It's dry........");
   
  }
  delay(500);
//////////////////////////////////////////////////////////////////////////////////////////////////
Serial.println("Connected to CHANNEL 01......");


////////////////////////////////////////////////////////////////////////////////////////////////
// set the fields with the values{
 
    ThingSpeak.setField(1, temperatureC);  // Air Temperature
    ThingSpeak.setField(2, humidity);      // Air Humidity
    ThingSpeak.setField(3, hic);          // Heat Index
    ThingSpeak.setField(4, BrPressure);    //Barometric Pressure(Air Pressure)
    ThingSpeak.setField(5, MQ135_data);   // Air Quality
    ThingSpeak.setField(6, Iluminance);     // Lux Values
    ThingSpeak.setField(7, sensorValue);    // Rain Detection
    ThingSpeak.setField(8, WindSpeed);    //WindSpeed
   
   
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber1, myWriteAPIKey1);

    if(x == 200){
      Serial.println("\nChannel 01 update successful.");
    }
    else{
      Serial.println("Problem updating channel  01. HTTP error code " + String(x));
    }
    lastTime = millis();
 {
  delay(10000);
 }
}
