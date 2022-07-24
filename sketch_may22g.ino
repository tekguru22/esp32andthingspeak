int led = 23; // LED pin
int reelSwitch = 2; // magnetic senso rpin
int switchState; // variable to store reel switch value
void setup() 
{
  pinMode (led, OUTPUT);
  pinMode (reelSwitch, INPUT);
}
void loop()
{
  switchState = digitalRead(reelSwitch); // read the value of digital interface 2 and assign it to switchState
  
  if (switchState == HIGH) // when the magnetic sensor detect a signal, LED is flashing
  {
    digitalWrite(led, HIGH);
  }
  else 
  {
    digitalWrite(led, LOW);
  }
}
