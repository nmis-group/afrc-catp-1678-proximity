#include <ArduinoBLE.h>
long randflip;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

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
        Serial.print(millis()/1000);
        Serial.print(" | RSSI: ");
        Serial.print(peripheral.rssi());
        Serial.print(" | Address: ");
        Serial.print(peripheral.address());
        Serial.print(" | Local Name: ");
        Serial.println(peripheral.localName());
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
