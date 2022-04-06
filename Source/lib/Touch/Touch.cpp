#include "Touch.h"

//#define DEBUG

//#define COL_1 15 // 15

void Init_Touchpad()
{

    // must be literals because of precompiler directives.
    CONFIGURE_GPIO_OUT(15); // COLUMN 1
    CONFIGURE_GPIO_OUT(16); // COLUMN 2
    CONFIGURE_GPIO_OUT(0);  // COLUMN 3
    CONFIGURE_GPIO_OUT(4);  // COLUMN 3

    gpio_pad_pulldown(0);

    CONFIGURE_GPIO_IN_PD(12); // row 1
    CONFIGURE_GPIO_IN_PD(14); // row 2
    CONFIGURE_GPIO_IN_PD(27); // row 3
    CONFIGURE_GPIO_IN_PD(26); // row 4

    CONFIGURE_GPIO_IN_PU(17); // ENTER KEY

    Serial.begin(115200);

#ifdef DEBUG

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
}

void Send_Buffer(Buffer *buff)
{
    Serial.println(buff->base[buff->size]);
}

Keymask *Init_Keymask()
{
    Keymask *temp = (Keymask *)malloc(sizeof(Keymask));

    return temp;
}

void Touchpad_Loop()
{

    // Keymask *mask = Init_Keymask();
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

    int enter = digitalRead(ENTER_KEY);

    if (LOW == enter && EnterKeyDebounce != enter)
    {
        Serial.println("printing");
        // Send_Buffer();
    }
    EnterKeyDebounce = enter;
}
