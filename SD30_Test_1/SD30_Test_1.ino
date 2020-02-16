/*

  Initial testing of the SD30 CO2 sensor for openair-violet

  Attempts to send the C02 ppm every second accross a serial 
  port so it is availble to visualized for by the associated process sketch.

  Requires the SD30 Ardunio Lib.

  Based off the sample detailed below:
  
  Reading CO2, humidity and temperature from the SCD30
  By: Nathan Seidle
  SparkFun Electronics
  Date: May 22nd, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14751

  This example demonstrates the various settings available on the SCD30.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  Serial.print it out at 9600 baud to serial monitor.

  Note: All settings (interval, altitude, etc) are saved to non-volatile memory and are
  loaded by the SCD30 at power on. There's no damage in sending that at each power on.

  Note: 100kHz I2C is fine, but according to the datasheet 400kHz I2C is not supported by the SCD30
*/

#include <Wire.h>

//Click here to get the library: http://librarymanager/All#SparkFun_SCD30
#include "SparkFun_SCD30_Arduino_Library.h"

SCD30 airSensor;

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  Serial.println("SCD30 Example");

  airSensor.begin(); //This will cause readings to occur every two seconds

  //airSensor.setMeasurementInterval(2); //Change number of seconds between measurements: 2 to 1800 (30 minutes)

  //My desk is ~1600m above sealevel
  airSensor.setAltitudeCompensation(1); //Set altitude of the sensor in m

  //Pressure in Boulder, CO is 24.65inHg or 834.74mBar
  airSensor.setAmbientPressure(1037); //Current ambient pressure in mBar: 700 to 1200
}

void loop()
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
  else{
    Serial.write(0);    
    //Serial.print(".");
  }

  delay(1000);
}
