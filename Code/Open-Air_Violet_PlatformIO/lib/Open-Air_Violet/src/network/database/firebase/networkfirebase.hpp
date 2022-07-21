#ifndef NETWORKFIREBASE_HPP
#define NETWORKFIREBASE_HPP
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>



class NetworkFirebase
{
public:
    NetworkFirebase();
    virtual ~NetworkFirebase();

    bool begin_firebase();
    void process_firebase();

private:
    unsigned long _sendDataPreviousMillis;
    int _sendDataInterval;
    bool _auth_ok;
};
extern NetworkFirebase networkFirebase;
#endif // NETWORKHTTP_HPP