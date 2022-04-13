//#include "Keypad.h"
#include "Control.h"

#define DEBUG

EventGroupHandle_t control_bits;

TaskHandle_t armSys;
TaskHandle_t awaitArm;
TaskHandle_t awaitAlarm;
TaskHandle_t raiseAlarm;

TimerHandle_t alarmTimer;
StaticTimer_t alarmTimerBuffer;
int alarmTimerID = 1;
/* Declare a variable to hold the created event group. */

//#define DEBUG

TaskHandle_t touchpadLoop;

EventGroupHandle_t touch_event_bits;

TaskHandle_t Task0;
TaskHandle_t Task1;
QueueHandle_t keypad_queue_handle;
QueueHandle_t pushed_input_handle;

QueueHandle_t Get_Input_Handle()
{
    return pushed_input_handle;
}

void Init_Touchpad()
{
    keypad_queue_handle = xQueueCreate(64, sizeof(char));
    pushed_input_handle = xQueueCreate(64, sizeof(char));

    touch_event_bits = xEventGroupCreate();
    // must be literals because of precompiler directives.
    CONFIGURE_GPIO_OUT(15); // COLUMN 1
    CONFIGURE_GPIO_OUT(16); // COLUMN 2
    CONFIGURE_GPIO_OUT(0);  // COLUMN 3
    CONFIGURE_GPIO_OUT(4);  // COLUMN 3

    CONFIGURE_GPIO_IN_PD(12); // row 1
    CONFIGURE_GPIO_IN_PD(14); // row 2
    CONFIGURE_GPIO_IN_PD(27); // row 3
    CONFIGURE_GPIO_IN_PD(26); // row 4

    CONFIGURE_GPIO_IN_PU(17); // ENTER KEY

    Serial.begin(115200);

#ifdef DEBUG2

    Serial.printf("\nRegister for GPIO 4: %d \n", GPIO_REG_READ(IO_MUX_GPIO4_REG));
    Serial.printf("Register for GPIO 0: %d \n", GPIO_REG_READ(IO_MUX_GPIO0_REG));
    Serial.printf("Register for GPIO 15: %d \n", GPIO_REG_READ(IO_MUX_GPIO15_REG));
    Serial.printf("Register for GPIO 16: %d \n", GPIO_REG_READ(IO_MUX_GPIO0_REG));

    Serial.printf("\nRegister for GPIO 4: %d \n", GPIO_REG_READ(GPIO_PIN4_REG));
    Serial.printf("Register for GPIO 0: %d \n", GPIO_REG_READ(GPIO_PIN0_REG));
    Serial.printf("Register for GPIO 15: %d \n", GPIO_REG_READ(GPIO_PIN15_REG));
    Serial.printf("Register for GPIO 16: %d \n", GPIO_REG_READ(GPIO_PIN16_REG));

    Serial.printf("\nRegister for GPIO 4: %d \n", GPIO_REG_READ(GPIO_FUNC4_OUT_SEL_CFG_REG));
    Serial.printf("Register for GPIO 0: %d \n", GPIO_REG_READ(GPIO_FUNC0_OUT_SEL_CFG_REG));
    Serial.printf("Register for GPIO 15: %d \n", GPIO_REG_READ(GPIO_FUNC15_OUT_SEL_CFG_REG));
    Serial.printf("Register for GPIO 16: %d \n", GPIO_REG_READ(GPIO_FUNC16_OUT_SEL_CFG_REG));

#endif

    xTaskCreatePinnedToCore(
        Touchpad_Loop,            /* Function to implement the task */
        "Keyboard functionality", /* Name of the task */
        2000,                     /* Stack size in words */
        NULL,                     /* Task input parameter */
        0,                        /* Priority of the task */
        &touchpadLoop,            /* Task handle. */
        1);                       /* Core where the task should run */
}

