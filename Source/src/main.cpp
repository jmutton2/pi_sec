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

// Acts as shared memory
const int PASSWORD_STATUS = 20;
const int RING = 21;
const int COUNTDOWN = 22;
const int DISABLE_SYS_KEY = 23;
const int ENABLE_SYS_KEY = 24;
const int ENABLE_NETWORK_PEERS = 25;
const int RESET_ALARM_KEY = 26;
const int ALERT_INTERRUPT = 27;
const int RAISE_ALARM_INTERRUPT = 28;

//------------IDEA__--------------------
// Could have enter trigger a submit which lets the password be readable if the -- nevermind lol

int sys_enabled;

void ENABLE_SYS(void);
void DISABLE_SYS(void);
void RESET_ALARM(void);
void RAISE_ALARM(void);
void AWAIT_ALARM(void);
void CHECK_PASS(void);

void setup()
{
  sys_enabled = 1;

  // if (HIGH_POWER)
  Server_Init();
  // if (ENABLE_NETWORK_PEERS) >> Peer_Init()

  // if (KEYPAD)
  // Run Set_Pass()
}

void loop()
{
  // Interrupt to enable nad disable the system
  // Triggered by change to system rising/falling
  // Could have two pins or just one (ENABLE_SYS_KEY and DISABLE_SYS_KEY)
  // attachInterrupt(DISABLE_SYS_KEY, DISABLE_SYS, FALLING);
  attachInterrupt(ENABLE_SYS_KEY, ENABLE_SYS, RISING);

  // Handles turning off the alarm
  attachInterrupt(RESET_ALARM_KEY, RESET_ALARM, RISING);

  // Sets the pin to ask for a password
  // Checks a password correct pin or password incorrect pin
  attachInterrupt(ALERT_INTERRUPT, AWAIT_ALARM, RISING);
  attachInterrupt(RAISE_ALARM_INTERRUPT, RAISE_ALARM, RISING);

  if (COUNTDOWN)
  {
    // delay(10000) << Wait for 10 seconds
    attachInterrupt(PASSWORD_STATUS, CHECK_PASS, HIGH);
    attachInterrupt(PASSWORD_STATUS, RESET_ALARM, LOW);
  }
}

// Arms the system
void ENABLE_SYS()
{
  sys_enabled = 1;
}

// Disarms the system
void DISABLE_SYS()
{
  sys_enabled = 1;
}

// Turns the alarms off
void RESET_ALARM()
{
  digitalWrite(ALERT_INTERRUPT, LOW);
  digitalWrite(RAISE_ALARM_INTERRUPT, LOW);
}

// Trigger the alarm countdown noise
// Start
void AWAIT_ALARM()
{
  digitalWrite(COUNTDOWN, HIGH);
}

void CHECK_PASS()
{
}

// Trigger the alarm
void RAISE_ALARM()
{
  digitalWrite(ALERT_INTERRUPT, LOW);
  digitalWrite(RAISE_ALARM_INTERRUPT, HIGH);
}