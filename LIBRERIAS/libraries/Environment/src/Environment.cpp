/*
  Environment.cpp - Environment library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "Environment.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

////Statics
/**
  * Get the option ID through its enum type.
  * @see menuOptions
  * @param _option Option enum type to convert to ID or index.
  * @return A numeric ID or index for the option selected.
*/
int Environment::getOptionID(menuOptions _option){ return (int)_option; }

/**
  * Get the option enum type through its ID or index.
  * @see menuOptions
  * @param _id Option ID or index.
  * @return The enum type related to the numeric ID option.
*/
menuOptions Environment::getOptionByID(int _id){ return (menuOptions)_id; }

/**
  * Get the option enum type through its keyword.
  * @see menuOptions
  * @param _keyword Keyword choosen for refer to the option.
  * @return The enum type related to the keyword option.
*/
menuOptions Environment::keywordToOption(String _keyword){
	_keyword.toUpperCase();
	_keyword.remove(_keyword.length() - 2);
		Serial.println("_keyword queda como: " + _keyword);
	if(_keyword == "GENERAL") return MO_GENERAL;
	else if(_keyword == "TERMICA") return MO_TERMICA;
	else if(_keyword == "GRUPOS") return MO_GRUPOS;
	else if(_keyword == "TELEFONO1" || _keyword == "TEL1") return MO_TELEFONO1;
	else if(_keyword == "TELEFONO2" || _keyword == "TEL2") return MO_TELEFONO2;
	else if(_keyword == "TELEFONO3" || _keyword == "TEL3") return MO_TELEFONO3;
  else if(_keyword == "CAMBIAR TELEFONO1" ||_keyword == "CAMBIAR TEL1") return MO_CAMBIAR_TELEFONO1;
	else if(_keyword == "CAMBIAR TELEFONO2" ||_keyword == "CAMBIAR TEL2") return MO_CAMBIAR_TELEFONO2;
	else if(_keyword == "CAMBIAR TELEFONO3" ||_keyword == "CAMBIAR TEL3") return MO_CAMBIAR_TELEFONO3;
  else if(_keyword == "BORRAR TELEFONO1" ||_keyword == "BORRAR TEL1") return MO_DEL_TELEFONO1;
	else if(_keyword == "BORRAR TELEFONO2" ||_keyword == "BORRAR TEL2") return MO_DEL_TELEFONO2;
	else if(_keyword == "BORRAR TELEFONO3" ||_keyword == "BORRAR TEL3") return MO_DEL_TELEFONO3;
	else if(_keyword == "FECHA") return MO_FECHA;
	else if(_keyword == "HORA") return MO_HORA;
	else if(_keyword == "ALERTAS" || _keyword == "ALERTA") return MO_ALERTAS;
	else if(_keyword == "CAMBIAR ALERTAS" || _keyword == "CAMBIAR ALERTA") return MO_CAMBIAR_ALERTAS;
	else return MO_NULL;
}

/**
  * Verify if a String is a phone number or not.
  * @param _number String to analize.
  * @retval true Is a phone number.
  * @retval false Is not a phone number.
*/
bool Environment::isAPhoneNumber(String _number){
  Serial.println(_number + " is a valid phone number?");
  if(_number[0] != '+') return false;
  for(int i = 0; i < _number.length(); i++){
	  Serial.println("Analizando " + _number[i]);
	  if(!(isDigit(_number[i]) || _number[i] == '+')) return false;
  }
  return true;
}

////No Statics
//geters
/**
  * Get the General configured pin.
  * @return The pin of General Current.
*/
int8_t Environment::getGeneralPin(void){ return this->pinGeneral; }

/**
  * Get the Termica configured pin.
  * @return The pin of Termica Current.
*/
int8_t Environment::getTermicaPin(void){ return this->pinTermica; }

/**
  * Get the Grupos configured pin.
  * @return The pin of Generator sets Current.
*/
int8_t Environment::getGruposPin(void){ return this->pinGrupos; }

/**
  * Get the indexed phone number.
  * @param _index Index of Phone groove on EEPROM. (0-2)
  * @return The Data object of the phone requested.
*/
Data Environment::getPhone(uint8_t _index){ 
	switch(_index){
		case 0:
			return bloque->getDataObject("PHONE1"); 
		case 1:
			return bloque->getDataObject("PHONE2"); 
		case 2:
			return bloque->getDataObject("PHONE3"); 
		default:
			Data dataError;
			return dataError;
	}
}

