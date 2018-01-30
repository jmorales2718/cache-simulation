#include "Set.h"

int main()
{
  Set s;
  int capacity = 512; 
  int block_size = 64;
  int setAssociativity = 4;
  long long addr = 260;
  int blockAddr = addr / block_size; 
  int numBlocks = capacity / block_size;
  int numSets = numBlocks / setAssociativity;
  long long index = blockAddr % numSets;
  s.initializeSet(capacity, block_size, setAssociativity, index);
  s.addBlock(addr);
  s.printSet();

  return 0;
}
