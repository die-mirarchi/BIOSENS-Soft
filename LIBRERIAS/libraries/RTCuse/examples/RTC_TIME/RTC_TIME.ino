#include <RTCuse.h>

RTCuse rtc;

void setup() {
  Serial.begin(9600);
  rtc.adjustDate();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(rtc.getDate());
  delay(1000);
}
