/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2
*/

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
