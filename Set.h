// John Morales
// Program 3
// Set.cpp
// CS 301
//
// Purpose: The set class is created  in order to store data of a cache
//          set object. It also contains a vector of blocks, which will
//          store all the cache blocks in the set. 
//


#ifndef _SET_H_
#define _SET_H_

#include <vector>
#include "Block.h"

// This class represents a single set contained in a cache and all of its
// cooresponding data. The user can create a set simply by inputing the capacity
// of the cache, the block size, the set associativity of the cache, the index of
// the set in the cache.



class Set
{
  public:
    
    
    // Default Constructor creates the set object and assigns default values to
    // the global variables.
    //
    Set();


    // Initializes the variables, by using the given arguments, without populating 
    // all of the blocks contained in the set. 
    //
    void initializeVars(long long addr, int capacity, int block_size, int setAssoc, long long setIndex);


    // Initializes the variables, by using the given arguments, and populates the set
    // with empty blocks.
    //
    void initializeDefaultSet(long long addr, int capacity, int block_size, int setAssoc, long long setIndex);


    // Determines if the set is full, where full is defined as needing to have an
    // eviction or a hit in order to access the set. Then it returns the boolean
    // value indicating whether or not the set is full.
    //
    bool isSetFull();


    // Using the given address argument, this method checks if the access is a hit,
    // in the current set object. If it is the method will return the lru of the 
    // hit in the current set. If not it will return -1.
    //
    int checkForHit(long long addr);


    // Determines if the access is not a hit, if not we add a block to the current set 
    // or evict the least recently used block. The given address argument indicates the
    // values of the block to add.
    //
    void addBlock(long long addr);;

    
    // returns the vector containing all of the blocks in the set.
    //
    std::vector<Block> getMySet(){ return mySet;};

    
    // sets the value of the vector containing all of the blocks in the set.
    //
    void setMySet(std::vector<Block> vec){mySet = vec;};
    
    
    // Returns the gloabl variable setAsssoc's value.
    //
    int getSetAssoc(){return setAssoc;};

    
    // Returns the gloabl variable hitCounter's value.
    //
    int getHitCounter(){return hitCounter;};

    
    // Changes the value of the global variable hitCounter to be equal the argument
    // hitCntr.
    //
    void setHitCounter(int hitCntr){this->hitCounter = hitCntr;};

    
    // Increments the lru values when a there is an access to the set. The argument 
    // editedIndex indicates the index most recently used, target lru indicates the
    // lru of the most recently used index and full before access indicates if the
    // set was already full before the most recent access.
    //
    void incLRU(unsigned long long indexToEdit, int targetLRU, bool fulBeforeAccess);


    // Evicts a block from the provided index and replaces it with the block created
    // from the indicated address.
    //
    void evictBlock(long long addr, long long index);

    
    // Prints the set number and each block in the set.
    //
    void printSet();
  
  
  private:
     
    long long setIndex; //current set's index in the cache
    long long currTag;
    int hitCounter;
    int setAssoc;
    int currBCapacity;
    int currBlock_size;
    
    std::vector<Block> mySet;
};
#endif
