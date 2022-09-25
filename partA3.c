/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fib.h"
#include "thread_util.h"
#include <inttypes.h>
/* Array of thread ID */
pthread_t *idArr;
/* Array of counter */
uint64_t *countArr;

/* thread variable to track it's array index */
__thread int threadIdx = -1;

/* number of threads will created */
int threads = 0;

void *myThread(void *param)
{
  int i;

  /* find the index of current thread's id */
  for (i=0;i<threads;i++){
    if (idArr[i] == pthread_self()) {
      /* save it */
      threadIdx = i;
    }
  }

  /* call fib() with given size */
  for(i=1;i<=*(int*)param;i++){
  	fib(i);
  }

  /* skeleton program */
  printf("Thread id: %ld, fib(%d) to fib(1) is called\n",idArr[threadIdx],
  *(int*)param);

  pthread_exit(NULL);
}

int main(int argc,char **argv)
{
    int deadline = 0;
    int size = 0;
    int i = 0;
     /* check arguments (usage) */
     if (! parse_args(argc,argv,&threads,&deadline,&size)) {
         return -1;
     }

     /* allocate counter and id array */
     countArr = (uint64_t*) malloc(threads * sizeof(uint64_t));
     idArr = (pthread_t*) malloc(threads * sizeof(pthread_t));

    /* Create threads */
    for (i=0;i<threads;i++){
        pthread_create( &idArr[i], NULL, myThread, &size);

    }

    /* wait all thread finish */
     for (i = 0; i < threads; i++) {
        pthread_join(idArr[i],NULL);
     }

     return 0;


}
