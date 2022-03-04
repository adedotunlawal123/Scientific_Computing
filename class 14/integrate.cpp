#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cmath>
using std::cos;
using std::pow;

#include "mtrand.hpp"
mtrand R;

double trapezoidIntegrator( double (&f)(double),
      double a, double b, unsigned int N )
{
   assert(N > 0);
   const double width = b-a;
   assert(width > 0.0);
   const double h = width/N;
   double sum = 0.5*( f(a) + f(b) );
   for (unsigned int i = 1; i < N; ++i)
   {
      const double x_i = a + i*h;
      sum += f(x_i);
   }
   return sum*h;
}

double f(double x)
{
   // f(x) = (x cos(x^3.5))^2
   const double c = cos(pow(x,3.5));
   return x*x*c*c;
}

int main()
{
   cout.precision(14);
   // int_0^2 x^2 cos^2(x^3.5) dx
   cout << "Trapezoid rule:" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,10) << " (10 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,50) << " (50 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,250) << " (250 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,1000) << " (1000 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,5000) << " (5000 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,25000) << " (25000 slices)" << endl;
   cout << "I = " << trapezoidIntegrator(f,0.0,2.0,10000) << " (10000 slices)" << endl;

   cout << "Monte Carlo:" << endl;
   double sum = 0.0;
   int n = 0;
   for (; n < 1000; ++n)
   {
      // int_0^2 dx f(x) = int_0^2 dx x^2 cos^2(x^3.5)
      // Importance sampling with respect to the x^2 term
      // P(x) = int_0^x p(y) dy
      //      = int_0^x y^2 dy / int_0^2 y^2 dy 
      //      = [(1/3)x^3] / [(1/3)2^3] := R
      //   x <- (8R)^(1/3) in [0,2) but nonuniform
      const double x = pow(8.0*R(),1.0/3.0);
      const double c = cos(pow(x,3.5));
      sum += c*c;
   }
   cout << "I = " << (8.0/3.0)*sum/1000 << " (1000 samples)" << endl;

   for (; n < 10000; ++n)
   {
      const double x = pow(8.0*R(),1.0/3.0);
      const double c = cos(pow(x,3.5));
      sum += c*c;
   }
   cout << "I = " << (8.0/3.0)*sum/10000 << " (10000 samples)" << endl;

   for (; n < 100000; ++n)
   {
      const double x = pow(8.0*R(),1.0/3.0);
      const double c = cos(pow(x,3.5));
      sum += c*c;
   }
   cout << "I = " << (8.0/3.0)*sum/100000 << " (100000 samples)" << endl;
   return 0;
}
