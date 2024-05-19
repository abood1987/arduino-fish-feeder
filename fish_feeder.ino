#include "config.h"

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  connectToMQTT();
  setupTimeClient();
  attachServo();
  connectLed();
}

void loop() {
  mqttLoop();

  float temp = readTemperature();
  if (!isnan(temp)) {
    char tempStr[8];
    dtostrf(temp, 1, 2, tempStr);
    publishTemperature(tempStr);
  }

  delay(2000); // Delay between temperature readings
}
