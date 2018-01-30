#include "Cache.h"
#include <iostream>

int main()
{
  Cache c;
  int capacity      = 256;
  int block_size    = 64;
  int associativity = 4;
  long long address    = 260;
  c.initialize(capacity, block_size);
  c.addAccess(address);
  c.printContents();



  return 0;
}
