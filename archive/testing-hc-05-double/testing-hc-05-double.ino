#include <stdlib.h>
#include <SoftwareSerial.h>

SoftwareSerial HC05scan(10, 11); // RX | TX
SoftwareSerial HC05advr(2, 3); // RX | TX
const byte numChars = 32;
char recvc[numChars];
char c=' ';
boolean newData = false;
String hexval;
long decval;
long int strtol (const char *__nptr, char **__endptr, int __base);
unsigned int recvclen;
boolean NL = true;

void setup() {
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println("Configuring advertising HC-05...");
    HC05advr.begin(38400);
    HC05advr.write("AT+RESET\r\n"); delay(50); while (HC05advr.available()){c = HC05advr.read();Serial.write(c);}
    HC05advr.write("AT+ROLE=0\r\n"); delay(50); while (HC05advr.available()){c = HC05advr.read();Serial.write(c);}  
    HC05advr.write("AT+ROLE?\r\n");  delay(50); while (HC05advr.available()){c = HC05advr.read();Serial.write(c);}
    Serial.println("Configuring scanning HC-05...");
    HC05scan.begin(38400);
    HC05scan.listen();  
//    HC05scan.write("AT+RESET\r\n"); delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}
    HC05scan.write("AT+ROLE=1\r\n"); delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}    
    HC05scan.write("AT+ROLE?\r\n"); delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}
    HC05scan.write("AT+INIT\r\n");;  delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}
    HC05scan.write("AT+INQM=1,1,48\r\n");;  delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}
    HC05scan.write("AT+INQM?\r\n");;  delay(100); while (HC05scan.available()){c = HC05scan.read();Serial.write(c);}       
}

//void loop()
//{
//    if (HC05scan.available()) {
//        c = HC05scan.read();
//        Serial.write(c);
//    }
//    if (Serial.available()) {
//        c = Serial.read();
//        HC05scan.write(c);   
//        if (NL) { Serial.print(">");  NL = false; }
//        Serial.write(c);
//        if (c==10) { NL = true; }
//    }
//}


void loop() {
    HC05scan.write("AT+INIT\r\n");
    delay(50);
    HC05scan.write("AT+INQM=1,20,5\r\n");
    delay(50);
    HC05scan.write("AT+INQ\r\n");
    delay(50);
    recvHC05();
    showRSSI();
    delay(150); 
}

void recvHC05() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '+';
    char endMarker = '\r';
    char rc;
    while (HC05scan.available() > 0 && newData == false) {
        rc = HC05scan.read();
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
              HC05scan.flush();
        }
        else {
              newData = false;
              HC05scan.flush();
        }
    }
}
