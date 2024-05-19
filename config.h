const int SERVO_PIN = 9;
const int TEMPERATURE_PIN = 2;
const int LED_PIN = 5;
const int SERVO_FEED_TIME_MS = 1000;

//-------------------
const char WIFI_SSID[] = ""; 
const char WIFI_PASS[] = "";

const char WIFI_SSID[] = ""; 
const char WIFI_PASS[] = "";

//------------------
const char MQTT_SERVER[] = "broker.hivemq.com";
const int MQTT_PORT = 1883;

const char BASE_TOPIC_NAME[] = "fishFeeder";
const char MQTT_LED_STATUS[] = "fishFeeder/light";
const char MQTT_FEED_NOW[] = "fishFeeder/feedNow";
const char MQTT_NEW_PLAN_TIME[] = "fishFeeder/newPlanTime";
const char MQTT_NEW_PLAN_INTERVAL[] = "fishFeeder/newPlanInterval";
const char MQTT_SERVO_STATUS[] = "fishFeeder/motorStatus";
const char MQTT_TEMPERATURE_STATUS[] = "fishFeeder/temperature";
