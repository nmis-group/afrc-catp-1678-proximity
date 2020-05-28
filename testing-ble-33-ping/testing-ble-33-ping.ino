#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("Scanning...");
}

void loop() {
  // check if a peripheral has been discovered
  BLE.scan();
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
    }
  }
}
