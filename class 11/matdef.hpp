#ifndef MATDEF_HPP
#define MATDEF_HPP

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

size_t idx4(size_t, size_t);

double inner_prod(const double u[], const double v[], int);

void outer_prod(double out[], const double u[], const double v[], 
      int, int);

void multiply(double out[], const double inL[], const double inR[],
      int, int, int);

#endif
