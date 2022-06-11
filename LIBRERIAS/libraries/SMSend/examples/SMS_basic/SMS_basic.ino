#include <SMSend.h>

SMSend sms(3,2,9600);
String msj;

void setup() {
  Serial.begin(9600);
  sms.sendSMS("+5411xxxxxxxx","Hola, soy tu Arduino y acabo de gastar 5,6 pesos en enviarte esto :)");
}

void loop() {
  String mensaje = sms.receiveSMS();
  
  Serial.print("Telefono: ");
  Serial.println(sms.getMessageInfo(PHONE_NUMBER,mensaje));
  Serial.print("FECHA: ");
  Serial.println(sms.getMessageInfo(SENT_DATE,mensaje));
  Serial.print("Mensaje: ");
  Serial.println(sms.getMessageInfo(MESSAGE,mensaje));
  
  if(sms.isSMS(mensaje)){
    msj = sms.getMessageInfo(MESSAGE,mensaje);
    sms.sendSMS(sms.getMessageInfo(PHONE_NUMBER,mensaje),msj);
  }
}
