/*
 NAME: Matthew Munro
 NSID: mam552
 STUDENT NUMBER: 11291769
 NAME: Yi Luan
 NSID: yil160
 STUDENT NUMBER: 11253856
 CMPT 332 2022
 A3
*/
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
    // printf(  "Process: %d  is runnig prior %d\n",getpid(),getpriority());
    // printf("Process: %d  is runnig\n",getpid());


    return fib(num - 1) + fib(num - 2);
}

void do_nice(int incr){
  if (nice(incr)!=-1)
  {
      printf("Successfully increment %d priority to process %d \n",incr
      ,getpid());
  }else
  {
      // printf("Failed to change process %d priority by num using nice()\n"
      // ,getpid());
  }
}

void runTest(int numproc){
    int tempid;
    int i;

    for (i = 0; i < numproc; i++) {
      tempid = fork();
      /* child in an infinite loop make parent possible */
      if (tempid==0) {
        while(1){
          int randSleep = rand() % 5;
          int randFib = rand() % 40;
          int niceProb = rand() % 10;
          int randNice = rand() % 4 + 1;

          //printf("Process %d get sleep for %d time\n",getpid(),randSleep);
          sleep(randSleep);
          //printf("Process %d wake up, prior is %d\n",getpid(),getpriority());
          if (niceProb == 1)
          {
              do_nice(randNice);
          }
          printf("Process %d before running fib(%d) prior is %d\n"
          ,getpid(),randFib,getpriority());
          fib(randFib);


        };
      }else if (tempid == -1) {
        printf("Fail to create new process\n" );
      }
  }
}


int main() {
  runTest(5);
  return 0;
}
