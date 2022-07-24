
#define SENSOR_PIN 36

void setup ()  
{   
  float peakToPeak = 0;                                  // peak-to-peak level
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
   
  Serial.begin(115200);
  
  Serial.print("Noise dB.........");
}
  
 
   
void loop ()  
{ 
   unsigned long startMillis= millis();                   // Start of sample window
                                                             // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);                    //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   int db = map(peakToPeak,20,900,49.5,90);             //calibrate for deciBels
 
  
  Serial.print("Loudness: ");
  Serial.print(db);
  Serial.print("dB");
  
  
    delay(200); }
 
       // thingspeak needs minimum 15 sec delay between updates.
 
