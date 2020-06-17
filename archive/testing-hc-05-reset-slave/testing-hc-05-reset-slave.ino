#include <stdlib.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); // RX | TX
const byte numChars = 32;
char recvc[numChars];
char c=' ';
boolean newData = false;
String hexval;
long decval;
long int strtol (const char *__nptr, char **__endptr, int __base);
unsigned int recvclen;

void setup() {
    Serial.begin(9600);
    initHC05();
}

void loop() {
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

void inqmHC05() {
    BTserial.write("AT+ROLE=1\r\n");
    delay(20);
    BTserial.write("AT+INIT\r\n");
    delay(20);
    BTserial.write("AT+INQM=1,20,5\r\n");
    delay(20);
    BTserial.write("AT+INQ\r\n");
}

void scanHC05() {
    BTserial.write("AT+INQC\r\n");
//    delay(20);
    Serial.print(millis()/1000);
    Serial.println(" | scanning...");  
    BTserial.write("AT+ROLE=0\r\n");
    delay(150);
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

void showRSSI() {
    int cidx1 = String(recvc).indexOf(',');
    int cidx2 = String(recvc).indexOf(',', cidx1 + 1);
    int cidx3 = String(recvc).indexOf(',', cidx2 + 1);
    String address;
    String devclass;
    String rssi;
    if (newData == true) {
        address = String(recvc).substring(0, cidx1);
        devclass = String(recvc).substring(cidx1, cidx2);
        rssi = String(recvc).substring(cidx2, cidx3);
        hexval = "0x"+String(rssi).substring(String(rssi).length()-4, String(rssi).length());
        decval = strtol(hexval.c_str(), NULL, 16);
        if (hexval.length() == 6 && decval > 1000) {
              Serial.print(millis()/1000);
              Serial.print(" | rssi -- ");
              Serial.print(hexval);
              Serial.print("(");Serial.print(decval);Serial.print(")");
              Serial.print(" | add -- ");
              Serial.println(address);
              newData = false;
              BTserial.flush();
        }
        else {
              newData = false;
              BTserial.flush();
        }
    }
}
