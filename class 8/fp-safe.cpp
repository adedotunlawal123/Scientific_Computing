#include <cassert>

#include <cmath>
using std::fabs;

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <vector>
using std::vector;

#include <utility>
using std::pair;

#include <tuple>
using std::tuple;

double norm_unsafe(double x, double y)
{
   return sqrt(x*x + y*y);
}

double norm(double x, double y)
{
   const double xx = fabs(x);
   const double yy = fabs(y);
   if (xx > yy)
   {
      const double r = yy/xx;
      return xx*sqrt(1.0+r*r);
   }
   else
   {
      const double r = xx/yy;
      return yy*sqrt(1.0+r*r);
   }
}

void quadratic_roots_unsafe(double a, double b, double c,
                            double &x1, double &x2)
{
   const double X = sqrt(b*b-4*a*c);
   x1 = (-b + X)/(2*a);
   x2 = (-b - X)/(2*a);
}

void quadratic_roots(double a, double b, double c,
                            double &x1, double &x2)
{
   const double X2 = b*b-4*a*c;
   assert(X2 >= 0.0);
   const double X = sqrt(X2);
   const double Y = ( b > 0.0 ? -b-X : -b+X );
   x1 = 2*c/Y;
   x2 = Y/(2*a);
}

int main()
{
   cout << "Norm of a 2-vector:" << endl;
   vector<pair<double,double>> coords { 
      { 1.0, 2.0}, 
      {2.0, 3.0},
      {3.0, 4.0},
      {1.5e-2, 4.75e+3},
      {-1386, 29.12}
   };

   for (auto& [x,y] : coords)
   {
      cout
         << std::defaultfloat
         << "|(" << x << "," << y << ")| =" << endl;
      cout.precision(20);
      cout.setf(std::ios::scientific);
      cout
         << "     " << norm(x,y) << endl
         << " cf. " << norm_unsafe(x,y) << endl << endl;
   }

   cout << endl << "Roots of a quadratic polynomial:" << endl;
   vector<tuple<double,double,double>> quads {
      { 2, -24, 70},
      { 0.25, 258.2, 5.3 },
      { 0.1, 1.77e4, 2.3e-3 }
   };
   for (auto& [a,b,c] : quads)
   {
      double x1, x2;
      cout << std::defaultfloat
         << a << "x^2 + " << b << "x" << " + " << c << " = 0" << endl;
      quadratic_roots(a,b,c,x1,x2);
      cout.precision(20);
      cout.setf(std::ios::scientific);
      cout << "      x1 = " << x1 << "; x2 = " << x2 << endl;
      quadratic_roots_unsafe(a,b,c,x1,x2);
      cout <<" cf.   x1 = " << x1 << "; x2 = " << x2 << endl;
   }

   return 0;
}
