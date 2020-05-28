#include <ArduinoBLE.h>
long randflip;

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
  randomSeed(analogRead(0));
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  randflip = random(1000);
  if (randflip < 500) {
    BLE.scan();
//    Serial.println(millis()/1000);
//    Serial.println(" | scanning...");
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
        if (peripheral.rssi() < -80){
           digitalWrite(LED_BUILTIN, LOW);
        }
        else {
          digitalWrite(LED_BUILTIN, HIGH); 
        }
      }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}
