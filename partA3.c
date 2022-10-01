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
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include "fib.h"
#include "thread_util.h"
#include <inttypes.h>

/* Array of counter */
ThreadEntry *countArr;
/* Count how many threads have been created */
int threadCount = 0;

/* See PartA.design.txt */
size_t PA_GetUID() {
    return pthread_self();
}

void *myThread(void *param)
{
  int i;
  time_t start = 0;
  time_t end = 0;
  time_t dur = 0;
  time(&start);
  /* Set the start time for the thread */
  for (i = 0; i < threadCount; i++) {
    if (countArr[i].uid == PA_GetUID()) {
      countArr[i].startTime = start;
    }
  }

  /* call fib() with given size */
  for(i=1;i<=*(int*)param;i++){
  	fib(i);
  }
  time(&end);
  dur = end - start;

  /* Print results for this thread. */
  for (i = 0; i < threadCount; i++) {
    if (countArr[i].uid == PA_GetUID()) {
      printf("Thread id: %ld, fib(%d) to fib(1) is called "
      "with %ld invocations in %ld sec.\n",pthread_self(),
      *(int*)param, countArr[i].count, dur);
    }
  }

  /* Set our uid back to zero so the parent thread
     knows we've finished. */
  for (i = 0; i < threadCount; i++) {
    if (countArr[i].uid == PA_GetUID()) {
      countArr[i].uid = 0;
    }
  }

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
        threadCount += 1;
        pthread_create( &thread, NULL, myThread, &size);
        countArr[i].uid = thread;
    }

    sleep(deadline);

    /* kill threads past deadline */
     for (i = 0; i < threads; i++) {
        /* Check which threads haven't completed */
        if (countArr[i].uid != 0) {
          time_t end = 0;
          time_t dur = 0;
          time(&end);
          dur = end - countArr[i].startTime;
          printf("Thread id: %ld, fib(%d) to fib(1) is called "
          "with %ld invocations in %ld sec.\n",pthread_self(),
          size, countArr[i].count, dur);
        }
     }

    /* No need to actually kill threads that are still working, they will end
       with the parent process. */ 
     return 0;
}
