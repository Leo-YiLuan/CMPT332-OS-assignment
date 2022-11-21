#include "kernel/types.h"
#include "user/user.h"
int
do_rand(unsigned long *ctx)
{
/*
 * Compute x = (7^5 * x) mod (2^31 - 1)
 * without overflowing 31 bits:
 *      (2^31 - 1) = 127773 * (7^5) + 2836
 * From "Random number generators: good ones are hard to find",
 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
 * October 1988, p. 1195.
 */
    long hi, lo, x;

    /* Transform to [1, 0x7ffffffe] range. */
    x = (*ctx % 0x7ffffffe) + 1;
    hi = x / 127773;
    lo = x % 127773;
    x = 16807 * lo - 2836 * hi;
    if (x < 0)
        x += 0x7fffffff;
    /* Transform to [0, 0x7ffffffd] range. */
    x--;
    *ctx = x;
    return (x);
}

unsigned long rand_next = 1;

int
rand(void)
{
    rand_next+= getpid();
    return do_rand(&rand_next);
}

int fib(int num){
    if (num <= 2) {
        return 1;
    }
    // printf("Process: %d  is runnig prior %d\n",getpid(),nice(0));
    // printf("Process: %d  is runnig\n",getpid());


    return fib(num - 1) + fib(num - 2);
}

void runTest(int numproc){
    int tempid;
    int i;
    // int fibNum;

    for (i = 0; i < numproc; i++) {
      tempid = fork();
      /* child in an infinite loop make parent possible */
      if (tempid==0) {
        while(1){
          int randSleep = rand() % 7;
          int randFib = rand() % 40;
          printf("Process %d get sleep for %d time\n",getpid(),randSleep);
          sleep(randSleep);
          printf("Process %d wake up\n",getpid());
          printf("Process %d is runnig prior %d\n",getpid(),nice(0));


          fib(randFib);

        };
      }else if (tempid == -1) {
        printf("Fail to create new process\n" );
      }
  }
}


int main() {
  runTest(4);
  return 0;
}
