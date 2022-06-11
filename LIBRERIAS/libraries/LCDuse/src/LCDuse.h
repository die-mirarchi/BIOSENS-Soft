/*
  LCDuse.h - LCDuse library for Arduino - description
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef LCDuse_h
#define LCDuse_h

// Include libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Data.h>

/**
 *  LCDuse class. Class for LCD management.\n
 *  This class is in charge of setup and use the LCD Screen with I2C connections.
 */
class LCDuse{
  // user-accessible "public" interface
  public:
	//Initializers
    void init(byte _address = 0x27, uint8_t _columns = 16, uint8_t _rows = 2);
    
    //print for 2 rows LCD's
    void print(String _text1, String _text2 = "", unsigned short int inicPos1 = 0, unsigned short int inicPos2 = 0);
    void print(String _text1, Data _data2, unsigned short int inicPos1 = 0, unsigned short int inicPos2 = 0);
    void print(Data _data1, String _text2 = "", unsigned short int inicPos1 = 0, unsigned short int inicPos2 = 0);
    void print(Data _data1, Data _data2, unsigned short int inicPos1 = 0, unsigned short int inicPos2 = 0);

  // library-accessible "private" interface
  private:
    LiquidCrystal_I2C *_lcd;    /*!< LiquidCrystal for LCD management. */
};

#endif

