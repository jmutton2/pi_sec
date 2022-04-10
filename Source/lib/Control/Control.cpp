#include "Control.h"

#define DEBUG

int CHECK_PASS(std::string st)
{
    static std::string pass = st; // first time you call this function, set pass

    if (pass.compare(st) == 0)
    {
        return 1;
    }
    else
        return 0;
    // Compare mem->useless_information with mem2->uselessInformation
    // If equal >> RESET_ALARM(mem)
}

// Reads input from user
std::string GET_INPUT()
{
    char key_read;
    std::string temp;
    while (pdTRUE == xQueueReceive(pushed_input_handle, &key_read, (TickType_t)50))
    {
        temp = temp + key_read;
    }
    return temp;
}

// Waiting to be armed
// Disarmed state
void AWAIT_ARM(void *pvParameters)
{
#ifdef DEBUG
    Serial.println("IN AWAIT_ARM");
#endif
    std::string in;
    for (;;)
    {

        xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, portMAX_DELAY);

        // Check for L user input to lock/arm system
        in = GET_INPUT();
        std::string arm = "L";
        if (in.compare(arm) == 0)
        {
            xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, portMAX_DELAY);

            // Await user password
            in = GET_INPUT();
            if (CHECK_PASS(in))
            {
                if (armSys)
                {
                    vTaskResume(armSys);
                    vTaskSuspend(NULL);
                }
                else
                {

                    xTaskCreatePinnedToCore(
                        ARM_SYS,              /* Function to implement the task */
                        "System armed state", /* Name of the task */
                        400,                  /* Stack size in words */
                        NULL,                 /* Task input parameter */
                        0,                    /* Priority of the task */
                        &armSys,              /* Task handle. */
                        1);                   /* Core where the task should run */
                }
            }
        }
    }
}

// Arms the system
// Note >> This needs to be relayed to other peers
void ARM_SYS(void *pvParameters)
{
#ifdef DEBUG
    Serial.println("IN ARM_SYS");
#endif
    std::string in;
    for (;;)
    {

        EventBits_t ret;
        ret = xEventGroupWaitBits(touch_event_bits, (ENTER_KEY + ALARM_SIGNAL), 1, 0, portMAX_DELAY);
        if (ret & ALARM_SIGNAL)
        {
            if (awaitAlarm)
            {
                vTaskResume(awaitAlarm);
                vTaskSuspend(NULL);
            }
            else
            {
                xTaskCreatePinnedToCore(
                    AWAIT_ALARM,                 /* Function to implement the task */
                    "Alarm Tripped, await pass", /* Name of the task */
                    400,                         /* Stack size in words */
                    NULL,                        /* Task input parameter */
                    0,                           /* Priority of the task */
                    &awaitAlarm,                 /* Task handle. */
                    1);                          /* Core where the task should run */
            }
        }
        else
        {

            in = GET_INPUT();
            std::string disarm = "-";
            if ((in.compare(disarm) == 0))
            {
                vTaskResume(awaitArm);
                vTaskSuspend(NULL);
            }
        }
    }
}

