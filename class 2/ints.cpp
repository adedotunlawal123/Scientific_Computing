#include <cstdint>

#include <iostream>
using std::cout;
using std::endl;

template <class T>
void report(T i)
{
   cout << i << " stored in " << sizeof(T) << " bytes" << endl;
   return;
}
   
int main()
{
   unsigned int i1 = -1;
   int i2 = -1;
   cout << "Unsigned and signed int:" << endl;
   report(i1);
   report(i2);

   unsigned long int i3 = 1;
   long int i4 = -1;
   cout << "Unsigned and signed long int: " << endl;
   report(i3);
   report(i4);

   unsigned long long int i5 = -1;
   long long int i6 = -1;
   cout << "Unsigned and signed long long int:" << endl;
   report(i5);
   report(i6);

   uint16_t j1 = -1;
   int16_t j2 = -1;
   cout << "Unsigned and signed 16-bit int:" << endl;
   report(j1);
   report(j2);

   cout << "Widest int available:" << endl;
   uintmax_t j7 = -1;
   report(j7);

   return 0;
}

