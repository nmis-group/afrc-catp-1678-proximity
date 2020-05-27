#include <ArduinoBLE.h>
boolean modeflag = false;

//String deviceID;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Proximity Sensor");
  Serial.println("Starting service...");
  

  // start scanning for peripheral
//  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  while (modeflag == false) {
    BLE.scan();
    Serial.println("scanning...");
    BLEDevice peripheral = BLE.available();
    if (peripheral) {
      if (peripheral.localName() == "Proximity Sensor") {
        Serial.print(millis()/1000);
        Serial.print(" | RSSI: ");
        Serial.print(peripheral.rssi());
        Serial.print(" | Address: ");
        Serial.print(peripheral.address());
        Serial.print(" | Local Name: ");
        Serial.println(peripheral.localName());
        modeflag = true;
      }
    }
  }
  while (modeflag == true) {
    BLE.advertise();
    Serial.println("advertising...");
    delay(1000);
    modeflag = false;
  }
}
