#include "SCD30.hpp"

AirSensor::AirSensor()
{
  // constructor
}

AirSensor::~AirSensor()
{
  // destructor
}

void AirSensor::setupSensor()
{
    Wire.begin();

    Serial.begin(BAUD_RATE);
    Serial.println("SCD30 Example");

    airSensor.begin(); // This will cause readings to occur every two seconds

    // airSensor.setMeasurementInterval(2); //Change number of seconds between measurements: 2 to 1800 (30 minutes)

    // My desk is ~1600m above sealevel
    airSensor.setAltitudeCompensation(1); // Set altitude of the sensor in m

    // Pressure in Boulder, CO is 24.65inHg or 834.74mBar
    airSensor.setAmbientPressure(1037); // Current ambient pressure in mBar: 700 to 1200
}

void AirSensor::loopSensor()
{
    if (airSensor.dataAvailable())
    {
        Serial.write(1);
        //    Serial.print("co2(ppm):");
        Serial.print(airSensor.getCO2());

        //    Serial.print(" temp(C):");
        //    Serial.print(airSensor.getTemperature(), 1);
        //
        //    Serial.print(" humidity(%):");
        //    Serial.print(airSensor.getHumidity(), 1);

        Serial.println();
    }
    else
    {
        Serial.write(0);
        // Serial.print(".");
    }

    my_delay(1); // delay for 1 second
}

AirSensor airSensor;