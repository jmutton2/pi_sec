#include <>


typedef struct keypad_
{
pinmode(row_1, HIGH);
    digitalread(Column_1);
    digitalread(Column_2);
    digitalread(Column_3);
    digitalread(Column_4);
pinmode(row_1, LOW);
pinmode(row_2, HIGH);
    digitalread(Column_1);
    digitalread(Column_2);
    digitalread(Column_3);
    digitalread(Column_4);
pinmode(row_2, LOW);
pinmode(row_3, HIGH);
    digitalread(Column_1);
    digitalread(Column_2);
    digitalread(Column_3);
    digitalread(Column_4);
pinmode(row_3, LOW);
pinmode(row_4, HIGH);
    digitalread(Column_1);
    digitalread(Column_2);
    digitalread(Column_3);
    digitalread(Column_4);
pinmode(row_4, LOW);
}