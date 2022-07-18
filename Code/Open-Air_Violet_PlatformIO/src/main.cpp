#include <sensors/SCD30/SCD30.hpp>

void setup() {
  SCD30_airsensor.begin();
  // put your setup code here, to run once:
}

void loop() {
  SCD30_airsensor.loopSensor();
  // put your main code here, to run repeatedly:
}