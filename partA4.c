/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1
*/
#include <stdio.h>
#include <stdlib.h>
#include "fib.h"
#include "thread_util.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

uint64_t *countArr;
__thread int threadIdx;

void timer(){
  /* skeleton function */
  printf("timer is called start timing \n");

}

int main(int argc, char **argv){
  int processes = 0;
  int deadline = 0;
  int size = 0;
  /* pid for processed call fib() */
  pid_t fibproc;
  /* pid for timer process */
  pid_t timerproc;
  int i=0;
  /* check arguments (usage) */
  if (! parse_args(argc,argv,&processes,&deadline,&size)) {
      return -1;
  }
  /* create timer process */
  timerproc = fork();
    if (timerproc == 0) {
      /* skeleton program show that timer process created */
      printf("In timer process id: %d\n",getpid());
      /* call timer function here */
      timer();
  }
  /* in main process */
  if (timerproc > 0) {
    /* create processes based on the argument */
    for(i =0 ;i<processes;i++)
    {
      /* create fib() process */
        fibproc= fork();
        /* in fib() process */
        if(fibproc == 0)
        {
            /* skeleton program shows N process has been created */
            printf("process: %d is created!\n",getpid());
            /* fib() called */
            printf("In process: %d, fib(%d) is called!\n",getpid(),size);
            fib(size);
            exit(0);
        }
    }
  }
  /* wait children process finish */
  wait(NULL);
  return 0;
}
