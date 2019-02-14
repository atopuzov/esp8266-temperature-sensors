#include "mqtt.h"
// #include "cert.h"

bool configuredMQTT = false;

BearSSL::WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

char mqttServer[63]   = {0};
char mqttUsername[10] = {0};
char mqttPassword[20] = {0};
char mqttTopic[20]    = {0};
int  mqttPort         = 0;

unsigned long lastReconnectAttempt = 0;
// BearSSL::X509List cert(dst_root_ca_x3);


void mqttSetup() {
  // Faster but less secure ciphers
  std::vector<uint16_t> myCustomList = { BR_TLS_RSA_WITH_AES_256_CBC_SHA256, BR_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA, BR_TLS_RSA_WITH_3DES_EDE_CBC_SHA };
  wifiClient.setCiphers(myCustomList);

  // wifiClient.setTrustAnchors(&cert);
  wifiClient.setInsecure();
  mqttClient.setServer(mqttServer, mqttPort);
};

void mqttReconnect() {
  unsigned long now = millis();
  if (now - lastReconnectAttempt > 2000) {
    Serial.print(F("Attempting MQTT connection..."));
    if (mqttClient.connect(clientName.c_str(), mqttUsername, mqttPassword)) {
      Serial.println(F("connected"));
      lastReconnectAttempt = 0;
    } else {
      lastReconnectAttempt = now;
      Serial.print(F("failed, rc="));
      Serial.print(mqttClient.state());
      Serial.println(F(" try again in 2 seconds"));
    };
  };
};
