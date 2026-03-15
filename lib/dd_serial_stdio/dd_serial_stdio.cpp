#include "dd_serial_stdio.h"

int ddSerialGetChar(FILE *f)
{
    while (!Serial.available()) // asteptam pana cand sunt date disponibile
        ;
    return Serial.read(); // returnam caracterul citit
}
int ddSerialPutChar(char ch, FILE *f)

{
    return Serial.write(ch); // scriem caracterul pe seriala
}
void ddSerialStdioSetup()
{
    Serial.begin(SERIAL_BAUDRATE);
    FILE *srv_serial_stream = fdevopen(ddSerialPutChar,
                                       ddSerialGetChar); // asociem functiile de citire/scriere cu un flux
    stdin = srv_serial_stream;                           // redirectionam intrarea standard
    stdout = srv_serial_stream;                          // redirectionam iesirea standard
    printf("\r\nsrvSerial Started\n");
}