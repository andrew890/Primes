// ---------------------------------------------------------------------------
// PrimeCPP.cpp : Dave's Garage Prime Sieve in C++ - No warranty for anything!
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <ctime>
#include <iostream>
#include <bitset>
#include <map>
#include <cstring>
#include <cmath>
#include <vector>
#include <sys/time.h>

using namespace std;

class prime_sieve
{
  private:

      long sieveSize;
      vector<bool> Bits;

      bool validateResults()
      {
          return 78498 == countPrimes();
      }

   public:

      prime_sieve(long n)
        : Bits(n, true), sieveSize(n)
      {
      }

      ~prime_sieve()
      {
      }

      void runSieve()
      {
          int factor = 3;
          int q = (int) sqrt((double)sieveSize);

          while (factor <= q)
          {
              for (int num = factor; num < sieveSize; num += 2)
              {
                  if (Bits[num])
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * factor; num < sieveSize; num += factor * 2)
                  Bits[num] = false;

              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = (sieveSize >= 2);                             // Starting count (2 is prime)
          for (int num = 3; num <= sieveSize; num+=2)
          {
              if (Bits[num])
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");

          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %ld, Count1: %d, Count2: %d, Valid: %d\n",
                 passes,
                 duration,
                 duration / passes,
                 sieveSize,
                 count,
                 countPrimes(),
                 validateResults());

          // Following 2 lines added by rbergen to conform to drag race output format
          printf("\n");
          printf("davepl;%d;%f;1;algorithm=base,faithful=yes,bits=1\n", passes, duration);
      }

      int countPrimes()
      {
          int count =  (sieveSize >= 2);;
          for (int i = 3; i < sieveSize; i+=2)
              if (Bits[i])
                  count++;
          return count;
      }
};

int main()
{
    auto passes = 0;
    //auto tStart = steady_clock::now();

    timeval tim;
    gettimeofday(&tim,NULL);

    double tstart = tim.tv_sec + ((double)tim.tv_usec/1000000);


    while (true)
    {
        prime_sieve sieve(1000000L);
        sieve.runSieve();
        passes++;
        timeval now;
        gettimeofday(&now,NULL);
        double tnow = now.tv_sec + ((double)now.tv_usec/1000000);

        if (tnow - tstart >= 5)
        {
            sieve.printResults(false, (tnow - tstart), passes);
            break;
        }
    }
}
