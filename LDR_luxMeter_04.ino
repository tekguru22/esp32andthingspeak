 /*  RL=500/lux
 *  V0=5*(RL/(RL+R))
 *  V0=LDR_value*ADC_value
 *  lux=(250/V0)-50
 *  Author: Ashish Kumar 
    Org: INVOOTECH                  */
float lux=0.00,ADC_value=0.0048828125,LDR_value;
#define AnalogPin 36
void setup() {

  pinMode(AnalogPin,INPUT);    //make analog pin A0 as input

  Serial.begin(115200);   //initialize serial monitor

}

void loop() {

  LDR_value=analogRead(AnalogPin);

  lux=(250.000000/(ADC_value*LDR_value))-50.000000;

  Serial.println(lux);

  delay(1000);

}
