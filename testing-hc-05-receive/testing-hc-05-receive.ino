#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
int ledpin=13; // led on D13 will show blink on / off
int c;
 
void setup() 
{
    Serial.begin(9600);
    Serial.println("Waiting for 0 or 1");
    BTserial.begin(9600);
    pinMode(ledpin,OUTPUT);
    digitalWrite(ledpin,0);  
}
 
void loop()
{
    if (BTserial.available())
    {  
        c = BTserial.read();
        if(c=='1')
        {
          digitalWrite(ledpin,1);
        }
        if(c=='0')
        {
          digitalWrite(ledpin,0);
        }
        Serial.write(c);
    } 
}
