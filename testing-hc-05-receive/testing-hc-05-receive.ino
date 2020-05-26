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
    initHC05();
}

void initHC05() {
    Serial.println(__DATE__);
    BTserial.begin(38400);
    Serial.println("Resetting...");
    BTserial.write("AT+RESET\r\n");    
    delay(50); while (BTserial.available()){c = BTserial.read();Serial.write(c);}
    Serial.println("Changing HC-05 mode to slave...");
    BTserial.write("AT+ROLE=0\r\n");
//    delay(50); while (BTserial.available()){c = BTserial.read();Serial.write(c);}
//    Serial.println("Begin inquiring bluetooth devices...");
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
