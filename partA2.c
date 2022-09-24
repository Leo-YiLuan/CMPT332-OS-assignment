#include <stdio.h>
#include <stdlib.h>

#include <standards.h>
#include <os.h>
#include "fib.h"
#include "thread_util.h"

uint64_t *arr;
__thread int threadIdx = -1;
int threadIdxStart = -1;

PROCESS myThread(void *param)
{
  threadIdxStart ++;
  threadIdx = threadIdxStart;
  fib(*(int*)param);
  printf("Thread num: %d, fin(%d) is called\n",threadIdx, *(int*)param);
}

int mainp(int argc, char** argv)
{

  int threads = 0;
  int deadline = 0;
  int size = 0;
  int i = 0;

  if (! parse_args(argc,argv,&threads,&deadline,&size)) {
      return -1;
  }

  arr = (uint64_t*) malloc(threads * sizeof(uint64_t));


  for ( i = 0; i < threads; i++) {

    Create( (void(*)()) myThread,16000,NULL, &size,
  		   NORM, USR );
    }


  return 0;
}
