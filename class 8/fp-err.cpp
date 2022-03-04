#include <cassert>

#include <cstdlib>
using std::atoi;

#include <cmath>
using std::sqrt;
using std::tan;
using std::isinf;

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include "bitconvert.h"

int main(int argc, char *argv[])
{
   convert64_t D;
   assert(argc==2); // one argument
   int c = atoi(argv[1]);
   switch (c)
   {
      case 1:
         cout << "Positive overflow:" << endl;
         D.F64 = 1.0;
         while (!isinf(D.F64))
         {
            D.F64 *= 8.0;
            cout << endl << "---> " << D.F64 << " <---" << endl;
            show_bits(cout,D);
         }
         break;
      case 2:
         cout << "Negative overflow:" << endl;
         D.F64 = -1.0;
         while (!isinf(D.F64))
         {
            D.F64 *= 8.0;
            cout << endl << "---> " << D.F64 << " <---" << endl;
            show_bits(cout,D);
         }
         break;
      case 3:
         cout << "Near misses:" << endl;
         cout << "-1 + 0.1 + ... + 0.1 (ten times) = "
            << -1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 << endl;
         cout << "tan(-pi) = " << tan(-M_PI) << endl;
         cout << "tan(pi/2) = " << tan(0.5*M_PI) << endl;
         break;
      case 4:
         cout << "Error state algebra:" << endl;
         const double inf = 1.0/0.0;
         D.F64 = inf;
         cout << "---> " << D.F64 << " <---" << endl;
         show_bits(cout,D);
         const double neg_inf = -1.0/0.0;
         D.F64 = neg_inf;
         cout << "---> " << D.F64 << " <---" << endl;
         show_bits(cout,D);
         const double nan = 0.0/0.0;
         D.F64 = nan;
         cout << "---> " << D.F64 << " <---" << endl;
         show_bits(cout,D);
         const double zero = 0.0;
         D.F64 = zero;
         show_bits(cout,D);
         cout << "---> " << D.F64 << " <---" << endl;
         const double one = 1.0;
         D.F64 = one;
         cout << "---> " << D.F64 << " <---" << endl;
         show_bits(cout,D);
         cout << one << " * " << inf << " = " << one*inf << endl;
         cout << neg_inf << " * " << one << " = " << neg_inf*one << endl;
         cout << zero << " * " << inf << " = " << zero*inf << endl;
         cout << neg_inf << " * " << zero << " = " << neg_inf*zero << endl;
         cout << one << " / " << zero << " = " << one/zero << endl;
         cout << zero << " / " << zero << " = " << zero/zero << endl;
         cout << "sqrt(-1) = " << sqrt(-1) << endl;
         cout << nan << " + " << inf << " = " << nan + inf << endl;
         cout << neg_inf << " + " << inf << " = " << neg_inf + inf << endl;
         break;
   }
   return 0;
}
