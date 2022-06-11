#include <Environment.h>
#include <Data.h>
#include <Block.h>
#include <RTCuse.h>

RTCuse rtc;
Block b;
Data arregloDeDatos[] = { *(new Data("PHONE1",0,"+541150484555")),
                          *(new Data("PHONE2",20,"+541150484556")),
                          *(new Data("PHONE3",40,"+541150484557")),
                          *(new Data("ALERTS",60,"50"))};

Environment env(&b,&rtc);

void setup() {
  Serial.begin(9600);
  
  b.init(arregloDeDatos,1000);    //Create the data block from byte 1000 of the EEPROM
  b.initAllData();                //Initialize the data in the EEPROM for all the data in the block (Only for first time data load)
  
  for(int i = 0; i < 12; i++)		//Run every possible option wit the Environment created and get the answer.
    Serial.println( env.runMenuOption(Environment::getOptionByID(i)) );
}

void loop() {
  //Empty
}
