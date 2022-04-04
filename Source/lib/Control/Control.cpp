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

void CHECK_PASS()
{
}

Control *ControlInit(uint16_t max_size)
{
    Control *temp = malloc(sizeof(Control));
    temp->Buffer = BufferInit(PASSWORD_SIZE);

    return temp;
}