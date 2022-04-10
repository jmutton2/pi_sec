#include <Arduino.h>
#include "Control.h"
#include "LP_Peer.h"

// DEFINE THE DEVICE
#define KEYPAD
// #define DOOR_SENSOR
//#define CAMERA
//#define AC_SENSOR
//#define NETWORK_SENSOR
// #define DEBUG

#if defined KEYPAD || defined NETWORK_SENSOR || defined AC_SENSOR || defined CAMERA
#define HIGH_POWER
#endif

#ifdef DOOR_SENSOR
#define LOW_POWER
#endif

#ifdef HIGH_POWER
#include "HP_Peer.h"
#endif

#ifdef LOW_POWER
#include "LP_Peer.h"
#endif

#ifdef KEYPAD
// #include "Touch.h"
#include "Keypad.h"
#endif

#ifdef DOOR_SENSOR
#include "Door_Sensor.h"
#endif

#ifdef DEBUG
#include "Touch.h"
#endif

// DEFINE SHARED MEMORY
Control *control_ptr = ControlInit();
// -------------------

// DEFINE PINS

void AWAIT_ALARMTEMP()
{
    AWAIT_ALARM(control_ptr);
}
// -------------------

// SETUP
void setup()
{

#ifdef DEBUG
    Init_Touchpad();

#endif

#ifndef DEBUG

#ifdef HIGH_POWER
    Server_Init();
#endif

#ifdef LOW_POWER
    WiFi_Init();
#endif

#ifdef KEYPAD
    // Keypad_Init(control_ptr);
#endif

#ifdef DOOR_SENSOR
#endif

#endif
}
// -------------------

// LOOP
void loop()
{

    attachInterrupt(2, AWAIT_ALARMTEMP, RISING);
    Serial.print(control_ptr->system_state);
    delay(1000);
#ifdef DEBUG
    delay(10);

    Touchpad_Loop();
#endif

#ifndef DEBUG

#ifdef HIGH_POWER
    // HP_Device_Loop(control_ptr);
#endif

#ifdef LOW_POWER
#endif

#ifdef KEYPAD
    // Keypad_Loop(control_ptr);
#endif

#ifdef DOOR_SENSOR
    Door_Sensor_Loop();
#endif

#endif
}
// -------------------