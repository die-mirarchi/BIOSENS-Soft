#include <Data.h>
#include <Block.h>
#include <RTCuse.h>
#include <Environment.h>

RTCuse rtc;
Block b;
Data estructuraDeDatos[] = {  *(new Data("PHONE1",  0,"+541150484555")),
                              *(new Data("PHONE2", 20,"-NO DEFINIDO-")),
                              *(new Data("PHONE3", 40,"-NO DEFINIDO-")),
                              *(new Data("ALERTS", 60,"30")),
                              *(new Data("DATE1" , 70)),
                              *(new Data("DATE2" ,100)), 
                              *(new Data("DATE3" ,130))                  };

Environment env(&b,&rtc);

void setup(){
  Serial.begin(9600);
  Serial.println("Cargando la estructura de los datos en la EEPROM");

  b.init(estructuraDeDatos,1000);    //Create the data block from byte 1000 of the EEPROM (Change location if want)
  b.initAllData();                   //Initialize the data in the EEPROM for all the data in the block (Only for first time data load)

  Serial.println("Datos cargados correctamente");
}

void loop(){
  //Empty
}
