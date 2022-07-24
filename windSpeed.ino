int val;
long last=0;
int stat=LOW;
int stat2;
int count=0;
int sens=75;    // indicates the limit reading between dark and light,              // it has to be tested as it may change
                // acording on the              
                // distance the leds are placed.
int nBlades=2;  // the number of blades of the propeller
int miliseconds=500; // the time it takes each reading

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() 
{   val=analogRead(0);
  if(val<sens)
    stat=LOW;
   else
    stat=HIGH;
   digitalWrite(13,stat); // the led on pin 13 shows
                          // the state of the circuit.
   if(stat2!=stat){       // counts when the state changes, 
                          // thats from (dark to light) or 
                          // from (light to dark).  
     count++;  
     stat2=stat;
   }
   if(millis()-last>=miliseconds){
     double rps=((double)count/nBlades)/2.0*1000.0/miliseconds;  
     double rpm=((double)count/nBlades)/2.0*60000.0/(miliseconds);
     Serial.print((count/2.0));
     Serial.print("  RPS ");
     Serial.print(rps);
     Serial.print(" RPM");
     Serial.print(rpm);
     Serial.print("  VAL ");
     Serial.println(val);
     count=0;
     last=millis();
   }
}
