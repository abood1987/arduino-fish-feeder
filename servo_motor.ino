#include <Servo.h>

Servo servo;  // create servo object to control a servo

void attachServo() {
  servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  pinMode(SERVO_PIN, INPUT);
}

void detachServo() {
  servo.detach();
}

void feedFish() {
  // solve buzz problem by switching the servo off after moveing it.
  pinMode(SERVO_PIN, OUTPUT);
  servo.writeMicroseconds(1000);
  delay(SERVO_FEED_TIME_MS);
  servo.writeMicroseconds(1500);
  pinMode(SERVO_PIN, INPUT);
}