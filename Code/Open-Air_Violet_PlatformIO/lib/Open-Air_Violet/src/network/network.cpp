/**
 * WiFi Events
 *0  SYSTEM_EVENT_WIFI_READY               < ESP32 WiFi ready
 *1  SYSTEM_EVENT_SCAN_DONE                < ESP32 finish scanning AP
 *2  SYSTEM_EVENT_STA_START                < ESP32 station start
 *3  SYSTEM_EVENT_STA_STOP                 < ESP32 station stop
 *4  SYSTEM_EVENT_STA_CONNECTED            < ESP32 station connected to AP
 *5  SYSTEM_EVENT_STA_DISCONNECTED         < ESP32 station disconnected from AP
 *6  SYSTEM_EVENT_STA_AUTHMODE_CHANGE      < the auth mode of AP connected by ESP32 station changed
 *7  SYSTEM_EVENT_STA_GOT_IP               < ESP32 station got IP from connected AP
 *8  SYSTEM_EVENT_STA_LOST_IP              < ESP32 station lost IP and the IP is reset to 0
 *9  SYSTEM_EVENT_STA_WPS_ER_SUCCESS       < ESP32 station wps succeeds in enrollee mode
 *10 SYSTEM_EVENT_STA_WPS_ER_FAILED        < ESP32 station wps fails in enrollee mode
 *11 SYSTEM_EVENT_STA_WPS_ER_TIMEOUT       < ESP32 station wps timeout in enrollee mode
 *12 SYSTEM_EVENT_STA_WPS_ER_PIN           < ESP32 station wps pin code in enrollee mode
 *13 SYSTEM_EVENT_AP_START                 < ESP32 soft-AP start
 *14 SYSTEM_EVENT_AP_STOP                  < ESP32 soft-AP stop
 *15 SYSTEM_EVENT_AP_STACONNECTED          < a station connected to ESP32 soft-AP
 *16 SYSTEM_EVENT_AP_STADISCONNECTED       < a station disconnected from ESP32 soft-AP
 *17 SYSTEM_EVENT_AP_STAIPASSIGNED         < ESP32 soft-AP assign an IP to a connected station
 *18 SYSTEM_EVENT_AP_PROBEREQRECVED        < Receive probe request packet in soft-AP interface
 *19 SYSTEM_EVENT_GOT_IP6                  < ESP32 station or ap or ethernet interface v6IP addr is preferred
 *20 SYSTEM_EVENT_ETH_START                < ESP32 ethernet start
 *21 SYSTEM_EVENT_ETH_STOP                 < ESP32 ethernet stop
 *22 SYSTEM_EVENT_ETH_CONNECTED            < ESP32 ethernet phy link up
 *23 SYSTEM_EVENT_ETH_DISCONNECTED         < ESP32 ethernet phy link down
 *24 SYSTEM_EVENT_ETH_GOT_IP               < ESP32 ethernet got IP from connected AP
 *25 SYSTEM_EVENT_MAX

 WiFi.status() return values:
    *0  WL_IDLE_STATUS                       < ESP32 station is in idle state
    *1  WL_NO_SSID_AVAIL                     < ESP32 station cannot find any SSID in scan results
    *2  WL_SCAN_COMPLETED                    < ESP32 station has finished the scan
    *3  WL_CONNECTED                         < ESP32 station has a connection to an AP
    *4  WL_CONNECT_FAILED                    < ESP32 station failed to connect to an AP
    *5  WL_CONNECTION_LOST                   < ESP32 station has lost connection to an AP
    *6  WL_DISCONNECTED                      < ESP32 station is in disconnected state
 */

#include "network.hpp"

AsyncWebServer server(80);

WiFiClient espClient;

/**
 * @brief Construct a new Network:: Network object
 *
 */
Network::Network() : _previousMillis(0),
                     _interval(30000),
                     _wifiConnected(false) {}

/**
 * @brief Destroy the Network:: Network object
 *
 */
Network::~Network() {}

void notFound(AsyncWebServerRequest *request)
{
    log_i("NOT_FOUND: ");
    if (request->method() == HTTP_GET)
        log_i("GET");
    else if (request->method() == HTTP_POST)
        log_i("POST");
    else if (request->method() == HTTP_DELETE)
        log_i("DELETE");
    else if (request->method() == HTTP_PUT)
        log_i("PUT");
    else if (request->method() == HTTP_PATCH)
        log_i("PATCH");
    else if (request->method() == HTTP_HEAD)
        log_i("HEAD");
    else if (request->method() == HTTP_OPTIONS)
        log_i("OPTIONS");
    else
        log_i("UNKNOWN");
    log_i(" http://%s%s\n", request->host().c_str(), request->url().c_str());
    request->send(404, "text/plain", "Not found.");
}

