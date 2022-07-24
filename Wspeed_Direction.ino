#include <math.h>

#define WindDir 36
#define WindSpd 32
#define Offset 0;

volatile unsigned long Rotations; // cup rotation counter used in interrupt routine
volatile unsigned long ContactBounceTime; // Timer to avoid contact bounce in interrupt routine

float WindSpeed; // speed miles per hour
int VaneValue;// raw analog value from wind vane
int Direction;// translated 0 - 360 direction
int CalDirection;// converted value with offset applied
int LastValue;


////////////////////////////////////////////////////////
// This is the function that the interrupt calls to increment the rotation count
void isr_rotation () {

if ((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact.
Rotations++;
ContactBounceTime = millis();
}
}
////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////
// Converts compass direction to heading
void getHeading(int direction) {
if(direction < 22)
Serial.println("N");
else if (direction < 67)
Serial.println("NE");
else if (direction < 112)
Serial.println("E");
else if (direction < 157)
Serial.println("SE");
else if (direction < 212)
Serial.println("S");
else if (direction < 247)
Serial.println("SW");
else if (direction < 292)
Serial.println("W");
else if (direction < 337)
Serial.println("NW");
else
Serial.println("N");
} 
/////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

void setup() {
LastValue = 1;
Serial.begin(115200);
pinMode(WindSpd, INPUT);
pinMode(WindDir, INPUT);
attachInterrupt(digitalPinToInterrupt(WindSpd), isr_rotation, FALLING);

Serial.println("......Smart Weather Station...... ");
Serial.println("WindValue Direction Heading Rotations MPH");
}
/////////////////////////////////////////////////////////////////////////
void loop() {

////////////////////////////////////////////////////
Rotations = 0; // Set Rotations count to 0 ready for calculations

sei(); // Enables interrupts
delay (1000); // Wait 3 seconds to average
cli(); // Disable interrupts

// convert to mp/h using the formula V=P(2.25/T)
// V = P(2.25/3) = P * 0.75

WindSpeed = Rotations * 0.75;
//Serial.print("\t\t\t\t\t\t");
//Serial.print(Rotations); 
//Serial.print("\t");
//Serial.print(WindSpeed);
/////////////////////////////////////////////////////////////

VaneValue = analogRead(WindDir);
Direction = map(VaneValue, 0, 1023, 0, 360);
CalDirection = Direction + Offset;

if(CalDirection > 360)
CalDirection = CalDirection - 360;

if(CalDirection < 0)
CalDirection = CalDirection + 360;

// Only update the display if change greater than 2 degrees.
if(abs(CalDirection - LastValue) > 5)
{
Serial.print(VaneValue); 
Serial.print("\t");
Serial.print(CalDirection); 
Serial.print("\t");
getHeading(CalDirection);
LastValue = CalDirection;
}
WindSpeed = Rotations * 0.75;
Serial.print("\t");
Serial.print(Rotations); 
Serial.print("\t");
Serial.print(WindSpeed);
Serial.println("\t");
delay (250); // Wait 1 seconds to average

}
