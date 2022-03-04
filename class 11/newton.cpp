#include <iostream>
using std::cout;
using std::endl;

#include <cmath>
using std::sin;
using std::cos;
using std::exp;
using std::fabs;

// f(x) is smooth and has a derivative
// f'(x) is know or easy to compute
double newton_raphson(double (&f)(double),
      double (&fp)(double),
      double x0, double tolerance)
{
   // guess x0
   // true root is x*
   // f(x0) = f(x*-dx) = f(x*) - f'(x*)dx + O(dx)^2
   //                    =   0   - f'(x*)dx + truncate
   // solve for dx = -f(x0)/f'(x0)
   // x1 = x0 + dx = x0 - f(x0)/f'(x0) should be better
   // x_{n+1} := x_n - f(x_n)/f'(x_n)
   //                  ^^^^^^^^^^^^^^
   //                  dx
   // (x_0, x_1, x_2, ...)
   //  ^^^
   //  guess
   while (true)
   {
      const double dx = f(x0)/fp(x0);
      if (fabs(dx) < tolerance)
         return x0;
      x0 -= dx;
   }
}

double secant_method(double (&f)(double),
      double x, double xx, double tolerance)
{
   // x_{n+1} := x_n - f(x_n)(x_n-x_{n-1})/(f(x_n) - f_{x_{n-1}})
   double dx;
   do
   {
      dx = -(xx-x)*f(xx)/(f(xx)-f(x));
      x = xx;
      xx += dx;
   } while (fabs(dx) > tolerance);
   return xx;
}

double g(double x) { return exp(-x) - sin(x); }
double gprime(double x) { return -exp(-x) - cos(x); }

int main()
{
   const double x1 = newton_raphson(g,gprime,0.1,1.2e-7);
   const double x2 = secant_method(g,0.0,0.2,1.2e-7);

   cout.precision(12);
   cout
      << "Root of g(x) = exp(-x) - sin(x) fount at" << endl
      << " x = " << x1 << endl
      << "(x = " << x2 << ")" << endl;

   return 0;
}
