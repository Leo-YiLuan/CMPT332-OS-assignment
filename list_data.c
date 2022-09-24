#include "list.h"

#include <stddef.h>

#define MAX_NODES 1000
#define MAX_LISTS 10

LIST lists[MAX_LISTS];
LIST *freeLists = &lists[0];

NODE nodes[MAX_NODES];
NODE *freeNodes = &nodes[0];