/*
  Block.h - Block library for Arduino - description
  Copyright (c) 2021 UNSAM CIDI.  All right reserved.
*/

// Ensure this library description is only included once
#ifndef Block_h
#define Block_h

// Include libraries
#include <Arduino.h>
#include <Data.h>

/**
 *  Block class. Class for joint data management.\n
 *  This class is in charge of managing a data set (Data.h) integrated in itself, so that we can more easily access certain functionalities of the data structure to be created.
 */
class Block{
  // User-accessible "public" interface
  public:
	//Initializers (Defined here cause an error when declaring on another file)
	/**
	  * Initialize the Block charging the Data on it.
	  * @param _bloques The Data structure on an array.
	  * @param _offset The whole block offset.
	  * @return The Data object requested.
	*/
    template<size_t N>
    void init(Data (&_bloques)[N], unsigned int _offset = 0){
	  this->blockOffset = _offset;
	  this->dataQuantity = (uint16_t) N;
	  dataBlocks = (Data**) malloc(sizeof(Data)*this->dataQuantity);
	  for(int i = 0; i < (int)N; i++){
		dataBlocks[i] = &_bloques[i];
		dataBlocks[i]->setOffset(_bloques[i].getOffset() + this->blockOffset);
	  }
	}
	
	//Internal Initializer
    void initAllData(void);
	
	//Destructors
	~Block(void);
	
	//Gets
    Data getDataObject(uint8_t _index);
    Data getDataObject(String _dataName);
    unsigned int getBlockOffset(void);
	
	//Sets
    void setBlockOffset(unsigned int _offset);

  // Library-accessible "private" interface
  private:
    Data **dataBlocks;				/*!< The set of Datas who make the Data Structure. */
    unsigned int blockOffset;		/*!< The whole block offset. */
    uint16_t dataQuantity;			/*!< the amount of data in the block*/
};

#endif