void Network::networkRoutes()
{
    static const char *MIMETYPE_HTML{"text/html"};
    /* static const char *MIMETYPE_CSS{"text/css"}; */
    /* static const char *MIMETYPE_JS{"application/javascript"}; */
    /* static const char *MIMETYPE_PNG{"image/png"}; */
    /* static const char *MIMETYPE_JPG{"image/jpeg"}; */
    /* static const char *MIMETYPE_ICO{"image/x-icon"}; */
    static const char *MIMETYPE_JSON{"application/json"};

    // Web Server Root URL
    server.on("/", HTTP_GET, [&](AsyncWebServerRequest *request)
              { request->send(200); });

    // preflight cors check
    server.on("/", HTTP_OPTIONS, [&](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse* response = request->beginResponse(204);
        response->addHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        response->addHeader("Access-Control-Allow-Headers", "Accept, Content-Type, Authorization, FileSize");
        response->addHeader("Access-Control-Allow-Credentials", "true");
        request->send(response); });

    // Route to set GPIO state to LOW
    /* server.on("/toggle", HTTP_GET, [&](AsyncWebServerRequest *request)
              {
                    int params = request->params();
                    for(int i=0;i<params;i++)
                    {
                        AsyncWebParameter* p = request->getParam(i);
                            // HTTP POST Relay Value
                        if (p->name() == "pin") 
                        {
                            String relay = p->value().c_str();
                            log_i("switching state of pin: %s\n", relay.c_str());
                            cfg.config.relays[relay.toInt()] = (cfg.config.relays[relay.toInt()] == true) ? false : true;
                        }
                        log_i("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                    }
                    request->send(200, MIMETYPE_JSON, "toggled"); }); */

    server.on("/data.json", HTTP_GET, [&](AsyncWebServerRequest *request)
              {
                  my_delay(1L);
                  String temp = cfg.config.data_json_string;
                  request->send(200, MIMETYPE_JSON, temp);
                  temp = ""; });

    server.on("/api/reset/config", HTTP_GET, [&](AsyncWebServerRequest *request)
              {
                  cfg.resetConfig();
                  request->send(200); });

    server.on("/api/reset/device", HTTP_GET, [&](AsyncWebServerRequest *request)
              {
                  request->send(200);
                  my_delay(1L);
                  ESP.restart(); });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

    server.onNotFound(notFound);
    server.begin();
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool Network::SetupNetworkStack()
{
    String SSID;
    String PASS;

    project_config.loadConfig();
    if (!project_config.loadConfig())
    {
        log_i("[INFO]: Failed to load config\n");
        return false;
    }

    log_i("[INFO]: Loaded config\n");
    // Load values saved in SPIFFS
    if (!PRODUCTION)
    {
        // print it on the serial monitor
        log_i("%s\n", project_config.config_t.password);
    }

    if (project_config.config_t.ssid[0] == '\0' || project_config.config_t.password[0] == '\0')
    {
        log_i("[INFO]: No SSID or password has been set.\n");
        log_i("[INFO]: Please configure the Wifi Manager by scanning the QR code on your device.\r\n");
        return false;
    }
    log_i("[INFO]: Configured SSID: %s\r\n", project_config.config_t.ssid);

    // Set your Gateway IP address
    IPAddress localIP;
    IPAddress gateway;
    IPAddress subnet;

    WiFi.mode(WIFI_STA);
    /* localIP.fromString(WiFi.localIP().toString());
    gateway.fromString(WiFi.gatewayIP().toString());
    subnet.fromString(WiFi.subnetMask().toString());

    if (!WiFi.config(localIP, gateway, subnet))
    {
        log_e("[INFO]: STA Failed to configure\n");
        return false;
    } */

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);

    WiFi.setHostname(project_config.config_t.hostname); // define hostname

    WiFi.begin(project_config.config_t.ssid, project_config.config_t.password); // connect to wifi network

    unsigned long currentMillis = millis();
    _previousMillis = currentMillis;

    while (WiFi.status() != WL_CONNECTED)
    {
        stateManager_WiFi.setState(ProgramStates::DeviceStates::WiFiState_e::WiFiState_Connecting);
        currentMillis = millis();
        if (currentMillis - _previousMillis >= _interval)
        {
            log_i("[INFO]: WiFi connection timed out.\n");
            stateManager_WiFi.setState(ProgramStates::DeviceStates::WiFiState_e::WiFiState_Error);
            return false;
        }
    }

    log_i("[INFO]: Connected to WiFi.\n");
    log_i("IP address: %s\n", WiFi.localIP().toString().c_str());
    stateManager_WiFi.setState(ProgramStates::DeviceStates::WiFiState_e::WiFiState_Connected);
    return true;
}

/**
 * @brief Setup the network stack and routes - fail to AP mode if STA fails
 *
 */
