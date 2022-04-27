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
#pragma once
#ifndef SCD30_HPP
#define SCD30_HPP
#include "defines.hpp"
#include <Wire.h> // Change to TinyI2C for more performance
#include <SparkFun_SCD30_Arduino_Library.h>

class AirSensor : public SCD30
{
public:
    AirSensor();
    ~AirSensor();
    void setupSensor();
    void loopSensor();

private:
    // private stuff goes here
};

extern AirSensor airsensor;
#endif