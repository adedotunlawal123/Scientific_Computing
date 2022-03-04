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
const double r2 = R + 8500.0; // km (apogee)
const double r1 = R + 1000.0; // km (perogee)
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
   double t_[3];
   double r_[3];
   double theta_[3];
   size_t i = 0;
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
      t_[i] = t;
      r_[i] = r;
      theta_[i] = theta;
      if (n > 3)
      {
         const size_t i0 = (i+1)%3;
         const size_t i1 = (i+2)%3;
         const size_t i2 = i;
         const double rdot = (r_[i2] - r_[i0])/(2.0*dt);
         const double thetadotA = 
            (theta_[i2] - theta_[i0] + 2.0*M_PI)/(2.0*dt);
         const double thetadotB = 
            (theta_[i2] - theta_[i0])/(2.0*dt);
         const double thetadotC = 
            (theta_[i2] - theta_[i0] - 2.0*M_PI)/(2.0*dt);
         const double tmp = fabs(thetadotA) < fabs(thetadotB) ?
            thetadotA : thetadotB;
         const double thetadot = fabs(thetadotC) < fabs(tmp) ?
            thetadotC : tmp;
         cout << t_[i1] << "\t" << r_[i1] << "\t" << theta_[i1]
            << "\t" << rdot << "\t" << thetadot << endl;
      }
      i = (i+1)%3;
      // t0    t_: [ t0, -, - ]
      //             ^
      //             i=0
      // t1    t_: [ t0, t1, - ]
      //                 ^
      //                 i=1
      // t2    t_: [ t0, t1, t2 ]
      //                     ^
      //                     i=2
      // t3    t_: [ t3, t1, t2 ]
      //             ^
      //             i=0
   }
   return 0;
}
