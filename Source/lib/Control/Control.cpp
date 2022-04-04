#include "Control.h"

// Waiting to be armed
void AWAIT_ARM(Control *mem)
{
    mem->system_state = 1;
}

// Arms the system
// Note >> This needs to be relayed to other peers
void ENABLE_SYS(Control *mem)
{
    mem->system_state = 2;
}

// Disarms the system
void DISABLE_SYS(Control *mem)
{
    mem->system_state = 3;
}

// Turns the alarms off
void RESET_ALARM(Control *mem)
{
    mem->system_state = 2;
}

// Trigger the alarm countdown
void AWAIT_ALARM(Control *mem)
{
    mem->system_state = 4;
    // Start a countdown for 10 seconds
    // if CHECK_PASS() > 0
    // RESET_ALARM()
    // else
    // RAISE_ALARM()
}

// Trigger the alarm
void RAISE_ALARM(Control *mem)
{
    mem->system_state == 5;
    // if CHECK_PASS() > 0
    // RESET_ALARM() << Return to state 1 (new state)
}

void CHECK_PASS()
{
    // Compare mem->useless_information with mem2->uselessInformation
    // If equal >> RESET_ALARM(mem)
}

void CREATE_PASS()
{
    // Check if pass exists
    // if mem->useless_information
    // return
    // If no pass exists
    // mem->useless_inforomation = mem2?
}

Control *ControlInit()
{
    Control *temp = (Control *)malloc(sizeof(Control));
    temp->buffer = BufferInit(PASSWORD_SIZE);

    return temp;
}

Buffer *BufferInit(int max_size)
{
    Buffer *temp = (Buffer *)malloc(sizeof(Buffer));

    temp->base = (char *)malloc(sizeof(char) * max_size);
    temp->size = 0;
    temp->max_size = max_size;

    return temp;
}