void Touchpad_Loop(void *pvParameters)
{
    for (;;)
    {
        vTaskDelay((TickType_t)50);

        static int EnterKeyDebounce = 0;
        static uint32_t last_base[] = {0, 0, 0, 0};
        const uint8_t columns[] = {COL_1, COL_2, COL_3, COL_4};
        const uint8_t rows[] = {ROW_1, ROW_2, ROW_3, ROW_4};
        uint32_t base[4];
        static uint32_t mask = ((1 << ROW_1) + (1 << ROW_2) + (1 << ROW_3) + (1 << ROW_4));

        for (int counter = 0; counter <= 3; counter++)
        {
            REG_WRITE(GPIO_OUT_W1TS_REG, 1 << columns[counter]);
            gpio_input_get(); // Checking the registers to sink the residual charge. Problems with ghost presses otherwise.
            base[counter] = mask & gpio_input_get();
            REG_WRITE(GPIO_OUT_W1TC_REG, 1 << columns[counter]);
        }

        for (int i = 0; i <= 3; i++)
        {
            if (base[i] != last_base[i])
            {
                // Serial.printf("Change detected: %d \n", base[i]);
                last_base[i] = base[i];
                for (int j = 0; j <= 3; j++)
                {
                    if (base[i] & (1 << rows[j]))
                    {
                        char key_pressed = Touchpad_Lookup[i][j];
                        xQueueSend(keypad_queue_handle, &key_pressed, portMAX_DELAY);
                        // Buffer_Append(pass_buff, Touchpad_Lookup[i][j]);
                        // Serial.printf("key pressed: %c \n", Touchpad_Lookup[i][j]);
#ifdef DEBUG
                        Serial.printf("Base[%d] compared: %d --------", i, base[i]);
                        Serial.printf("Row mask: %d -----", (1 << rows[j]));
                        Serial.printf(" j and i values: %d, %d \n", j, i);

                        Serial.printf("key pressed: %c \n", Touchpad_Lookup[i][j]);

#endif
                    }
                }
            }
        }

        int enter = digitalRead(ENTER_KEY_GPIO);

        if (LOW == enter && EnterKeyDebounce != enter)
        {
            char key_printing;
            Serial.println("printing");
            while (pdTRUE == xQueueReceive(keypad_queue_handle, &key_printing, ((TickType_t)10)))
            {

                xQueueSend(pushed_input_handle, &key_printing, ((TickType_t)1000));
                // TODO
                // Make task that pushes keypad queue to pushed input queue
                //  When the enter key gets pressed, it will try to take a semaphore to push
                //  It will write to a pushed buffer or queue (which one?)
                // then will release semaphore
                Serial.print(key_printing);
            }
            Serial.print('\n');
            xEventGroupSetBits(touch_event_bits, ENTER_KEY_GPIO);
            // pass_buff = Buffer_Clear(pass_buff);
            //  Send_Buffer();
        }
        EnterKeyDebounce = enter;
    }
}

///////////////////////////////////////////////////////////Control Code Begins

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

void Keypad_Init(void)
{

    Init_Touchpad();
}

//#define DEBUG

TaskHandle_t makePass;
QueueHandle_t input_handle;

// static std::string pass;

// int CHECK_PASS(std::string st)
// {
//     pass = st; // first time you call this function, set pass

//     if (pass.compare(st) == 0)
//     {
//         return 1;
//     }
//     else
//         return 0;
//     // Compare mem->useless_information with mem2->uselessInformation
//     // If equal >> RESET_ALARM(mem)
// }

// Reads input from user

// Waiting to be armed
// Disarmed state

void CREATE_ARM_SYS()
{
#ifdef DEBUG
    Serial.println("armSys does not exist. Creating");
#endif

    BaseType_t TaskCreateReturn = xTaskCreatePinnedToCore(
        ARM_SYS,              /* Function to implement the task */
        "System armed state", /* Name of the task */
        2000,                 /* Stack size in words */
        NULL,                 /* Task input parameter */
        0,                    /* Priority of the task */
        &armSys,              /* Task handle. */
        1);                   /* Core where the task should run */

    if (TaskCreateReturn == pdPASS)
    {
#ifdef DEBUG
        Serial.println("Created OK!");
#endif
        vTaskDelete(NULL);
    }
    else if (TaskCreateReturn == pdFAIL)
    {
#ifdef DEBUG
        Serial.println("Something went wrong");
#endif
    }
}

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
#ifdef DEBUG
            Serial.println("Lock Command, Enter password: ");
#endif
            xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, portMAX_DELAY);

            // Await user password
            in = GET_INPUT();
            if (CHECK_PASS(in))
            {
#ifdef DEBUG
                Serial.println("Password OK! Locking...");
#endif
                CREATE_ARM_SYS();
            }
        }
    }
}

