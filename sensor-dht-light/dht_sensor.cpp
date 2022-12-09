// include Arduino library to use Arduino function in cpp files
#include <Arduino.h>

// include specific libraries:
// - DHT Sensor: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 4 // Digital pin connected to the DHT sensor
#define DHT_TYPE DHT22 // DHT 22 (AM2302)
DHT_Unified dht(DHT_PIN, DHT_TYPE);

void dht_init_sensor() {
  Serial.println("dht_init_sensor - called");
  // Initialize DHT device
  dht.begin();
  sensor_t sensor;
  // Print temperature sensor details.
  dht.temperature().getSensor(&sensor);
  Serial.println(F("dht_init_sensor - temperature"));
  Serial.print(F("dht_init_sensor - temperature - Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("dht_init_sensor - temperature - Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("dht_init_sensor - temperature - Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("dht_init_sensor - temperature - Max Value:   "));
  Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print(F("dht_init_sensor - temperature - Min Value:   "));
  Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print(F("dht_init_sensor - temperature - Resolution:  "));
  Serial.print(sensor.resolution); Serial.println(F("°C"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("dht_init_sensor - humidity"));
  Serial.print(F("dht_init_sensor - humidity - Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("dht_init_sensor - humidity - Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("dht_init_sensor - humidity - Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("dht_init_sensor - humidity - Max Value:   "));
  Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print(F("dht_init_sensor - humidity - Min Value:   "));
  Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print(F("dht_init_sensor - humidity - Resolution:  "));
  Serial.print(sensor.resolution); Serial.println(F("%"));
}

float dht_get_temperature() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  return event.temperature;
}

float dht_get_humidity() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  return event.relative_humidity;
}