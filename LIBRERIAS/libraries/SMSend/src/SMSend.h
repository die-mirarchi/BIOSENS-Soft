/*
  SMSend.h - SMSend library for Arduino - description
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef SMSend_h
#define SMSend_h

// Include libraries
#include <Arduino.h>
#include <SoftwareSerial.h>	//Change _SS_MAX_RX_BUFF to 256 in that file
#include <HardwareSerial.h>	//Change SERIAL_RX_BUFFER_SIZE to 128 and 256 in that file

/** 
  * datos_mensaje enum.
  * Different data types we can extract from a message.
  */
enum datos_mensaje{
  MESSAGE = 0,    /**< The message itself. */ 
  PHONE_NUMBER,       /**< The phone that sent the message. */ 
  SENT_DATE           /**< The date the message was sent. */ 
};

/**
 *  SMSend class. Class for sending and receiving SMS with SIM800L.\n
 *  This class is in charge of send and receive SMS messages and access its information.
 */
class SMSend{
  // user-accessible "public" interface
  public:
	  //Constructors
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	SMSend(uint8_t _serial = 1, int _baudRate = 9600);
	SMSend(HardwareSerial* _serial, int _baudRate = 9600);
#else
	SMSend(uint8_t _pinRX, uint8_t _pinTX, int _baudRate);
#endif
	
	//Send
    void sendSMS(String _phoneNumber, String _message);
    
    //Receive
	String receiveSMS();

	//SMS message data administration
	bool isSMS(String _message);
	
    String getMessageSMS(String _message);
    String getMessagePhone(String _message);
    String getMessageDate(String _message);
    
    String getMessageInfo(datos_mensaje _option, String _message);

  // library-accessible "private" interface
  private:
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	HardwareSerial *swseri;			/*!< Selected Hardware Serial for the SIM800L. */
#else
	SoftwareSerial *swseri;         /*!< New Software Serial for the SIM800L. */
#endif
};

#endif

