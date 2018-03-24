/*
  Analog Input
  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  writing the output to the console
  
*/
int sensorPin = 0;     // select the input pin for the analog pin
int sensorValue = 0;  // variable to store the value coming from the sensor
void setup() {
  //set up the output with the correct upload speed
  Serial.begin(115200);
  pinMode(0, INPUT); 
}
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  //float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(sensorValue);
  // print the value from the sensor to the console
  //Serial.println(sensorValue);
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}


