#include <A2a.h>
#define endereco 0x08

#define pinLED1 3
#define pinLED2 4
#define pinosom 7

A2a arduinoMaster;

byte displayLEDAnt;
bool rele;

void setup() {
  arduinoMaster.begin(endereco);
  arduinoMaster.onReceive(receberDados);
  arduinoMaster.onRequest(enviarDados);

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode (pinosom, INPUT);
  
  rele=false;

  Serial.begin(9600);
}

void loop() {   
  byte displayLED = arduinoMaster.varWireRead(2);
  bool rele = digitalRead(pinosom);
  if ((displayLED != displayLEDAnt) ||(rele=!rele) ||((pinosom)==HIGH)) {
      digitalWrite(pinLED2, displayLED >= 2);
      displayLEDAnt = displayLED; 
  }
  digitalWrite(pinLED2,rele);
}

void receberDados() {
  arduinoMaster.receiveData(); 
}

void enviarDados() {
  arduinoMaster.sendData(); 
}
