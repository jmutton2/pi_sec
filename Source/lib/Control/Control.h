#ifndef _CTRL
#define _CTRL

#define PASSWORD_SIZE 5

#include <stdlib.h>
#include <Arduino.h>



typedef struct _buffer
{
    char *base;
    int size;
    int max_size;
} Buffer;

typedef struct _control
{
    int system_state;
    Buffer *buffer;
} Control;

Buffer *Buffer_Init(int max_size);
void Buffer_Append(Buffer *buff, const char ch);
int Buffer_Compare(Buffer *buff1, Buffer *buff2);
Buffer *Buffer_Clear(Buffer *buff);
std::string Buffer_To_String(Buffer *buff);

Control *ControlInit(void);

void ENABLE_SYS(Control *);
void DISABLE_SYS(Control *);
void RESET_ALARM(Control *);
void AWAIT_ALARM(Control *);
void RAISE_ALARM(Control *);
int CHECK_PASS(std::string st);
void CREATE_PASS(Control *);

#endif