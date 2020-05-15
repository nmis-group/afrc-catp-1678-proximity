#include <SoftwareSerial.h>// import the serial library

 
SoftwareSerial BT(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer
int SerialValue;


 
void setup()
{
  // put your setup code here, to run once:
  BT.begin(9600);
  BT.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}
 
void loop()
{
  // put your main code here, to run repeatedly:
  if (BT.available())
  {
    BluetoothData=BT.read();
    if(BluetoothData=='1')
    {
      // if number 1 pressed ....
      digitalWrite(ledpin,1);
      BT.println("LED  On D13 ON ! ");
    }
    if (BluetoothData=='0')
    {
      // if number 0 pressed ....
      digitalWrite(ledpin,0);
      BT.println("LED  On D13 Off ! ");
    }
    if (BluetoothData=='2')
    {
      // if number 0 pressed ....
      SerialValue = BT.read();
      BT.print("RSSI: ");
      BT.println(SerialValue);
    }
  }
delay(100);// prepare for next data ...
}

//      BT.println(BT.rssi())
