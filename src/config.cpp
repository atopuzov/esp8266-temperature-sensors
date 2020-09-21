#include "config.h"

bool loadConfig() {
  if (!SPIFFS.begin()) {
    Serial.println(F("Failed to mount file system."));
    return false;
  }

  File configFile = SPIFFS.open(F("/config.json"), "r");
  if (!configFile) {
    Serial.println(F("Failed to open config file."));
    return false;
  }

  DynamicJsonDocument json(1024);
  auto error = deserializeJson(json, configFile);

  if (error) {
    Serial.println(F("Failed to parse config file."));
    return false;
  }

  // Load wifi configuration
  auto wifi = json["wifi"];

  for (unsigned int i = 0; i < wifi.size(); i++) {
    const char* ssid      = wifi[i]["ssid"];
    const char* password  = wifi[i]["password"];
    wifiMulti.addAP(ssid, password);
  };

  // Load mqtt configuration
  strcpy(mqttUsername, json["mqtt"]["username"]);
  strcpy(mqttPassword, json["mqtt"]["password"]);
  strcpy(mqttServer,   json["mqtt"]["server"]);
  strcpy(mqttTopic,    json["mqtt"]["topic"]);
  mqttPort =           json["mqtt"]["port"];

  configFile.close();
  return true;
}
