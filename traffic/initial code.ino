// Define the pins for the first ultrasonic sensor
const int trigPin1 = 9;   // Trigger pin for sensor 1
const int echoPin1 = 10;  // Echo pin for sensor 1

// Define the pins for the second ultrasonic sensor
const int trigPin2 = 11;  // Trigger pin for sensor 2
const int echoPin2 = 12;  // Echo pin for sensor 2



void setup() {
  // Serial communication setup
  Serial.begin(9600);

  // Set up the pins for the first ultrasonic sensor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Set up the pins for the second ultrasonic sensor
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  // Measure distance for the first sensor
  int fullTrafic = 0;
  int partialTrafic = 0;
  int noTrafic = 0;
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" M");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" M");

  if (distance1 < 5 && distance2 < 5) {
    fullTrafic = 1;
  } else if (distance1 < 5 && distance2 > 5) {
    partialTrafic = 1;
  } else {
    noTrafic = 1;
  }
  if (fullTrafic) {
    Serial.println("full trafic");
  }
  if (partialTrafic) {
    Serial.println("PARTIAL trafic");
  }
  if (noTrafic) {
    Serial.println("NO trafic");
  }



  // Measure distance for the second sensor


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



// Define the pins for the Full trafic LED
const int fullTraficLedPin = 5 // D1 	GPIO 5

// Define the pins for the parialy trafic LED
const int parialyTraficLedPin = 4 // D2 GPIO 4

// Define the pins for the no trafic LED
const int noTraficLedPin = 0 // D3 GPIO 0