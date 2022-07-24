// These constants, define values needed for the LDR readings and ADC
#define LDR_PIN                   1
#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           5.0
#define REF_RESISTANCE            5030  // measure this for best results
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("Light Sensor Test")); Serial.println("");
}

void loop(void) 
{  
  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  
  // Perform the analog to digital conversion  
  ldrRawData = analogRead(LDR_PIN);
  
  // RESISTOR VOLTAGE_CONVERSION
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;

  // voltage across the LDR is the 5V supply minus the 200 resistor voltage
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  
  // LDR_RESISTANCE_CONVERSION
  // resistance that the LDR would have for that voltage  
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  
  // LDR_LUX Conveter
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
 
  // print out the results
  Serial.print("LDR Illuminance: "); 
  Serial.print(ldrLux);    // for thingspeak this Value .......
  Serial.println(" lux");
  delay(250);
}
