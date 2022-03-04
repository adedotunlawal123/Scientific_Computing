#include <cassert>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cmath>
using std::fabs;
using std::sin;
using std::cos;
using std::tan;
using std::atan2;

const double R = 6378.1; // km (radius of the earth)
const double r2 = R + 3000.0; // km (apogee)
const double r1 = R + 500.0; // km (perogee)
const double a = 0.5*(r1+r2); // semi-major axis
const double e = (r2-r1)/(2.0*a); // eccentricity
const double mu = 398600.4418; // km^3/s^2
const double P = 2*M_PI*sqrt(a*a*a/mu)/3600.; // period in hrs
const double dt = P/5075;

double eccentric_anomaly(double M, double E)
{
   //                           ^         ^
   //                mean anomaly    inital guess for eccentric anomaly
   int count = 0;
   while (true)
   {
      const double f = E-M-e*sin(E);
      if (++count > 20 and fabs(f) < 1E-12) return E;
      const double fp = 1-e*cos(E);
      // E_{n+1} = E_n - f(E_n)/f'(E_n)
      E -= f/fp;
   }
}

int main()
{
   cerr << "Eccentricity e = " << e << endl;
   cerr << "Period P = " << P << endl;
   double lastE = 0.0;
   for (int n = 1; n < 50000; ++n)
   {
      const double t = n*dt;
      const double M = 2.0*M_PI*t/P;
      const double E = eccentric_anomaly(M,lastE);
      lastE = E;
      const double theta = 2.0*atan2(
            sqrt(1+e)*tan(0.5*E),
            sqrt(1-e));
      const double r = a*(1-e*cos(E));
      cout << t << "\t" << r << "\t" << theta << endl;
   }
   return 0;
}
