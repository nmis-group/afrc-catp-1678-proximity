#include <ArduinoBLE.h>


void setup() {
  Serial.begin(9600);
  while (!Serial); // wait
  
  Serial.println("setup");
  BLE.begin();
  BLE.setEventHandler(BLEDiscovered, discovered);
  BLE.scanForAddress("xx:yy:zz:aa:bb:cc", true);
}

void logDevice(BLEDevice dev) {
  Serial.print("BLE device found: ");
  Serial.print("address=");
  Serial.print(dev.address());
  Serial.print(", rssi=");
  Serial.print(dev.rssi());
  if (!dev.hasLocalName()) {
    Serial.println("");
    return;
  }
  Serial.print(", name=");
  Serial.print(dev.localName());
  Serial.println("");
}

void discovered(BLEDevice dev) {
  BLE.stopScan();
  logDevice(dev);
  delay(250); // ms
  BLE.scanForAddress("xx:yy:zz:aa:bb:cc", true);
}

void loop() {
  BLE.poll(1000); // ms
}
