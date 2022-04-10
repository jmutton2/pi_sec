#ifndef _CTRL
#define _CTRL

#define PASSWORD_SIZE 5

#include <Arduino.h>
#include <stdlib.h>
#include "Definitions.h"
#include "Keypad.h"


EventGroupHandle_t control_bits;

TaskHandle_t armSys;
TaskHandle_t awaitArm;
TaskHandle_t awaitAlarm;
TaskHandle_t raiseAlarm;

TimerHandle_t alarmTimer;
StaticTimer_t alarmTimerBuffer;
int alarmTimerID = 1;

void ARM_SYS(void *);
std::string GET_INPUT(void);
void AWAIT_ARM(void *);
void ALARM_TIMER_TIMEOUT(void *);
void AWAIT_ALARM(void *);
void RAISE_ALARM(void *);
void Init_Control();

#endif
