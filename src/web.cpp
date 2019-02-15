#include "web.h"
#include "measure.h"
#include "mqtt.h"


AsyncWebServer webServer(HTTP_PORT);

void webSetup() {
  webServer.addHandler(new SPIFFSEditor("admin", "admin"));

  // Prometheus metrics
  webServer.on("/metrics", HTTP_GET,
            [](AsyncWebServerRequest * request) {
              AsyncResponseStream *response = request->beginResponseStream("text/prometheus; version=0.4");

              response->print("# HELP temperature_c Temperature in celsius\n");
              response->print("# TYPE temperature_c gauge\n");
              response->printf("temperature_c{client=\"%s\"} %f\n\n", clientName.c_str(), temperature);

              response->print("# HELP humidity_p Relative humidity\n");
              response->print("# TYPE humidity_p gauge\n");
              response->printf("humidity_p{client=\"%s\"} %f\n\n", clientName.c_str(), humidity);

              if (hasPressure) {
                response->print("# HELP pressure_hpa Pressure in hPa\n");
                response->print("# TYPE pressure_hpa gauge\n");
                response->printf("pressure_hpa{client=\"%s\"} %f\n\n", clientName.c_str(), pressure);
              };

              response->print("# HELP wifi_rssi_dbm Received Signal Strength Indication, dBm\n");
              response->print("# TYPE wifi_rssi_dbm counter\n");
              response->printf("wifi_rssi_dbm{client=\"%s\"} %d\n\n", clientName.c_str(), WiFi.RSSI());

              response->print("# HELP heap_free_bytes Free heap in bytes\n");
              response->print("# TYPE heap_free_bytes gauge\n");
              response->printf("heap_free_bytes{client=\"%s\"} %d\n\n", clientName.c_str(), ESP.getFreeHeap());

              response->print("# HELP uptime_seconds Uptime in seconds\n");
              response->print("# TYPE uptime_seconds gauge\n");
              response->printf("uptime_seconds{} %f\n\n", ((double)millis())/1000.0);
              request->send(response);
            });

  webServer.begin();

};
