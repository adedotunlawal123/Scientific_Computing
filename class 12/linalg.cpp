#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "matrix.hpp"
#include "matrix_upper_tri.hpp"

matrix A({ 1, 2, 3, 4,
           4, 1, 6, 2,
           7, 8, 1, 3,
           1, 5, 9, 2 }, 4, 4); // 4x4 matrix

matrix I({ 1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1 }, 4, 4);

matrix u({ -1, 2, 5, -4 }, 4, 1);
matrix v({ -2, 3, -1, 8 }, 4, 1); // column vector

int main()
{
   cout << "A = " << endl;
   cout << A << endl;

   matrix B = A + 1.5*I*2;
   cout << "B = " << endl;
   cout << B << endl;

   cout
      << endl << "uT*v = " << (transpose(u)*v)(0,0)
      << " = " << dot(u,v) << " = " << u.dot(v) << endl;

   matrix C = A*B;
   cout << endl << "C = " << endl;
   cout << C << endl;

   matrix M(5,5);
   cout << "rows of M is " << M.rows() << endl;
   cout << "cols of M is " << M.cols() << endl;
   cout << "elements of M is " << M.size() << endl;

   // M(0,0) is an lvalue via double& operator()
   M(0,0) = 3.0;

   // M(0,0) is an rvalue via double operator() const
   const double x = M(0,0);
   
   M(2,3) = x;

   cout << endl << "M = " << endl;
   cout << M << endl;

   matrix P({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 5, 2);
   cout << endl << "P = " << endl;
   cout << P << endl;

   matrix Q({ -1, 3, 4, 9, 3, -5, 6, -1, -2, 0}, 5, 2);
   cout << endl << "Q = " << endl;
   cout << Q << endl;

   matrix R = P + Q;
   cout << endl << "R = P + Q" << endl;
   cout << R << endl;

   matrix S(R);
   cout << endl << "S = " << endl;
   cout << S << endl;

   matrix Pt = transpose(P);
   matrix Qt, T;
   Qt = Q.transpose();
   T = Pt*P;
   cout << endl << "T = Pt*P" << endl;
   cout << T << endl;

   cout << endl << "Q*Qt" << endl;
   cout << Q*Qt << endl;

   matrix_upper_tri U(6,6);
   U(0,0) = 1.0;
   U(0,3) = -2.0;
   U(2,2) = 3.0;
   U(2,5) = -0.5;
   cout << "U = " << endl;
   cout << U << endl;
   
   matrix_upper_tri V({ 1, 2, 3, 4, 5, 6,
                           7, 8, 9,10,11,
                             12,13,14,15,
                                16,17,18,
                                   19,20,
                                      21 }, 6, 6);
   cout << "V = " << endl;
   cout << V << endl;

   cout << "U*V = " << U*V << endl;

   matrix W(6,6);

   U*W;

   return 0;
}

