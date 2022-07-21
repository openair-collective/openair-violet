#if K30_SUPPORT
#include <sensors/K30/K30.hpp>
#endif // K30_SUPPORT
#if SCD30_SUPPORT
#include <sensors/SCD30/SCD30.hpp>
#endif // SCD30_SUPPORT

#include "network/network.hpp"
#include "network/database/firebase/networkfirebase.hpp"

void setup()
{
  Serial.begin(BAUD_RATE);
#if SCD30_SUPPORT
  SCD30_airSensor.begin();
#endif // SCD30_SUPPORT
  network.SetupServer(); // initialise the server file system and print details of the network
  network.SetupWebServer(); // initialise the web server
  networkFirebase.begin_firebase(); // initialise the firebase
}

void loop()
{
#if K30_SUPPORT
  K30_airSensor.loopSensor();
#endif // K30_SUPPORT
#if SCD30_SUPPORT
  SCD30_airSensor.loopSensor();
#endif // SCD30_SUPPORT
  network.CheckNetworkLoop(); // check the network loop
  networkFirebase.process_firebase(); // process the firebase
}