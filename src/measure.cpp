#include "measure.h"

// Temperature sensors supported
bool haveBME = false;
bool haveSHT = false;

// Sensor values
float temperature = 0.0;
float humidity    = 0.0;
float pressure    = 0.0;

bool hasPressure = false; // bme280 has pressure
int timestamp = 0;

BME280<> BMESensor;
SHT3X SHTSensor(0x45);

Ticker tempMeasureScheduler;
volatile bool measureTemperatureEventTriggered = false;

void sensorsSetup() {
  haveBME = hasPressure = BMESensor.begin();
  haveSHT = SHTSensor.get() == 0;

  takeMeasurement();
  // Every MEASURE_INTERVAL mark temperature measurment
  tempMeasureScheduler.attach(MEASURE_INTERVAL, []() {measureTemperatureEventTriggered = true;});
};

// Read temperature and humidity from ST30 sensor
bool measureSHT() {
  if (haveSHT) {
    SHTSensor.get();
    temperature = SHTSensor.cTemp;
    humidity    = SHTSensor.humidity;
    return true;
  };
  return false;
};

// Read temperature, humidity and pressure from BME280 sensor
bool measureBME() {
  if (haveBME) {
    BMESensor.refresh();
    temperature = BMESensor.temperature;
    humidity    = BMESensor.humidity;
    pressure    = BMESensor.pressure;
    return true;
  };
  return false;
};

// Record the measurements
bool takeMeasurement () {
  Serial.println(F("Measuring temperature:"));
  if (measureSHT() || measureBME()) {
    timestamp = now();
    Serial.print(F("Temperature in Celsius: "));
    Serial.println(temperature);
    Serial.print(F("Relative Humidity     : "));
    Serial.println(humidity);
    if (hasPressure) {
      Serial.print(F("Pressure in hPa       : "));
      Serial.println(pressure / 100.0F);
    }
    return true;
  };
  return false;
}
