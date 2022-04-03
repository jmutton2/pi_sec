#include 'Touch.h'

#define ROW_1 12
#define ROW_2
#define ROW_3
#define ROW_4
#define COLUMN_1

void Poll_Touchpad()
{
    pinmode(ROW_1, OUTPUT);
    digitalwrite(ROW_1, HIGH)
        digitalread(COLUMN_1);
        digitalread(COLUMN_2);
        digitalread(COLUMN_3);
        digitalread(COLUMN_4);
    digitalwrite(ROW_1, LOW);

    pinmode(ROW_2, OUTPUT);
    digitalwrite(ROW_2, HIGH)
        digitalread(COLUMN_1);
        digitalread(COLUMN_2);
        digitalread(COLUMN_3);
        digitalread(COLUMN_4);
    digitalwrite(ROW_2, LOW);

    pinmode(ROW_3, OUTPUT);
    digitalwrite(ROW_3, HIGH)
        digitalread(COLUMN_1);
        digitalread(COLUMN_2);
        digitalread(COLUMN_3);
        digitalread(COLUMN_4);
    digitalwrite(ROW_3, LOW);
    
    pinmode(ROW_4, OUTPUT);
    digitalwrite(ROW_4, HIGH)
        digitalread(COLUMN_1);
        digitalread(COLUMN_2);
        digitalread(COLUMN_3);
        digitalread(COLUMN_4);
    digitalwrite(ROW_4, LOW);
}
