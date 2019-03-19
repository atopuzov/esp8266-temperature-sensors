#include "ntp.h"
#include <ESP8266WiFi.h>

bool ntpSyncStarted = false;

void ntpSetup() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov", "time.windows.com");
};

bool ntpTimeSynced() {
  time_t now = time(nullptr);
  return now > 1546300800; // 2019-01-01
}
