#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

String Setup_test = " ";
String Signal = " ";
String attempt = "OK\r\n";
String Rssi = " ";
int nombre_de_mesure = 5; // A changer ici et plus bas dans inqm!
int laenge = ' ';
int a;
long somme = 0;
long amplitude_du_signal = ' ';
long fixe = 0;


void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  BTSerial.write("at+reset\r\n");
  Setup_test = BTSerial.readString();
  while (Setup_test != attempt){
     Setup_test = BTSerial.readString();
  }
  Serial.print(Setup_test);
  BTSerial.write("at+cmode=1\r\n");
  Setup_test = BTSerial.readString();
  while (Setup_test != attempt){
     Setup_test = BTSerial.readString();
  }
  Serial.print(Setup_test);
  BTSerial.write("at+inqm=1,5,48\r\n");    //nombre_de_mesure a changé ici egalement
  Setup_test = BTSerial.readString();
  while (Setup_test != attempt){
     Setup_test = BTSerial.readString();
  }
  Serial.print(Setup_test);
  BTSerial.write("at+init\r\n");
  Setup_test = BTSerial.readString();
  while (Setup_test != attempt){
     Setup_test = BTSerial.readString();
  }
  Serial.print(Setup_test);
}

void loop()
{


BTSerial.write("at+inq\r\n");
  Signal = " ";
  fixe = 0;
  a = 0;
  // Le temps que HC 05 n'a pas repondu attend une reponse
  while (Signal.startsWith(" ",0)){
  if (BTSerial.available()) {

    Signal = BTSerial.readString();
    Serial.print(Signal);
    laenge = ((Signal.length()-2)/(nombre_de_mesure));
      for (int i = 0; i < (nombre_de_mesure+1);i++){
        Rssi = Signal.substring((i*laenge)+(laenge-6),(i*laenge)+laenge);
        char rssi[5] = {Rssi.charAt(0),Rssi.charAt(1),Rssi.charAt(2),Rssi.charAt(3)};
        somme = strtol(rssi, NULL, 16);  //Convertir le contenu du String Rssi (4 lettres / chiffres ex: FFBC) en DECimal (convertir de hexa en decimal) puis mettre le long somme à la valeur du String Rssi
        fixe = fixe + somme; //Faire la somme des differentes valeurs de signal Rssi      
        a++;
//        Serial.print(Rssi);        
    }
  }
 }
     amplitude_du_signal = fixe/a;
     Serial.print(amplitude_du_signal);

    }
