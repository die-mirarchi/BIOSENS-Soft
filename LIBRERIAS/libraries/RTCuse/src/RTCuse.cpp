/*
  RTCuse.cpp - RTCuse library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "RTCuse.h"

// Constructor/Initializer and Destructors /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
/**
  * Save a character in the _offset byte in EEPROM.
  * @param _offset The byte where will be stored the character on EEPROM.
  * @param _dato The character to save in EEPROM.
  * @return Nothing.
*/
void RTCuse::saveInEEPROM(uint16_t _offset, char _dato){
    EepromRTC.write(_offset, (byte)_dato);
}

/**
  * Save a String in EEPROM starting on the _offset byte.
  * @param _offset The byte where will be stored the String on EEPROM.
  * @param _dato The String to save in EEPROM.
  * @return Nothing.
*/
void RTCuse::saveInEEPROM(uint16_t _offset, String _dato){
    for(int i = 0; i < _dato.length(); i++)
		this->saveInEEPROM(_offset+i, _dato[i]);
}

/**
  * Read a character in EEPROM.
  * @param _offset The byte where is the character that we want to read.
  * @return Character on _offset byte in EEPROM.
*/
char RTCuse::readInEEPROM(uint16_t _offset){
	return (char)EepromRTC.read(_offset);
}

/**
  * Read a String in EEPROM.
  * @param _offset The initial byte where is the String that we want to read.
  * @param _length The length of the data we want to read.
  * @return String from _offset byte in EEPROM of size _length.
*/
String RTCuse::readInEEPROM(uint16_t _offset, unsigned int _length){
    String datoRetornar;
    for(int i = 0; i < _length; i++)
      datoRetornar += this->readInEEPROM(_offset+i);
    return datoRetornar;
}

/**
  * Get the actual date as a String.
  * @return Parsed String who indicates the date and time DD/MM/YYYY - hh:mm:ss.
*/
String RTCuse::getDate(void){
    DateTime date = this->getDateTime();
    String fecha = "";
    if(date.day() < 10) fecha += "0";
    fecha += date.day();
    fecha += "/";
    if(date.month() < 10) fecha += "0";
    fecha += date.month();
    fecha += "/";
	fecha += date.year();
	
    fecha += " - ";
  
    if(date.hour() < 10) fecha += "0";
    fecha += date.hour();
    fecha += ":";
    if(date.minute() < 10) fecha += "0";
    fecha += date.minute();
    fecha += ":";
    if(date.second() < 10) fecha += "0";
    fecha += date.second();
    
    return fecha;
}

/**
  * Adjust the Date when the program is uploaded from the computer.
  * @return Nothing.
*/
void RTCuse::adjustDate(void){
   if (!rtc.begin()) while (1);
   if (rtc.lostPower()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

/**
  * Get the actual date and hour in a DateTime object.
  * @return DateTime object with the actual date and hour.
*/
DateTime RTCuse::getDateTime(void){ return rtc.now(); }

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

