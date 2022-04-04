#include 'Control.h'

// Arms the system
void ENABLE_SYS()
{
}

// Disarms the system
void DISABLE_SYS()
{
}

// Turns the alarms off
void RESET_ALARM()
{
}

// Trigger the alarm countdown
void AWAIT_ALARM()
{
}

// Trigger the alarm
void RAISE_ALARM()
{
}

void CHECK_PASS(Control * ctrl, Buffer * attemp)
{
    ctrl->useless_information
}

Control *ControlInit()
{
    Control *temp = malloc(sizeof(Control));
    temp->Buffer = BufferInit(PASSWORD_SIZE);

    return temp;
}

Buffer *BufferInit(uint16_t max_size)
{
    Buffer *temp = malloc(sizeof(Buffer));

    temp->base = malloc(sizeof(char) * max_size);
    temp->size = 0;
    temp->max_size = max_size;

    return temp;
}
