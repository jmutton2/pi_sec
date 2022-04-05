#ifndef _TOUCH
#define _TOUCH

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "Control.h"

typedef struct _keymask
{
    int base[4][4];
} Keymask;

// int debounce;

void Init_Touchpad();
void Send_Buffer(Buffer *buff);
void Touchpad_Loop();
void Poll_Touchpad(Keymask *keymask);

// #include "freertos.h"

#endif