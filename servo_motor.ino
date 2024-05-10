#include <Servo.h>

Servo servo;  // create servo object to control a servo

void attachServo() {
  servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}

void detachServo() {
  servo.detach();
}

void feedFish() {
  servo.writeMicroseconds(1000);
  delay(SERVO_FEED_TIME_MS);
  servo.writeMicroseconds(1500);
}