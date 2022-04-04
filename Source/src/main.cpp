#include <Arduino.h>
#include "Control.h"

// DEFINE THE DEVICE
//#define KEYPAD
//#define DOOR_SENSOR
//#define CAMERA
//#define AC_SENSOR
//#define NETWORK_SENSOR

#ifdef KEYPAD || NETWORK_SENSOR || AC_SENSOR || CAMERA
#define HIGH_POWER
#endif

#ifdef DOOR_SENSOR
#define LOW_POWER
#endif

#ifdef HIGH_POWER
#include "HP_Peer.h"
#include "HP_Loop.h"
#endif

#ifdef LOW_POWER
#include "LP_Peer.h"
#include "LP_Loop.h"
#endif

#ifdef KEYPAD
#include <Touch.h>
#include "KP_Loop.h"
#endif

#ifdef DOOR_SENSOR
#include "DS_Loop.h"
#endif

// DEFINE SHARED MEMORY

// -------------------

// DEFINE PINS

// -------------------

// SETUP
void setup()
{
    //##IF DEFINED HP_DEVICE
    // Server_Init();

    //##IF DEFINED LP_DEVICE
    // Wifi_Init();

    //##If DEFINED KEYPAD
    // Create_Pass();
    // check for stored password, if none:
    // Note >> This needs to be relayed to other peers

    // Enable_Sys();
    // Note >> This needs to be relayed to other peers
}
// -------------------

// LOOP
void loop()
{
    //##IF DEFINED HP_DEVICE
    // HP_Device_Loop();

    //##IF DEFINED LP_DEVICE

    //##If DEFINED KEYPAD
    // Keypad_Loop();

    //##IF DEFINED DOOR_SENSOR
    // Door_Sensor_Loop();
}
// -------------------