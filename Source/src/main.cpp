#include <Arduino.h>

#define KEYPAD
//#define DOOR_SENSOR
// Define other nodes to be made

#ifdef KEYPAD
#include <Touch.h>
#endif

#ifdef DOOR_SENSOR

#endif

void setup()
{
  // To run once

  // ------------------------------- \\
  // Define network SSID and PASS
  // Define GPIO pins to read from
  // Run setPass()
}

void loop()
{
  // To run repetedly

  // if (keypad)
  // ------------------------------- \\
    // Check for addNode()
  // > Make a connection

  // Check for enableSys()
  // > Set a flag to enable some stuff

  // Check for disableSys()
  // > Set a flag to not check stuff

  // Check for removeNode()
  // > Remove the node that is pinging some specific thing
}