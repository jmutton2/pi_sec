void Door_Sensor_Loop()
{
    // Check for DOOR_STATE_CHANGED interrupt
    // Alert (POST) to parent
    Send_Alert();
}
