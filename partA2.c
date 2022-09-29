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

#include <standards.h>
#include <kernelConfig.h>
#include <os.h>
#include "fib.h"
#include "thread_util.h"
#include <inttypes.h>

#define TICKS_PER_SECOND 1000000 / TICKINTERVAL

uint64_t PA_GetUID() {
    return MyPid();
}

typedef struct Params Params;
struct Params {
  int threads;
  int deadline;
  int size;
};

/* Array of counter */
ThreadEntry *countArr;
/* count how many times thread been created */
int threadCount = 0;

PROCESS myThread(void *param)
{
  int i = 0;
  /* call fib() with given size */
  for(i=1;i<=*(int*)param;i++){
  	fib(i);
  }

  for (i = 0; i < threadCount; i++) {
    if (MyPid() == (PID)countArr[i].uid) {
      printf("Thread id: %ld, fib(%d), with %ld invocations.\n", MyPid(), *(int*)param, countArr[i].count);
    }
  }
}


PROCESS parentThread(void *param) {
  Params *params = (Params*)param;
  int i = 0;

    for (i = 0; i < params->threads; i++) {
    threadCount += 1;
    countArr[i].uid = Create((void(*)())myThread, 1048576, NULL, (void*)&(params->size), NORM, USR);
  }

  Sleep(params->deadline * TICKS_PER_SECOND);

  for (i = 0; i < params->threads; i++) {
    if (Kill(countArr[i].uid) != PNUL) {
      printf("Thread id: %ld, fib(%d), with %ld invocations.\n", countArr[i].uid, params->size, countArr[i].count);
    }
  }
}

int mainp(int argc, char** argv)
{

  int threads = 0;
  int deadline = 0;
  int size = 0;
  Params *params = malloc(sizeof(Params));

  /* check arguments (usage) */
  if (! parse_args(argc,argv,&threads,&deadline,&size)) {
      return -1;
  }
  params->threads = threads;
  params->deadline = deadline;
  params->size = size;

  /* allocate counter and id array */
  countArr = (ThreadEntry*) malloc(threads * sizeof(ThreadEntry));
  memset(countArr, 0, threads * sizeof(ThreadEntry));

  Create((void(*)())parentThread, 16000, "parent", (void*)params, HIGH, USR);

  return 0;
}
