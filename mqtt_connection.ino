#include <PubSubClient.h>
#include <WiFiS3.h>
#include <TimeLib.h>
#include <cstring>  // For memcpy

int msgCounter = 0;

unsigned long feedTime = 0; // Default to 1 hour
unsigned long feedInterval = 0; // Default to 1 hour
unsigned long lastFeedTime = 0;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void connectToMQTT() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqttCallback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("MUS2-24-FishFeeder")) {
      Serial.println("Connected to MQTT");
      mqttSubscribe();
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  }
}

void mqttLoop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();
}

void mqttSubscribe() {
  client.subscribe(MQTT_FEED_NOW);
  client.subscribe(MQTT_NEW_PLAN_TIME);
  client.subscribe(MQTT_NEW_PLAN_INTERVAL);
  client.subscribe(MQTT_LED_STATUS);
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];  // Create a buffer to hold the payload plus a null terminator
  memcpy(message, payload, length);  // Copy the payload to the buffer
  message[length] = '\0';  // Null-terminate the string

  Serial.print(String(topic));
  Serial.println(message);
  if (String(topic) == MQTT_FEED_NOW) {
    publishServoStatus("1");
    feedFish();
    publishServoStatus("0");
  } else if (String(topic) == MQTT_NEW_PLAN_TIME) {
    feedTime = atol(message) / 1000;  // Convert milliseconds to seconds
    lastFeedTime = 0;
  } else if (String(topic) == MQTT_NEW_PLAN_INTERVAL) {
    if (strcmp(message, "d") == 0) {
      feedInterval = atol(message) * 24 * 60 * 60 * 1000; // Convert day to milliseconds
    } else if (strcmp(message, "h") == 0) {
      feedInterval = atol(message) * 60 * 60 * 1000; // Convert hours to milliseconds
    } else if (strcmp(message, "m") == 0) {
      feedInterval = atol(message) * 60 * 1000; // Convert minutes to milliseconds
    }
  } else if(String(topic) == MQTT_LED_STATUS) {
    toggleLed(message);
  }
}

void publishLedStatus(const char* status) {
  client.publish(MQTT_LED_STATUS, status);
}

void publishServoStatus(const char* status) {
  client.publish(MQTT_SERVO_STATUS, status);
}

void publishTemperature(const char* temperature) {
  client.publish(MQTT_TEMPERATURE_STATUS, temperature);
}

void checkScheduledFeeding() {
  if (feedTime && !lastFeedTime && time_t(now()) >= feedTime) {
    publishServoStatus("1");
    feedFish();
    publishServoStatus("0");
    lastFeedTime = millis();
  } else  if (feedInterval && lastFeedTime && millis() - lastFeedTime >= feedInterval) {
    publishServoStatus("1");
    feedFish();
    publishServoStatus("0");
    lastFeedTime = millis();
  }
}