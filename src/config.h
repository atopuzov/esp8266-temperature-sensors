#pragma once

#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

#include "wifi.h"
#include "mqtt.h"

bool loadConfig();

#endif
