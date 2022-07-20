#include "Humidity.hpp"

// Global Variables
#if USE_SHT31_SENSOR
Adafruit_SHT31 sht31;
Adafruit_SHT31 sht31_2;
#endif // USE_SHT31_SENSOR

#if USE_DHT_SENSOR
DHT_Unified dht(DHTPIN, DHTTYPE);
#endif // USE_DHT_SENSOR

Humidity::Hum result;

Humidity::Humidity() : _delayS(0),
#if USE_DHT_SENSOR
                       _status(0)
#endif // USE_DHT_SENSOR
#if USE_SHT31_SENSOR
                       ,
                       _enableHeater(false),
                       _loopCnt(0),
                       _HUMIDITY_SENSORS_ACTIVE(0)
#endif // USE_SHT31_SENSOR
{
}

Humidity::~Humidity()
{
}

/******************************************************************************
 * Function: Setup Humidity Sensors
 * Description: This function is used to initialise the humidity sensors and their respective heaters
 * Parameters: None
 * Return: int - 0 for no sensors found, 1 for  1 sensor found, 2 for 1 sensors found, 3 for 2 sensors found
 ******************************************************************************/
byte Humidity::setupSensor()
{
#if USE_DHT_SENSOR
  // Initialize the DHT sensor.
  dht.begin();
  log_i("DHT Sensor connected!");
  _status = 1;
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  log_d("------------------------------------");
  log_d("Temperature Sensor");
  log_d("Sensor Type: %c", sensor.name);
  log_d("Driver Ver: %d", sensor.version);
  log_d("Unique ID:  %d", sensor.sensor_id);
  log_d("Max Value: %d °C", sensor.max_value);
  log_d("Min Value: %d °C", sensor.min_value);
  log_d("Resolution: %d °C", sensor.resolution);
  log_d("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  log_d("Humidity Sensor");
  log_d("Sensor Type: %c", sensor.name);
  log_d("Driver Ver: %d", sensor.version);
  log_d("Unique ID:  %d", sensor.sensor_id);
  log_d("Max Value:  %d %%", sensor.max_value);   // 100%
  log_d("Min Value:  %d %%", sensor.min_value);   // 0%
  log_d("Resolution:  %d %%", sensor.resolution); // 0.5%
  log_d("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  _delayS = sensor.min_delay / 1000000;
  log_d("Delay: %d ms", _delayS);
  log_d("------------------------------------");
  log_d("");
  return _status;
#endif // USE_DHT_SENSOR

#if USE_SHT31_SENSOR
  log_d("SHT31 Sensors Setup Beginning....");
  // Set to 0x45 for alternate i2c address
  if (!sht31.begin(0x44) && !sht31_2.begin(0x45))
  {
    log_d("Couldn't find SHT31 sensors");
    log_d("SHT31 Sensors Setup did not complete successfully, check your wiring or the addresses and try again");
    _HUMIDITY_SENSORS_ACTIVE = 0;
    return 0;
  }
  else if (!sht31.begin(0x44) && sht31_2.begin(0x45))
  {
    log_d("Found 1 SHT31 Sensor");
    _HUMIDITY_SENSORS_ACTIVE = 1;
    return 1;
  }
  else if (!sht31_2.begin(0x45) && sht31.begin(0x44))
  {
    log_d("Found 2 SHT31 Sensor");
    _HUMIDITY_SENSORS_ACTIVE = 2;
    return 2;
  }
  else
  {
    log_d("SHT31 Sensors Setup Complete");
    _HUMIDITY_SENSORS_ACTIVE = 3;
    return 3;
  }
  my_delay(2L); // delay in between reads for stability
#endif          // USE_SHT31_SENSOR
  return 0;
}

#if USE_DHT_SENSOR
Humidity::Hum Humidity::readDHT()
{
  // Delay between measurements.
  my_delay(_delayS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    log_d("Error reading temperature!");
  }
  else
  {
    log_d("Temperature: %.3f°C", event.temperature);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    log_d("Error reading humidity!");
  }
  else
  {
    log_d("Humidity: %.3f%%", event.relative_humidity);
  }
  result.temp = event.temperature;
  result.humidity = event.relative_humidity;
  return result;
}
#endif // USE_DHT_SENSOR

#if USE_SHT31_SENSOR
bool Humidity::checkHeaterEnabled()
{
  switch (_HUMIDITY_SENSORS_ACTIVE)
  {
  case 0:
    return false;
    break;
  case 1:
  {
    bool _sensor1 = sht31.isHeaterEnabled();
    bool heaterenabled = false;
    if (_loopCnt >= 30)
    {
      _enableHeater = !_enableHeater;
      sht31.heater(_enableHeater);
      log_d("Heater Enabled State: %s", _enableHeater ? "Enabled" : "Disabled");
      if (_sensor1)
      {
        log_d("Sensor 1 Heater ENABLED");
        heaterenabled = true;
      }
      else
      {
        log_d("Sensor 1 Heater Disabled");
        heaterenabled = false;
      }
      _loopCnt = 0;
    }
    _loopCnt++;
    return heaterenabled;
    break;
  }
  case 2:
  {
    bool _sensor2 = sht31_2.isHeaterEnabled();
    bool heaterenabled = false;
    if (_loopCnt >= 30)
    {
      _enableHeater = !_enableHeater;
      sht31_2.heater(_enableHeater);
      log_d("Heater Enabled State: %s", _enableHeater ? "Enabled" : "Disabled");
      if (_sensor2)
      {
        log_d("Sensors have Heater ENABLED");
        heaterenabled = true;
      }
      else
      {
        log_d("Sensor 1 Heater Disabled");
        heaterenabled = false;
      }
      _loopCnt = 0;
    }
    _loopCnt++;
    return heaterenabled;
    break;
  }
  case 3:
  {
    bool _sensor1 = sht31.isHeaterEnabled();
    bool _sensor2 = sht31_2.isHeaterEnabled();
    bool heaterenabled = false;
    if (_loopCnt >= 30)
    {
      _enableHeater = !_enableHeater;
      sht31.heater(_enableHeater);
      sht31_2.heater(_enableHeater);
      log_d("Heater Enabled State: %s", _enableHeater ? "Enabled" : "Disabled");
      if (_sensor1 != _sensor2)
      {
        log_d("Sensors have Heater ENABLED");
        heaterenabled = true;
      }
      else
      {
        log_d("Sensor 1 Heater Disabled");
        heaterenabled = false;
      }
      _loopCnt = 0;
    }
    _loopCnt++;
    return heaterenabled;
    break;
  }
  default: // Should never get here
    return false;
    break;
  }
}

/******************************************************************************
 * Function: Average Stack Humidity Temp
 * Description: This function is used to average the Temp of the stack - from the temp sensors built into the Humidity Sensors
 * Parameters: None
 * Return: float
 * Note: This function MUST be called after the ReadSensor function
 ******************************************************************************/
float Humidity::AverageStackTemp()
{
  switch (_HUMIDITY_SENSORS_ACTIVE)
  {
  case 0:
  {
    float stack_temp = 0;
    return stack_temp; // return 0 if no sensors are active
    break;
  }

  case 1:
  {
    float stack_temp = result.temp_sht31;
    return stack_temp; // Only one sensor - return the value of that sensor
    break;
  }

  case 2:
  {
    float stack_temp = result.temp_sht31_2;
    return stack_temp; // Only one sensor - return the value of that sensor
    break;
  }

  case 3:
  {
    float stack_temp = result.temp_sht31 + result.temp_sht31_2;
    return stack_temp / 2; // Read the _temperature from the sensor and average the two sensors.
    break;
  }

  default:
  {
    break;
  }
  }
}

/******************************************************************************
 * Function: Average Stack Humidity
 * Description: This function is used to average the humidity of the stack
 * Parameters: None
 * Return: float
 * Note: This function MUST be called after the ReadSensor function
 ******************************************************************************/
float Humidity::StackHumidity()
{
  switch (_HUMIDITY_SENSORS_ACTIVE)
  {
  case 0:
  {
    float stack_humidity = 0;
    return stack_humidity; // return 0 if no sensors are active
    break;
  }

  case 1:
  {
    float stack_humidity = result.humidity;
    return stack_humidity; // Only one sensor - return the value of that sensor
    break;
  }

  case 2:
  {
    float stack_humidity = result.humidity_2;
    return stack_humidity; // Only one sensor - return the value of that sensor
    break;
  }

  case 3:
  {
    float stack_humidity = result.humidity + result.humidity_2;
    return stack_humidity / 2; // Read the _humidity from the sensor and average the two sensors.
    break;
  }

  default:
  {
    break;
  }
  }
}

/******************************************************************************
 * Function: Read Humidity Sensors
 * Description: This function is used to read the humidity of the stack sensors
 * Parameters: None
 * Return: float array
 ******************************************************************************/
Humidity::Hum Humidity::ReadSensor()
{
  switch (_HUMIDITY_SENSORS_ACTIVE)
  {
  case 0:
  {
    result.temp_sht31 = 0;
    result.humidity_sht31 = 0;
    result.temp_sht31_2 = 0;
    result.humidity_sht31_2 = 0;
    return result;
    break;
  }
  case 1:
  {
    float temp = sht31.readTemperature();
    float hum = sht31.readHumidity();
    // check if 'is not a number
    if (!isnan(temp))
    { // check if 'is not a number'
      log_d("Temp *C = %.3f\t\t", temp);
    }
    else
    {
      log_d("Failed to read temperature");
    }

    if (!isnan(hum))
    { // check if 'is not a number'
      log_d("Hum. % = %.3f\t\t", hum);
    }
    else
    {
      log_d("Failed to read humidity");
    }
    my_delay(0.1L); // delay in between reads for stability

    // Toggle heater enabled state every 30 seconds
    // An ~3.0 degC _temperature increase can be noted when heater is enabled
    // This is needed due to the high operating humidity of the system
    checkHeaterEnabled();
    result.temp_sht31 = temp;
    result.humidity_sht31 = hum;
    return result;
    break;
  }
  case 2:
  {
    float temp_2 = sht31_2.readTemperature();
    float hum_2 = sht31_2.readHumidity();
    if (!isnan(temp_2))
    { // check if 'is not a number'
      log_d("Temp *C = %.3f\t\t", temp_2);
    }
    else
    {
      log_d("Failed to read temperature");
    }

    if (!isnan(hum_2))
    { // check if 'is not a number'
      log_d("Hum. % = %.3f\t\t", hum_2);
    }
    else
    {
      log_d("Failed to read humidity");
    }
    my_delay(0.1L); // delay in between reads for stability

    // Toggle heater enabled state every 30 seconds
    // An ~3.0 degC _temperature increase can be noted when heater is enabled
    // This is needed due to the high operating humidity of the system
    checkHeaterEnabled();
    result.temp_sht31_2 = temp_2;
    result.humidity_sht31_2 = hum_2;
    return result;
    break;
  }
  case 3:
  {
    float temp_1 = sht31.readTemperature();
    float temp_2 = sht31_2.readTemperature();
    if (!isnan(temp_1))
    { // check if 'is not a number'
      log_d("Temp 1 *C = %.3f\t\t", temp_1);
    }
    else
    {
      log_d("Failed to read temperature");
    }

    if (!isnan(temp_2))
    { // check if 'is not a number'
      log_d("Temp 2 *C = %.3f\t\t", temp_2);
    }
    else
    {
      log_d("Failed to read humidity");
    }

    // check if 'is not a number'
    float hum_1 = sht31.readHumidity();
    float hum_2 = sht31_2.readHumidity();
    if (!isnan(hum_1))
    { // check if 'is not a number'
      log_d("Temp 1 *C = %.3f\t\t", hum_1);
    }
    else
    {
      log_d("Failed to read temperature");
    }

    if (!isnan(hum_2))
    { // check if 'is not a number'
      log_d("Temp 2 *C = %.3f\t\t", hum_2);
    }
    else
    {
      log_d("Failed to read humidity");
    }
    my_delay(1L); // delay in between reads for stability
    result = {temp_1, hum_1, temp_2, hum_2};
    return result;
    break;
  }
  default: // Should never get here
    result.temp_sht31 = 0;
    result.humidity_sht31 = 0;
    result.temp_sht31_2 = 0;
    result.humidity_sht31_2 = 0;
    return result;
    break;
  }
}
#endif // USE_HUMIDITY_SENSOR

Humidity humidity;
