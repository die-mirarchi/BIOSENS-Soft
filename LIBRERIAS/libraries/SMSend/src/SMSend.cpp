/*
  SMSend.cpp - SMSend library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "SMSend.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	/**
	  * SMSend object constructor for Arduino Mega 1280 or 2560.
	  * @param _serial Select the Hardware Serial port tu use (1,2,3).
	  * @param _baudRate The baud rate of the communication with SIM800L.
	  * @return Nothing.
	*/
	SMSend::SMSend(uint8_t _serial, int _baudRate){
		switch(_serial){
			case 1:
				swseri = &Serial1;
				break;
			case 2:
				swseri = &Serial2;
				break;
			case 3:
				swseri = &Serial3;
				break;
			default:
				swseri = &Serial1;
		}
		swseri->begin(_baudRate);
	}
	
	/**
	  * SMSend object constructor for Arduino Mega 1280 or 2560.
	  * @param _serial Select the Hardware Serial port tu use passing its addres. (&Serial1,&Serial2,&Serial3).
	  * @param _baudRate The baud rate of the communication with SIM800L.
	  * @return Nothing.
	*/
	SMSend::SMSend(HardwareSerial *_serial, int _baudRate){
		swseri = _serial;
		swseri->begin(_baudRate);
	}
#else
	/**
	  * SMSend object constructor for Arduino UNO, Leonardo and more.
	  * @param _pinRX RX pin for new Software Serial.
	  * @param _pinTX TX pin for new Software Serial.
	  * @param _baudRate The baud rate of the communication with SIM800L.
	  * @return Nothing.
	*/
	SMSend::SMSend(uint8_t _pinRX, uint8_t _pinTX, int _baudRate){
		swseri = new SoftwareSerial(_pinRX,_pinTX);
		swseri->begin(_baudRate);
	}
#endif

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

/**
  * Send an SMS to a phone number.
  * @param _phoneNumber The phone number as +ZZxxxxxxxxxx. Example: +541199999999
  * @param _message The message to send.
  * @return Nothing.
*/
void SMSend::sendSMS(String _phoneNumber, String _message){
	swseri->println("AT+CMGF=1");  delay(200); 
	String command = "AT+CMGS=\"" + _phoneNumber + "\"";
	swseri->println(command);      delay(200);
	swseri->print(_message);       delay(500);
	swseri->print(char(0x1A));     delay(2000);
}

/**
  * Verify if a message was received and get it.
  * @return The message with its information (without parsing).
*/
String SMSend::receiveSMS(){
	swseri->println("AT+CMGF=1"); delay(100);
	swseri->println("AT+CNMI=1,2,0,0,0"); delay(5000);

	String msg = "";
	while(swseri->available() > 0)
		msg += (char)swseri->read();
	
	return msg.substring(42);
}

/**
  * Verify if the message received is a SMS or not.
  * @param _message The message received.
  * @retval true The message is a valid SMS.
  * @retval false The message is not a valid SMS.
*/
bool SMSend::isSMS(String _message){
	return _message.substring(0,4) == "+CMT";
}

/**
  * Get the message itself using the whole String received from receiveSMS() and parsing it.
  * @see receiveSMS()
  * @param _message The message received.
  * @return Only the message.
*/
String SMSend::getMessageSMS(String _message){
	String sms;
	bool flag;
	int cont = 0, inic, fin;

	for(int i = 0; i < _message.length(); i++){
		if(_message[i] == '\"'){ 
		  cont++; 
		  if(cont == 6) {inic = i+3; break;}
		  flag = true;
		}
		flag = false;
	}

	return _message.substring(inic);
}

/**
  * Get the phone who sent a message using the whole String received from receiveSMS() and parsing it.
  * @see receiveSMS()
  * @param _message The message received.
  * @return Phone who sent the message.
*/
String SMSend::getMessagePhone(String _message){
	String sms;
	bool flag;
	int cont = 0, inic, fin;

	for(int i = 0; i < _message.length(); i++){
		if(_message[i] == '\"'){ cont++; flag = true;}

		if(cont == 1 && flag) inic = i+1;
		else if(cont == 2 && flag) {fin = i; break;}
		flag = false;
	}

	return _message.substring(inic,fin);
}

/**
  * Get the Date when the message was sent using the whole String received from receiveSMS() and parsing it.
  * @see receiveSMS()
  * @param _message The message received.
  * @return The Date when the message was sent.
*/
String SMSend::getMessageDate(String _message){
	String sms;
	bool flag;
	int cont = 0, inic, fin;

	for(int i = 0; i < _message.length(); i++){
		if(_message[i] == '\"'){ cont++; flag = true;}

		if(cont == 5 && flag) inic = i+1;
		else if(cont == 6 && flag) {fin = i; break;}
		flag = false;
	}

	return _message.substring(inic,fin);
}

/**
  * Get the message information we want using the datos_mensaje enum types and parcing the String received from receiveSMS().
  * @see receiveSMS()
  * @see datos_mensaje
  * @param _option The information we want to extract.
  * @param _message The message received.
  * @return The message information requested.
*/
String SMSend::getMessageInfo(datos_mensaje _option,String _message){ 
	String res;
	if(this->isSMS(_message)){
		switch(_option){
		  case MESSAGE:
			return this->getMessageSMS(_message);
		  case PHONE_NUMBER:
			res = this->getMessagePhone(_message);
			res.remove(3,1);
			return res;
		  case SENT_DATE:
			res = this->getMessageDate(_message);
			return res;
		}
	} else return "ERROR";
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

