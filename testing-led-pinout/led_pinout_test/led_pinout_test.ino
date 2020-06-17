
#include <SoftwareSerial.h>
int flag;
int lastFlag;

void setup() {
    Serial.begin(9600);
    pinMode(11, OUTPUT);
    Serial.print("Set LED HIGH (1) or LOW (0)\r\n");
    delay(100);
    flag = -1;
    lastFlag = -1;
}

void loop() {
  if(Serial.available() > 0)  {
    flag= Serial.read()-'0'; // can be -1 if read error
    if(flag != lastFlag){
      switch(flag) {
          case 1:
             digitalWrite(11,HIGH);
             Serial.print("Setting LED to HIGH\r\n");
             lastFlag = flag;
          break;

          case 0:
             digitalWrite(11,LOW);
             Serial.print("Setting LED to LOW\r\n");
             lastFlag = flag;
          break;

          default:
            break;
      } //end switch case
   } //end interior if
   else{
    Serial.print("No Change!\r\n");
   }
 } //end exterior if
}
