

#ifndef __LIST_DATA_H__
#define __LIST_DATA_H__

#define MAX_LISTS 10
#define MAX_NODES 1000

extern LIST_ENTRY lists[MAX_LISTS];
extern LIST_ENTRY *freeLists;
extern NODE_ENTRY nodes[MAX_NODES];
extern NODE_ENTRY *freeNodes;

#endif /* __LIST_DATA_H__ */
