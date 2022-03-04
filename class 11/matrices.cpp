#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "matdef.hpp"

double A[4*4] = { 1, 2, 3, 4,
                  4, 1, 6, 2,
                  7, 8, 1, 3,
                  1, 5, 8, 2 };

double I[4*4] = { 1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1 };

double u[4] = { -1, 2, 5, -4 };
double v[4] = { -2, 3, -1, 8 };

int main()
{
   for (size_t i = 0; i < 4; ++i)
   {
      for (size_t j = 0; j < 4; ++j)
      {
         cout << setw(5) << A[idx4(i,j)];
      }
      cout << endl;
   }

   double B[4*4] = {0};
   for (size_t n = 0; n < 16; ++n)
      B[n] = A[n] + 3*I[n];

   cout << endl;

   for (size_t i = 0; i < 4; ++i)
   {
      for (size_t j = 0; j < 4; ++j)
      {
         cout << setw(5) << B[idx4(i,j)];
      }
      cout << endl;
   }
   return 0;
}

