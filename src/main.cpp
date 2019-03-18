/*
 */
#include "Arduino.h"

#include "config.h"
#include "wifi.h"
#include "ntp.h"
#include "measure.h"
#include "mqtt.h"
#include "web.h"
#include "mdns.h"

void blink_led();
String macToStr(const uint8_t* mac);

String clientName = "";

StaticJsonBuffer<200> jsonBuffer;
JsonObject& JsonData = jsonBuffer.createObject();
char JSONmessageBuffer[120];

void setup()
{
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  unsigned char mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  JsonData["client"] = clientName;

  loadConfig();

  wifiSetup();
  ntpSetup();
  mqttSetup();
  webSetup();
  mdnsSetup();
  sensorsSetup();
};

// Publishes the measured temperature and humidity to MQTT
void publishTemperature () {
  JsonData["temperature"] = temperature;
  JsonData["humidity"] = humidity;
  if (hasPressure) {
    JsonData["pressure"] = pressure;
  };
  // JsonData["timestamp"] = timestamp;
  JsonData.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  blink_led();
  Serial.printf("Publishing to MQTT: %s\n", JSONmessageBuffer);
  mqttClient.publish(mqttTopic, JSONmessageBuffer);
};

void loop() {
  if (not wifiConnected)
    wifiConnect();

  if (not ntpSyncStarted && wifiConnected)
    ntpStart();

  if (ntpSyncStarted && not wifiConnected)
    ntpStop();


  if (ntpSyncEventTriggered) {
    processNtpSyncEvent (ntpEvent);
    ntpSyncEventTriggered = false;
  };

  // Ticker marked
  bool measured = false;
  if (measureTemperatureEventTriggered) {
    measured = takeMeasurement();
    measureTemperatureEventTriggered = false;
  };

  if (wifiConnected) {
    MDNS.update();

    if (!mqttClient.connected()) {
      mqttReconnect();
    } else {
      mqttClient.loop(); // MQTT loop

      if (measured) {
        publishTemperature();
      };
    };
  };
}

// Blinks the builtin LED
void blink_led() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i)
    result += String(mac[i], 16);
  return result;
}
