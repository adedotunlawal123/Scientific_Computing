#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>
using std::exp;
using std::sin;

//        \
// [        x       +               ]
// ^        ^ \    ^               ^
// a        root    c=(a+b)/2       b

double bisection_method_v1(double (&f)(double),
      double a, double b, double tolerance)
{
   assert(f(a)*f(b) < 0.0);
   assert(a < b);
   const double width = b-a;
   const double c = 0.5*(a+b);
   if (width < tolerance) return c;
   if (f(a)*f(c) < 0.0) return bisection_method_v1(f,a,c,tolerance);
   return bisection_method_v1(f,c,b,tolerance);
}

double bisection_method_v2(double (&f)(double),
       double a, double b, double tolerance)
{
   assert(f(a)*f(b) < 0.0);
   assert(a < b);
   double c = 0.5*(a+b);
   do
   {
      if (f(a)*f(c) < 0.0) // if root in [a,c]
         b = c;
      else
      {
         assert(f(c)*f(b) < 0.0);
         a = c;
      }
      assert(a < b);
      c = 0.5*(a+b);
   } while (b - a > tolerance);
   return c;
}

double g(double x) { return exp(-x) - sin(x); }

int main()
{
   const double x1 = bisection_method_v1(g,0.0,1.5,1.2e-7);
   const double x2 = bisection_method_v2(g,0.0,1.5,1.2e-7);

   cout.precision(12);
   cout
      << "Root of g(x) = exp(-x) - sin(x) found at" << endl
      << " x = " << x1 << endl
      << "(x = " << x2 << ")" << endl;
   return 0;
}
