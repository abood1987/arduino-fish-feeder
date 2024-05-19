#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setupTimeClient() {
  timeClient.begin();
  timeClient.setTimeOffset(3600);  // Set your time zone offset in seconds
}

long getSeconds() {
  timeClient.update();
  return timeClient.getEpochTime();
}