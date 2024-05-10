#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);

void setupDHT() {
  sensors.begin();
}

float readTemperature() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  return sensors.getTempCByIndex(0);
}

