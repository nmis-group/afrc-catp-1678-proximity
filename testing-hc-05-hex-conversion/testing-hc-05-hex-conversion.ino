#include <stdlib.h>
#include <SoftwareSerial.h>

long int strtol (const char *__nptr, char **__endptr, int __base);
SoftwareSerial BTserial(10, 11); // RX | TX
const long baudRate = 38400; 
char c=' ';
const byte numChars = 32;
char recvc[numChars];
boolean newData = false;
String hexval;
long decval;
 
void setup() {
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTserial.begin(baudRate);  
    Serial.print("BTserial started at "); Serial.println(baudRate);
    Serial.println(" ");
    while (BTserial.available()){
      c = BTserial.read();
      Serial.write(c);
    }
    Serial.println("Sending 'AT' command...");
    BTserial.write("AT\r\n");
    delay(100);
    while (BTserial.available()){
      c = BTserial.read();
      Serial.write(c);
    }    
    Serial.println("Changing HC-05 mode to master...");
    BTserial.write("AT+ROLE=1\r\n");
    delay(100);
    while (BTserial.available()){
      c = BTserial.read();
      Serial.write(c);
    }
//    Serial.println("Initialising for inquiries...");
//    BTserial.write("AT+INIT\r\n");
//    delay(100);
//    while (BTserial.available()){
//      c = BTserial.read();
//    }    
//    Serial.println("Sending inquiry format...");    
//    BTserial.write("AT+INQM=1,1,48\r\n");
//    delay(100);
//    while (BTserial.available()){
//      c = BTserial.read();
//      Serial.write(c);
//    }
    Serial.println("Begin inquiring available bluetooth slave devices...");
}

void loop() {
    BTserial.write("AT+INIT\r\n");
    delay(50);
    BTserial.write("AT+INQM=1,1,48\r\n");
    delay(50);
    BTserial.write("AT+INQ\r\n");
    delay(50);
    recvHC05();
    showhexvals();
//    
//    BTserial.flush();
//    
//    BTserial.write("AT+INQ\r\n");
//    while (BTserial.available())
//    {
//        c = BTserial.read();
//        Serial.write(c);
//    }
//    delay(100);
     
}


void recvHC05() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '+';
    char endMarker = '\r';
    char rc;
 
    while (BTserial.available() > 0 && newData == false) {
        rc = BTserial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                recvc[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                recvc[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showhexvals() {
    if (newData == true) {
        hexval = "0x"+String(recvc).substring(20, 24);
        decval = strtol(hexval.c_str(), NULL, 16);
        Serial.print("Received: ");
        Serial.print(recvc);
        Serial.print(", Decimal: ");
        Serial.println(decval);
        newData = false;
        BTserial.flush();
        delay(50);
    }
}
