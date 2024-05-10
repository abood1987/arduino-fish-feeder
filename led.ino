void connectLed() {
  pinMode(LED_PIN, OUTPUT);
}


void toggleLed(const char* status) {
  if (strcmp(status, "1") == 0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
