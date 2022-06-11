/*
  RTCuse.h - RTCuse library for Arduino - description
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef RTCuse_h
#define RTCuse_h

// Include libraries
#include <Arduino.h>
#include <RTClib.h>
#include <AT24CX.h> //Change AT24CX_ID to B1010111 (0x57) in that file.

/**
 *  RTCuse class. Class for RTC time and EEPROM management.\n
 *  This class is in charge of managing the RTC EEPROM and provide the time and date using the same module.
 */
class RTCuse{
  // user-accessible "public" interface
  public:
	//EEPROM methods
	void saveInEEPROM(uint16_t _offset, char _dato);
	void saveInEEPROM(uint16_t _offset, String _dato);
	char readInEEPROM(uint16_t _offset);
	String readInEEPROM(uint16_t _offset, unsigned int _length);

	//Time methods
	void adjustDate(void);
	DateTime getDateTime(void);
	String getDate(void);

  // library-accessible "private" interface
  private:
    AT24C32 EepromRTC;				/*!< Manage RTC EEPROM AT24C32. */
    RTC_DS3231 rtc;					/*!< Manage RTC date and time with DS3231. */
};

#endif

