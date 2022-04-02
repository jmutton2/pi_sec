#include <Arduino.h>

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
#include "High_Power_Peer.h"
#endif

#ifdef LOW_POWER
#include "Low_Power_peer.h"
#endif

#ifdef KEYPAD
#include <Touch.h>
#endif

#ifdef DOOR_SENSOR

#endif

// DEFINE SHARED MEMORY

// -------------------

// DEFINE PINS

// -------------------

// DEFINE FUNCTIONS

// -------------------

// SETUP
void setup()
{
}
// -------------------

// LOOP
void loop()
{
}
// -------------------

// Arms the system
void ENABLE_SYS()
{
}

// Disarms the system
void DISABLE_SYS()
{
}

// Turns the alarms off
void RESET_ALARM()
{
}

// Trigger the alarm countdown
void AWAIT_ALARM()
{
}

// Trigger the alarm
void RAISE_ALARM()
{
}

void CHECK_PASS()
{
}