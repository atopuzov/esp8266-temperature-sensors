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

StaticJsonDocument<200> jsonDoc;
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
  jsonDoc["client"] = clientName;

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
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidity"] = humidity;
  if (hasPressure) {
    jsonDoc["pressure"] = pressure;
  };
  // JsonData["timestamp"] = timestamp;

  serializeJson(jsonDoc, JSONmessageBuffer);

  blink_led();
  Serial.printf("Publishing to MQTT: %s\n", JSONmessageBuffer);
  mqttClient.publish(mqttTopic, JSONmessageBuffer);
};

void loop() {
  if (not wifiConnected)
    wifiConnect();

  // Ticker marked
  bool measured = false;
  // if (measureTemperatureEventTriggered) {
  //   measured = takeMeasurement();
  //   measureTemperatureEventTriggered = false;
  // };
  measured = takeMeasurement();

  if (wifiConnected) {
    MDNS.update();

    if (ntpTimeSynced() && !mqttClient.connected()) {
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
