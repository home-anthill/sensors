// include Arduino library to use Arduino function in cpp files
#include <Arduino.h>
// include library to configure I2C port
#include <Wire.h>

// include specific libraries:
// `DPS310-Pressure-Sensor` by Infineon (latest version on `dps310 branch` or
// commit hash `ed02f803fc780cbcab54ed8b35dd3d718f2ebbda` from `https://github.com/Infineon/DPS310-Pressure-Sensor`).
// You cannot use the one published on ArduinoIDE Library Manager, because it's outdated or not available.
#include <Dps310.h>

// Configure I2C GPIOs
#define I2C_SDA 39
#define I2C_SCL 40
// global variables
Dps310 Dps310PressureSensor = Dps310();

void barometer_init_sensor() {
  Serial.println("barometer_init_sensor - called");
  Wire.setPins(I2C_SDA, I2C_SCL);
  Dps310PressureSensor.begin(Wire);
  Serial.println("barometer_init_sensor - sensor initialized successfully!");
}

float barometer_get_temperature() {
  Serial.println("barometer_get_temperature - called");
  float temperature;
  if (Dps310PressureSensor.measureTempOnce(temperature) == 0) {
    Serial.printf("barometer_get_temperature - temperature [°C]: %.2f\n", temperature);
    return temperature;
  }
  return -999;
}

float barometer_get_airpressure() {
  Serial.println("barometer_get_airpressure - called");
  float pressure;
  if (Dps310PressureSensor.measurePressureOnce(pressure) == 0) {
    pressure = pressure / 1000;
    Serial.printf("barometer_get_airpressure - pressure [hPAa]: %.2f\n", pressure);
    return pressure;
  }
  return -999;
}