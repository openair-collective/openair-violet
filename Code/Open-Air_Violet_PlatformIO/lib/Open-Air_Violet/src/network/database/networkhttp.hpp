#ifndef NETWORKHTTP_HPP
#define NETWORKHTTP_HPP
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class NetworkHTTP
{
public:
    NetworkHTTP();
    virtual ~NetworkHTTP();
    
    bool begin();

};
extern NetworkHTTP networkHTTP;
#endif // NETWORKHTTP_HPP