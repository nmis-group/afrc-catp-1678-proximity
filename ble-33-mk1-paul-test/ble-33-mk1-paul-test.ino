#include <ArduinoBLE.h>
long randflip; 
int pin_prox = 10;
int pin_lo = 9;
int pin_mid = 8;
int pin_hi = 7;

//Variables for counting
const unsigned long intervalRSSI = 100;
const unsigned long intervalSensor = 5000;
unsigned long currentTime;
unsigned long previousRSSITime;
unsigned long previousSensorTime;
int rssiCount;
int rssiTotal;

//Variables for LED stuff
int ledPins[] = {7,8,9,10};
enum led {RED = 7, AMBER, GREEN, BLUE};
int threshold = 75;
int infCount;

void setup() {
<<<<<<< HEAD

=======
>>>>>>> 9854ef626f7b9706e5bee0ca1bfbf35c1245c4ac
  Serial.begin(9600);
  BLE.begin();
  BLE.setLocalName("Proximity Sensor 10");
  randomSeed(analogRead(0));

  //Initialise and flash each LED
  for(int i =4; i >= 0; i--){
    pinMode(ledPins[i],OUTPUT);
    digitalWrite(ledPins[i], HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
  }
  previousRSSITime = 0;
  previousSensorTime = 0;
  rssiCount = 0;
  rssiTotal = 0;
  infCount = 0;
  
  // turn on all lights to test
  digitalWrite(pin_prox, HIGH);
  digitalWrite(pin_lo, HIGH); 
  digitalWrite(pin_mid, HIGH); 
  digitalWrite(pin_hi, HIGH);
  delay(1000);
  
  // turn then back off
  digitalWrite(pin_prox, LOW);
  digitalWrite(pin_lo, LOW); 
  digitalWrite(pin_mid, LOW); 
  digitalWrite(pin_hi, LOW);  
}

void loop() {
  randflip = random(1000);
  if (randflip < 500) {
    BLE.scan();
    BLEDevice peripheral = BLE.available();
    if (peripheral) {
      if (peripheral.localName().startsWith("Sensor", 10)){
        Serial.print(" | RSSI: ");
        Serial.print(peripheral.rssi());
        Serial.print(" | Address: ");
        Serial.print(peripheral.address());
        Serial.print(" | Local Name: ");
        Serial.println(peripheral.localName());
        if (peripheral.rssi() > -65){
           digitalWrite(pin_prox, HIGH);
           delay(100);
           digitalWrite(pin_prox, LOW);
        }
        else {
           digitalWrite(pin_prox, LOW);
        }
      }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}
