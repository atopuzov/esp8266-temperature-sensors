#include "ntp.h"

int timeZone = 0;
int minutesTimeZone = 0;
bool ntpSyncEventTriggered = false; // True if a time even has been triggered
NTPSyncEvent_t ntpEvent; // Last triggered event
bool ntpSyncStarted = false;

void processNtpSyncEvent (NTPSyncEvent_t ntpEvent) {
  if (ntpEvent) {
    Serial.print ("Time Sync error: ");

    if (ntpEvent == noResponse)
      Serial.println ("NTP server not reachable");
    else if (ntpEvent == invalidAddress)
      Serial.println ("Invalid NTP server address");

  } else {
    Serial.print ("Got NTP time: ");
    Serial.println (NTP.getTimeDateString (NTP.getLastNTPSync ()));
  }
}

void ntpStart() {
  NTP.begin ("pool.ntp.org", timeZone, true, minutesTimeZone);
  NTP.setInterval (63);
  ntpSyncStarted = true;
};

void ntpStop() {
  NTP.stop();
};

void ntpSetup() {
  NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
                        ntpEvent = event;
                        ntpSyncEventTriggered = true;
                      });
};
