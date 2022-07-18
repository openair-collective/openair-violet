#include "K30.hpp"

K30_AirSensor::K30_AirSensor(int i2c_address) : _i2c_address(i2c_address), _rc(1), _co2(0)
{
    Wire.begin();
}

K30_AirSensor::~K30_AirSensor() {}

byte K30_AirSensor::readCO2(int &CO2level)
{

    byte recValue[4] = {0, 0, 0, 0};

    Wire.beginTransmission(_i2c_address);
    Wire.write(0x22);
    Wire.write(0x00);
    Wire.write(0x08);
    Wire.write(0x2A);
    Wire.endTransmission();
    my_delay(0.030L);

    Wire.requestFrom(_i2c_address, 4);
    my_delay(0.020L);

    byte i = 0;
    while (Wire.available())
    {
        recValue[i] = Wire.read();
        i++;
    }

    byte checkSum = recValue[0] + recValue[1] + recValue[2];
    CO2level = (recValue[1] << 8) + recValue[2];

    if (i == 0)
    {
        return 2;
    }
    else if (checkSum == recValue[3])
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void K30_AirSensor::loopSensor()
{
    log_i("Reading K30 sensor ...... \n");
    _rc = readCO2(_co2);
    if (_rc != 0)
    {
#if defined(ESP32)
        log_e("Failure to read sensor\n");
#else
        Serial.println("Failure to read sensor");
#endif // ESP32
        return;
    }
#if defined(ESP32)
    log_d("Successful reading\n");
    log_i("%d ppm",_co2);
#else
    Serial.println("Successful reading");
    Serial.print(_co2);
    Serial.println(" ppm");
#endif // ESP32

    my_delay(3); // delay for 3 seconds - non-blocking
}

K30_AirSensor K30_airSensor(0x68);
