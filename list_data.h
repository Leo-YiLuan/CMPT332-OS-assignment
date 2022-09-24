

#ifndef __LIST_DATA_H__
#define __LIST_DATA_H__

#define MAX_LISTS 10
#define MAX_NODES 1000

/* 
 For extended info on how our stacks of free lists/nodes works,
 please see the partC documentation.
*/
extern LIST lists[MAX_LISTS];
extern LIST *freeLists;
extern NODE nodes[MAX_NODES];
extern NODE *freeNodes;

#endif /* __LIST_DATA_H__ */
