#include <SoftwareSerial.h>
int ledPins[] = {7,8,9,10};
enum led {RED = 7, AMBER, GREEN, BLUE};
bool flag;
bool lastFlag;
int threshold = 75; //allow change of rssi threshold value. Gain of 75 was approx threshold from testing.
int infCount; //Initialised to zero in setup

void setup() {
  //init and flash each LED
  Serial.begin(9600);
  for(int i =4; i >= 0; i--){
    pinMode(ledPins[i],OUTPUT);
    delay(100);
    digitalWrite(ledPins[i],HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
    delay(100);  
  }
  //initialise variables for use in loop.
  infCount = 0;
  flag = false;
  lastFlag = false;
  Serial.write("Initialisation Complete");
}

void loop() {
  //RNG to mimic RSSI Polling
  int rssi = rand() % 100 + 1;
  Serial.print("RSSI value: ");
  Serial.println(rssi);

  
  if(inThreshold(rssi)){                  // In thresh, flag high
    flag = true;                          
    if(flagChange(flag, lastFlag)){        //in thresh, flag change
     digitalWrite(BLUE,HIGH);               
     infCount++;
     Serial.println("in thresh, flag change");
     //Code to begin logging infraction
    }
    else{                                 //in thresh, no flag change
      digitalWrite(BLUE,HIGH);
      Serial.println("in thresh, no flag change");
    }
  }
  else{                                   //out thresh, flag low
    flag = false;
    if (flagChange(flag,lastFlag)){        //out thresh, flag change
     digitalWrite(BLUE,LOW);
     Serial.println("out thresh, flag change");
     //Code to end logging infraction 
    }
    else{                                 //out thresh, no change
     digitalWrite(BLUE,LOW); 
     Serial.println("out thresh, no flag change");
    }
  }
  lastFlag = flag;
  delay(1000);
  setLED();
  Serial.print("Infraction Count: ");
  Serial.println(infCount);
}

bool flagChange(bool f, bool lf) {
    if( f != lf ){
      return true;
    }
    else {
      return false;
    }
}

bool inThreshold(int rssi) {
  if(rssi >= threshold){
    return true;
  }
  else{
    return false;
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
