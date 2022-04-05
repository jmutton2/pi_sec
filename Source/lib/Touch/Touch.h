#ifndef _TOUCH
#define _TOUCH

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "Control.h"
#include <stdio.h>
#include <string.h>



#define CONFIGURE_GPIO_OUT(_n) ({             \
    gpio_matrix_out(_n, 0x100, false, false); \
    gpio_pad_select_gpio(_n);                 \
    gpio_pad_set_drv(_n, 1);                  \
})

//    REG_SET_BIT(IO_MUX_GPIO ## _n ## _REG, FUN_IE);
#define CONFIGURE_GPIO_IN_PD(_n) ({             \
    REG_SET_BIT(IO_MUX_GPIO##_n##_REG, FUN_IE); \
    gpio_pad_pulldown(_n);                      \
})

//    REG_SET_BIT(IO_MUX_GPIO ## _n ## _REG, FUN_IE);
#define CONFIGURE_GPIO_IN_PU(_n) ({ \
    gpio_pad_pullup(_n);            \
})

#define COL_1 15 // 15
#define COL_2 16 // 16
#define COL_3 0  // 0
#define COL_4 4  // 4
#define ROW_1 12 // 12
#define ROW_2 14 // 14
#define ROW_3 27 // 27
#define ROW_4 26 // 26

#define ENTER_KEY 17 // 17

//Buffer *Touchpad_Buffer = BufferInit(32);
const char Touchpad_Lookup[4][4] = {{'L', '7', '4', '1'},
                                    {'/', '8', '5', '2'},
                                    {'*', '9', '6', '3'},
                                    {'-', '+', 'D', '0'}};



typedef struct _keymask
{
    uint32_t base[4];
} Keymask;

void Init_Touchpad();
void Send_Buffer(Buffer *buff);
void Touchpad_Loop();


#endif