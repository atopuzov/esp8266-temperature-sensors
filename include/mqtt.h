#pragma once

#ifndef MY_MQTT_H
#define MY_MQTT_H
/* #include <WiFiClientSecure.h> */
#include <WiFiClientSecureBearSSL.h>

#include <PubSubClient.h>

void mqttReconnect();
void mqttSetup();

extern bool configuredMQTT;
extern PubSubClient mqttClient;
extern String clientName;

extern char mqttServer[];
extern char mqttUsername[];
extern char mqttPassword[];
extern char mqttTopic[];
extern int mqttPort;
#endif
