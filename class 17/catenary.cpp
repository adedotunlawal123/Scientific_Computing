#include <cstdlib>
using std::exit;

#include <iostream>
using std::endl;

#include <iomanip>
using std::setw;

#include <fstream>
using std::ofstream;

#include <cmath>
using std::cosh;

ofstream fout;

bool at_least_one_measurement;

void initialize(void)
{
   fout.open("string.dat");
}

void start_new_data_set(void)
{
   if (at_least_one_measurement)
   {
      fout << endl << endl;
      at_least_one_measurement = false;
   }
}

void add_measurement(float x, float y)
{
   if (!at_least_one_measurement)
      at_least_one_measurement = true;
   fout << setw(25) << x << setw(25) << y << endl;
}

void exit_gracefully(void)
{
   fout.close();
   exit(0);
}

float a = 1.0F;
float x_0 = 0.0F;
float y_0 = -0.5F;

float catenary(float x)
{
   return a*(cosh((x-x_0)/a)-1.0F)+y_0;
}

