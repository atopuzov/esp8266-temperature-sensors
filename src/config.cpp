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

  size_t size = configFile.size();
  // if (size > 1024) {
  //   Serial.println("Config file size is too large.");
  //   return false;
  // }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println(F("Failed to parse config file."));
    return false;
  }

  // Load wifi configuration
  JsonArray& wifi = json["wifi"];

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

  return true;
}
