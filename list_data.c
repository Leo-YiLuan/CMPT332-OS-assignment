#include "list.h"

#include <stddef.h>

#define MAX_NODES 1000
#define MAX_LISTS 10

LIST_ENTRY lists[MAX_LISTS] = {0};
LIST_ENTRY *freeLists = &lists[0];

NODE_ENTRY nodes[MAX_NODES] = {0};
NODE_ENTRY *freeNodes = &nodes[0];
