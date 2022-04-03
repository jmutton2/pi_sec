#include <Arduino.h>

// DEFINE THE DEVICE
#define KEYPAD
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
    //##IF DEFINED HP_DEVICE
    // Start HP Server
    // Note >> This needs to connect to other peers

    //##IF DEFINED LP_DEVICE
    // Start LP Server

    //##If DEFINED KEYPAD
    // Create Password

    // Enable System
    // Note >> This needs to be relayed to other peers
}
// -------------------

// LOOP
void loop()
{

    //##IF DEFINED HP_DEVICE
    //#STATE: ARMED
    // Check for UNARM interrupt
    // Check for AWAIT_ALARM interrupt

    //#STATE: UNARMED
    // Check for ARM interrupt

    //##IF DEFINED LP_DEVICE

    //##If DEFINED KEYPAD
    //#STATE: AWAITING ALARM
    // Check for password correctness
    // FALSE => set_state to ALARM_RINGING
    // TRUE => set_state to UNARMED

    //#STATE: ALARM_RINGING
    // Check for password correctness
    // TRUE => set_state to UNARMED

    //##IF DEFINED DOOR_SENSOR
    // Check for DOOR_STATE_CHANGED interrupt
    // Alert (POST) to parent
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