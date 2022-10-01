#include "kernel/types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1 = fork();
  int pid2 = fork();
  int pid3 = fork();
  int pid4 = fork();
  int pid5 = fork();
  int pid6 = fork();
  if (pid1 > 0 && pid2 > 0 && pid3>0 && pid4>0 &&pid5>0 && pid6>0 ) {
    int current_runnable;
    current_runnable = numprocs();
    printf("%d|||\n", current_runnable);  }
  return 0;
}
