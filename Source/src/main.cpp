#include <Arduino.h>
#include "High_Power_Peer.h"

// Keypad
#define KEYPAD

// Door_Sensor
//#define DOOR_SENSOR

#ifdef KEYPAD
#include <Touch.h>
#endif

#ifdef DOOR_SENSOR

#endif

const int SYS_STATUS = 26; // <<< CHANGE THIS TO WHATEVER PIN THE KEYPAD IS CONNECTION TO
const int ALERT_INTERRUPT = 27;
const int RAISE_ALARM_INTERRUPT = 28;

int countdown = 0;
int sys_enabled = 0;

void setup()
{
  Server_Init();

  // if (keypad)
  // Run Set_Pass()
}

void loop()
{
  attachInterrupt(SYS_STATUS, CHANGE_SYS_STATUS, CHANGE);

  // if (keypad)
  attachInterrupt(ALERT_INTERRUPT, AWAIT_ALARM, HIGH);
  attachInterrupt(RAISE_ALARM_INTERRUPT, RAISE_ALARM, HIGH);

  // Countdown to check for timer
  if (countdown)
  {
    // Timer decrease
    // if (password == saved password)
    // digitalWrite(ALERT_INTERRUPT, LOW);

    // if (password !== saved password)
    //  digitalWrite(RAISE_ALARM_INITERRUPT, HIGH);
  }

  // Check for Remove_Node()
  // > Check for close packet
  // > Send close packet
  // > Close the connection that sent close packet

  // Check for Close_Connection()
  // > Send a request to close packet
  // > Await response and close if close packet received
}

// Enable or Disable the system
void CHANGE_SYS_STATUS()
{
  sys_enabled = !sys_enabled;
}

// Trigger the alarm countdown noise
void AWAIT_ALARM()
{
  countdown = 1;
}

// Trigger the alarm
void RAISE_ALARM()
{
  digitalWrite(ALERT_INTERRUPT, LOW);
  digitalWrite(RAISE_ALARM_INTERRUPT, HIGH);
}