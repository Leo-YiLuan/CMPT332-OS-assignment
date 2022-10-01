#include "kernel/types.h"
#include "user.h"

int testNumprocs(int n){
  int *childrenID = malloc(sizeof(int)*n);
  int current_runnable;
  int i;
  for (i = 0; i < n; i++) {
    if (fork()==0) {
      childrenID[i] = getpid();
      while (1);
    }
  }
  current_runnable = numprocs();
  printf("%d|||\n", current_runnable);
  return current_runnable;

}

int
main(int argc, char *argv[])
{

  testNumprocs(5);

  return 0;
}
