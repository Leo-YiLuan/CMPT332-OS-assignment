#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  printf("Free Pages: %ld", getNumPages());
  exit(0);
}
