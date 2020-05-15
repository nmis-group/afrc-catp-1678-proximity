//  Sketc: basicSerialWithNL_001
// 
//  Uses hardware serial to talk to the host computer and software serial 
//  for communication with the Bluetooth module
//  Intended for Bluetooth devices that require line end characters "\r\n"
//
//  Pins
//  Arduino 5V out TO BT VCC
//  Arduino GND to BT GND
//  Arduino D9 to BT RX through a voltage divider
//  Arduino D8 BT TX (no need voltage divider)
//
//  When a command is entered in the serial monitor on the computer 
//  the Arduino will relay it to the bluetooth module and display the result.
//
 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
 
const long baudRate = 38400; 
char c=' ';
boolean NL = true;
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTserial.begin(baudRate);  
    Serial.print("BTserial started at "); Serial.println(baudRate);
    Serial.println(" ");
}
 
void loop()
{
 
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTserial.available())
    {
        c = BTserial.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTserial.write(c);   
 
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
 
}



//#include <SoftwareSerial.h>
//SoftwareSerial BTserial(10, 11); // RX | TX
//int ledpin=13; // led on D13 will show blink on / off
//int c;
// 
//void setup() 
//{
//    Serial.begin(9600);
//    Serial.println("Waiting for 0 or 1");
//    BTserial.begin(9600);
//    pinMode(ledpin,OUTPUT);
//    digitalWrite(ledpin,0);  
//}
// 
//void loop()
//{
//    if (BTserial.available())
//    BTSerial.write("at+inq\r\n");
//
//    
//    {  
//        c = BTserial.read();
//        if(c=='1')
//        {
//          digitalWrite(ledpin,1);
//        }
//        if(c=='0')
//        {
//          digitalWrite(ledpin,0);
//        }
//        Serial.write(c);
//    } 
//}
