#ifndef _KEYPAD
#define _KEYPAD

#ifndef test
#define test
//#include "Definitions.h"
#endif

#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define CONFIGURE_GPIO_OUT(_n) ({             \
    gpio_matrix_out(_n, 0x100, false, false); \
    gpio_pad_select_gpio(_n);                 \
    gpio_pad_set_drv(_n, 1);                  \
    gpio_pad_pulldown(_n);                    \
    REG_WRITE(IO_MUX_GPIO##_n##_REG, 10880);  \
})

//    REG_SET_BIT(IO_MUX_GPIO ## _n ## _REG, FUN_IE);
#define CONFIGURE_GPIO_IN_PD(_n) ({             \
    REG_SET_BIT(IO_MUX_GPIO##_n##_REG, FUN_IE); \
    gpio_pad_pulldown(_n);                      \
})

//    REG_SET_BIT(IO_MUX_GPIO ## _n ## _REG, FUN_IE);
#define CONFIGURE_GPIO_IN_PU(_n) ({             \
    REG_SET_BIT(IO_MUX_GPIO##_n##_REG, FUN_IE); \
    gpio_pad_pullup(_n);                        \
})

//*********VERY IMPORTANT**********
// IF CHANGING, YOU MUST ALSO CHANGE THE VALUES IN TOUCH_INIT()
#define COL_1 15 // 15
#define COL_2 16 // 16
#define COL_3 0  // 0
#define COL_4 4  // 4
#define ROW_1 12 // 12
#define ROW_2 14 // 14
#define ROW_3 27 // 27
#define ROW_4 26 // 26

#define ENTER_KEY_GPIO 17 // 17

// Buffer *Touchpad_Buffer = BufferInit(32);
const char Touchpad_Lookup[4][4] = {{'L', '7', '4', '1'},
                                    {'/', '8', '5', '2'},
                                    {'*', '9', '6', '3'},
                                    {'-', '+', 'D', '0'}};

int CHECK_PASS(std::string);
void Init_Touchpad();
void Touchpad_Loop(void *);
void Create_Password(void *);

void Keypad_Init(void);



#endif

// void Keypad_Init(void );
// void Keypad_Loop(void );
