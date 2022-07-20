/*
 Network.h - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
*/
#pragma once
#ifndef NETWORK_hpp
#define NETWORK_hpp

#include <defines.hpp>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "data/config/project_config.hpp"
#include "data/StateManager/StateManager.hpp"

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
    bool CheckNetworkLoop();
    void CheckConnectionLoop_Active();
    bool LoopWifiScan();

    // variables
private:
    // Timer variables
    unsigned long _previousMillis;
    const long _interval; // interval to wait for Wi-Fi connection (milliseconds)
    bool _wifiConnected;
};

extern Network network;
#endif
