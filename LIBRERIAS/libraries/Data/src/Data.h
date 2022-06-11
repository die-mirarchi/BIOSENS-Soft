/*
  Data.h - Data library for Arduino - description
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef Data_h
#define Data_h

// Include libraries
#include <Arduino.h>
#include <RTCuse.h>

/**
 *  Data class. Class for save and read data in EEPROM.\n
 *  This class is in charge of create and manage a single data on the RTC EEPROM.
 */
class Data{
  // user-accessible "public" interface
  public:
	//Constructors
    Data(int16_t _offset = -1, String _data = "");
    Data(String _name, int16_t _offset = -1, String _data = "");
	
	//Initializer
    void init(void);
    
    //gets
    String getData(void);                         	//Read the entire data on EEPROM
	String getStaticData(void);
	String getName(void);                         	//Get the name given to the Data
    unsigned int getLength(void);                 	//Get the lenght of the data without the header lenght
    int16_t getOffset(void);                     	//Get the offset value of the Data
    int16_t getEndOfData(void);                  	//Get the last byte of the data

    //sets
    //void setLenght(unsigned int _length);         //Set the lenght of the data without the header lenght
    void setOffset(int16_t _offset);             	//Set the offset value of the Data
    void setData(String _data);                   	//Change the Data only on the RAM.

  // library-accessible "private" interface
  private:
    //Attributes
    unsigned int dataLength;                      /*!< Length of the data on bytes. */
    int16_t offsetOnEEPROM;                       /*!< Offset of the data in the EEPROM. */
    String dataSave, dataName;					  /*!< Static data and data's name as possible identifier. */
    RTCuse rtcManage;                        	  /*!< Rtc EEPROM management. */
};

#endif

