//Libraries
//DHT Sensor (Temperature and Humidity)
#include "DHT.h"
//Wifi Library for ESP8266
#include "ESP8266WiFi.h"
// Servo Library
#include <Servo.h>
// WiFi parameters
const char* ssid = "Puppet Guest";
const char* password = "argon4949";
//Defining constants
// Pin
#define DHTPIN 2
// DHT22 sensor
#define DHTTYPE DHT22
// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
// Host of the HTTP
const char* host = "dweet.io";
//Indicate which pin on the board
int servoPin = 15;
//Create an instance of a Servo
Servo servo;
//beginning angle for Servo
int angle = 0;   // servo position in degrees
//Indicate which pin on the board
int photocellPin = 0;
void setup() {
  Serial.begin(112500);
  
  // Initializing DHT22 sensor
  dht.begin();
  // Attaching Servo to control wire
  servo.attach(servoPin);
  //Connect pin 0 as input for light sensor
  pinMode(0, INPUT); //light sensor
  
  //Connect 2 as input for temp&humidity sensor
  pinMode(2, INPUT); // temp&humidity sensor
  //Connect 15 as output for Servo
  pinMode(15, OUTPUT); //servo
  // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}
void loop() {
  
  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  //Error message if connection failed
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  //Read value from photocell
  int photoValue = analogRead(photocellPin);
   // Reading temperature and humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  //If the value of the photcell reads below 900, indicating change in light
  if (photoValue < 900 || t > 31) {
    //Turn the Servo a full rotation
    angle = 180;
  } else {
    angle = 0;
    }
  // This will send the request to the server
  // Include the values of the temperature, humidity and light sensor
  client.print(String("GET /dweet/for/wwc18iotteam7?temperature=") + String(t) + "&humidity=" + String(h) + "&lumens=" + String(photoValue) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
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
  //Move the Servo to its new angle!
  servo.write(angle);
  //Delay the sensor 2 second 
  delay(2000);
}

