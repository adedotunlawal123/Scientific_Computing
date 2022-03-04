#include <cstdlib>
using std::atoi;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cmath>
using std::exp;

// exp(x) = 1 + x + x^2/2! + ...
double exp1(double x, unsigned long int cutoff)
{
   unsigned long int n = 1;
   double sum = 1.0;
   double x_pow_n = x;
   unsigned long int n_fact = n;
   do
   {
      sum += x_pow_n/n_fact;
      x_pow_n *= x;
      n_fact *= ++n;
   } while (n <= cutoff);
   return sum;
}

double exp2(double x, unsigned long int cutoff)
{
   unsigned long int n = 1;
   double sum = 1.0;
   double term = x;
   while (n <= cutoff)
   {
      sum += term;
      n += 1;
      term *= x/n;
   }
   return sum;
}

// exp(x) = 1 + x*(1 + (x/2)*(1 + (x/3)*(1 + ...
double exp3(double x, unsigned long int n)
{
   double sum = x/n;
   while (n != 1)
      ( sum += 1 ) *= (x/--n);
   // this line means:
   // sum = sum + 1
   // n = n - 1
   // sum = sum * (x/n)
   return 1+sum;
}

int main(int argc, char *argv[])
{
   assert(argc==2); // 0:exp 1:cutoff
   const int trunc = atoi(argv[1]); // dangerous! no error handling
   const double xlist[] = 
   { 0.0, 0.243, 0.567, 0.752, 1.0, 2.62, 5.99, 12.8 };
   cout.precision(12);
   for (auto x : xlist)
      cout 
         << setw(5) << x
         << setw(19) << exp1(x,trunc)
         << setw(17) << exp2(x,trunc)
         << setw(17) << exp3(x,trunc)
         << setw(17) << exp(x) << endl;
   return 0;
}

