/* John Morales
 * Cache.cpp
 * Project 3
 * CS 301
 * Purpose: To create a configurable memory cache class that uses the Set and block
 * classes to store cache fields.
 */

#include "Cache.h"
#include <cmath>
#include <iomanip> 
#include <stdlib.h>

using namespace std;

/* 
* This method just creates an instance of the class.  However, there is
* no default configuration of the class, so the initialize() method must
* be called to actually create a cache that is properly configured.
*/
Cache::Cache()
{ 
  totalHitNum    = 0;    
  totalMissNum   = 0;  
  totalAccessNum = 0;
  hitRate        = 0.0;
}


/* Destructor for the class releases all dynamically allocated memory.
*/
Cache::~Cache(){}


/* This method configures the cache.  The capacity and block size need
* to be specified in bytes.  The set associativity is by default set
* to 1 (direct mapped) if no argument is specified.  All of the three
* arguments must be powers of two.  Additionally, the capacity divided
* by the (block_size * associativity) must not have a fractional 
* component.  Finally, the method prints out information about the
* configuration of the cache (see example output files).
*/
void Cache::initialize(int capacity, int block_size, int associativity)
{
  //Checks for format correctness, if format is incorrect exits program
  if(initializeArgFormatCorrect(capacity, block_size, associativity) != true)
  {
    cerr << endl;
    cerr << "One or more of your arguments is incorrect." <<  endl;
    cerr << endl;
    cerr << "All arguments must be powers of two and Capacity divided by the product of " << endl;
    cerr << "block_size and associativity must not have a fractional component." << endl;
    cerr << endl;
    exit(EXIT_FAILURE);
  }
    int numBlocks   = capacity / block_size;
    this->capac     = capacity;
    this->b_size    = block_size;
    this->assoc     = associativity;
    this->numSets   = numBlocks / associativity;
   
    this->printConfig();
}


/* Adds the address specified as an access to the current cache contents, 
* potentially evicting an existing entry in the cache.  The address
* is specified in bytes.
*/
void Cache::addAccess(long long addr)
{
  cout << dec;
  
  // if the cache doesn't have the right number of sets, populate all of them.
  if( static_cast<int>(myCache.size()) < numSets)
  {
    populateSets(addr);
  }
  initializeBlockAddr(addr);  
  
  Set s;
  s.setMySet(myCache[index].getMySet());
  s.setHitCounter(myCache[index].getHitCounter());
  s.initializeVars(addr, capac, b_size, assoc, index);
  s.addBlock(addr);
  
  this->myCache[index] = s;  
  totalAccessNum++;
}


/* prints the current contents of the cache.  the output is organized
* by cache sets and displays the index, tag, valid bit, and lru state.
*/
void Cache::printContents()
{
  for(unsigned int i = 0; i < myCache.size(); i++)
  {
    myCache[i].printSet();
  }
}


/* Prints the statistics about cache accesses including the number of
* accesses, hits, misses, and hit rate.
*/
void Cache::printStatistics()
{
  calcStatistics();

  cout << "ACCESSES " << totalAccessNum << endl;
  cout << "HITS "     << totalHitNum    << endl;
  cout << "MISSES "   << totalMissNum   << endl;
  cout << "HIT RATE " << hitRate        << endl;
}


/* Returns the number of accesses made to the cache. 
*/
long long Cache::getNumberAccesses()
{
  return totalAccessNum;
}


/* Returns the number of access that resulted in cache misses.
*/
long long Cache::getNumberMisses()
{
  long long accesses = getNumberAccesses();
  long long missNum  = accesses - totalHitNum;
  return missNum;
}


/* Finds the sum of the total hits and updates the global variable storing
 * this value.
*/
void Cache::calculateTotalHits()
{
  for(unsigned int i = 0; i < myCache.size(); i++)
  {
    totalHitNum += myCache[i].getHitCounter(); 
  }
}


/* By using the number of hits and accesses, this method calculates the hit
 * rate of the cache.
 */
void Cache::calculateHitRate()
{
  calculateTotalHits(); 
  long long accesses = getNumberAccesses();
  hitRate = (double)totalHitNum / (double)accesses;
}


/* Calls the calculateHitrate and getNumberMisses methods to prepare
 * the program to print the statisics.
 */
void Cache::calcStatistics()
  {
    calculateHitRate();   
    totalMissNum = getNumberMisses();
  }


/* Initializes the values of the blockAddr, index and tag for use in
 * other methods.
 */
void Cache::initializeBlockAddr(long long addr)
{
  this->blockAddr = addr / b_size;
  index = blockAddr % numSets;
  tag   = blockAddr / numSets;
} 

/* By using the arguments capacity, block_size, and associativity, this method
 * finds out if all the arguments are powers of two and if the capacity divided by
 * the product of block_size and associativity is a whole number. If both of these
 * conditions are met, then true is returned, otherwise false is returned.
 */
bool Cache::initializeArgFormatCorrect(int capacity, int block_size, int associativity)
{
    bool capacityCorrect = false;
    bool block_sizeCorrect = false;
    bool associativityCorrect = false;
    bool nonFractionComponent = false;

      // Checks that capacity is a power of 2
      if(capacity == 1 || capacity % 2 == 0)
      {
        capacityCorrect = true;
      }

      // Checks that block_size is a power of 2
      if(block_size == 1 || block_size % 2 == 0)
      {
        block_sizeCorrect = true;
      }

      // Checks that associativity is a power of 2
      if(associativity == 1 || associativity % 2 == 0)
      {
        associativityCorrect = true;
      }
     
      // Checks that capacity divided by the product of block_size and associativity is non-fractional.
      if(capacity % (block_size * associativity) == 0)      
      {
        nonFractionComponent = true;
      }
      
      // If all were true, then the format is correct.
      if(capacityCorrect == true && block_sizeCorrect == true && associativityCorrect == true && nonFractionComponent == true)
      {
        return true;
      }
    return false; 
}


/* Prints the configuration information
 */
void Cache::printConfig()
{
  cout << "Capacity "      << capac   << endl;
  cout << "Block size "    << b_size  << endl;
  cout << "Associativity " << assoc   << endl;
  cout << "Num Sets "      << numSets << endl;
}


/* Creates default sets in the cache. The default set will also contain n default
 * blocks corresponding to the associativity.
 */
void Cache::populateSets(long long addr)
{
  for(int i = 0; i < numSets; i++)
  {
    Set s;  
    s.initializeDefaultSet(addr, capac, b_size, assoc, i); 
    myCache.push_back(s);
  }
}
