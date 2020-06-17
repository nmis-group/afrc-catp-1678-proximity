#include <SoftwareSerial.h>
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i =4; i >= 0; i--){
    pinMode(ledPins[i],OUTPUT);
  }
  previousRSSITime = 0;
  previousSensorTime = 0;
  rssiCount = 0;
  rssiTotal = 0;
  infCount = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  int rssi = rand() % 50 + 51;
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
    Serial.print("RSSI Running Total: ");
    Serial.println(rssiTotal);
    Serial.print("Counter Value: ");
    Serial.println(rssiCount);
    int meanRSSI = rssiTotal/rssiCount;
    Serial.print("Mean over 5 seconds: ");
    Serial.println(meanRSSI);
    if (meanRSSI >= threshold){
      infCount++;
      Serial.print("Exceeds Threshold. Total Infractions: ");
      Serial.println(infCount);
    }
    previousSensorTime = currentTime;
    rssiTotal = 0;
    rssiCount = 0;
  }
  setLED();
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
