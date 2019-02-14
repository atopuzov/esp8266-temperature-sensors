#pragma once

#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

void wifiConnect();
void wifiSetup();

extern ESP8266WiFiMulti wifiMulti;
extern bool wifiConnected;
#endif
