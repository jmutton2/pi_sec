// Arms the system
// Note >> This needs to be relayed to other peers
void ENABLE_SYS(Control *mem)
{
    mem->system_state = 1;
}

// Disarms the system
void DISABLE_SYS(Control *mem)
{
    mem->system_state = 2;
}

// Turns the alarms off
void RESET_ALARM(Control *mem)
{
    mem->system_state = 1;
}

// Trigger the alarm countdown
void AWAIT_ALARM(Control *mem)
{
    mem->system_state = 3;
    // Start a countdown for 10 seconds
    // if CHECK_PASS() > 0
    // RESET_ALARM()
}

// Trigger the alarm
void RAISE_ALARM(Control *mem)
{
    mem->system_state = 4;
    // if CHECK_PASS() > 0
    // RESET_ALARM()
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
