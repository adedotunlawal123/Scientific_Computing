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
   cerr << "Usage: corner #points" << endl;
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
   
   unsigned long int corner[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

   for (size_t n = 0; n < N; ++n)
   {
      const double x = 2.0*R()-1.0; // [0,1) -> [-1,1)
      const double y = 2.0*R()-1.0;
      const double z = 2.0*R()-1.0;
      // generate (x,y,z) that lives in the 2x2x2 cube
      size_t k = 0;
      if (x > 0.0) k += 1;
      if (y > 0.0) k += 2;
      if (z > 0.0) k += 4;
      ++corner[k]; // histogram according to which corner its closet to
   }

   for (size_t i = 0; i < 8; ++i)
      cout << i+1 << " " << double(corner[i])/N << endl; // 3/8 == 0 != 3.75
   
   return 0;
}