void ALARM_SIGNAL_TRIGGER_ISR()
{
    BaseType_t xHigherPriortyTaskWoken, xResult;

    xHigherPriortyTaskWoken = pdFALSE;

    xResult = xEventGroupSetBitsFromISR(touch_event_bits, ALARM_SIGNAL, &xHigherPriortyTaskWoken);

    if (xResult != pdFAIL && xHigherPriortyTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}

// Arms the system
// Note >> This needs to be relayed to other peers
void ARM_SYS(void *pvParameters)
{
    // digitalWrite(19, LOW);
    xEventGroupClearBits(touch_event_bits, ALARM_SIGNAL);

    attachInterrupt(19, ALARM_SIGNAL_TRIGGER_ISR, RISING);
#ifdef DEBUG
    Serial.println("IN ARM_SYS");
#endif
    std::string in;
    EventBits_t ret;
    in = "";
    for (;;)
    {

        ret = xEventGroupWaitBits(touch_event_bits, (ENTER_KEY + ALARM_SIGNAL), 1, 0, portMAX_DELAY);
        if (ret & ALARM_SIGNAL)
        {
#ifdef DEBUG
            Serial.println("ALARM Tripped through Web");
#endif

            xTaskCreatePinnedToCore(
                AWAIT_ALARM,                /* Function to implement the task */
                "Alarm Tripped await pass", /* Name of the task */
                2000,                       /* Stack size in words */
                NULL,                       /* Task input parameter */
                0,                          /* Priority of the task */
                &awaitAlarm,                /* Task handle. */
                1);                         /* Core where the task should run */
            vTaskDelete(NULL);
        }
        else
        {

            in = GET_INPUT();
            std::string disarm = "-";
            if ((in.compare(disarm) == 0))
            {
#ifdef DEBUG
                Serial.println("Disarming Command: Enter Pass");
#endif
                xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, pdMS_TO_TICKS(10000));

                // Await user password
                in = GET_INPUT();
                if (CHECK_PASS(in))
                {
#ifdef DEBUG
                    Serial.println("Password OK! Disarming");
#endif
                    xTaskCreatePinnedToCore(
                        AWAIT_ALARM,                /* Function to implement the task */
                        "Alarm Tripped await pass", /* Name of the task */
                        2000,                       /* Stack size in words */
                        NULL,                       /* Task input parameter */
                        0,                          /* Priority of the task */
                        &awaitAlarm,                /* Task handle. */
                        1);
                    /* Core where the task should run */ // BUG HERE, it says password ok but then reboots
                    vTaskDelete(NULL);
                }
#ifdef DEBUG
                Serial.println("Password Not OK or Timeout! System Still armed");
#endif
            }
        }
    }
}

// Trigger the alarm countdown
void AWAIT_ALARM(void *pvParameters)
{
#ifdef DEBUG
    Serial.println("IN WAIT ALARM. Enter Password to avoid death");
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

    std::string input;
    EventBits_t ret;
    for (;;)
    {
        ret = xEventGroupWaitBits(touch_event_bits, (ENTER_KEY + ALARM_TIMEOUT), 1, 0, pdMS_TO_TICKS(25000));
        if (ret & ENTER_KEY)
        {
            input = GET_INPUT();
#ifdef DEBUG
            Serial.printf("1 or 0 ? it is: %d", CHECK_PASS(input));
#endif
            if (CHECK_PASS(input))
            {
#ifdef DEBUG
                Serial.println("Password OK! Disarming");
#endif
                xTimerDelete(alarmTimer, portMAX_DELAY);
                xTaskCreatePinnedToCore(
                    AWAIT_ALARM,                /* Function to implement the task */
                    "Alarm Tripped await pass", /* Name of the task */
                    2000,                       /* Stack size in words */
                    NULL,                       /* Task input parameter */
                    0,                          /* Priority of the task */
                    &awaitAlarm,                /* Task handle. */
                    1);                         /* Core where the task should run */
                vTaskDelete(NULL);
            }
            else if (wrongAttempts < 3 && CHECK_PASS(input) != 1)
            {
                wrongAttempts++;
#ifdef DEBUG
                Serial.printf("Password NOT OK! You have %d tries left \n", (3 - wrongAttempts));
#endif
            }
            else
            {
#ifdef DEBUG
                Serial.println("Too many wrong attempts. Prepare to die");
#endif

                xTaskCreatePinnedToCore(
                    RAISE_ALARM,   /* Function to implement the task */
                    "Raise alarm", /* Name of the task */
                    1000,          /* Stack size in words */
                    NULL,          /* Task input parameter */
                    0,             /* Priority of the task */
                    &raiseAlarm,   /* Task handle. */
                    1);            /* Core where the task should run */
                vTaskDelete(NULL);
            }
        }
        if (ret & ALARM_TIMEOUT)
        {
#ifdef DEBUG
            Serial.println("TIMES UP. Prepare to die");
#endif

            xTaskCreatePinnedToCore(
                RAISE_ALARM,   /* Function to implement the task */
                "Raise alarm", /* Name of the task */
                1000,          /* Stack size in words */
                NULL,          /* Task input parameter */
                0,             /* Priority of the task */
                &raiseAlarm,   /* Task handle. */
                1);
            vTaskDelete(NULL);
        }
    }
}

// Trigger the alarm
void ALARM_TIMER_TIMEOUT(TimerHandle_t xtimer)
{
#ifdef DEBUG
    Serial.println("Alarm Timer Timeout!!!! ");
#endif
    xEventGroupSetBits(touch_event_bits, ALARM_TIMEOUT); // This might be realy fucky, since its a timer... Is this an interrupt?
}

void RAISE_ALARM(void *pvParameters)
{
    for (;;)
    {
#ifdef DEBUG
        Serial.println("INTRUDER DETECTED");
#endif
    }
}

void Create_Password(void *pvParameters)
{
    xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, portMAX_DELAY);

    std::string temp = GET_INPUT();
    CHECK_PASS(temp);

    xEventGroupWaitBits(touch_event_bits, ENTER_KEY, 1, 0, portMAX_DELAY);

    std::string temp2 = GET_INPUT();
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

        vTaskDelete(NULL); // This might be the bug, does it delete await arm? it shouldnt
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

    control_bits = xEventGroupCreate();
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
