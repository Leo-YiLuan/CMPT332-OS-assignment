/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A2
*/
#include "list.h"
#include <stdio.h>
#include <string.h>

/*
 For extended info on how our stacks of free lists/nodes works,
 please see the partC documentation.
*/
extern LIST lists[MAX_LISTS];
extern LIST *freeLists;
extern NODE nodes[MAX_NODES];
extern NODE *freeNodes;


void *ListRemove(LIST *list){
    void *item;
    NODE *removeNode;
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list \n");
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    /* if not in the list (At BEFORE or AFTER) do nothing */
    if (list->state != NORMAL) {
      return NULL;
    }
    item = list->currNodep->item;
    removeNode  = list->currNodep;
    /* only one node */
    if (list->listCount==1) {
      *(NODE**)removeNode = freeNodes;
      freeNodes = removeNode;
      memset(list,0,sizeof(LIST));
    }
    /* when at last node */
    else if (list->currNodep == list->lastNodep) {
        list->currNodep = removeNode->prev;
        list->listCount--;
        list->lastNodep = list->currNodep;
        list->currNodep->next = NULL;
        *(NODE**)removeNode = freeNodes;
        freeNodes = removeNode;
    /* when at first node */
    }else if (list->currNodep == list->firstNodep){
        list->currNodep = removeNode->next;
        list->listCount--;
        list->firstNodep = list->currNodep;
        list->currNodep->prev = NULL;
        *(NODE**)removeNode = freeNodes;
        freeNodes = removeNode;
    /* when in middle */
    }else{
        list->currNodep = removeNode->next;
        list->listCount--;
        removeNode->next->prev = removeNode->prev;
        removeNode->prev->next = removeNode->next;

        *(NODE**)removeNode = freeNodes;
        freeNodes = removeNode;
    }
    return item;
}

void ListFree(LIST *list, void (*itemFree)(void*)){
    NODE *node = NULL;
    if (list == NULL){
        return;
   }else if (itemFree == NULL)
    {
        return;
    }

    /* Free all nodes and item data. */
    node = list->firstNodep;
    while (node) {
        NODE *nextNode = node->next;
        itemFree(node->item);

        /* Free the current node. */
        *(NODE**)node = freeNodes;
        freeNodes = node;

        node = nextNode;
    }

    /* Add the newly freed list entry to the front of the stack */
    *(LIST**)list = freeLists;
    freeLists = list;
}

void *ListTrim(LIST *list){
    void *item;
    NODE *removeNode;

    if (list == NULL){
        printf("Error in procedure ListTrim(): Invalid parameter list \n");
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }

    item = list->lastNodep->item;
    removeNode = list->lastNodep;
    if (list->listCount == 1) {
      *(NODE**)removeNode = freeNodes;
      freeNodes = removeNode;
      memset(list,0,sizeof(LIST));
    }else{
      removeNode->prev->next = NULL;
      list->lastNodep = removeNode->prev;
      list->currNodep = list->lastNodep;
      *(NODE**)removeNode = freeNodes;
      freeNodes = removeNode;
      list->listCount --;
    }


    return item;

}
