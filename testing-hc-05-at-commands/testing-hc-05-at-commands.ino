#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
//int ledpin=13; // led on D13 will show blink on / off
char c = ' ';
boolean NL = true;
int ledpin = 13;
 
void setup() 
{
    Serial.begin(9600);
    BTserial.begin(38400);
    pinMode(ledpin,OUTPUT);
    digitalWrite(ledpin,0);
}

void loop()
{
    if (BTserial.available());
    {
        c = BTserial.read();
        Serial.write(c);
    }

    BTserial.write("AT");
    delay(1000);
}
