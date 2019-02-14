#pragma once

#ifndef MY_NTP_H
#define MY_NTP_H

#include <NtpClientLib.h>

void ntpSetup();
void ntpStart();
void ntpStop();
void processNtpSyncEvent (NTPSyncEvent_t ntpEvent);

extern NTPSyncEvent_t ntpEvent;
extern bool ntpSyncStarted;
extern bool ntpSyncEventTriggered;
#endif
