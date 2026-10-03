/*
  Line Following Robot Car
  Fab Lab (ECLER1VS103), Semester II

  Team:
  Soham Patil
  Ved Patil
  Tanmay Pawar
  Reva Phalke

  Sensor pins from project presentation:
    Left IR  -> D2
    Right IR -> D3

  Example motor-driver input pins from presentation:
    D5, D6, D9, D10

  IMPORTANT:
  IR modules can use different output polarities. Set LINE_DETECTED
  after checking your actual sensor module.

  The presentation states:
    Left = 0, Right = 0 -> move straight

  The remaining turn/search behavior below is a practical implementation
  assumption for a two-sensor line follower and should be calibrated
  on the actual robot.
*/

const int LEFT_SENSOR_PIN  = 2;
const int RIGHT_SENSOR_PIN = 3;

// L298N/L293D-style input pins.
// Change these if your physical wiring is different.
const int LEFT_MOTOR_IN1  = 5;
const int LEFT_MOTOR_IN2  = 6;
const int RIGHT_MOTOR_IN1 = 9;
const int RIGHT_MOTOR_IN2 = 10;

// Change to HIGH if your IR module reports HIGH on the line.
const int LINE_DETECTED = LOW;

const int BASE_SPEED = 150;
const int TURN_SPEED = 190;
const int SEARCH_SPEED = 120;

void setup() {
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  Serial.begin(9600);
  stopMotors();
}

void loop() {
  int leftState = digitalRead(LEFT_SENSOR_PIN);
  int rightState = digitalRead(RIGHT_SENSOR_PIN);

  bool leftOnLine = (leftState == LINE_DETECTED);
  bool rightOnLine = (rightState == LINE_DETECTED);

  Serial.print("Left: ");
  Serial.print(leftState);
  Serial.print("  Right: ");
  Serial.println(rightState);

  // Matches the presentation's documented straight condition:
  // Left = 0 and Right = 0 -> move straight.
  if (leftState == LOW && rightState == LOW) {
    driveForward(BASE_SPEED, BASE_SPEED);
  }
  // Practical two-sensor interpretation:
  // left sensor sees line -> steer left.
  else if (leftOnLine && !rightOnLine) {
    driveForward(90, TURN_SPEED);
  }
  // right sensor sees line -> steer right.
  else if (!leftOnLine && rightOnLine) {
    driveForward(TURN_SPEED, 90);
  }
  // Both sensors off the line -> search/stop behavior.
  else {
    driveForward(SEARCH_SPEED, -SEARCH_SPEED);
  }

  delay(5);
}

void driveForward(int leftSpeed, int rightSpeed) {
  setMotor(LEFT_MOTOR_IN1, LEFT_MOTOR_IN2, leftSpeed);
  setMotor(RIGHT_MOTOR_IN1, RIGHT_MOTOR_IN2, rightSpeed);
}

void setMotor(int in1, int in2, int speedValue) {
  speedValue = constrain(speedValue, -255, 255);

  if (speedValue > 0) {
    analogWrite(in1, speedValue);
    analogWrite(in2, 0);
  } else if (speedValue < 0) {
    analogWrite(in1, 0);
    analogWrite(in2, -speedValue);
  } else {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
  }
}

void stopMotors() {
  setMotor(LEFT_MOTOR_IN1, LEFT_MOTOR_IN2, 0);
  setMotor(RIGHT_MOTOR_IN1, RIGHT_MOTOR_IN2, 0);
}
