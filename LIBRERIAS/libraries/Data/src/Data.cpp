/*
  Data.cpp - Data library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "Data.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

/**
  * Constructor to the Block charging the data on it.
  * @param _offset The data offset on the EEPROM.
  * @param _data The data as a String.
*/
Data::Data(int16_t _offset, String _data){
  this->offsetOnEEPROM = _offset;
  this->dataLength = _data.length();
  this->dataSave = _data;
}

/**
  * Constructor to the Block charging the data on it.
  * @param _name The data name for search it in a Block using this Data object.
  * @param _offset The data offset on the EEPROM.
  * @param _data The data as a String.
*/
Data::Data(String _name, int16_t _offset, String _data){
  this->offsetOnEEPROM = _offset;
  this->dataLength = _data.length();
  this->dataSave = _data;
  this->dataName = _name;
}

//Initializer
/**
  * Initialize the data in the EEPROM.
  * Saves the data in the eeprom using the offset selected only if there is a data defined.
  *
  * @return Nothing.
*/
void Data::init(void){
  if(dataSave != "")
    this->setData(dataSave);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

/**
  * Get the data reading on the EEPROM starting from the indicated offset to the end of the data.
  * @return The data saved on EEPROM as a String.
*/
String Data::getData(void){ 
	if(this->getOffset() == -1) return "ERROR";
	String dataReturn = "";
	char caracter = rtcManage.readInEEPROM(offsetOnEEPROM);
	int i = 0;
	while(caracter != '\0'){
		dataReturn += caracter;
		caracter = rtcManage.readInEEPROM(offsetOnEEPROM + i + 1); 
		i++;
	}
	this->dataLength = i;
	return dataReturn;
}

/**
  * Get the static data setted on Constructor, not the EEPROM saved data.
  * @return The static data.
*/
String Data::getStaticData(void){ return this->dataSave; }
/**
  * Get the name of the data. It's not in the EEPROM.
  * @return The data's name.
*/
String Data::getName(void){ return this->dataName; }
/**
  * Get the length of data in EEPROM on bytes.
  * @return The data Length.
*/
unsigned int Data::getLength(void){ return this->dataLength; }
/**
  * Get the offset byte of data in EEPROM.
  * @return The data's byte offset.
*/
int16_t Data::getOffset(void) { return this->offsetOnEEPROM; }
/**
  * Get the static end of data byte in EEPROM
  * @return The data's end of data Byte.
*/
int16_t Data::getEndOfData(void) { return this->getOffset() + this->dataLength;}

//Sets
/**
  * Set the offset byte of data in EEPROM.
  * @param _offset The new data offset on EEPROM.
  * @return Nothing.
*/
void Data::setOffset(int16_t _offset){ offsetOnEEPROM = _offset; }

/**
  * Change the data writing in EEPROM.
  * @param _data The new data to write in EEPROM.
  * @return Nothing.
*/
void Data::setData(String _data){
	if(this->getOffset() != -1){
		this->dataLength = _data.length();
		rtcManage.saveInEEPROM(this->offsetOnEEPROM,_data);
		rtcManage.saveInEEPROM(this->getEndOfData(), (char)'\0');
	}
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library