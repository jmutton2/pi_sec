
#include "headers.h"

// SETUP
void setup()
{

#ifdef DEBUG
    // Init_Touchpad();
#endif

#ifndef DEBUG

#ifdef KEYPAD
    Init_Touchpad();
    Init_Control();
    Server_Init();
#endif

#ifdef DOOR_SENSOR
    WiFi_Init();
    Door_Sensor_Loop();
#endif

#endif
}

void loop()
{
    vTaskDelete(NULL);
}
// -------------------