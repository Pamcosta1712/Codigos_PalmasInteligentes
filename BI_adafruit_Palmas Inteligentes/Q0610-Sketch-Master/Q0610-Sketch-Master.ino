// INCLUSÃO DE BIBLIOTECAS
#include <A2a.h>
#include "config.h"

// DEFINIÇÕES
#define endereco 0x08
#define pinLED1 3
#define pinLED2 4
#define pinosom 7

// INSTANCIANDO OBJETOS
AdafruitIO_Feed *displayLED = io.feed("displayLED");

A2a arduinoSlave;

// DECLARAÇÃO DE FUNÇÕES
void configuraMQTT();
void retornoDisplayLED(AdafruitIO_Data *data);

// DECLARAÇÃO DE VARIÁVEIS
bool comandoRecebido = false;

void setup() {
  
  Serial.begin(9600);
  while (! Serial);

  configuraMQTT();

  arduinoSlave.begin(0, 2);
  Serial.println("Atualizando valor do Display de LED");
  
  displayLED->get();
  io.run();
  
  Serial.println("Fim Setup");
}

void loop() {
  io.run();
}

// IMPLEMENTO DE FUNÇÕES
void configuraMQTT() {
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  displayLED->onMessage(retornoDisplayLED);
  //displayLED->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void retornoDisplayLED(AdafruitIO_Data *data) {
  Serial.print("Controle Recebido <- ");  
  Serial.println(data->value());
  
  arduinoSlave.varWireWrite(endereco, 2, byte(data->toInt()));
}
