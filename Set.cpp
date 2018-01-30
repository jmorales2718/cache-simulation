// John Morales
// Program 3
// Set.cpp
// CS 301
//
// Purpose: This program implements the set class in order to store data of a 
//          cache set object. It also contains a vector of blocks, which will
//          store all the cache blocks in the set. 
//


#include "Set.h"
#include <iostream>

using namespace std;


// Default Constructor creates the set object and assigns default values to
// the global variables.
//
Set::Set()
{
  setIndex       = 0;
  currTag        = 0;
  hitCounter     = 0;
  setAssoc       = 0;
  currBCapacity  = 0;
  currBlock_size = 0;
}


// Initializes the variables, by using the given arguments, without populating 
// all of the blocks contained in the set. 
//
void Set::initializeVars(long long addr, int capacity, int block_size, int setAssoc, long long setIndex)
{
  this->setAssoc       = setAssoc;
  this->currBCapacity  = capacity;
  this->currBlock_size = block_size; 
  this->setIndex       = setIndex;

  int numSets    = capacity / (block_size * setAssoc);
  int blockAddr  = addr / block_size;
  currTag        = blockAddr / numSets;  
}


// Initializes the variables, by using the given arguments, and populates the set
// with empty blocks.
//
void Set::initializeDefaultSet(long long addr, int capacity, int block_size, int setAssoc, long long setIndex)
{
  initializeVars(addr, capacity, block_size, setAssoc, setIndex);
  
  //adds empty blocks to fill the set.
  for(int i = 0; i < setAssoc; i++)
  {
    Block b;
    mySet.push_back(b);
  }
}


// Determines if the set is full, where full is defined as needing to have an
// eviction or a hit in order to access the set. Then it returns the boolean
// value indicating whether or not the set is full.
//
bool Set::isSetFull()
{
  int count = 0;
  for(unsigned int i = 0; i < mySet.size(); i++)
  {
    if(mySet[i].getValidBit() == 1)
    {
      count++;
    }
    else
    {
      break;
    }
  }
  if(count == setAssoc)
  {
    return true;
  }
  return false;
}


// Using the given address argument, this method checks if the access is a hit,
// in the current set object. If it is the method will return the lru of the 
// hit in the current set. If not it will return -1.
//
int Set::checkForHit(long long addr)
{
  // will be returned as either the index of the hit or -1 if not a hit
  int lruOfHit = -1;

  // moves through set looking for a hit
  for(unsigned int i = 0 ; i < mySet.size(); i++)
  { 
    // checks if there is a hit.
   
    if(mySet[i].getTag() == currTag && mySet[i].getLRU() >= 0 && mySet[i].getIndex() == setIndex && mySet[i].getValidBit() == 1)
    {
      lruOfHit = mySet[i].getLRU();
      break;
    }
  }
  // every time we hit, we increment hitCounter
  if(lruOfHit != -1)
  {
    hitCounter++;  
  }
  return lruOfHit;
}


