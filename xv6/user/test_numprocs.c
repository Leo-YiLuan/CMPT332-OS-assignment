#include "kernel/types.h"
#include "user.h"

int i;

int testNumprocs(int n){
  int childrenID[64];
  int current_runnable;
  int tempid=0;

  for (i = 0; i < n; i++) {
    printf("forked\n" );
    tempid = fork();

    if (tempid==0) {
      while (1);
    }else if (tempid == -1) {
      printf("Fail to create new process\n" );
    }else{
      childrenID[i] = tempid;
    }
  }

  current_runnable = numprocs();

  for (i = 0; i < n; i++) {
    if (kill(childrenID[i])==-1) {
      printf("Fail to kill: %d\n",childrenID[i]);
    }
      childrenID[i]=0;

}

  return current_runnable;

}

int
main(int argc, char *argv[])
{

  printf("10: %d\n", testNumprocs(10));
  printf("12: %d\n", testNumprocs(12));
  printf("21: %d\n", testNumprocs(21));

  return 0;
}
