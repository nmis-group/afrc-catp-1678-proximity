#include <ArduinoBLE.h>
long randflip; 
/*
int pin_prox = 10;
int pin_lo = 9;
int pin_mid = 8;
int pin_hi = 7;
*/

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

  BLE.begin();
  BLE.setLocalName("Proximity Sensor");
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
}

void loop() {
  currentTime = millis();
  randflip = random(1000);
  if (randflip < 500) {
    BLE.scan();
    BLEDevice peripheral = BLE.available();
    if (peripheral) {
      if (peripheral.localName() == "Proximity Sensor") {
        /*
        if (peripheral.rssi() < -80){
           digitalWrite(pin_prox, LOW);
        }
        else {
          digitalWrite(pin_prox, HIGH);
        }
        */
        int rssi = peripheral.rssi();
        if (currentTime - previousRSSITime >= intervalRSSI) {
        rssiTotal += rssi;
        rssiCount++;
        if (rssi >= threshold){
          digitalWrite(BLUE,HIGH); 
        }
        else{
          digitalWrite(BLUE,LOW);  
        }
        previousRSSITime = currentTime;
      }
      if (currentTime - previousSensorTime >= intervalSensor){
        int meanRSSI = rssiTotal/rssiCount;
        if (meanRSSI >= threshold){
         infCount++;
        }
        previousSensorTime = currentTime;
        rssiTotal = 0;
        rssiCount = 0;
      }
      setLED();
     }
    }
  }
  if (randflip > 500){
    BLE.advertise();
  }
}

void setLED(){
  if(infCount <= 10) {
    digitalWrite(GREEN,HIGH);
    digitalWrite(AMBER,LOW);
    digitalWrite(RED,LOW);
  }
  else if(infCount > 10 && infCount <= 50){
    digitalWrite(GREEN,LOW);
    digitalWrite(AMBER,HIGH);
    digitalWrite(RED,LOW);
  }
  else{
    digitalWrite(GREEN,LOW);
    digitalWrite(AMBER,LOW);
    digitalWrite(RED,HIGH);
  }
}
