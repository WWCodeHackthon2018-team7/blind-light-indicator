#include <Servo.h> 
int servoPin = 15;
Servo servo;   
int angle = 0;   // servo position in degrees
int photocellPin = 0;
  
void setup() { 
  Serial.begin(112500);
  servo.attach(servoPin); 
  pinMode(0, INPUT);
  pinMode(15, OUTPUT);
} 
  
void loop() { 
  int photoValue = analogRead(photocellPin); 
  int newAngle = reading/3 - 100;
  // open blinds = 180, less light = 
  // closed blinds = 0, more light, close the blinds at integer 700
 
  Serial.print(photoValue);
  Serial.print("Angle" + newAngle);
  Serial.print("\n");
  
  servo.write(newAngle);  
           
  delay(100);  
} 


