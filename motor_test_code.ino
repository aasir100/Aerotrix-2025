// Define motor control pins
const int in1 = 2;  // Control pin 1 for Motor A
const int in2 = 3;  // Control pin 2 for Motor A

const int in3 = 4;  // Control pin 1 for Motor B
const int in4 = 5;  // Control pin 2 for Motor B

void setup() {
  // Set all motor control pins as OUTPUT
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Test Motor A forward
  Serial.println("Motor A: Forward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(3000); // Run for 3 seconds

  // Stop Motor A
  Serial.println("Motor A: Stop");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000); // Wait for 2 seconds

  // Test Motor A reverse
  Serial.println("Motor A: Reverse");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(3000); // Run for 3 seconds

  // Stop Motor A
  Serial.println("Motor A: Stop");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000); // Wait for 2 seconds

  // Test Motor B forward
  Serial.println("Motor B: Forward");
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(3000); // Run for 3 seconds

  // Stop Motor B
  Serial.println("Motor B: Stop");
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000); // Wait for 2 seconds

  // Test Motor B reverse
  Serial.println("Motor B: Reverse");
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(3000); // Run for 3 seconds

  // Stop Motor B
  Serial.println("Motor B: Stop");
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000); // Wait for 2 seconds
}