#ifndef _HEAD
#define _HEAD

#define ENTER_KEY BIT0
#define ALARM_SIGNAL BIT1
#define ALARM_TIMEOUT BIT2

// DEFINE THE DEVICE
#define KEYPAD
// #define DOOR_SENSOR
//#define CAMERA
//#define AC_SENSOR
//#define NETWORK_SENSOR
//#define DEBUG

//#include "Definitions.h"
#include <Arduino.h>
#include "Control.h"

#if defined KEYPAD || defined NETWORK_SENSOR || defined AC_SENSOR || defined CAMERA
#define HIGH_POWER
#endif

#ifdef DOOR_SENSOR
#define LOW_POWER
#endif

#ifdef HIGH_POWER
#include "HPpeer.h"
#endif

#ifdef LOW_POWER
#include "LP_Peer.h"
#endif

#ifdef KEYPAD
// #include "Touch.h"
//#include "Keypad.h"
#endif

#ifdef DOOR_SENSOR
#include "Door_Sensor.h"
#endif

#ifdef DEBUG
#include "Touch.h"
#endif

// DEFINE PINS

#endif