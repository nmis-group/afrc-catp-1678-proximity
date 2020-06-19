#include <ArduinoBLE.h>
long randflip; 
int pin_prox = 10;
int pin_lo = 9;
int pin_mid = 8;
int pin_hi = 7;

void setup() {
  BLE.begin();
  BLE.setLocalName("Proximity Sensor");
  randomSeed(analogRead(0));
  pinMode(pin_prox, OUTPUT);
  pinMode(pin_lo, OUTPUT);
  pinMode(pin_mid, OUTPUT);
  pinMode(pin_hi, OUTPUT);
}

void loop() {
  randflip = random(1000);
  if (randflip < 500) {
    BLE.scan();
    BLEDevice peripheral = BLE.available();
    if (peripheral) {
//      if (peripheral.localName() == "Proximity Sensor") {
        if (peripheral.rssi() < -80){
           digitalWrite(pin_prox, LOW);
//al
        }
        else {
          digitalWrite(pin_prox, HIGH);
//          digitalWrite(pin_lo, HIGH); 
//          digitalWrite(pin_mid, HIGH); 
//          digitalWrite(pin_hi, HIGH); 
        }
//      }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}
