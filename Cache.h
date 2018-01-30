/* John Morales
 * Cache.h
 * Project 3
 * CS 301
 * Purpose: To create a configurable memory cache class that uses the Set and block
 * classes to store cache fields.
 */

#ifndef _CACHE_H_
#define _CACHE_H_

#include "Set.h"
#include <iomanip>
#include <iostream>

/*
 * This class represents a configurable memory cache.  To configure the
 * cache, the user must specify the cache capacity in bytes, the block
 * size in bytes, and the set-associativity.  The default set-associativity
 * is 1, meaning direct-mapped.
 *
 * The user can add memory accesses to the cache by specifying the byte
 * address for the memory location.  Each access is assumed to be 4 
 * bytes wide.  
 *
 * The user has the ability to print out the current contents of the cache
 * as well as query the cache about access and hit/miss statistics.
 */
class Cache {
 public:
  /* 
   * This method just creates an instance of the class.  However, there is
   * no default configuration of the class, so the initialize() method must
   * be called to actually create a cache that is properly configured.
   */
  Cache();

  /* Destructor for the class releases all dynamically allocated memory.
   */
  ~Cache();

  /* This method configures the cache.  The capacity and block size need
   * to be specified in bytes.  The set associativity is by default set
   * to 1 (direct mapped) if no argument is specified.  All of the three
   * arguments must be powers of two.  Additionally, the capacity divided
   * by the (block_size * associativity) must not have a fractional 
   * component.  Finally, the method prints out information about the
   * configuration of the cache (see example output files).
   */
  void initialize(int capacity, int block_size, int associativity = 1);  

  /* Adds the address specified as an access to the current cache contents, 
   * potentially evicting an existing entry in the cache.  The address
   * is specified in bytes.
   */
  void addAccess(long long addr);
                               
  /* prints the current contents of the cache.  the output is organized
   * by cache sets and displays the index, tag, valid bit, and lru state.
   */
  void printContents();

  /* Prints the statistics about cache accesses including the number of
   * accesses, hits, misses, and hit rate.
   */
  void printStatistics();

  /* Returns the number of accesses made to the cache. 
   */
  long long getNumberAccesses();

  /* Returns the number of access that resulted in cache misses.
   */
  long long getNumberMisses();

  
 private:
  
  /* Finds the sum of the total hits and updates the global variable storing
   * this value.
  */
  void calculateTotalHits();

  /* By using the numbee of hits and accesses, this method calculates the hit
   * rate of the cache.
   */
  void calculateHitRate();

  /* Calls the calculateHitrate and getNumberMisses methods to prepare
   * the program to print the statisics.
   */
  void calcStatistics();

  /* Initializes the values of the blockAddr, index and tag for use in
   * other methods.
   */
  void initializeBlockAddr(long long blockAddr);
  
  /* By using the arguments capacity, block_size, and associativity, this method
   * finds out if all the arguments are powers of two and if the capacity divided by
   * the product of block_size and associativity is a whole number. If both of these
   * conditions are met, then true is returned, otherwise false is returned.
   */
  bool initializeArgFormatCorrect(int capacity, int block_size, int associativity);
  
  /* Prints the configuration information
   */
  void printConfig();
  
  /* Creates default sets in the cache. The default set will also contain n default
   * blocks corresponding to the associativity.
   */
  void populateSets(long long addr);

  long long index;
  long long tag;
  int       blockAddr;
  int       numSets;
  int       capac;
  int       b_size;
  int       assoc;
  long long totalHitNum;
  long long totalMissNum;
  long long totalAccessNum;
  double    hitRate;

  std::vector<Set> myCache;

};

#endif
