#pragma once

#ifndef MY_MEASURE_H
#define MY_MEASURE_H

#include <Wire.h>
#include <TimeLib.h>
#include <Ticker.h>

#include <BME280_t.h>
#include <WEMOS_SHT3X.h>

#define MEASURE_INTERVAL 10

bool takeMeasurement ();
void sensorsSetup ();

extern float temperature;
extern float humidity;
extern float pressure;
extern bool hasPressure;
extern int timestamp;

extern volatile bool measureTemperatureEventTriggered;

#endif
