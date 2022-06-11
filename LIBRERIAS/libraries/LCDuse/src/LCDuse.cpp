/*
  LCDuse.cpp - LCDuse library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "LCDuse.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
/**
  * Initialize the LCD setup and reset it for its correctly use.
  * @param _address The I2C LCD address.
  * @param _columns Number of LCD char columns.
  * @param _rows Number of LCD char rows.
  * @return Nothing.
*/
void LCDuse::init(byte _address, uint8_t _columns, uint8_t _rows){
	_lcd = new LiquidCrystal_I2C(_address, _columns, _rows);
	_lcd->init();
	_lcd->clear();
	_lcd->backlight();
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
/**
  * Print on the screen (Only for 2 rows LCD device).
  * @param _text1 Text to print in first row.
  * @param _text2 Text to print in second row.
  * @param inicPos1 Column start position in the first row.
  * @param inicPos2 Column start position in the second row.
  * @return Nothing.
*/
void LCDuse::print(String _text1, String _text2, unsigned short int inicPos1, unsigned short int inicPos2){
	_lcd->clear();
	_lcd->setCursor(inicPos1,0);   //Set cursor to character 2 on line 0
	_lcd->print(_text1);
	_lcd->setCursor(inicPos2,1);   //Move cursor to character 2 on line 1
	_lcd->print(_text2);
}

/**
  * Print on the screen (Only for 2 rows LCD device).
  * @param _text1 Text to print in first row.
  * @param _data2 Data object to print in second row.
  * @param inicPos1 Column start position in the first row.
  * @param inicPos2 Column start position in the second row.
  * @return Nothing.
*/
void LCDuse::print(String _text1, Data _data2, unsigned short int inicPos1, unsigned short int inicPos2){
  this->print(_text1,_data2.getData(),inicPos1,inicPos2);
}

/**
  * Print on the screen (Only for 2 rows LCD device).
  * @param _data1 Data object to print in first row.
  * @param _text2 Text to print in second row.
  * @param inicPos1 Column start position in the first row.
  * @param inicPos2 Column start position in the second row.
  * @return Nothing.
*/
void LCDuse::print(Data _data1, String _text2, unsigned short int inicPos1, unsigned short int inicPos2){
  this->print(_data1.getData(),_text2,inicPos1,inicPos2);
}

/**
  * Print on the screen (Only for 2 rows LCD device).
  * @param _data1 Data object to print in first row.
  * @param _data2 Data object to print in second row.
  * @param inicPos1 Column start position in the first row.
  * @param inicPos2 Column start position in the second row.
  * @return Nothing.
*/
void LCDuse::print(Data _data1, Data _data2, unsigned short int inicPos1, unsigned short int inicPos2){
  this->print(_data1.getData(),_data2.getData(),inicPos1,inicPos2);
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