// Determines if the access is not a hit, if not we add a block to the current set 
// or evict the least recently used block. The given address argument indicates the
// values of the block to add.
//
void Set::addBlock(long long addr)
{
  // Will indicate if the set was full before the most recent access.
  bool fullPreAccess       = false; 
  bool hit                 = false;   // Will indicate if there was a hit.
  int hitLRU               = -1;      // Will store the lru of the a hit's block.
  unsigned int indexToEdit = 0; 
  int accessLRU            = 0;

  hitLRU = checkForHit(addr);         //retrieve hit lru if there is a hit.
  
  //determines if there was a hit or not.
  if(hitLRU != -1)
  {
    //Check if set was full before access
    if(isSetFull() == true)
    {
      fullPreAccess = true;
    }
    
    hit       = true;
    accessLRU = hitLRU;
    int lruIndex = -1;
    
    //finds the index that will be changed
    for(unsigned int i = 0;  i < mySet.size()-1; i++)
    {
      if(mySet[i].getLRU() == accessLRU)
      {
        lruIndex = i;
      }
    }
    indexToEdit = lruIndex;
  }
  //if not a hit add access.
  else
  {
    // Handles case where there will be an eviction
    if(isSetFull() == true)
    {

      fullPreAccess = true;
      int maxLRU    = -1;      // will store the highest lru of set
      int lruIndex  = -1;    // will store the index of the block contiaining maxLRU
   
      // Searches the set to find the least recently used block
      for(indexToEdit = 0; indexToEdit < mySet.size() - 1; indexToEdit++)
      {
            // finds the block with highest lru
            if(mySet[indexToEdit].getLRU() > maxLRU)
            {
              maxLRU = mySet[indexToEdit].getLRU();
              lruIndex = indexToEdit;
              accessLRU = maxLRU; 
            }  
      }
      //handle case of direct mapped cache
      if(setAssoc == 1)
      {
        lruIndex = 0;
      }
      // if not a hit and full set we must call evict
      evictBlock(addr, lruIndex);  
    }
    //if the set isn't full and isn't a hit we need to add to the first index with valid bit of 0
    else
    {
      for(indexToEdit = 0; indexToEdit < mySet.size(); indexToEdit++)
      {
        // if not a hit then we have to add a new block to the set 
          Block b;
          b.initializeBlock(addr, setAssoc, currBCapacity, currBlock_size);
          // find the first index with a valid bit of 0
          while(mySet[indexToEdit].getValidBit() == 1)
          {
            indexToEdit++;
          }
          this->mySet[indexToEdit] = b;
          break;   
      }
    }
  }
  // if the set associativity is 1 we don't need to increment lrus
  // because there is only one block per set.
  if(setAssoc > 1)
  {
    this->incLRU(indexToEdit, accessLRU, fullPreAccess);
  }
}


// Increments the lru values when a there is an access to the set. The argument 
// editedIndex indicates the index most recently used, target lru indicates the
// lru of the most recently used index and full before access indicates if the
// set was already full before the most recent access.
//
void Set::incLRU(unsigned long long editedIndex, int targetLRU, bool fullBeforeAccess)
{
  // Handles case where set was full before the newest value was accessed 
  if(isSetFull() == true && fullBeforeAccess == true)
  {
    //increments every lru that was less than the most recently used (mru).
    for(unsigned int j = 0; j < mySet.size(); j++)
    {
      //only increment lru values less than the mru
      if(mySet[j].getLRU() < targetLRU)
      {
        int tempLRU = mySet[j].getLRU() + 1;
        mySet[j].setLRU(tempLRU);
      }
    }
  }
  // Handles case where set wasn't full before newest value was accessed
  else
  {
    // Increments every lru that is not the mru or uninitialized
    for(unsigned int j = 0; j < mySet.size(); j++)
    {
      // Increment if lru is uninitialized (i.e. -1) or not equal to mru
      if(mySet[j].getLRU() >= 0 && editedIndex != j)
      {
        int tempLRU = mySet[j].getLRU() + 1;
        mySet[j].setLRU(tempLRU);
      }
    }
  }    
  //Set the lru of the mru block to 0 
  mySet[editedIndex].setLRU(0);
}


// Evicts a block from the provided index and replaces it with the block created
// from the indicated address.
//
void Set::evictBlock(long long addr, long long index)
{
  Block b;
  b.initializeBlock(addr, setAssoc, currBCapacity, currBlock_size);
  mySet[index] = b;
}


// Prints the set number and each block in the set.
//
void Set::printSet()
{
  cout << "*******" << "Set " << setIndex << "*******" << endl;
  for(unsigned int i = 0 ; i < mySet.size(); i++)
  {   
    cout << "Index " << i << ":" << " ";
    mySet[i].printBlock();
  }
  cout << "***********************" << endl;
}
