// include Arduino library to use Arduino function in cpp files
#include <Arduino.h>
// include library to configure I2C port
#include <Wire.h>

// include specific libraries:
// `Grove - Air quality sensor` by Seeed Studio (latest version on `master branch` or
// commit hash `58e4c0bb5ce1b0c9b8aa1265e9f726025feb34f0` from `https://github.com/Seeed-Studio/Grove_Air_quality_Sensor`).
// You cannot use the one published on ArduinoIDE Library Manager, because it's outdated and not compatibile with ESP32 devices.
#include "Air_Quality_Sensor.h"

#define AIR_QUALITY_PIN 4 // Digital pin connected to the airQuality sensor
AirQualitySensor sensor(AIR_QUALITY_PIN);
// global variable used to store the current value read by the sensor
int current_air_value = -1; // initial uninitialized value

void airquality_init_sensor() {
  Serial.println("airquality_init_sensor - called");
  if (sensor.init()) {
    Serial.println("airquality_init_sensor - sensor initialized successfully!");
  } else {
    Serial.println("airquality_init_sensor - cannot initialize sensor");
  }
}

int airquality_get_value() {
  Serial.println("airquality_get_value - called");
  int new_value = -1; // initial uninitialized value
  int quality = sensor.slope();
  Serial.print("airquality_get_value - sensor value: ");
  Serial.println(sensor.getValue());
  if (quality == AirQualitySensor::FORCE_SIGNAL) {
      Serial.println("airquality_get_value - Very high pollution! Force signal active.");
      new_value = AirQualitySensor::FORCE_SIGNAL;
  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
      Serial.println("airquality_get_value - High pollution!");
      new_value = AirQualitySensor::HIGH_POLLUTION;
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
      Serial.println("airquality_get_value - Low pollution!");
      new_value = AirQualitySensor::LOW_POLLUTION;
  } else if (quality == AirQualitySensor::FRESH_AIR) {
      Serial.println("airquality_get_value - Fresh air.");
      new_value = AirQualitySensor::FRESH_AIR;
  }
  if (current_air_value != new_value && new_value != -1) {
    current_air_value = new_value;
  }
  return new_value;
}

int airquality_get_prev_value() {
  return current_air_value;
}