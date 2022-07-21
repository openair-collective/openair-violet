#include "StateManager.hpp"

StateManager<ProgramStates::DeviceStates::State_e> stateManager_Device;
StateManager<ProgramStates::DeviceStates::WiFiState_e> stateManager_WiFi;
StateManager<ProgramStates::DeviceStates::WebServerState_e> stateManager_WebServer;
StateManager<ProgramStates::DeviceStates::ButtonState_e> stateManager_Buttons;
StateManager<ProgramStates::DeviceStates::PumpState_e> stateManager_Pump;
StateManager<ProgramStates::DeviceStates::DatabaseState_e> stateManager_Database;