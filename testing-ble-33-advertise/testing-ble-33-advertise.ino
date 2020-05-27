#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  BLE.setLocalName("Proximity Sensor");
  Serial.println("BLE LED Peripheral");
}

void loop() {
  BLE.advertise();
}
