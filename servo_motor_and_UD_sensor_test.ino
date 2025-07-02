#include <Servo.h>

// Define pins for the ultrasonic sensor
const int trigPin = A1;  // Trig pin connected to analog pin 1
const int echoPin = A2; // Echo pin connected to analog pin 2

// Define servo pin
const int servoPin = 9; // Servo signal pin connected to digital pin 9

Servo myServo; // Create a servo object

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo to the servo pin
  myServo.attach(servoPin);
}

void loop() {
  // Move servo to 45° and measure distance
  myServo.write(45);
  delay(2000); // Wait for 2 seconds
  int distance45 = measureDistance();
  Serial.print("Distance at 45°: ");
  Serial.print(distance45);
  Serial.println(" cm");

  // Move servo to 90° and measure distance
  myServo.write(90);
  delay(2000); // Wait for 2 seconds
  int distance90 = measureDistance();
  Serial.print("Distance at 90°: ");
  Serial.print(distance90);
  Serial.println(" cm");

  // Move servo to 135° and measure distance
  myServo.write(135);
  delay(2000); // Wait for 2 seconds
  int distance135 = measureDistance();
  Serial.print("Distance at 135°: ");
  Serial.print(distance135);
  Serial.println(" cm");
}

// Function to measure distance using the ultrasonic sensor
int measureDistance() {
  long duration;

  // Send a short pulse to the Trig pin to start the measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the Echo pin to get the pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  int distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/µs

  return distance;
}
