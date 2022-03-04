#include <cmath>
using std::cos;
using std::exp;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

const double nu = 2.5; //Hz
const double omega = 2*M_PI*nu; //radians/s;
const double t0 = 1.25; //s

const double dt = 0.001; //s
const double A = 10; //cm
const double B = 2; //cm

int main()
{
   for (int i = 0; i < 5000; ++i)
   {
      const double t = i*dt;
      const double x = (A*cos(omega*t) + B*cos(2*omega*t))*exp(-t/t0);
      cout <<setw(20) << t << setw(20) << x << endl;
   }
   return 0;
}
