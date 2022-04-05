#include "Touch.h"

//#define COL_1 15 // 15

#define COL_1 15 // 15
#define COL_2 16 // 16
#define COL_3 0  // 0
#define COL_4 4  // 4
#define ROW_1 27 // 27
#define ROW_2 25 // 25
#define ROW_3 33 // 33
#define ROW_4 32 // 32

#define ENTER_KEY 17

Buffer *Touchpad_Buffer = BufferInit(32);
const char Touchpad_Lookup[4][4] = {{'L', '7', '4', '1'},
                                    {'/', '8', '5', '2'},
                                    {'*', '9', '6', '3'},
                                    {'-', '+', 'D', '0'}};

void Init_Touchpad()
{
    // pinMode(COL_1, OUTPUT);

    REG_SET_BIT(GPIO_ENABLE_REG, COL_1);   // Define GPIO15 as output
    REG_WRITE(GPIO_FUNC15_OUT_SEL, 0x100); // Special peripheral index value (0x100)
    pinMode(COL_1, OUTPUT);
    pinMode(COL_2, OUTPUT);
    pinMode(COL_3, OUTPUT);
    pinMode(COL_4, OUTPUT);

    pinMode(ROW_1, INPUT_PULLDOWN);
    pinMode(ROW_2, INPUT_PULLDOWN);
    pinMode(ROW_3, INPUT_PULLDOWN);
    pinMode(ROW_4, INPUT_PULLDOWN);

    pinMode(ENTER_KEY, INPUT_PULLUP);

    Serial.begin(115200);
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

int debounce = 0;
int last_base[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
void Touchpad_Loop()
{
    // Keymask *mask = Init_Keymask();

    int base[4][4];
    int counter = 0;

    // digitalWrite(COL_1, HIGH);
    REG_SET_BIT(GPIO_OUT_W1TS_REG, BIT15);
    base[counter][0] = digitalRead(ROW_1);
    base[counter][1] = digitalRead(ROW_2);
    base[counter][2] = digitalRead(ROW_3);
    base[counter][3] = digitalRead(ROW_4);
    REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT15);
    digitalWrite(COL_1, LOW);

    counter++;

    digitalWrite(COL_2, HIGH);
    base[counter][0] = digitalRead(ROW_1);
    base[counter][1] = digitalRead(ROW_2);
    base[counter][2] = digitalRead(ROW_3);
    base[counter][3] = digitalRead(ROW_4);
    digitalWrite(COL_2, LOW);

    counter++;

    digitalWrite(COL_3, HIGH);
    base[counter][0] = digitalRead(ROW_1);
    base[counter][1] = digitalRead(ROW_2);
    base[counter][2] = digitalRead(ROW_3);
    base[counter][3] = digitalRead(ROW_4);
    digitalWrite(COL_3, LOW);

    counter++;

    digitalWrite(COL_4, HIGH);
    base[counter][0] = digitalRead(ROW_1);
    base[counter][1] = digitalRead(ROW_2);
    base[counter][2] = digitalRead(ROW_3);
    base[counter][3] = digitalRead(ROW_4);
    digitalWrite(COL_4, LOW);

    // // columns

    for (int i = 0; i <= 3; i++)
    {
        // rows
        for (int j = 0; j <= 3; j++)
        {
            Serial.print(base[i][j]);
            if (base[i][j] != last_base[i][j])
            {
                last_base[i][j] = base[i][j];
                if (base[i][j] == HIGH)
                {

                    // Serial.println("appending");
                    // Serial.println(Touchpad_Lookup[i][j]);
                    Buffer_Append(Touchpad_Buffer, Touchpad_Lookup[i][j]);
                }
            }
        }
    }
    Serial.print('\n');
    int enter = digitalRead(ENTER_KEY);

    if (LOW == enter && debounce != enter)
    {
        Serial.println("printing");
        Send_Buffer(Touchpad_Buffer);
    }
    debounce = enter;
}

// // Not a lot of readability because this should be called on a 500Hz timer.
// void Poll_Touchpad(Keymask *mask)
// {

//     // return mask;
//     int counter = 0;
//     // mask->base = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

//     digitalWrite(COL_1, HIGH);
//     mask->base[counter][0] = digitalRead(ROW_1);
//     mask->base[counter][1] = digitalRead(ROW_2);
//     mask->base[counter][2] = digitalRead(ROW_3);
//     mask->base[counter][3] = digitalRead(ROW_4);
//     digitalWrite(COL_1, LOW);

//     counter++;

//     digitalWrite(COL_2, HIGH);
//     mask->base[counter][0] = digitalRead(ROW_1);
//     mask->base[counter][1] = digitalRead(ROW_2);
//     mask->base[counter][2] = digitalRead(ROW_3);
//     mask->base[counter][3] = digitalRead(ROW_4);
//     digitalWrite(COL_2, LOW);

//     counter++;

//     digitalWrite(COL_3, HIGH);
//     mask->base[counter][0] = digitalRead(ROW_1);
//     mask->base[counter][1] = digitalRead(ROW_2);
//     mask->base[counter][2] = digitalRead(ROW_3);
//     mask->base[counter][3] = digitalRead(ROW_4);
//     digitalWrite(COL_3, LOW);

//     counter++;

//     digitalWrite(COL_4, HIGH);
//     mask->base[counter][0] = digitalRead(ROW_1);
//     mask->base[counter][1] = digitalRead(ROW_2);
//     mask->base[counter][2] = digitalRead(ROW_3);
//     mask->base[counter][3] = digitalRead(ROW_4);
//     digitalWrite(COL_4, LOW);
// }
