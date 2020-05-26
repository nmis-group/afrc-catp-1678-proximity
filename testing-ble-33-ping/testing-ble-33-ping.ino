#include <ArduinoBLE.h>

//String deviceID;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  Serial.println("BLE Central scan");

  // start scanning for peripheral
//  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  BLE.scan();
  BLEDevice peripheral = BLE.available();
  if (peripheral) {

    if (peripheral.localName() == "Proximity Sensor 1") {

      Serial.print(millis()/1000);
      
      Serial.print(" | RSSI: ");
      Serial.print(peripheral.rssi());

      Serial.print(" | Address: ");
      Serial.print(peripheral.address());
      
      Serial.print(" | Local Name: ");
      Serial.println(peripheral.localName());
    }





//    // print the local name, if present
//    if (peripheral.hasLocalName()) {
//      Serial.print(" | Local Name: ");
//      Serial.print(peripheral.localName());
//    }
//
//    // print the advertised service UUIDs, if present
//    if (peripheral.hasAdvertisedServiceUuid()) {
//      Serial.print(" | Service UUIDs: ");
//      for (int i = 0; i < peripheral.advertisedServiceUuidCount(); i++) {
//        Serial.print(peripheral.advertisedServiceUuid(i));
//        Serial.print(" ");
//      }
//    }
  }
}
