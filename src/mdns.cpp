#include "mdns.h"
#include "mqtt.h"
#include "web.h"

extern String clientName;

// Configure MQTT server from mDNS
bool mdnsDiscoverMqtt () {
  Serial.println(F("Sending mDNS Query"));

  int numberOfMQTTHosts = MDNS.queryService("mqtt", "tcp");
  if (numberOfMQTTHosts < 1) {
    Serial.println(F("No MQTT servers found."));
    return false;
  };

  // Returns the first found MQTT server
  // strcpy(mqttServer, MDNS.IP(0));
  mqttPort = MDNS.port(0);
  return true;
};

// Sets up the mDNS stack
void mdnsSetup() {
  if (!MDNS.begin(clientName.c_str())) {
    Serial.println(F("Error setting up mDNS"));
  } else {
    Serial.println(F("mDNS setup finished"));
  };

  MDNS.addService(F("prometheus-http"), "tcp", HTTP_PORT);
  MDNS.addService(F("http"), "tcp", HTTP_PORT);
}
