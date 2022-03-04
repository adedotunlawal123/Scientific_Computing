#include <iostream>
using std::cout;
using std::endl;

unsigned int binomial(unsigned int n, unsigned int k)
{
   // look up table for (n choose k) = n!/k!/(n-k)!
   static const unsigned int Pascal[] = {
                 1,
                1,1,
               1,2,1,
              1,3,3,1,
             1,4,6,4,1,
           1,5,10,10,5,1,
          1,6,15,20,15,6,1,
         1,7,21,35,35,21,7,1 };
   assert(n >= k);
   return Pascal[n*(n+1)/2+k];
}

int main()
{
   cout << "(5 choose 3) = " << binomial(5,3) << endl;
   cout << "(3 choose 1) = " << binomial(3,1) << endl;
   cout << "(7 choose 4) = " << binomial(7,4) << endl;

   for (unsigned int n = 0; n < 8; ++n)
   {
      unsigned int sum = 0;
      for (unsigned int k = 0; k <= n; ++k)
         sum += binomial(n,k);
      assert(sum == (1 << n));
      cout << "Entries in row " << n << " sum to " << sum << endl;
   }
   return 0;
}
