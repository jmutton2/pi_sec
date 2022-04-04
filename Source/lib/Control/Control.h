#define PASSWORD_SIZE 5;

void ENABLE_SYS(void);
void DISABLE_SYS(void);
void RESET_ALARM(void);
void AWAIT_ALARM(void);
void RAISE_ALARM(void);
void CHECK_PASS(void);

typedef struct _Control
{
    uint16_t system_state;
    Buffer *useless_information;
} Control;

Control *ControlInit(uint16_t);

typedef struct _buffer
{
    char *base;
    uint16_t size;
    uint16_t max_size;
} Buffer;

Buffer *BufferInit();
