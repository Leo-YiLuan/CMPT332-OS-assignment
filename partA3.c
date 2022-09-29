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

/* Array of counter */
ThreadEntry *countArr;
int threadCount = 0;

size_t PA_GetUID() {
    return pthread_self();
}

void *myThread(void *param)
{
  int i;

  /* call fib() with given size */
  for(i=1;i<=*(int*)param;i++){
  	fib(i);
  }

  /* skeleton program */
  printf("Thread id: %ld, fib(%d) to fib(1) is called\n",pthread_self(),
  *(int*)param);

  pthread_exit(NULL);
}

int main(int argc,char **argv)
{
    int deadline = 0;
    int size = 0;
    int threads = 0;
    int i = 0;
     /* check arguments (usage) */
     if (! parse_args(argc,argv,&threads,&deadline,&size)) {
         return -1;
     }

     /* allocate counter and id array */
     countArr = (ThreadEntry*) malloc(threads * sizeof(ThreadEntry));

    /* Create threads */
    for (i=0;i<threads;i++){
        pthread_t thread;
        pthread_create( &thread, NULL, myThread, &size);
        countArr[i].uid = thread;
    }

    /* wait all thread finish */
     for (i = 0; i < threads; i++) {
        pthread_join(countArr[i].uid,NULL);
     }

     return 0;
}