void Network::SetupWebServer()
{
    if (SetupNetworkStack())
    {
        networkRoutes();
        log_i("OpenAir Violet server started\n");
    }
    else
    {
        // TODO: Route for root to  "Please Scan QR code"
        // TODO: There should be a reset mode that will reset the device to factory settings and restart the device.
        // TODO: Should be a physical reset button on the PCB itself - not a touch button - hold for 5 seconds to reset. Flash LED to indicate reset per second.
        // Connect to Wi-Fi Network with SSID and password

        log_i("[INFO]: Setting Access Point...\n");

        log_i("[INFO]: Configuring access point...\n");
        WiFi.mode(WIFI_AP);

        // You can remove the password parameter if you want the AP to be open.
        log_i("Wifi Connection Failed. \r\nStarting AP. \r\nAP IP address: ");
        IPAddress IP = WiFi.softAPIP();
        log_i("[INFO]: AP IP address: %s.\r\n", IP.toString().c_str());

        if (!PRODUCTION)
        {
            WiFi.softAP(DEFAULT_HOSTNAME, NULL, 10, 0, 2); // AP mode without password
        }
        else
        {
            WiFi.softAP(WIFI_SSID, WIFI_PASS, 10, 0, 3); // AP mode with password
        }
        WiFi.setTxPower(WIFI_POWER_11dBm);

        networkRoutes(); // call the network routes function to setup the routes
    }
}

// ######################## server functions #########################

/******************************************************************************
 * Function: Check Network Connection Loop
 * Description: This function checks the Network connection and reconnects if necessary - is called in the loop() function every 5 seconds
 * Parameters: None
 * Return: None
 ******************************************************************************/
bool Network::CheckNetworkLoop()
{
    stateManager_WiFi.setState((WiFi.status() != WL_CONNECTED) ? ProgramStates::DeviceStates::WiFiState_e::WiFiState_Disconnected : ProgramStates::DeviceStates::WiFiState_e::WiFiState_Connected);
    return (stateManager_WiFi.getCurrentState() == ProgramStates::DeviceStates::WiFiState_e::WiFiState_Connected) ? true : false;
}

void Network::CheckConnectionLoop_Active()
{
    unsigned long currentMillis = millis();
    // if WiFi is down, try reconnecting
    if (stateManager_WiFi.getCurrentState() == ProgramStates::DeviceStates::WiFiState_e::WiFiState_Disconnected && (currentMillis - _previousMillis >= _interval))
    {
        log_i("WiFi is disconnected, reconnecting...\n");
        WiFi.disconnect();
        WiFi.reconnect();
        _previousMillis = currentMillis;
    }
}

void Network::SetupServer()
{
    log_i("\n");
    log_i("System Information:\n");
    log_i("\n");
    log_i("PLatformI0 compile time: %s (%s)\n", __DATE__, __TIME__);
    log_i("PLatformI0 Unix compile time: %d\n", COMPILE_UNIX_TIME);
    log_i("Project directory: %s\n", PROJECT_PATH);
    log_i("Version: %d\n", VERSION);
    log_i("Heap: %d\n", ESP.getFreeHeap());
    log_i("SDK: %s\n", ESP.getSdkVersion());
    log_i("MAC address: %s\n", WiFi.macAddress().c_str());
    log_i("CPU Speed: %dMHz\n", ESP.getCpuFreqMHz());
    log_i("Flash Size: %dKB\n", ESP.getFlashChipSize());
    log_i("[INFO]: System Information Sent\n");
    log_i("\n");

    // FS debug information
    // THIS NEEDS TO BE PAST THE WIFI SETUP!! OTHERWISE WIFI SETUP WILL BE DELAYED
    log_i("SPIFFS contents:\n");
#ifdef ESP32
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file)
    {
        log_i("FS File: %s, size: %i\n", file.name(), file.size());
        file = root.openNextFile();
    }
    log_i("\n");
    unsigned int totalBytes = SPIFFS.totalBytes();
    unsigned int usedBytes = SPIFFS.usedBytes();
    if (usedBytes == 0)
    {
        log_i("NO WEB SERVER FILES PRESENT: \n");
    }
    log_i("FS Size: %iKB, used: %iKB, %0.2f%%\n",
          totalBytes, usedBytes,
          (float)100 / totalBytes * usedBytes);
    log_i("\n");
#endif
}

bool Network::LoopWifiScan()
{
    log_i("[INFO]: Beginning WIFI Network\n");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    log_i("[INFO]: scan done\n");
    if (n == 0)
    {
        log_i("[INFO]: no networks found\n");
        return false;
    }
    else
    {
        log_i("[INFO]: %d networks found\n", n);
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "OPEN");
                break;
            case WIFI_AUTH_WEP:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "WPA_WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "WPA2_ENTERPRISE");
                break;
            default:
                log_i("%d: %s (%d) %s", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), "UNKNOWN");
                break;
            }
            my_delay(0.1L);
            return true;
        }
    }
    log_i("\n");

    // Wait a bit before scanning again
    my_delay(5L);
    return true;
}

Network network;
