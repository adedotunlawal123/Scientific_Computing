#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::atoi;
using std::exit;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::setw;

#include "mtrand.hpp"
mtrand R;

void bad(void)
{
   cerr << "Usage: pairs #points" << endl;
   exit(1);
}

int main(int argc, char* argv[])
{
   if (argc != 2) bad();
   size_t N;
   {
      const int N_ = atoi(argv[1]);
      if (N_ < 1) bad();
      N = N_;
   }
   
   for (size_t n = 0; n < N; ++n)
      cout << setw(20) << R() << setw(20) << R() << endl;

   return 0;
}
