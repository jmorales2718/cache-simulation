#include "Block.h"
#include <iostream>
using namespace std;

int main()
{

  Block b;
  
  b.initializeBlock(260, 4, 512, 64);
  cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
  cout << "      Test Initialize Block     " << endl;
  cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
  
  cout << "index: "  << b.getIndex()  << "    ";  
  cout << "tag: "    << b.getTag()    << "    ";
  cout << "lru: "    << b.getLRU()    << "    ";
  cout << "offset: " << b.getOffset() << endl;
}
