void Keypad_Loop(Control mem)
{
    // If in await alarm state, give 10 seconds to disarm
    if (mem->system_state == 3)
    {
        delay(10000);
        if (CHECK_PASS() > 0)
        {
            mem->system_state = 2;
        }
        else
        {
            mem->system_state = 4;
        }
    }

    // If in alarm state, give option to reset
    if (mem->system_state == 4)
    {
        if (CHECK_PASS() > 0)
        {
            mem->system_state = 2;
        }
    }
}