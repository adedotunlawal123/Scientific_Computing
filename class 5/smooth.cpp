#include <cassert>

#include <cstdlib>
using std::atoi;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::setw;

#include <fstream>
using std::ifstream;

unsigned long int fact(unsigned long int n)
{
   if (n == 0) return 1ul;
   else return n*fact(n-1);
}

unsigned int binomial(unsigned int n, unsigned int k)
{
   // look up table for (n choose k) = n!/k!/(n-k)!
   static const unsigned int Pascal[] = {
                 1,              //    0        n=0:       0
                1,1,             //   1,2       n=1:      1,... +k  
               1,2,1,            //  3,4,5      n=2:     3,...
              1,3,3,1,           // 6,7,8,9     n=3:    6,...
             1,4,6,4,1,          // 10,...      n=4:   10,...
           1,5,10,10,5,1,
          1,6,15,20,15,6,1,
         1,7,21,35,35,21,7,1 };
   assert(n >= k);
   if (n < 8) return Pascal[n*(n+1)/2+k];
   else return fact(n)/fact(k)/fact(n-k);
}

void exit_with_error(const char* str)
{
   cerr << str << endl;
   exit(1);
}

int main(int argc, char *argv[])
{
   if (argc != 3) exit_with_error("Usage: smooth smoothing-level filename");
   ifstream fin(argv[2]);
   if (!fin.is_open()) exit_with_error("Couldn't open the file");
   const int sl = atoi(argv[1]);
   if (sl < 2 or sl > 13) exit_with_error("Choose a smoothing level in the range of 2 to 12");
   const unsigned int n = (unsigned int)sl;
   const unsigned int n1 = n-1;
   const unsigned int two_pow_n1 = (1 << n1);
   double tvals[7];
   double xvals[7];
   unsigned int idx = 0;
   bool loaded = false;
   while (true)
   {
      double t, x;
      fin >> t >> x;
      if (!fin) break;
      tvals[idx] = t;
      xvals[idx++] = x;
      if (idx == n)
      {
         loaded = true;
         idx = 0;
      }
      if (loaded)
      {
         // +---+---+---+---+---+---+
         // | d | e | f | a | b | c |   ==>  (a+5b+10c+10d+5e+f)/32
         // +---+---+---+---+---+---+
         //               ^
         //              idx
         double twgt = 0.0;
         double xwgt = 0.0;
         for (unsigned int j = 0; j < n; ++j)
         {
            const unsigned int k = (n+j-idx)%n;
            const double choose = binomial(n1,k);
            twgt += choose*tvals[j];
            xwgt += choose*xvals[j];
         }
         cout
            << setw(20) << twgt/two_pow_n1
            << setw(20) << xwgt/two_pow_n1 << endl;
      }
   }
   return 0;
}
