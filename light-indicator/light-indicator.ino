//Libraries
#include "DHT.h"
#include <Servo.h>

/* Simple test of the functionality of the photo resistor

Connect the photoresistor one leg to pin 0, and pin to +5V
Connect a resistor (around 10k, higher
values gives higher readings) from pin 0 to GND.

----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/

// Pin
#define DHTPIN 2
// Use DHT11 sensor
#define DHTTYPE DHT22
// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
int servoPin = 15;
Servo servo;
int angle = 0;   // servo position in degrees
int photocellPin = 0; //define a pin for Photo resistor
void setup() {
  Serial.begin(112500); //begin serial communication
  dht.begin(); // Initializing DHT22 sensor
  servo.attach(servoPin); // Attaching Servo to control wire
  pinMode(0, INPUT); //light sensor
  pinMode(2, INPUT); // temp&humidity sensor
  pinMode(15, OUTPUT); //servo
}
void loop() {
  int photoValue = analogRead(photocellPin);
  if (photoValue < 800) {
    angle = 180;
  } else {
    angle = 0;
  }
  // Reading temperature and humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Display data
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.println("\n");
  Serial.println(photoValue);
  Serial.println("\n");
  servo.write(angle);
  delay(2000);
}

