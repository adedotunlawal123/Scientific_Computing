// Place k beads into n positions along a string.
// Generate and print all possible configurations.

#include <cstdlib>
using std::exit;
using std::strtol;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

void usage(void)
{
   cerr << "Usage: beads (k value) (n value)" << endl;
   cerr << " -- place k beads into n positions" << endl;
   cerr << " -- requires 0 < k <= n" << endl;
   exit(1);
}

size_t popcount(size_t b)
{
   size_t pc;
   for (pc = 0; b != 0; b >>=1)
      pc += b & size_t(1);
   // pc = pc + (b & 1u);
   // b=5: 000101
   //    & 000001 
   //    --------
   //      000001
   return pc;
}

void show_beads(size_t b, size_t top)
{
   for (size_t mask = 1; mask < top; mask <<= 1)
      cout << (b & mask ? 'o' : '-');
   cout << endl;
}

int main(int argc, char *argv[])
{
   // parse the command line arguments
   size_t k, n;
   if (argc != 3)
      usage();
   else
   {
      char *endptr;
      long int kk = strtol(argv[1],&endptr,10);
      if (endptr == NULL or *endptr != '\0') usage();
      long int nn = strtol(argv[2],&endptr,10);
      if (endptr == NULL or *endptr != '\0') usage();
      if (kk > nn or kk < 0 or nn < 1) usage();
      k = size_t(kk);
      n = size_t(nn);
   }

   // generate and print all the valid configurations
   const size_t top = (1 << n);
   for (size_t bits = 0; bits < top; ++bits)
      if (popcount(bits) == k) show_beads(bits,top);
   return 0;
}
