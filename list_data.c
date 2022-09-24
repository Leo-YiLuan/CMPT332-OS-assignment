/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1
*/
#include "list.h"

#include <stddef.h>

#define MAX_NODES 1000
#define MAX_LISTS 10

LIST lists[MAX_LISTS];
LIST *freeLists = &lists[0];

NODE nodes[MAX_NODES];
NODE *freeNodes = &nodes[0];