// Trigger the alarm countdown
void AWAIT_ALARM(void *pvParameters)
{
#ifdef DEBUG
    Serial.println("IN WAIT ALARM");
#endif
    int wrongAttempts = 0;
    alarmTimer = xTimerCreateStatic(
        "Alarm Timer",        // Human readable name
        pdMS_TO_TICKS(20000), // Timer period
        pdFALSE,              // auto reload timer
        &alarmTimer,          // Timer ID
        ALARM_TIMER_TIMEOUT,  // Callback function
        &alarmTimerBuffer     // state buffer. Stores timer state
    );

    xTimerStart(alarmTimer, (TickType_t)100);

    std::string in;
    EventBits_t ret;
    for (;;)
    {
        ret = xEventGroupWaitBits(touch_event_bits, (ENTER_KEY + ALARM_TIMEOUT), 1, 0, pdMS_TO_TICKS(25000));
        if (ret & ENTER_KEY)
        {
            in = GET_INPUT();
            if (CHECK_PASS(in))
            {
                xTimerDelete(alarmTimer, portMAX_DELAY);
                vTaskResume(awaitArm);
                vTaskDelete(NULL);
            }
            else if (wrongAttempts < 3)
            {
                wrongAttempts++;
            }
            else
            {
                if (raiseAlarm)
                {
                    vTaskResume(raiseAlarm);
                    vTaskDelete(NULL);
                }
                else
                {
                    xTaskCreatePinnedToCore(
                        RAISE_ALARM,   /* Function to implement the task */
                        "Raise alarm", /* Name of the task */
                        300,           /* Stack size in words */
                        NULL,          /* Task input parameter */
                        0,             /* Priority of the task */
                        &raiseAlarm,   /* Task handle. */
                        1);            /* Core where the task should run */
                }
            }
        }
        if (ret & ALARM_TIMEOUT)
        {
            if (raiseAlarm)
            {
                vTaskResume(raiseAlarm);
                vTaskDelete(NULL);
            }
            else
            {
                xTaskCreatePinnedToCore(
                    RAISE_ALARM,   /* Function to implement the task */
                    "Raise alarm", /* Name of the task */
                    300,           /* Stack size in words */
                    NULL,          /* Task input parameter */
                    0,             /* Priority of the task */
                    &raiseAlarm,   /* Task handle. */
                    1);
            }
        }
    }
}

// Trigger the alarm
void ALARM_TIMER_TIMEOUT(TimerHandle_t xtimer)
{
    xEventGroupSetBits(control_bits, ALARM_TIMEOUT); // This might be realy fucky, since its a timer... Is this an interrupt?
}

void RAISE_ALARM(void *pvParameters)
{
#ifdef DEBUG
    Serial.println("INTRUDER DETECTED");
#endif
}

void Create_Password(void *pvParameters)
{
    xEventGroupWaitBits(touch_event_bits, BIT0, 1, 0, portMAX_DELAY);

    char key_read;
    std::string temp;
    while (pdTRUE == xQueueReceive(pushed_input_handle, &key_read, (TickType_t)50))
    {
        temp = temp + key_read;
        // NEEED CODE HERE DO SOMETHING WITH THIS CHARACTER STUFF PLEASE ALKflksjdlk;fjasl;kdnfl;ka
        // alskjfisladflnshklfhkjasdfkljahskdjlfhjkas
        // spiGeMode
    }
    CHECK_PASS(temp);

    xEventGroupWaitBits(touch_event_bits, BIT0, 1, 0, portMAX_DELAY);

    std::string temp2;
    while (pdTRUE == xQueueReceive(pushed_input_handle, &key_read, (TickType_t)50))
    {
        temp2 = temp2 + key_read;
        // NEEED CODE HERE DO SOMETHING WITH THIS CHARACTER STUFF PLEASE ALKflksjdlk;fjasl;kdnfl;ka
        // alskjfisladflnshklfhkjasdfkljahskdjlfhjkas
        // spiGeMode
    }
    if (CHECK_PASS(temp2))
    {
        Serial.println("Password OK!");

        xTaskCreatePinnedToCore(
            AWAIT_ARM,          /* Function to implement the task */
            "Wait to be armed", /* Name of the task */
            1000,               /* Stack size in words */
            NULL,               /* Task input parameter */
            0,                  /* Priority of the task */
            &awaitArm,          /* Task handle. */
            1);                 /* Core where the task should run */

        vTaskDelete(NULL);
    }
    else
    {
        Serial.println("Password NOT OK! Restarting......");
        // you fucked up
        ESP.restart();
    }
}

void Init_Control()
{
    // epic
    xTaskCreatePinnedToCore(
        Create_Password,   /* Function to implement the task */
        "Create Password", /* Name of the task */
        1000,              /* Stack size in words */
        NULL,              /* Task input parameter */
        0,                 /* Priority of the task */
        &makePass,         /* Task handle. */
        1);                /* Core where the task should run */
}

// int CHECK_PASS(std::string st)
// {
//     static std::string pass = st; // first time you call this function, set pass

//     if (pass.compare(st) == 0)
//     {
//         return 1;
//     }
//     else
//         return 0;
//     // Compare mem->useless_information with mem2->uselessInformation
//     // If equal >> RESET_ALARM(mem)
// }
