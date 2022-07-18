/*
 Network.h - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
*/
#pragma once
#ifndef NETWORK_hpp
#define NETWORK_hpp

#include <defines.hpp>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "data/project_config.hpp"

extern WiFiClient espClient;

class Network
{
public:
    // constructors
    Network();
    virtual ~Network();
    // Functions
    bool SetupNetworkStack();
    void SetupWebServer();
    void SetupServer();
    void networkRoutes();
    void CheckNetworkLoop();
    void CheckConnectionLoop_Active();
    bool LoopWifiScan();

    // variables
private:
    int CheckWifiState();
    // Timer variables
    unsigned long _previousMillis;
    const long _interval; // interval to wait for Wi-Fi connection (milliseconds)
    bool _wifiConnected;
};

extern Network network;
#endif
