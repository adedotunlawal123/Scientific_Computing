#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

size_t idx4(size_t i, size_t j) { return 4*i + j; }

double inner_prod(const double u[], const double v[], int N)
{
   double sum = u[0]*v[0];
   for (int i = 1; i < N; ++i)
      sum += u[i]*v[i];
   return sum;
}

void outer_prod(double out[], const double u[], const double v[], int N, int M)
{
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
         out[M*i+j] = u[i]*v[j];
}

void multiply(double out[], const double inL[], const double inR[],
      int N, int K, int M)
{
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
      {
         out[M*i+j] = 0.0;
         for (int k = 0; k < K; ++k)
            out[M*i+j] += inL[M*i+k]*inR[K*k+j];
      }
}

