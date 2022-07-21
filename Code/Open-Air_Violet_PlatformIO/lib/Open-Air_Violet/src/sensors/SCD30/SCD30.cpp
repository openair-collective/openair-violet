#include "SCD30.hpp"

SCD30_AirSensor::SCD30_AirSensor() {}

SCD30_AirSensor::~SCD30_AirSensor() {}

bool SCD30_AirSensor::begin()
{
  bool wire_lib_success = Wire.begin();
  bool success = _sd30.begin(); // This will cause readings to occur every two seconds
  //_sd30.setMeasurementInterval(2); // Change number of seconds between measurements: 2 to 1800 (30 minutes)
  // My desk is ~1600m above sealevel
  bool set_altitude_comp_success = _sd30.setAltitudeCompensation(1); // Set altitude of the sensor in m
  // Pressure in Boulder, CO is 24.65inHg or 834.74mBar
  bool set_ambient_pressure_success = _sd30.setAmbientPressure(1037); // Current ambient pressure in mBar: 700 to 1200
  //ECC statement based on the above booleans
  bool success_status = wire_lib_success && success && set_altitude_comp_success && set_ambient_pressure_success;
  return success_status;
}

void SCD30_AirSensor::loopSensor()
{
  if (!begin())
  {
#if defined(ESP32)
    log_e("SCD30_AirSensor::begin() failed to begin");
#else
    Serial.println("SCD30_AirSensor::begin() failed to begin");
#endif
    return;
  }

  if (!_sd30.dataAvailable())
  {
#if defined(ESP32)
    log_e("[SCD30]: No data available - sensor not connected?");
#else
    Serial.println("[SCD30]: No data available - sensor not connected?");
#endif
    return;
  }

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

  my_delay(1); // delay for 1 second - non-blocking
}

SCD30_AirSensor SCD30_airSensor;