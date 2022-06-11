#include <LCDuse.h>
#include <Data.h>

LCDuse lcdPrueba;
Data telefono(1000,"+541150484555");

void setup() {
  lcdPrueba.init();
  telefono.init();
  lcdPrueba.print("Nro de telefono:", telefono);
}

void loop() {
  //Empty
}
