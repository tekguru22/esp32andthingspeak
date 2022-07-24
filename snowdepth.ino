//This code is to use with HC-SR04 ultrasound module, 
//it measures the distance and display it on the serial montior in cm
//Refer to www.SurtrTech.com for more details

const int trigPin = 9; //pins where trigger and echo are wired
const int echoPin = 10;
#define SrBdRt 115200
long duration; //some variables that we need, duration and distance
int distance;

void setup() {
       pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
       pinMode(echoPin, INPUT); // Sets the echoPin as an Input
       Serial.begin(SrBdRt); // Starts the serial communication watch your baudrates
}

void loop() {

     digitalWrite(trigPin, LOW); //setting the trigger pin on low
     delayMicroseconds(2);       //delay is usually in miliseconds but here we are on µs
     digitalWrite(trigPin, HIGH);//emitting the ultrasounds
     delayMicroseconds(10);      //duration of emission
     digitalWrite(trigPin, LOW); //turning off the emitter

     duration = pulseIn(echoPin, HIGH); //measuring the duration pulseIn function measure the time between the echopin getting on high and the getting on low

distance= duration*0.034/2; //Quick maffs to get the correct distance you can do some calibration here as seen in the video

Serial.print("Distance: "); //printing on the serial monitor
Serial.print(distance);
Serial.println(" cm");
delay(1000); //Change the delay if you want to change the measuring frequency
}
