// Include the necessary libraries for ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "J7 pro";
const char* password = "77777777";
const char* serverEndPoin = "http://localhost:7080/traficData"



// Define GPIO pins for ESP8266 NodeMCU board
const int D0 = 16;  // GPIO 16
const int D1 = 5;   // GPIO 5
const int D2 = 4;   // GPIO 4
const int D3 = 0;   // GPIO 0
const int D4 = 2;   // GPIO 2
const int D5 = 14;  // GPIO 14
const int D6 = 12;  // GPIO 12
const int D7 = 13;  // GPIO 13
const int D8 = 15;  // GPIO 15
const int rx = 3    // GPIO 3 -> D9
const int tx = 1    // GPIO 1 -> d10


// Define the pins for the first ultrasonic sensor
const int trigPinA1 = D0;   // Trigger pin for sensor 1
const int echoPinA1 = D1;   // Echo pin for sensor 1

// Define the pins for the second ultrasonic sensor
const int trigPinA2 = D2;   // Trigger pin for sensor 2
const int echoPinA2 = D3;   // Echo pin for sensor 2

// Define the pins for the third ultrasonic sensor
const int trigPinB1 = D4;   // Trigger pin for sensor 2
const int echoPinB1 = D5;   // Echo pin for sensor 2

// Define the pins for the fourth ultrasonic sensor
const int trigPinB2 = D6;   // Trigger pin for sensor 2
const int echoPinB2 = D7;   // Echo pin for sensor 2

// Define LED pins
const int redLED = rx;     // Red LED pin
// const int yellowLED = D8;  // Yellow LED pin
const int greenLED = tx;   // Green LED pin

void setup() {
  // Serial communication setup
//   Serial.begin(9600);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("connecting to wifi");
    }
    Serial.println("Connected to wifi");

  // Set up the pins for the first ultrasonic sensor
  pinMode(trigPinA1, OUTPUT);
  pinMode(echoPinA1, INPUT);

  // Set up the pins for the second ultrasonic sensor
  pinMode(trigPinA2, OUTPUT);
  pinMode(echoPinA2, INPUT);

  // Set up the pins for the second ultrasonic sensor
  pinMode(trigPinB1, OUTPUT);
  pinMode(echoPinB1, INPUT);

  // Set up the pins for the second ultrasonic sensor
  pinMode(trigPinB2, OUTPUT);
  pinMode(echoPinB2, INPUT);

  // Set up LED pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Measure distance for the first sensor
  int fullTrafficA = 0;
  int partialTrafficA = 0;
  int noTrafficA = 0;

  int fullTrafficB = 0;
  int partialTrafficB = 0;
  int noTrafficB = 0;

  int distanceA1 = getDistance(trigPinA1, echoPinA1);
  int distanceA2 = getDistance(trigPinA2, echoPinA2);

  int distanceB1 = getDistance(trigPinB1, echoPinB1);
  int distanceB2 = getDistance(trigPinB2, echoPinB2);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" M");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" M");

  if (distanceA1 < 5 && distanceA2 < 5) {
    fullTrafficA = 1;
  } else if (distanceA1 < 5 && distanceA2 > 5) {
    partialTrafficA = 1;
  } else {
    noTrafficA = 1;
  }

  if (distanceB1 < 5 && distanceB2 < 5) {
    fullTrafficA = 1;
  } else if (distanceB1 < 5 && distanceB2 > 5) {
    partialTrafficA = 1;
  } else {
    noTrafficA = 1;
  }

  // Control LEDs based on traffic conditions
  if (fullTraffic) {
    digitalWrite(redLED, HIGH);    // Turn on red LED
    digitalWrite(yellowLED, LOW);  // Turn off yellow LED
    digitalWrite(greenLED, LOW);   // Turn off green LED
    Serial.println("Full traffic");
  }
  if (partialTraffic) {
    digitalWrite(redLED, LOW);     // Turn off red LED
    digitalWrite(yellowLED, HIGH);  // Turn on yellow LED
    digitalWrite(greenLED, LOW);    // Turn off green LED
    Serial.println("Partial traffic");
  }
  if (noTraffic) {
    digitalWrite(redLED, LOW);     // Turn off red LED
    digitalWrite(yellowLED, LOW);   // Turn off yellow LED
    digitalWrite(greenLED, HIGH);   // Turn on green LED
    Serial.println("No traffic");
  }

  // Add a delay between readings
  delay(500);
}

// Function to get distance for a given sensor
int getDistance(int trigPin, int echoPin) {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin to calculate distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Calculate distance in centimeters

  return distance / 100;
}
