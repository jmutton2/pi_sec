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