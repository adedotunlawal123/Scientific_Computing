#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <iomanip>
using std::setprecision;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <vector>
using std::vector;

#include <cmath>
using std::cosh;
using std::sinh;
using std::fabs;
using std::sqrt;

#include "mtrand.hpp"
mtrand R;

const int bootstrap_iterations = 100;
const int bootstrap_samples = 500;
const double eps = 1.0E-6;

void steepest_descent(double &x0, double &y0, double &a,
      const double x_data[bootstrap_samples],
      const double y_data[bootstrap_samples])
{
   x0 = 0.0;
   y0 = -0.5;
   a = 1.0;

   unsigned int count = 0;

   double step_x0 = 0.0;
   double step_y0 = 0.0;
   double step_a = 0.0;

   do
   {
      double grad_x0 = 0.0;
      double grad_y0 = 0.0;
      double grad_a = 0.0;

      for (int k = 0; k < bootstrap_samples; ++k)
      {
         const double dx = (x_data[k]-x0)/a;
         const double C = a*(cosh(dx)-1.0)+y0-y_data[k];
         grad_x0 -= C*sinh(dx);
         grad_y0 += C;
         grad_a += C*(cosh(dx) - 1.0 - dx*sinh(dx));
      }
      step_x0 = 0.01*grad_x0/bootstrap_samples;
      step_y0 = 0.01*grad_y0/bootstrap_samples;
      step_a = 0.01*grad_a/bootstrap_samples;

      x0 -= step_x0;
      y0 -= step_y0;
      a -= step_a;
   } while ( ++count < 100 or fabs(step_x0) > eps
         or fabs(step_y0) > eps or fabs(step_a) > eps);
}

void statistics(double &m, double &v, 
      const double data[bootstrap_iterations])
{
   m = v = 0.0;
   for (int n = 0; n < bootstrap_iterations; ++n)
      m += data[n];
   m /= bootstrap_iterations;
   for (int n = 0; n < bootstrap_iterations; ++n)
   {
      const double dm = data[n]-m;
      v += dm*dm;
   }
   v /= (bootstrap_iterations-1);
}

int main(int argc, char* argv[])
{
   if (argc != 1)
   {
      cerr << "Usage: string_fit" << endl;
      cerr << "This program takes no arguments" << endl;
      exit(1);
   }
   ifstream fin("string.dat");
   if (!fin.is_open())
   {
      cerr << "This program requires an input file names 'string.dat'" << endl;
      exit(1);
   }

   vector<double> x;
   vector<double> y;

   double xval, yval;
   fin >> xval >> yval;
   while(fin)
   {
      x.push_back(xval);
      y.push_back(yval);
      fin >> xval >> yval;
   }
   fin.close();

   assert(x.size() == y.size());

   if (x.size() == 0)
   {
      cerr << "No data in file `string.dat'" << endl;
      exit(1);
   }

   double x0[bootstrap_iterations];
   double y0[bootstrap_iterations];
   double a[bootstrap_iterations];

   double xb[bootstrap_samples];
   double yb[bootstrap_samples];

   cout << "Processing ..." << endl;

   for (int n = 0; n < bootstrap_iterations; ++n)
   {
      cout << "iteration " << n+1 << endl;
      for (int k = 0; k < bootstrap_samples; ++k)
      {
         const int i = R.randInt(x.size());
         xb[k] = x[i];
         yb[k] = y[i];
      }
      steepest_descent(x0[n],y0[n],a[n],xb,yb);
   }

   ofstream fout("auto-fit.gp");
   fout.precision(10);
   double mean = 0.0, var = 0.0;
   statistics(mean,var,x0);
   cout << "  x0 = " << setprecision(10) << mean << " +/- " << setprecision(2) << sqrt(var) << endl;
   fout << "x0 = " << setprecision(10) << mean << endl;
   statistics(mean,var,y0);
   cout << "  y0 = " << setprecision(10) << mean << " +/- " << setprecision(2) << sqrt(var) << endl;
   fout << "y0 = " << setprecision(10) << mean << endl;
   statistics(mean,var,a);
   cout << "   a = " << setprecision(10) << mean << " +/- " << setprecision(2) << sqrt(var) << endl;
   fout << "a = " << setprecision(10) << mean << endl;
   
   fout << endl << "c(x) = a*(cosh((x-x0)/a)-1)+y0" << endl;
   fout << endl << "plot 'string.dat', c(x)" << endl;
   fout.close();

   return 0;
}
