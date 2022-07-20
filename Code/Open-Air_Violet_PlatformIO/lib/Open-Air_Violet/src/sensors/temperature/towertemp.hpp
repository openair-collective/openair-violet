/*
 TowerTemp.h - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
 */

#ifndef TOWERTEMP_HPP
#define TOWERTEMP_HPP
// Data wire is plugged into port 42 on the ESP32
#define ONE_WIRE_BUS 42
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <vector>

class TowerTemp
{
public:
    TowerTemp();
    virtual ~TowerTemp();
    void SetupSensors();
    void readAddresses(DeviceAddress deviceAddress);
    void printAddress(DeviceAddress deviceAddress);
    void checkSensors();
    void setSensorCount();
    int getSensorCount();

    struct Temp
    {
        std::vector<float> temp;
    };

    Temp temp_sensor_results;

    Temp getTempC();
    Temp getTempF();

    // Friends

private:
    int _sensors_count;
};

extern TowerTemp tower_temp;
#endif