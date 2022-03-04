#include <cstdlib>
using std::atol;
using std::exit;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include "mtrand.hpp"
mtrand R;

void bad(void)
{
   cerr << "Usage: pi [-n] #points" << endl;
   cerr << "  -n   report numerical results only" << endl;
   exit(1);
}

int main(int argc, char* argv[])
{
   if ( !(argc == 2 or (argc == 3 and string(argv[1]) == "-n") )) bad();
   unsigned long int N;
   {
      const long int N_ = atol(argv[argc-1]);
      if (N_ < 1) bad();
      N = N_;
   }

   // compute pi by dart throwing
   unsigned long int enclosed = 0;
   for (unsigned long int n = 0; n < N; ++n)
   {
      const double x = 2.0*R() - 1.0;
      const double y = 2.0*R() - 1.0;
      if (x*x + y*y < 1.0) ++enclosed;
   }
   if (argc == 2)
      cout << N << "-point dartboard approximation to pi: ";
   cout << 4.0*double(enclosed)/N << endl;
   return 0;
}

