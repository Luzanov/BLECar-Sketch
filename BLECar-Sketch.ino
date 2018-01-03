#include <SoftwareServo.h>

#define PIN_SERVO A3
#define PIN_PWMA 9
#define PIN_AIN1 7
#define PIN_AIN2 8
#define PIN_STBY 6

SoftwareServo servo;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_STBY, OUTPUT);
  pinMode(PIN_PWMA, OUTPUT);
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  servo.attach(PIN_SERVO);
}

void loop() {
  if (Serial.available() >= 4) {
    int byte1 = Serial.read();
    int byte2 = Serial.read();
    int byte3 = Serial.read();
    int byte4 = Serial.read();

    int direction = byte2 << 8 | byte1;
    int speed = byte4 << 8 | byte3;
    
    // Handle direction
    if (direction != -1) {
      servo.write(direction);
    }

    // Handle speed
    digitalWrite(PIN_STBY, speed == 0 ? LOW : HIGH);

    if (speed != 0) {
      digitalWrite(PIN_AIN1, speed > 0 ? LOW : HIGH);
      digitalWrite(PIN_AIN2, speed > 0 ? HIGH : LOW);
      analogWrite(PIN_PWMA, abs(speed));
    }
  }
  SoftwareServo::refresh();
}
