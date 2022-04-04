#define PASSWORD_SIZE 5

#include <stdlib.h>

typedef struct _buffer
{
    char *base;
    int size;
    int max_size;
} Buffer;

Buffer *BufferInit(int max_size);

typedef struct _Control
{
    int system_state;
    Buffer *buffer;
} Control;

Control *ControlInit();

void ENABLE_SYS(Control *);
void DISABLE_SYS(Control *);
void RESET_ALARM(Control *);
void AWAIT_ALARM(Control *);
void RAISE_ALARM(Control *);
void CHECK_PASS(Control *, Buffer *);
void CREATE_PASS(Control *);
