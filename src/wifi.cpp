#include "wifi.h"

ESP8266WiFiMulti wifiMulti;
bool wifiConnected = false;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

void wifiConnectCallback(const WiFiEventStationModeGotIP& event) {
  Serial.print(F("\nWiFi connected to: "));
  Serial.println(WiFi.SSID());
  Serial.print(F("IP address       : "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Mac address      : "));
  Serial.println(WiFi.macAddress());
  wifiConnected = true;
}

void wifiDisconnectCallback(const WiFiEventStationModeDisconnected& event) {
  Serial.println(F("Wifi disconnected."));
  wifiConnected = false;
}

// Sets up the WiFi connection
void wifiSetup()
{
  wifiConnectHandler    = WiFi.onStationModeGotIP(wifiConnectCallback);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(wifiDisconnectCallback);
  WiFi.mode(WIFI_STA);
}

void wifiConnect() {
  wifiMulti.run();
}
