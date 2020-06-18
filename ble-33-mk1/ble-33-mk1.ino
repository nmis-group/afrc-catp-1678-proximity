#include <ArduinoBLE.h>
long randflip;

void setup() {
  BLE.begin();
  BLE.setLocalName("Proximity Sensor");
  randomSeed(analogRead(0));
  pinMode(10, OUTPUT);
}

void loop() {
  randflip = random(1000);
  if (randflip < 500) {
    BLE.scan();
    BLEDevice peripheral = BLE.available();
    if (peripheral) {
//      if (peripheral.localName() == "Proximity Sensor") {
        if (peripheral.rssi() < -80){
           digitalWrite(10, LOW);
        }
        else {
          digitalWrite(10, HIGH); 
        }
//      }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}
