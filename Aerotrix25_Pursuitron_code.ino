#include <Servo.h>

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

// Servo motor pin
#define servo_pin 9 // D9

// Threshold distances
const int pursuitThreshold = 30; // Pursue objects within 30 cm
const int tooCloseDistance = 10; // Move back if closer than 10 cm

// Servo angles for scanning (including 90 degrees for front)
const int scanAngles[] = {30, 60, 90, 120, 150};

Servo servo_motor; // Servo motor object

void setup() {
  // Initialize motor control pins as outputs
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Attach servo to pin D9 and set it to 90 degrees (center position)
  servo_motor.attach(servo_pin);
  servo_motor.write(90); // Center position
  delay(1000);

  // Set motor speed to 100/255 using PWM
  analogWrite(LeftMotorEnable, 100);
  analogWrite(RightMotorEnable, 100);
}

void loop() {
  int distance = measureDistance(); // Measure distance in front

  // If an object is within 30 cm, pursue it
  if (distance <= pursuitThreshold && distance > 0) {
    // If too close, move back until 10 cm
    if (distance < tooCloseDistance) {
      moveBackward();
      while (measureDistance() < tooCloseDistance) {
        delay(10); // Keep moving back until 10 cm is reached
      }
      moveStop();
    } else {
      moveForward(); // Otherwise, move forward
    }
  } else {
    servo_motor.write(90);
    moveStop();
    // If no object is detected, scan left and right
    int detectedAngle = scanForObject();
    if (detectedAngle != -1) {
      // Turn towards the detected angle and align with the object
      alignWithObject(detectedAngle);
    }
  }
  delay(50); // Small delay for stability
}
// Function to measure distance using ultrasonic sensor
int measureDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  return pulseIn(echo_pin, HIGH) * 0.0344 / 2; // Convert to cm
}

// Function to scan for objects at 30°, 60°, 90°, 120°, and 150°
int scanForObject() {
  for (int i = 0; i < 5; i++) {
    servo_motor.write(scanAngles[i]); // Move servo to the current angle
    delay(500); // Wait for the servo to stabilize
    int distance = measureDistance(); // Measure distance at this angle
    if (distance <= pursuitThreshold && distance > 0) {
      return scanAngles[i]; // Return the angle where an object is detected
    }
  }
  servo_motor.write(90); // Return servo to center position
  return -1; // No object detected
}

// Function to align the bot with the detected object
void alignWithObject(int targetAngle) {
  while (true) {
    // Turn towards the detected angle
    if (targetAngle < 90) {
      turnRight(); // Turn right if the target angle is less than 90 degrees
    } else if (targetAngle > 90) {
      turnLeft(); // Turn left if the target angle is greater than 90 degrees
    }

    // Move forward for 500 milliseconds
    moveForward();
    delay(500);
    moveStop();

    // Scan again to check if the object is now at 90 degrees
    int newDistance = measureDistance();
    if (newDistance <= pursuitThreshold && newDistance > 0) {
      // If the object is now centered, break the loop
      if (servo_motor.read() == 90) {
        break;
      }
    }

    // Update the target angle based on the new scan
    targetAngle = scanForObject();
    if (targetAngle == -1) {
      break; // Exit if no object is detected
    }
  }
}
// Motor control functions
void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
}
void moveBackward() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}
void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void turnLeft() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  delay(250); // Adjust delay for turning angle
  moveStop();
}
void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  delay(250); // Adjust delay for turning angle
  moveStop();
}
