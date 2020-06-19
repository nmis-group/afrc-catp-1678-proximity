#include <ArduinoBLE.h>
long randflip;
int pin_prox = 10;
int pin_lo = 9;
int pin_mid = 8;
int pin_hi = 7;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

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
        Serial.print(millis()/1000);
        Serial.print(" | RSSI: ");
        Serial.print(peripheral.rssi());
        Serial.print(" | Address: ");
        Serial.print(peripheral.address());
        Serial.print(" | Local Name: ");
        Serial.println(peripheral.localName());
        if (peripheral.rssi() < -80){
           digitalWrite(pin_prox, LOW);
           digitalWrite(pin_lo, LOW);
           digitalWrite(pin_mid, LOW);
           digitalWrite(pin_hi, LOW);
        }
        else {
          digitalWrite(pin_prox, HIGH);
          digitalWrite(pin_lo, HIGH); 
          digitalWrite(pin_mid, HIGH); 
          digitalWrite(pin_hi, HIGH); 
        }
//      }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}
