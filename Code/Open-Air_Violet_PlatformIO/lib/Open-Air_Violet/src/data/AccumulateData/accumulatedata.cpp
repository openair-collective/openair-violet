#include "accumulatedata.hpp"

AccumulateData::AccumulateData() : _maxTemp(100), _numTempSensors(0), inList(false) {}

AccumulateData::~AccumulateData() {}

//******************************************************************************
// * Function: Accumulate Data to send from sensors and store in json
// * Description: This function accumulates all sensor data and stores it in the main data structure.
// * Parameters: None
// * Return: None
//******************************************************************************/
void AccumulateData::loopSensors()
{
    _numTempSensors = tower_temp.getSensorCount();
    project_config.config_t.numTempSensors = _numTempSensors;

    // Initialize the library
#if USE_SHT31_SENSOR
    humidity.ReadSensor();
#endif // USE_SHT31_SENSOR

#if USE_DHT_SENSOR
    humidity.readDHT();
#endif // USE_DHT_SENSOR

    tower_temp.getTempC();
    
    // Relays
    for (int i = 0; i < sizeof(cfg.config.relays_pin) / sizeof(cfg.config.relays_pin[0]); i++)
    {
        Relay.RelayOnOff(cfg.config.relays_pin[i], cfg.config.relays[i]);
        log_d("Relay on pin: %d is %s", cfg.config.relays_pin[i], cfg.config.relays[i] ? "on" : "off");
    }
}

bool AccumulateData::SendData()
{
    String json = "";
    StaticJsonDocument<1024> jsonDoc;
    jsonDoc["id"] = "1";
    jsonDoc["timestamp"] = time(NULL);
    jsonDoc["max_temp"] = _maxTemp;
    jsonDoc["num_temp_sensors"] = _numTempSensors;
    // jsonDoc["flow_rate"] = _config.flow_rate;
    // jsonDoc["flow_rate_sensor_temp"] = _config.flow_rate_sensor_temp;

#if USE_SHT31_SENSOR
    switch (humidity._HUMIDITY_SENSORS_ACTIVE)
    {
    case 0:
        break;
    case 1:
        jsonDoc["humidity_sht31"] = humidity.result.humidity_sht31;
        jsonDoc["humidity_temp_sht31"] = humidity.result.temp_sht31;
        break;
    case 2:
        jsonDoc["humidity_sht31_2"] = humidity.result.humidity_sht31_2;
        jsonDoc["humidity_temp_sht31_2"] = humidity.result.temp_sht31_2;
        break;
    case 3:
        jsonDoc["humidity_sht31"] = humidity.result.humidity_sht31;
        jsonDoc["humidity_temp_sht31"] = humidity.result.temp_sht31;
        jsonDoc["humidity_sht31_2"] = humidity.result.humidity_sht31_2;
        jsonDoc["humidity_temp_sht31_2"] = humidity.result.temp_sht31_2;
        break;
    default:
        break;
    }

    jsonDoc["humidity_sht31_average"] = humidity.StackHumidity();
    jsonDoc["humidity_temp_sht31_average"] = humidity.AverageStackTemp();
#endif // USE_SHT31_SENSOR
#if USE_DHT_SENSOR
    jsonDoc["humidity_dht"] = humidity.result.humidity;
    jsonDoc["humidity_temp_dht"] = humidity.result.temp;
#endif // USE_DHT_SENSOR
#if ENABLE_PH_SUPPORT
    jsonDoc["ph_sensor"] = phsensor.getPH();
#endif // ENABLE_PH_SUPPORT
    JsonArray temp_sensor_data = jsonDoc.createNestedArray("temp_sensors");
    for (int i = 0; i < _numTempSensors; i++)
    {
        temp_sensor_data.add(tower_temp.temp_sensor_results.temp[i]);
    }

    // Relays
    JsonArray Relays = jsonDoc.createNestedArray("Tower_Relays_State");
    for (int i = 0; i < sizeof(cfg.config.relays) / sizeof(cfg.config.relays[0]); i++)
    {
        Relays.add(cfg.config.relays[i]);
    }

    if (serializeJson(jsonDoc, json) == 0)
    {
        log_e("[Data Json Document]: Failed to write to file");
        return false;
    }

    if (json.length() > 0)
    {
        cfg.config.data_json_string = json;
        serializeJsonPretty(jsonDoc, json);
        log_d("[Data Json Document]: %s", json.c_str());
        return true;
    }

    return false;
}

AccumulateData accumulatedata;
