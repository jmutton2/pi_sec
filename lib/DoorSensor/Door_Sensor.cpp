#include <Arduino.h>
#include "LP_Peer.h"

// Associated with touch pin 4
#define touchGPIO 4

void Door_Sensor_Loop()
{
    for (;;)
    {
        // Check for DOOR_STATE_CHANGED interrupt
        if (touchRead(touchGPIO) > 50)
        {
            Send_Alert();
            delay(500);
        }
    }
}
