// John Morales
// Program 3
// Block.cpp
// CS 301
//
//Purpose: To create the framework for storing information for a single block in a 
//         cache and allow for printing of that block's information.


#include "Block.h"
#include <iostream>
#include <iomanip>

using namespace std;


// Default constructor for a Block object, creates a default block with initialized
// cache fields.
//
Block::Block()
{
  validBit = 0;  
  offset   = 0;
  tag      = 0;
  index    = 0;
  lru      = -1;
}


// Initializes the block, using information about the address it will contain, the 
// set associativity of the current cache, and the capacity of the current cache and
// the block size in the current cache. This information is stored globally to be
// used by the get methods, as well as parse address.
//
void Block::initializeBlock(long long addr, int setAssociativity, int capacity, int block_size)
{
  assoc     = setAssociativity;
  capac     = capacity;
  bSize     = block_size;
  blockAddr = addr/block_size;
  numBlocks = capacity/block_size;
  
  parseAddress(addr);
  validBit = 1;
}


// Parses given address to calculate information such as: index, tag, and offset.
// This information is then stored in global variables to be used by get methods.
//
void Block::parseAddress(long long addr)
{
  // Handles case where address is 0 and calculations will just waste time.
  if(addr == 0)
  {
    lru = 0;
  }
  else
  {
    offset      = addr % bSize;
    int numSets = numBlocks / assoc;
    index       = blockAddr % numSets;
    tag         = blockAddr / numSets;
    lru         = 0;
   }
}


// Prints basic information about the block such as: tag, valid bit, and lru.
//
void Block::printBlock()
{
  
  cout << "tag "    << hex << getTag()      << " ";
  cout << "valid "  << dec << getValidBit() << " ";
  cout << "lru "    << dec << getLRU()      << endl;
}
