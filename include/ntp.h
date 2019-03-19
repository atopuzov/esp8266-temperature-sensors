#pragma once

#ifndef MY_NTP_H
#define MY_NTP_H

void ntpSetup();

extern bool ntpSyncStarted;
bool ntpTimeSynced();;
#endif
