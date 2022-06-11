#include <Block.h>

Data arregloDeDatos[] = { *(new Data("Tel1",0,"+541150484555")),
                          *(new Data("Tel2",20,"+541150484556")),
                          *(new Data("Tel3",40,"+541150484557")),
                          *(new Data("Tel4",60,"+541150484558")),
                          *(new Data("Tel5",80,"+541150484559")) };

Block b;

void setup() {
  Serial.begin(9600);
  b.init(arregloDeDatos,1000);    //Create the data block from byte 1000 of the EEPROM
  b.initAllData();                //Initialize the data in the EEPROM for all the data in the block (Only for first time data load)

  for(int i = 0; i < 5; i++){     //Visualize all the data in the Block and its offsets in the EEPROM.
    Serial.print("Offset: "); 
    Serial.println( b.getDataObject(i).getOffset() );
    Serial.print("Data: ");
    Serial.println( b.getDataObject(i).getData() );
  }

  //Search Data with its name
  Serial.println("Encontrar el Tel4:");
  Serial.println(b.getDataObject("Tel4").getData() );

  //Search Data that doesn't exist
  Serial.println("Buscar uno que no existe:");
  Serial.println(b.getDataObject("Tel6").getData() );

  Serial.println("Encontrar el Tel2:");
  Serial.println(b.getDataObject("Tel2").getData() );
}

void loop() {
  //Empty
}
