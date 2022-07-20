#ifndef ACCUMULATEDATA_HPP
#define ACCUMULATEDATA_HPP
#include <defines.hpp>
#include <lists.h>
#include <vector>
#include <ArduinoJson.h>
#include "data/config/project_config.hpp"
#include "sensors/humidity/humidity.hpp"
#include "sensors/temperature/towertemp.hpp"  

class AccumulateData
{
public:
    AccumulateData();
    virtual ~AccumulateData();

    void loopSensors();
    bool SendData();

    // Variables
    bool inList;

private:
    // Stack Data to send
    int _maxTemp;
    int _numTempSensors;
};

extern AccumulateData accumulatedata;

#endif