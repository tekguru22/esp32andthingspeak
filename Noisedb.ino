
 
int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = 36; // pin connected to pin O module sound sensor  

long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 40;
int soundmedium = 500;
 
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input   
  Serial.begin (115200); 
   
}  
   
void loop ()  
{  
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
 
  Serial.println (level-33);  
  
  delay(2000);
}
