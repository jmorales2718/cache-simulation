# Cache - C++

## Overview
This program allows for the creation of configurable memory caches. The cache capacity, block size, and set-associativity of the cache are all configurable by the user. The user can also add accesses to the cache and change what is stored in the cache this way. If the cache is full and the access is not a hit, there will be an eviction of the least recently used block. Finally, the user can print the contents of the current cache and print information about it like the current hit rate  or other hit/miss statistics.



## Classes:

**Cache:** This class uses the Block and Set Classes to simulate different cache configurations for different access patterns. 

The cache is initialized by the initialize method. Initialize takes the configurable variables as arguments then verifies that the format of the configurable variables are correct. If so these variables are stored globally.

Accesses are added to the cache, by using the addAccess method. addAccess takes the address of an access as an argument. By using this address, it then populates the sets, initializes the block address and stores the block address, index and tag globally. It then creates a Set object initializes it and adds it to the vector of Sets contained in Cache. Lastly it increments a global variable to keep track of the number of accesses to the cache.

The printStatistics Method is another important method in the Cache class. It Prints values for the number of: Accesses, hits, misses, and the hit rate.

Lastly, Cache contains a vector, myCache, which contains all of the cache's sets.



**Set:** This class holds information about a single cache set. It stores values for different fields such as: setIndex, currTag, hitCounter, setAssoc, currBCapacity and currBlock_size. setIndex is used to store the index of the current set in the cache. currTag contains the tag of the current access to the set. hitCounter is used to store the number of hits for the current set.

Set contains two initialize methods, which are both used by Cache in the appropriate situation. initializeVars only initializes the variables given as arguments and by using these initializes currTag. initializeDefaultSet calls initializeVars, and also creates populates the set with the correct number of Blocks.

The addBlock method takes in the address of an access as an argument. It then determines if the current address is a hit, if the set is full, and if an object needs to be evicted. Then it handles all possible situations and adds the access address to the set, incrementing hitCounter if the access was a hit.

incLRU is another important method in the set class. It takes in 3 arguments: editedIndex, targetLRU and fullBeforeAccess. editedIndex contains the index of the block being accessed. targetLRU contains the previous lru of the block being accessed. fullBeforeAccess is a boolean value which is true when the block was already full before the current access. These three values allow incLRU to increment the lrus in a set appropriately.

Lastly, Set contains a vector, mySet, which contains all of the cache's sets.



**Block:** This class holds information about a single cache block. It stores values for different fields such as: validBit, index, tag, offset, lru, assoc, capac, bSize, numBlocks and blockAddr. Block also contains methods to access and edit the values of the aforementioned objects.

The most important methods in Block are initializeBlock and parseAddress.

initializeBlock takes the current access’ address, setAssociativity, capacity, and block_size as arguments and uses them to initialize their cooresponding global variables so they can be used by parseAddress. It also initializes the validBit to 1.

parseAddress takes the current access’ address as a parameter and uses it and the global varibables initialized by initializeBlock to calculate the index and tag of the block. It also initializes the lru to 0.
