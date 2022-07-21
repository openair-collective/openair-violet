#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <Arduino.h>

/*
 * StateManager
 * All Project States are managed here
 */
class ProgramStates
{
public:
    struct DeviceStates
    {
        enum State_e
        {
            Starting,
            Started,
            Stopping,
            Stopped,
            Error
        };

        enum WiFiState_e
        {
            WiFiState_None,
            WiFiState_Connecting,
            WiFiState_Connected,
            WiFiState_Disconnected,
            WiFiState_Disconnecting,
            WiFiState_Error
        };

        enum WebServerState_e
        {
            WebServerState_None,
            WebServerState_Starting,
            WebServerState_Started,
            WebServerState_Stopping,
            WebServerState_Stopped,
            WebServerState_Error
        };

        enum ButtonState_e
        {
            Buttons_OFF,
            Buttons_ON,
            Buttons_PLUS,
            Buttons_MINUS,
            Buttons_ManAut,
            Buttons_Error
        };

        enum PumpState_e
        {
            PUMP_OFF,
            PUMP_ON,
            PUMP_MANUAL,
            PUMP_AUTOMATIC,
            PUMP_SERIAL_REPORT,
            PUMP_Error
        };

        enum DatabaseState_e
        {
            DatabaseState_None,
            DatabaseState_Starting,
            DatabaseState_Started,
            DatabaseState_Stopping,
            DatabaseState_Stopped,
            DatabaseState_Error
        };
    };
};

/*
 * EventManager
 * All Project Events are managed here
 */
template <class T>
class StateManager
{
public:
    StateManager() {}

    virtual ~StateManager() {}

    void setState(T state)
    {
        _current_state = state;
    }

    /*
     * Get States
     * Returns the current state of the device
     */
    T getCurrentState()
    {
        return _current_state;
    }

private:
    T _current_state;
};

extern StateManager<ProgramStates::DeviceStates::State_e> stateManager_Device;
extern StateManager<ProgramStates::DeviceStates::WiFiState_e> stateManager_WiFi;
extern StateManager<ProgramStates::DeviceStates::WebServerState_e> stateManager_WebServer;
extern StateManager<ProgramStates::DeviceStates::ButtonState_e> stateManager_Buttons;
extern StateManager<ProgramStates::DeviceStates::PumpState_e> stateManager_Pump;
extern StateManager<ProgramStates::DeviceStates::DatabaseState_e> stateManager_Database;

#endif // STATEMANAGER_HPP