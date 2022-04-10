
#include "headers.h"

// SETUP
void setup()
{

#ifdef DEBUG
    Init_Touchpad();
#endif

#ifndef DEBUG

    control_bits = xEventGroupCreate();
#ifdef KEYPAD
    Init_Touchpad();
    Init_Control();
#endif

#ifdef DOOR_SENSOR
    Door_Sensor_Loop();
#endif

#endif
}

void loop()
{
    vTaskDelete(NULL);
}
// -------------------

// DEFINE INTERRUPTS HANDLERS

void AWAIT_ALARM_INTERRUPT()
{
    AWAIT_ALARM(control_ptr);
}

// -------------------