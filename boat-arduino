// Sebastien Philo Boat Control Master Arduino.

#define motorPinA 3
#define motorPinB 2
#define motorPinC 5
#define motorPinD 4
#define trigPinA 8
#define echoPinA 9
#define trigPinB 12
#define echoPinB 13
#define trigPinC 10
#define echoPinC 11
#define button 6 
#include <Wire.h>
#define PI 3.14159

int buttonValue = 0;
int reqSpeed = 0; 
int reqSteer = 0;
  
long X_mag = 0; 
long Y_mag = 0; 

int outValue1 = 0;
int outValue2 = 0;
int outValue3 = 0;
int outValue4 = 0;
int outValue5 = 0;

void setup()
{
  // Sets communications rate.
  Serial.begin(9600);
  Wire.begin(); 

  // Set digital pins for motors and sensors.
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(motorPinC, OUTPUT);
  pinMode(motorPinD, OUTPUT);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT); 
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT); 
  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);
}

void loop()
{
  // Determines state of buttom from pin.
  int buttonState = digitalRead(button);

  // Defines values as 8-bit integers.
  byte outValue1;
  byte outValue2;
  byte outValue3;
  byte outValue4;
  byte outValue5;
  
  // Reads the serial monitor for values for  
  // speed and steering from labview.
  while (Serial.available())
  {
   int input1 = Serial.read();
   reqSpeed = map(input1,65,90,0,100);
   
   int input2 = Serial.read();
   reqSteer = map(input2,65,90,0,360);
  }
  
  // Controls motors based on speed and steering input.
  if (reqSpeed>0 && reqSteer<=15 && reqSteer>=-15) 
  { 
   // Drives both motors equally based on speed input.
   analogWrite(motorPinA, reqSpeed); 
   digitalWrite(motorPinB, LOW);  
   analogWrite(motorPinC, reqSpeed);
   digitalWrite(motorPinD, LOW);
  } 
  else if (reqSpeed>0 && reqSteer>15) 
  { 
   // Reduces speed on right motor, to turn right,
   // based on speed and steering input.
   analogWrite(motorPinA, -reqSteer-400); 
   digitalWrite(motorPinB, LOW);  
   analogWrite(motorPinC, reqSpeed);
   digitalWrite(motorPinD, LOW);
  } 
  else if (reqSpeed>0 && reqSteer<15) 
  { 
   // Reduces speed on left motor, to turn left,
   // based on speed and steering input.
   analogWrite(motorPinA, reqSpeed); 
   digitalWrite(motorPinB, LOW);  
   analogWrite(motorPinC, reqSteer-400);
   digitalWrite(motorPinD, LOW);
  }  
  else 
  // Motors are off, if there is no input.
  {
   digitalWrite(motorPinA, HIGH); 
   digitalWrite(motorPinB, HIGH); 
   digitalWrite(motorPinC, HIGH); 
   digitalWrite(motorPinD, HIGH);
  } 
  
  
  readmagnetometer(); 
  
  long durationA;
  long durationB;
  long durationC;
  
  // Reads distance of objects to the left.
  digitalWrite(trigPinA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinA, LOW);
  durationA = pulseIn(echoPinA, HIGH);

  // Reads distance of objects in front.
  digitalWrite(trigPinB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinB, LOW);
  durationB = pulseIn(echoPinB, HIGH);
  
  // Reads distance of objects to the right.
  digitalWrite(trigPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinC, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinC, LOW);
  durationC = pulseIn(echoPinC, HIGH);
  
  // Calculates angle of compass, 
  // based on magnometer readings.
  float Heading_rad = atan2(Y_mag,X_mag);
  float Heading_deg = (Heading_rad*180/PI);
  
  
  // Maps values of impact sensor, proximity sensors, 
  // and compass to a string to be entered into labview.
  outValue1 = map(durationA,0,19280,65,90);
  outValue2 = map(durationC,0,19280,65,90);
  outValue3 = map(durationB,0,19280,65,90);
  outValue4 = map(Heading_deg,0,360,65,90);
  outValue5 = (buttonValue,0,1,65,90);
    
  // Prints string, to be input into labview,
  // on the serial monitor.
  Serial.write(outValue1);
  Serial.write(outValue2);
  Serial.write(outValue3);
  Serial.write(outValue4);
  // Prints a fifth value in the string,
  // if impact is made in front.
   if (buttonState == HIGH)
  {
   Serial.write(outValue5);
   }
  Serial.println("");
  Serial.print("[Speed: ");
  Serial.print(reqSpeed);
  Serial.println(" ]");
  Serial.print("[Steering Angle: ");
  Serial.print(reqSteer);
  Serial.println(" ]");
  
  delay(250);
}
  
// Determines values of the magnometer.
void readmagnetometer() 
{ 
 long magX_B1; 
 long magX_B2; 
 long magY_B1; 
 long magY_B2; 
 
 // Reads values from slave arduino.
 Wire.requestFrom(30,4); 
 while(Wire.available()) 
 { 
 magX_B1 = Wire.read(); 
 magX_B2 = Wire.read(); 
 magY_B1 = Wire.read(); 
 magY_B2 = Wire.read(); 
 } 
 
 // Calculates XY coordinates of magnometer reading.
 X_mag = magY_B1*256 + magX_B2 - 32768 - 50; 
 Y_mag = magX_B1*256 + magY_B2 - 32768 - 225;    
}

 






