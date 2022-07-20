#include "StateManager.hpp"

StateManager<ProgramStates::DeviceStates::State_e> StateManager_Device;
StateManager<ProgramStates::DeviceStates::WiFiState_e> StateManager_WiFi;
StateManager<ProgramStates::DeviceStates::WebServerState_e> StateManager_WebServer;
StateManager<ProgramStates::DeviceStates::MDNSState_e> StateManager_MDNS;
StateManager<ProgramStates::DeviceStates::MQTTState_e> StateManager_MQTT;
StateManager<ProgramStates::DeviceStates::ButtonState_e> StateManager_Buttons;
StateManager<ProgramStates::DeviceStates::PumpState_e> StateManager_Pump;