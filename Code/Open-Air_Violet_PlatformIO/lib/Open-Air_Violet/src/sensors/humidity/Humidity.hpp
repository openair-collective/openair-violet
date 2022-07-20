/*
 Humidity.hpp - ESP32GreenHouseDIY Humidity library
 Copyright (c) 2021 ZanzyTHEbar
 */

#ifndef HUMIDITY_HPP
#define HUMIDITY_HPP
#include <defines.hpp>
#include <Wire.h>
#if USE_SHT31_SENSOR
#include <Adafruit_SHT31.h>

#endif // USE_SHT31_SENSOR

#if USE_DHT_SENSOR
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#if (USE_DHT11)
#define DHTTYPE DHT11 // DHT 11
#elif (USE_DHT22)
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#elif (USE_DHT21)
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#endif

#endif // USE_DHT_SENSOR

class Humidity
{
public:
  // Constructor
  Humidity();
  virtual ~Humidity();
  // Initialize the library
  byte setupSensor();
  
  struct Hum
  {
    float temp;
    float humidity;
    float temp_2;
    float humidity_2;
    float humidity_sht31;
    float temp_sht31;
    float humidity_sht31_2;
    float temp_sht31_2;
  };

  Hum result;

#if USE_DHT_SENSOR
  Hum readDHT();
#endif // USE_DHT_SENSOR

#if USE_SHT31_SENSOR
  bool checkHeaterEnabled();
  float StackHumidity();
  float AverageStackTemp();
  Hum ReadSensor();
#endif // USE_SHT31_SENSOR

  // Friends
  friend class Config;
  friend class AccumulateData;

  // Variables
private:
  uint32_t _delayS;
#if USE_DHT_SENSOR
  int _status;
#endif // USE_DHT_SENSOR
#if USE_SHT31_SENSOR
  bool _enableHeater;
  int _loopCnt;
  byte _HUMIDITY_SENSORS_ACTIVE;
#endif // USE_SHT31_SENSOR
};
extern Humidity humidity;
#endif