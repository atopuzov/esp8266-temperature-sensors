#include "mdns.h"
#include "web.h"

extern String clientName;

// // Configure MQTT server from mDNS
// bool query_mdns (char *server, char *port) {
//   Serial.println("Sending mDNS Query");

//   int numberOfMQTTHosts = MDNS.queryService("mqtt", "tcp");
//   if (numberOfMQTTHosts < 1)
//     return false;

//   *server = MDNS.IP(0);
//   *port = MDNS.port(0);
//   return true;
// };

// Sets up the mDNS stack
void mdnsSetup() {
  if (!MDNS.begin(clientName.c_str())) {
    Serial.println("Error setting up mDNS");
  } else {
    Serial.println("mDNS setup finished");
  };

  MDNS.addService("prometheus-http", "tcp", HTTP_PORT);
  MDNS.addService("http", "tcp", HTTP_PORT);
}
