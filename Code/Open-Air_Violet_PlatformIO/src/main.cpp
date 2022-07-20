#if K30_SUPPORT
#include <sensors/K30/K30.hpp>
#endif // K30_SUPPORT
#if SCD30_SUPPORT
#include <sensors/SCD30/SCD30.hpp>
#endif // SCD30_SUPPORT

void setup()
{
  Serial.begin(BAUD_RATE);
#if SCD30_SUPPORT
  SCD30_airsensor.begin();
#endif // SCD30_SUPPORT
  // put your setup code here, to run once:
}

void loop()
{
#if K30_SUPPORT
  K30_airsensor.loopSensor();
#endif // K30_SUPPORT
#if SCD30_SUPPORT
  SCD30_airsensor.loopSensor();
#endif // SCD30_SUPPORT
  // put your main code here, to run repeatedly:
}