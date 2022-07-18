#ifndef K30_HPP
#define K30_HPP
#include "defines.hpp"
#include <Wire.h> // Change to TinyI2C for more performance

class K30_AirSensor
{
public:
    K30_AirSensor(int i2c_address);
    virtual ~K30_AirSensor();

    byte readCO2(int &CO2level);
    void loopSensor();

private:
    int _i2c_address;
    int _co2;
    int _rc;
};
extern K30_AirSensor K30_airsensor;
#endif // K30_HPP