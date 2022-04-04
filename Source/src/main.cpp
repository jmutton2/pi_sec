#include <Arduino.h>
#include "Control.h"
#include "LP_Peer.h"
// DEFINE THE DEVICE
#define KEYPAD
//#define DOOR_SENSOR
//#define CAMERA
//#define AC_SENSOR
//#define NETWORK_SENSOR

#if defined KEYPAD || defined NETWORK_SENSOR || defined AC_SENSOR || defined CAMERA
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
// Control *control_ptr = (Control *)ControlInit();
// -------------------

// DEFINE PINS

// -------------------

// SETUP
void setup()
{
#ifdef HIGH_POWER
    Server_Init();
#endif

#ifdef LOW_POWER
    Wifi_Init();
#endif

#ifdef KEYPAD
    // CREATE_PASS(control_ptr);
    //  Create_Pass();
    //  check for stored password, if none:
    //  Note >> This needs to be relayed to other peers
#endif

    // ENABLE_SYS(control_ptr);
}
// -------------------

// LOOP
void loop()
{
    Send_Alert();
#ifdef HIGH_POWER
    // HP_Device_Loop(control_ptr);
#endif

#ifdef LOW_POWER
    // Send_Alert(control_ptr);
#endif

#ifdef KEYPAD
    // Keypad_Loop(control_ptr);
#endif

#ifdef DOOR_SENSOR
    // Door_Sensor_Loop();
#endif
}
// -------------------