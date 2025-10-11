// Sebastien Philo Boat Control Slave Arduino.

#include <Wire.h> 
#define PI 3.14159 
#define potPin A0

#define X_OFFSET 300 
#define Y_OFFSET 200 
#define X_SENS 1000 
#define Y_SENS 1000 
#define NOISE 50 

int potentiometer = 0; 

void setup() 
{
 // Sets communication rate.
 Serial.begin(9600);
 // Sets communication between master and slave arduino.
 Wire.begin(30); 
 Wire.onRequest(transmitvalues);
}

void loop() 
{ 
 delay(100); 
}
  
void transmitvalues() 
{ 
 // Transforms potentiomer reading into 
 // an angle in degrees.
 int potentiometer = analogRead(A0); 
 int heading = potentiometer*360.0/1023.0; 
 
 // Calculates magnometer values based on angle.
 long magX = cos(heading*PI/180)*X_SENS + X_OFFSET + random(-NOISE,NOISE); 
 long magY = sin(heading*PI/180)*Y_SENS + Y_OFFSET + random(-NOISE,NOISE); 
 magX += 32768; 
 magY += 32768; 
 
 int magX_B1 = magX/256; 
 int magX_B2 = magX%256; 
 int magY_B1 = magY/256; 
 int magY_B2 = magY%256; 
  
 // Sends value to master arduino.
 Wire.write(magX_B1); 
 Wire.write(magX_B2); 
 Wire.write(magY_B1); 
 Wire.write(magY_B2); 
}
