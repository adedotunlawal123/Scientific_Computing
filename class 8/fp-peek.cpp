#include <cassert>

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include "bitconvert.h"

int main()
{
   assert(sizeof(double) == 2*sizeof(uint32_t));
   assert(sizeof(uint64_t) == 2*sizeof(uint32_t));
   assert(sizeof(convert64_t) == sizeof(uint64_t));

   cout << "Double-precision floating point: " << endl;
   convert64_t D;

   // 64-bit float: s1 e11 m52 : s x 2^(e-offset)*(1 + .m)
   //  s/eeeeeeeeeee/mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   //  1 11122223333/4444555566667777888811112222333344445555666677778888
   //  \________________________________/\______________________________/
   //                HIGH                              LOW

   // ONE
   //  0/01111111111/0000000000000000000000000000000000000000000000000000
   //  1 11122223333/4444555566667777888811112222333344445555666677778888
   //  \________________________________/\______________________________/
   //      3   F   F    0   0   0   0   0   0   0   0   0   0   0   0   0
   // +2^0*(1+0.0000...)_2
   D.I32[HIGH_BITS] = 0x3FF00000;
   D.I32[LOW_BITS] = 0x0000000;
   show_bits(cout,D);
   cout << "1 -> " << D.F64 << endl << endl;
   assert(D.F64 == 1.);

   // minus ONE
   //  1/01111111111/0000000000000000000000000000000000000000000000000000
   //  1 11122223333/4444555566667777888811112222333344445555666677778888
   //  \________________________________/\______________________________/
   //      B   F   F    0   0   0   0   0   0   0   0   0   0   0   0   0
   // +2^0*(1+0.0000...)_2
   D.I32[HIGH_BITS] = 0xBFF00000;
   D.I32[LOW_BITS] = 0x0000000;
   show_bits(cout,D);
   cout << "-1 -> " << D.F64 << endl << endl;
   assert(D.F64 == -1.);

   // TWO-epsilon
   //  0/01111111111/1111111111111111111111111111111111111111111111111111
   //  1 11122223333/4444555566667777888811112222333344445555666677778888
   //  \________________________________/\______________________________/
   //      3   F   F    F   F   F   F   F   F   F   F   F   F   F   F   F
   // +2^0*(1+0.1111...)_2
   D.I32[HIGH_BITS] = 0x3FFFFFFF;
   D.I32[LOW_BITS] = 0x0000000;
   show_bits(cout,D);
   cout << "2-eps -> " << D.F64 << endl << endl;
   
   // TWO
   //  0/10000000000/0000000000000000000000000000000000000000000000000000
   //  1 11122223333/4444555566667777888811112222333344445555666677778888
   //  \________________________________/\______________________________/
   //      4   0   0    0   0   0   0   0   0   0   0   0   0   0   0   0
   // +2^1*(1+0.0000...)_2
   D.I32[HIGH_BITS] = 0x40000000;
   D.I32[LOW_BITS] = 0x0000000;
   show_bits(cout,D);
   cout << "2 -> " << D.F64 << endl << endl;
   assert(D.F64 == 2.);

   cout << "Single-precision floating point: " << endl;
   convert32_t S;

   // 32-bit float: s1 e8 m23 : s x 2^(e-offset)*(1 + .m)
   //  s/eeeeeeee/mmmmmmmmmmmmmmmmmmmmmmm
   //  1 11122223 33344445555666677778888
   //  \________________________________/

   // ONE
   //  0/01111111/00000000000000000000000
   //  1 11122223 33344445555666677778888
   //  \________________________________/
   //      3   F    8   0   0   0   0   0
   // +2^0*(1+.0000....)_2
   S.I32 = 0x3F800000;
   show_bits(cout,S);
   cout << "1 -> " << S.F32 << endl << endl;
   assert(S.F32 == 1.);

   S.F32 = 2.0F;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 3.0F;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 4.0F;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 5.0F;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 6.0F;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 3145728;
   cout << S.F32 << endl;
   show_bits(cout,S);
   
   S.F32 = 3145729;
   cout << S.F32 << endl;
   show_bits(cout,S);

   cout.precision(16);

   S.F32 = 50331648;
   cout << S.F32 << endl;
   show_bits(cout,S);
   S.I32++;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 50331649;
   cout << S.F32 << endl;
   show_bits(cout,S);

   S.F32 = 0.16;
   cout << S.F32 << endl;
   show_bits(cout,S);

   return 0;
}
