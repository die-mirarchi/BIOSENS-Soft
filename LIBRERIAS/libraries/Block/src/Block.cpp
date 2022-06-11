/*
  Block.cpp - Block library for Arduino - implementation
  Copyright (c) 2020 UNSAM CIDI.  All right reserved.
*/

// include this library's description file
#include "Block.h"

// Constructor/Initializer and Destructors /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
/**
  * Initialize all the stored Data in the EEPROM.
  * 
  * initAllData is in charge of execute the init() method on every Data saved on the block.\n
  * This will initialize the Data in EEPROM. Only for first time writing Data.
  *
  * @return Nothing
*/
void Block::initAllData(void){
  for(int i = 0; i < this->dataQuantity; i++)
    dataBlocks[i]->init();
}

/**
  * Destroy the instance.
  */
Block::~Block(){
	delete this->dataBlocks;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

//Gets
/**
  * Get the indexed Data object.
  * @param _index The Data index on block.
  * @return The Data object requested.
*/
Data Block::getDataObject(uint8_t _index){
  return *(dataBlocks[_index]);
}

/**
  * Get a Data object on block according to its name.
  * @param _dataName The name of the Data to search.
  * @return The Data object requested.
*/
Data Block::getDataObject(String _dataName){
  for(int i = 0; i < this->dataQuantity; i++)
    if(dataBlocks[i]->getName().equals(_dataName))
      return this->getDataObject(i);
  Data errorData;
  return errorData;
}

/**
  * Get the whole block offset on EEPROM.
  * @return The block offset on EEPROM.
*/
unsigned int Block::getBlockOffset(void){ return this->blockOffset; }

//Sets
/**
  * Set the whole block offset on EEPROM.
  * @param _offset - The new block offset on EEPROM.
  * @return Nothing.
*/
void Block::setBlockOffset(unsigned int _offset){ this->blockOffset = _offset; }

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

