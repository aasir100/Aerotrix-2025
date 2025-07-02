#include <Servo.h>          // Servo motor library
#include <NewPing.h>        // Ultrasonic sensor library

// Motor control pins
const int LeftMotorForward = 2;   // D2
const int LeftMotorBackward = 3;  // D3
const int RightMotorForward = 4;  // D4
const int RightMotorBackward = 10; // D10

// Enable pins for motor speed control
const int LeftMotorEnable = 6;    // D6 (PWM)
const int RightMotorEnable = 5;  // D5 (PWM)

// Ultrasonic sensor pins
#define trig_pin A1 // A1 (analog pin 1)
#define echo_pin A2 // A2 (analog pin 2)
#define maximum_distance 200 // Maximum distance in cm

boolean goesForward = false; // Tracks forward movement
int distance = 100; // Stores distance measured by the sensor

NewPing sonar(trig_pin, echo_pin, maximum_distance); // Ultrasonic sensor object
Servo servo_motor; // Servo motor object

void setup() {

  // Set motor control pins as outputs
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Set enable pins as outputs
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);

  // Attach servo to pin D9 and set it to 90 degrees (center position)
  servo_motor.attach(9); // D9
  servo_motor.write(90); // Center position
  delay(2000);

  // Set motor speed to 160 (out of 255)
  analogWrite(LeftMotorEnable, 100);
  analogWrite(RightMotorEnable, 100);

  // Initialize distance measurement
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  // If an obstacle is detected within 30 cm
  if (distance <= 30) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);

    // Measure distance to the right and left
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    // Decide which direction to turn based on distance
    if (distance >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward(); // If no obstacle, move forward
  }
  distance = readPing(); // Update distance measurement
}

int lookRight() {
  servo_motor.write(45); // Rotate servo to 45 degrees (right)
  delay(500);
  int distance = readPing(); // Measure distance
  delay(100);
  servo_motor.write(90); // Return servo to center (90 degrees)
  return distance;
}

int lookLeft() {
  servo_motor.write(135); // Rotate servo to 135 degrees (left)
  delay(500);
  int distance = readPing(); // Measure distance
  delay(100);
  servo_motor.write(90); // Return servo to center (90 degrees)
  return distance;
}

int readPing() {
  delay(70); // Wait for sensor stability
  int cm = sonar.ping_cm(); // Get distance in cm
  if (cm == 0) {
    cm = 250; // If no object is detected, set distance to 250 cm (maximum)
  }
  return cm;
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

void moveBackward() {
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(250);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(250);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}