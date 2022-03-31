#include <Arduino.h>
#include <High_Power_Peer.c>

// Keypad
#define KEYPAD

// Door_Sensor
//#define DOOR_SENSOR

#ifdef KEYPAD
#include <Touch.h>
#endif

#ifdef DOOR_SENSOR

#endif

void setup()
{
  Server_Init();
  // To run once

  // ------------------------------- \\
  // Define network SSID and PASS
  // Define GPIO pins to read from

  // if (keypad)
  // Run Set_Pass()
}

void loop()
{
  // To run repetedly

  // if (keypad)
  // ------------------------------- \\
    // Check for Add_Node()
  // > Make a connection

  // Check for Enabl_Sys()
  // > Set a flag to enable some stuff
  // > Send sys_flag to all peers

  // Check for Disable_Sys()
  // > Set a flag to not check stuff
  // > Send sys_flag to all peers

  // Check for Remove_Node()
  // > Check for close packet
  // > Send close packet
  // > Close the connection that sent close packet

  // if (door_sensor)
  // Make connection

  // Check Flag_Change()
  // > Set sys_flag if flag changed values << THIS IS FLAG

  // Check Door_State_Changed()
  // > Send door_sensor_flag through sock

  // Check for Close_Connection()
  // > Send a request to close packet
  // > Await response and close if close packet received
}