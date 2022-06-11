#include <Data.h>

Data telefono(1000,"+541150484555");    //Desde el byte 1000 hasta 1012

void setup() {
  Serial.begin(9600);
  telefono.init();
}

void loop() {
  Serial.println("Datos: ");
  
  Serial.println(telefono.getData());
  Serial.println(telefono.getLength());
  Serial.println(telefono.getOffset());
  Serial.println(telefono.getEndOfData());

  Serial.println("---------------------------------");
  delay(3000);
}
