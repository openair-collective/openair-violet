#ifndef NETWORKFIREBASE_HPP
#define NETWORKFIREBASE_HPP
#include "network/network.hpp"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

class NetworkFirebase : public Network
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