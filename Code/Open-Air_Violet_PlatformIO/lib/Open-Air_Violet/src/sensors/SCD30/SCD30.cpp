#include "SCD30.hpp"

SCD30_AirSensor::SCD30_AirSensor() {}

SCD30_AirSensor::~SCD30_AirSensor() {}

void SCD30_AirSensor::begin()
{
  Wire.begin();

  _sd30.begin(); // This will cause readings to occur every two seconds

  //_sd30.setMeasurementInterval(2); // Change number of seconds between measurements: 2 to 1800 (30 minutes)

  // My desk is ~1600m above sealevel
  _sd30.setAltitudeCompensation(1); // Set altitude of the sensor in m

  // Pressure in Boulder, CO is 24.65inHg or 834.74mBar
  _sd30.setAmbientPressure(1037); // Current ambient pressure in mBar: 700 to 1200
}

void SCD30_AirSensor::loopSensor()
{
  if (_sd30.dataAvailable())
  {
#if defined(ESP32)
    log_i("co2(ppm): %d", _sd30.getCO2());
    log_i("temp(C): %.3f", _sd30.getTemperature());
    log_i("humidity(%): %d", _sd30.getHumidity());
#else
    Serial.print("\t");
    Serial.print(_sd30.getTemperature());
    Serial.print("\t");
    Serial.print(_sd30.getHumidity());
    Serial.print("\t");
    Serial.print(_sd30.getCO2());
    Serial.println();
#endif
  }
  else
  {
    Serial.write(0);
  }
  my_delay(1); // delay for 1 second - non-blocking
}

SCD30_AirSensor SCD30_airsensor;