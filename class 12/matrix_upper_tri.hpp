#ifndef MATRIX_UPPER_TRI_HPP
#define MATRIX_UPPER_TRI_HPP

// 0   1   2   3   4   5
//     6   7   8   9  10
//        11  12  13  14
//            15  16  17
//                18  19
//                    20
// 6 rows and column
// 6+5+4+3+2+1 = 7*6/2 = 21 elements
//
// N rows and columns
// N(N+1)/2 elements
//
// idx(i,j) <--> j + i*(2N-1-i)/2

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

class matrix_upper_tri
{
private:
   // data encapsulation
   vector<double> data;
   size_t r, c;
protected:
   size_t idx(size_t i, size_t j) const
   {
      return j + i*(2*c-1-i)/2;
   }
public:
   matrix_upper_tri() : data(), r(0), c(0) {}
   matrix_upper_tri(size_t r_, size_t c_) : data(r_*c_,0.0), r(r_), c(c_) {}
   matrix_upper_tri(const vector<double> &v, size_t r_, size_t c_) :
      data(v), r(r_), c(c_) {}
   matrix_upper_tri(const matrix_upper_tri& A) : data(A.data), r(A.r), c(A.c) {}
   matrix_upper_tri(matrix_upper_tri&& A) : matrix_upper_tri()
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
   double operator()(size_t i, size_t j) const 
   { 
      return i > j ? 0.0 : data[idx(i,j)]; 
   }
   double& operator()(size_t i, size_t j) 
   {
      assert(i <= j);
      return data[idx(i,j)]; 
   }
   friend void swap(matrix_upper_tri& A, matrix_upper_tri& B)
   {
      swap(A.data, B.data);
      swap(A.r, B.r);
      swap(A.c, B.c);
   }
   matrix_upper_tri& operator=(matrix_upper_tri&& A)
   {
      swap(*this, A);
      return *this;
   }
   double dot(const matrix_upper_tri& A)
   {
      assert(this->size() == A.size());
      double sum = data[0]*A[0];
      for (size_t n = 1; n < A.size(); ++n)
         sum += data[n]*A[n];
      return sum;
   }
   matrix_upper_tri transpose()
   {
      matrix_upper_tri B(cols(),rows());
      for (size_t i = 0; i < B.cols(); ++i)
         for (size_t j = 0; j < B.rows(); ++j)
            B(i,j) = this->operator()(j,i);
      return B;
   }
   friend matrix_upper_tri operator+(matrix_upper_tri A, const matrix_upper_tri &B)
   {
      assert(A.rows()==B.rows());
      assert(A.cols()==B.cols());
      for (size_t n = 0; n < A.size(); ++n)
         A[n] += B[n];
      return A;
   }
   friend matrix_upper_tri operator*(const matrix_upper_tri &A, const matrix_upper_tri &B)
   {
      // C = A*B
      // C(i,k) = A(i,j)*B(j,k)
      matrix_upper_tri C(A.rows(), B.cols());
      assert(A.cols() == B.rows());
      for (size_t i = 0; i < C.rows(); ++i)
         for (size_t k = 0; k < C.cols(); ++k)
         {
            if (i <= k) C(i,k) = 0.0;
            for (size_t j = 0; j < A.cols(); ++j)
               if (i <= k) C(i,k) += A(i,j)*B(j,k);
         }
      return C;
   }
   friend matrix_upper_tri operator*(double s, const matrix_upper_tri &A)
   {
      matrix_upper_tri B(A.rows(), A.cols());
      for (size_t n = 0; n < A.size(); ++n)
         B[n] = s*A[n];
      return B;
   }
   friend matrix_upper_tri operator*(const matrix_upper_tri &A, double s)
   {
      return operator*(s,A);
   }
   friend ostream& operator<<(ostream& os, const matrix_upper_tri &A)
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
   friend bool operator==(const matrix_upper_tri &A, const matrix_upper_tri &B)
   {
      if (A.rows() != B.rows()) return false;
      if (A.cols() != B.cols()) return false;
      for (size_t n = 0; n < A.size(); ++n)
         if (A[n] != B[n])
            return false;
      return true;
   }
   friend bool operator!=(const matrix_upper_tri &A, const matrix_upper_tri &B)
   {
      return !(A==B);
   }
};

double dot(const matrix_upper_tri& A, const matrix_upper_tri &B)
   {
      assert(A.size() == B.size());
      double sum = A[0]*B[0];
      for (size_t n = 1; n < A.size(); ++n)
         sum += A[n]*B[n];
      return sum;
   }

matrix_upper_tri transpose(const matrix_upper_tri& A)
   {
      matrix_upper_tri B(A.cols(),A.rows());
      for (size_t i = 0; i < B.cols(); ++i)
         for (size_t j = 0; j < B.rows(); ++j)
            B(i,j) = A(j,i);
      return B;
   }

#endif // matrix_upper_tri_HPP
