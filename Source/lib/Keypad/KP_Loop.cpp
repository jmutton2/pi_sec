void Keypad_Loop()
{
    //#STATE: AWAITING ALARM
    // Check for password correctness
    // FALSE => set_state to ALARM_RINGING
    // TRUE => set_state to UNARMED

    //#STATE: ALARM_RINGING
    // Check for password correctness
    // TRUE => set_state to UNARMED
}