#include <ESP8266mDNS.h>

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
void setup_mdns() {
  if (!MDNS.begin(clientName.c_str())) {
    Serial.println("Error setting up mDNS");
  } else {
    Serial.println("mDNS setup finished");
  };
}
