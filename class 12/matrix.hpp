#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
using std::size_t;

#include <algorithm>
using std::swap;

#include <vector>
using std::vector;

#include <iostream>
using std::cerr;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;

// matrix A(4,5);
// A(2,3) = 3.0;
// const double y = A(1,4);
// A.data[3]; // illegal
// const int i = A.r; // illegal
// const int i = A.rows();
// A.rows() = 5; // illegal
// A.r = 8;
// A(1,1);

class matrix
{
private:
   // data encapsulation + data hiding
   vector<double> data;
   size_t r, c;
public:
   matrix() : data(), r(0), c(0) {}
   matrix(size_t r_, size_t c_) : data(r_*c_,0.0), r(r_), c(c_) {}
   matrix(const vector<double> &v, size_t r_, size_t c_) :
      data(v), r(r_), c(c_) {}
   matrix(const matrix& A) : data(A.data), r(A.r), c(A.c) {}
   matrix(matrix&& A) : matrix()
   {
      swap(*this, A);
   }
   size_t size() const { return data.size(); }
   void reinit(size_t r_, size_t c_)
   {
      r=r_;
      c=c_;
      data.resize(r*c);
      data.assign(r*c,0.0);
   }
   size_t rows() const { return r; }
   size_t cols() const { return c; }
   double operator[](size_t n) const { return data[n]; }
   double& operator[](size_t n) { return data[n]; }
   double operator()(size_t i, size_t j) const { return data[c*i + j]; }
   double& operator()(size_t i, size_t j) { return data[c*i + j]; }
   friend void swap(matrix& A, matrix& B)
   {
      swap(A.data, B.data);
      swap(A.r, B.r);
      swap(A.c, B.c);
   }
   matrix& operator=(matrix&& A)
   {
      swap(*this, A);
      return *this;
   }
   double dot(const matrix& A)
   {
      assert(this->size() == A.size());
      double sum = data[0]*A[0];
      for (size_t n = 1; n < A.size(); ++n)
         sum += data[n]*A[n];
      return sum;
   }
   matrix transpose()
   {
      matrix B(cols(),rows());
      for (size_t i = 0; i < B.cols(); ++i)
         for (size_t j = 0; j < B.rows(); ++j)
            B(i,j) = this->operator()(j,i);
      return B;
   }
   friend matrix operator+(matrix A, const matrix &B)
   {
      assert(A.rows()==B.rows());
      assert(A.cols()==B.cols());
      for (size_t n = 0; n < A.size(); ++n)
         A[n] += B[n];
      return A;
   }
   friend matrix operator*(const matrix &A, const matrix &B)
   {
      // C = A*B
      // C(i,k) = A(i,j)*B(j,k)
      matrix C(A.rows(), B.cols());
      assert(A.cols() == B.rows());
      for (size_t i = 0; i < C.rows(); ++i)
         for (size_t k = 0; k < C.cols(); ++k)
         {
            C(i,k) = 0.0;
            for (size_t j = 0; j < A.cols(); ++j)
               C(i,k) += A(i,j)*B(j,k);
         }
      return C;
   }
   friend matrix operator*(double s, const matrix &A)
   {
      matrix B(A.rows(), A.cols());
      for (size_t n = 0; n < A.size(); ++n)
         B[n] = s*A[n];
      return B;
   }
   friend matrix operator*(const matrix &A, double s)
   {
      return operator*(s,A);
   }
   friend ostream& operator<<(ostream& os, const matrix &A)
   {
      os.precision(4);
      for (size_t i = 0; i < A.rows(); ++i)
      {
         os << (i == 0 ? '/' : i == A.rows()-1 ? '\\' : '|');
         for (size_t j = 0; j < A.cols(); ++j)
            os << setw(5) << A(i,j);
         os
            << ' ' << (i == 0 ? '\\' : i == A.rows()-1 ? '/' : '|' )
            << endl;
      }
      return os;
   }
   friend bool operator==(const matrix &A, const matrix &B)
   {
      if (A.rows() != B.rows()) return false;
      if (A.cols() != B.cols()) return false;
      for (size_t n = 0; n < A.size(); ++n)
         if (A[n] != B[n])
            return false;
      return true;
   }
   friend bool operator!=(const matrix &A, const matrix &B)
   {
      return !(A==B);
   }
};

double dot(const matrix& A, const matrix &B)
   {
      assert(A.size() == B.size());
      double sum = A[0]*B[0];
      for (size_t n = 1; n < A.size(); ++n)
         sum += A[n]*B[n];
      return sum;
   }

matrix transpose(const matrix& A)
   {
      matrix B(A.cols(),A.rows());
      for (size_t i = 0; i < B.cols(); ++i)
         for (size_t j = 0; j < B.rows(); ++j)
            B(i,j) = A(j,i);
      return B;
   }

matrix inverse(const matrix &A)
{
   matrix B(A.rows(),A.cols());
   // do some stuff but only the public
   // A(N,N) 
   // O(N^3)
   // A*v O(N^2)
   // A*B O(N^2.84)
   return B;
}
// matrix Ainv = inverse(A);
// matrix Ainv = A.inverse();
#endif // MATRIX_HPP
