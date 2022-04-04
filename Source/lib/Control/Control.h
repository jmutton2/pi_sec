#define PASSWORD_SIZE 5;

typedef struct _buffer
{
    char *base;
    uint16_t size;
    uint16_t max_size;
} Buffer;

Buffer *BufferInit();

typedef struct _Control
{
    uint16_t system_state;
    Buffer *useless_information;
} Control;

Control *ControlInit();

void ENABLE_SYS(Control *);
void DISABLE_SYS(Control *);
void RESET_ALARM(Control *);
void AWAIT_ALARM(Control *);
void RAISE_ALARM(Control *);
void CHECK_PASS(Control *, Control *);
void CREATE_PASS(Control *);
