#include <RTCuse.h>

RTCuse rtc;

void setup() {
  Serial.begin(9600);
  
  rtc.saveInEEPROM(1000,"Hola, como andas viejo");  //Save the string on byte 1000
  delay(200);
  rtc.saveInEEPROM(1023,"Aloh");                    //Save the string on byte 1023
  delay(2000);
}

void loop() {
  Serial.println( rtc.readInEEPROM(1000, 22) );  //We read since byte 1000 for 22 bytes
  delay(5000);
  Serial.println( rtc.readInEEPROM(1017, 10) );  //We read since byte 1000 for 22 bytes
  delay(5000);
}
