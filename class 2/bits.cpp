// Show bit patterns for integers 0 through 63

#include <iostream>
using std::cout;
using std::endl;
using std::dec;
using std::hex;

#include <iomanip>
using std::setw;

// 1 : 0001
// 2 : 0010
// 3 : 0011
// 4 : 0100
// 5 : 0101
// 6 : 0110
// 7 : 0111
// 8 : 1000

int main()
{
   for (unsigned int i = 0; i < 0x40; ++i)
   {
      cout
         << setw(3) << hex << i << ":"
         << setw(3) << dec << i << ":  "
         << (i & 32 ? '1' : '-')
         << (i & 16 ? '1' : '-')
         << (i &  8 ? '1' : '-')
         << (i &  4 ? '1' : '-')
         << (i &  2 ? '1' : '-')
         << (i &  1 ? '1' : '-')
         << endl;
   }
   return 0;
}