/**
  * Get the indexed phone number as a String.
  * @param _index Index of Phone groove on EEPROM. (0-2)
  * @return The requested phone number as a String.
*/
String Environment::getPhoneString(uint8_t _index){ 
	return this->getPhone(_index).getData();
}

/**
  * Get the alerts time Data object.
  * @return Alert time Data object.
*/
Data Environment::getAlertTime(){ return bloque->getDataObject("ALERTS"); }

/**
  * Get the alerts time configured.
  * @return Alert time on minutes as an int.
*/
int Environment::getAlertTimeInt(){ return bloque->getDataObject("ALERTS").getData().toInt(); }

//setters
/**
  * Set the General pin.
  * @param _pinGeneral New Pin for General.
  * @return Nothing.
*/
void Environment::setGeneralPin(int8_t _pinGeneral){ this->pinGeneral = _pinGeneral; }

/**
  * Set the Termica pin.
  * @param _pinGeneral New Pin for Termica.
  * @return Nothing.
*/
void Environment::setTermicaPin(int8_t _pinTermica){ this->pinTermica = _pinTermica; }

/**
  * Set the Grupos pin.
  * @param _pinGeneral New Pin for Grupos.
  * @return Nothing.
*/
void Environment::setGruposPin(int8_t _pinGrupos){ this->pinGrupos = _pinGrupos; }

//Methods
/**
  * Run the option requested.
  * @see menuOtions
  * @param _option Option to run (menuOptions).
  * @param _arg Extra arguments if required.
  * @return A String with the response to the action performed.
*/
String Environment::runMenuOption(menuOptions _option, String _arg){
  switch(_option){
    case MO_GENERAL:
      if(digitalRead(this->pinGeneral)) return "Funcionando correctamente";
      else return "No esta en su correcto funcionamiento";
    case MO_TERMICA:
      if(digitalRead(this->pinTermica)) return "Funcionando correctamente";
      else return "No esta en su correcto funcionamiento";
    case MO_GRUPOS:
      if(digitalRead(this->pinGrupos)) return "Funcionando correctamente";
      else return "No esta en su correcto funcionamiento";
    
    case MO_TELEFONO1:
      return this->bloque->getDataObject("PHONE1").getData();
    case MO_TELEFONO2:
      return this->bloque->getDataObject("PHONE2").getData();
    case MO_TELEFONO3:
      return this->bloque->getDataObject("PHONE3").getData();
    case MO_CAMBIAR_TELEFONO1:
      if(!this->isAPhoneNumber(_arg)) return "Numero de telefono no valido";
      this->bloque->getDataObject("PHONE1").setData(_arg);
      return "Operacion validada";
    case MO_CAMBIAR_TELEFONO2:
      if(!this->isAPhoneNumber(_arg)) return "Numero de telefono no valido";
      this->bloque->getDataObject("PHONE2").setData(_arg);
      return "Operacion validada";
    case MO_CAMBIAR_TELEFONO3:
      if(!this->isAPhoneNumber(_arg)) return "Numero de telefono no valido";
      this->bloque->getDataObject("PHONE3").setData(_arg);
      return "Operacion validada";
  case MO_DEL_TELEFONO1:
	  this->bloque->getDataObject("PHONE1").setData("-NO DEFINIDO-");
	  return "Ranura borrada correctamente.";
	case MO_DEL_TELEFONO2:
	  this->bloque->getDataObject("PHONE2").setData("-NO DEFINIDO-");
	  return "Ranura borrada correctamente.";
	case MO_DEL_TELEFONO3:
	  this->bloque->getDataObject("PHONE3").setData("-NO DEFINIDO-");
	  return "Ranura borrada correctamente.";

    case MO_ALERTAS:
      return "Las alertas estan configuradas cada " + this->bloque->getDataObject("ALERTS").getData() + " minutos.";
    case MO_CAMBIAR_ALERTAS:
      if(_arg.toInt() <= 0) return "Operacion invalida";
	  this->bloque->getDataObject("ALERTS").setData(_arg);
      return "Operacion validada";

    case MO_FECHA:
      return this->rtc->getDate();
    case MO_HORA:
      return this->rtc->getDate();
    
    default:
      return "ERROR. Operacion invalida, consulte el manual.";  
  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library