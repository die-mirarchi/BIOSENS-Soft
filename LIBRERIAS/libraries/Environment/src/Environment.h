/*
  Environment.h - Environment library for Arduino - description
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef Environment_h
#define Environment_h

// Include libraries
#include <Arduino.h>
#include <Data.h>
#include <Block.h>
#include <RTCuse.h>

/** 
  * menuOptions enum.
  * Different options for run in our software.
  */
enum menuOptions : int8_t{
   MO_NULL = -1,            /*!< NULL value, no option. */
   MO_GENERAL = 0,          /*!< General current state. */
   MO_TERMICA,              /*!< Termica current state. */
   MO_GRUPOS,               /*!< Grupos current state. */

   MO_TELEFONO1,            /*!< Master phone number. */
   MO_TELEFONO2,            /*!< Secondary phone number. */
   MO_TELEFONO3,            /*!< Third phone number. */
   MO_CAMBIAR_TELEFONO2,    /*!< Change the secondary phone number. */
   MO_CAMBIAR_TELEFONO3,    /*!< Change the third phone number. */
   MO_DEL_TELEFONO2, 		/*!< Delete secondary phone of the groove. */
   MO_DEL_TELEFONO3,		/*!< Delete third phone of the groove. */
   
   MO_ALERTAS,              /*!< Time alerts on minutes. */
   MO_CAMBIAR_ALERTAS,      /*!< Change time alerts on minutes. */
  
   MO_FECHA, MO_HORA        /*!< Time and Date. */
};

/**
 *  Environment class. Class for managin all the most important software actionss.\n
 *  This class is in charge of the simple manage of the project environment and provide simplicity and clarity to the main code.
 */
class Environment{
  // user-accessible "public" interface
  public:
	//Constructor
  /**
    * Environment constructor.
    * @param _B The block addres for its use in the environment.
    * @param _rtc The block addres for its EEPROM use in the environment.
    * @param _pinGeneral Pin for General current verification.
    * @param _pinTermica Pin for Termica current verification.
    * @param _pinGrupos Pin for Grupos current verification.
  */
    Environment(Block *_B, RTCuse *_rtc, int8_t _pinGeneral = -1, int8_t  _pinTermica = -1, int8_t  _pinGrupos = -1){
      this->bloque = _B;
      this->rtc = _rtc;
      this->pinGeneral = _pinGeneral;
      this->pinTermica = _pinTermica;
      this->pinGrupos = _pinGrupos;
	  pinMode(this->pinGeneral,INPUT);
	  pinMode(this->pinTermica,INPUT);
	  pinMode(this->pinGrupos,INPUT);
	}
	
	//Static methods
    static int getOptionID(menuOptions _option);            //Returns an int for an option in the menu
    static menuOptions getOptionByID(int _id);              //Returns the option by the ID
	static menuOptions keywordToOption(String _keyword);	  //Returns the option by the text assigned
	static bool isAPhoneNumber(String _number);
    
	//geters Environment
    int8_t getGeneralPin(void);
    int8_t getTermicaPin(void);
    int8_t getGruposPin(void);
	
	//geters all
    Data getPhone(uint8_t _index);
    String getPhoneString(uint8_t _index);
    Data getAlertTime(void);
    int getAlertTimeInt(void);

    //setters
    void setGeneralPin(int8_t _pinGeneral);
    void setTermicaPin(int8_t _pinTermica);
    void setGruposPin(int8_t _pinGrupos);
	
    //Methods
	String runMenuOption(menuOptions _option, String _arg = "");           	//Return different information depending of the chosen option
																			//Run different instructions depending of the chosen option

  // library-accessible "private" interface
  private:
    Block *bloque;                            /*!< Block Pointer of Data Structure on our environment. */
    RTCuse *rtc;                              /*!< RTC Pointer for data management on EEPROM. */
    int8_t pinGeneral, pinTermica, pinGrupos; /*!< Sens pins. */
};

#endif

