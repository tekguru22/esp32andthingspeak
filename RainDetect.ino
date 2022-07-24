// for Arduino Microcontroller
//#define rainAnalog 36
//#define rainDigital 5

// for ESP8266 Microcontroller
//#define rainAnalog A0
//#define rainDigital D1

// for ESP32 Microcontroller
#define rainAnalog 35
#define rainDigital 34

void setup() {
  Serial.begin(115200);
  pinMode(rainDigital,INPUT);
}
void loop() {
  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);

  Serial.print(rainAnalogVal);
  Serial.print("\t");
  Serial.println(rainDigitalVal);
  delay(200);
}
