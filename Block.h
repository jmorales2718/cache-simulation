//John Morales
//Program 3
//Block.h
//CS 301
//
//Purpose: To create the framework for storing information for a single block in a 
//         cache and allow for printing of that block's information.


#ifndef _BLOCK_H_
#define _BLOCK_H_

// This class represents a single block contained in a cache and all of its
// cooresponding data. The user can create a block simply by inputing an
// address, an associativity value, a cache capacity, and a block size.
//
// The user also has the ability to print the current contents of the block and 
// retrieve the valid bit, index, tag, and lru. As well as change the lru value.
//
class Block
{
  public:
    //
    // Default constructor for a Block object, creates a default block with initialized
    // cache fields.
    //
    Block();

    
    // Initializes the block, using information about the address it will contain, the 
    // set associativity of the current cache, and the capacity of the current cache and
    // the block size in the current cache. This information is stored globally to be
    // used by the get methods, as well as parse address.
    //
    void initializeBlock(long long addr, int setAssociativity, int capacity, int block_size);

    
    // Parses given address to calculate information such as: index, tag, and offset.
    // This information is then stored in global variables to be used by get methods.
    //
    void parseAddress(long long addr);
    
    
    // Prints basic information about the block such as: tag, valid bit, and lru.
    //
    void printBlock();
    
    
    // Returns the valid bit of the current block object.
    //
    int getValidBit(){return validBit;};

    // Returns the index value of the current block object.
    //
    long long getIndex(){ return index;};

    // Returns the tag value of the current block object.
    //
    long long getTag(){return tag;};

    // Return the lru value of the current block object.
    //
    int getLRU(){return lru;};

    // Edits the value of the global lru variable.
    //
    void setLRU(int lRU){lru = lRU;};

  private:
    int validBit;
    long long index;
    long long tag;
    long long offset;
    int numBlocks;
    int bSize; // Will store block size;
    int capac;
    int assoc;
    int lru; 
    long long blockAddr;
};

#endif
