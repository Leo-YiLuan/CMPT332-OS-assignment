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
#include <os.h>
#include "fib.h"
#include "thread_util.h"
#include <inttypes.h>


/* Array of PID */
PID *idArr;
/* Array of counter */
uint64_t *countArr;

/* thread variable to track it's array index */
__thread int threadIdx = -1;

/* count how many times thread been created */
int threadCount = -1;

PROCESS myThread(void *param)
{
  int i;
  /* when new thread created thread count ++ */
  threadCount ++;

  /* save the array created order in thread variable, use as index */
  threadIdx = threadCount;
  /* save PID to PID array */
  idArr[threadIdx] = MyPid();

  /* call fib() with given size */
  for(i=1;i<=*(int*)param;i++){
  	fib(i);
  }
  /* skeleton program */
  printf("Thread id: %ld, fib(%d) to fib(1) is called\n",idArr[threadIdx],
  *(int*)param);}


int mainp(int argc, char** argv)
{

  int threads = 0;
  int deadline = 0;
  int size = 0;
  int i = 0;

  /* check arguments (usage) */
  if (! parse_args(argc,argv,&threads,&deadline,&size)) {
      return -1;
  }

  /* allocate counter and id array */
  countArr = (uint64_t*) malloc(threads * sizeof(uint64_t));
  idArr = (PID*) malloc(threads * sizeof(PID));

  /* create threads */
  for ( i = 0; i < threads; i++) {
      Create( (void(*)()) myThread,16000,NULL, &size,
  		   NORM, USR );
    }


  return 0;
}
