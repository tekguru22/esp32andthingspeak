E/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-door-sensor
 */

const int reedSwitchPin = 32;
const int radius = 8.5; 
int circumference;
//int circumference;   //declaring the circumference variable
int totaltime;       //declaring the total time until the next trip on the reed switch variable
int Speed;           //declaring the Speed variable
int timer;           //declaring the timer to calculate the total time variable

const int ledPin =  2;
int buttonState = 0;
int lastMillis = 0;
/////////////////////////////
void isr()           
 {
      
 }


///////////////////////////////////
void IRAM_ATTR fonction_ISR() {
      timer++;                        // Begin the timer and start counting
      delayMicroseconds(9600);        // Delay to start after a 0.0096 seconds   
    
}

void setup() {
    Serial.begin(115200);
    Serial.print("...........WindSpeed........"); 
//    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin,OUTPUT);
   // attachInterrupt(reedSwitchPin, fonction_ISR, CHANGE);
    attachInterrupt(reedSwitchPin, fonction_ISR, RISING);
    digitalWrite(ledPin, buttonState);
    pinMode(reedSwitchPin, INPUT_PULLUP);                         // Sets the reed switch to be an input
   timer = 0;                                                 // Sets timer to 0 seconds
   Speed = 0;                                                 // sets the speed to 0 seconds
   totaltime = 0;                                             // sets the total time to start off at 0
   circumference = 6.28 * radius; 

}

void loop() {
    if (millis() - totaltime >= 1000) {                                      // Gets varibales to go into the loop everytime the millis() - the total time elapsed is less than 1ms
                                                                            // So unless I become superman then no human will be able to achieve this. 
        detachInterrupt(digitalPinToInterrupt(2));                          // Stops the timer from the reading from pin 2 aka the reed switch

        Speed = ((8.181818182*circumference)/(millis() - totaltime)*timer); // Calculates the speed of the bike. The 8.18 number is converting the time in seconds into hours and inches into feet.

        timer = 0;                                                          // Makes the timer go back to zero
        totaltime = millis();                                               // Makes the total time the new time
        attachInterrupt(digitalPinToInterrupt(2), isr, RISING);             // Make the ISR loop attach back
//        attachInterrupt(buttonPin, fonction_ISR, CHANGE);
                                                        // Prints the speed to the LCD display
        Serial.print("...WindSpeed.....");                                              // Prints "Speed" to serial monitor. Mainly for troubleshooting.  
        Serial.println(Speed);                                                // Prints the speed to the serial monitor. Mainly for troubleshooting.

   }}



/*
void IRAM_ATTR fonction_ISR() {
    ets_printf("Boutton pressé\n");
    // Code de la fonction
}

void setup() {
    Serial.begin(115200);
    pinMode(33, INPUT_PULLUP);
    attachInterrupt(33, fonction_ISR, FALLING);
}

void loop() {
}
*/

/*
#define DOOR_SENSOR_PIN  19  // ESP32 pin GIOP19 connected to door sensor's pin

int doorState;

void setup() {
  Serial.begin(115200);                     // initialize serial
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode
}

void loop() {
  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    Serial.println("The door is open");
  } else {
    Serial.println("The door is closed");
  }
}


*/
