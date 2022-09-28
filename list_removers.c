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
#include "list.h"
#include <stdio.h>
#include <string.h>

#include "list_data.h"

/**
 *  These functions just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
void *ListRemove(LIST *list){
    void *item = list->currNodep->item;
    NODE *removeNode = list->currNodep;
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list \n");
        return NULL;
    }
    if (list->listCount==1) {
      *(NODE**)removeNode = freeNodes;
      freeNodes = removeNode;
      memset(list,0,sizeof(LIST));
    }
    else if (list->currNodep == list->lastNodep) {
        list->currNodep = removeNode->prev;
        list->listCount--;
        list->lastNodep = list->currNodep;
        list->currNodep->next = NULL;
        *(NODE**)removeNode = freeNodes;
        freeNodes = removeNode;
    }else if (list->currNodep == list->firstNodep){
        list->currNodep = removeNode->next;
        list->listCount--;
        list->firstNodep = list->currNodep;
        list->currNodep->prev = NULL;
        *(NODE**)removeNode = freeNodes;
        freeNodes = removeNode;
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
    if (list == NULL){
        printf("Error in procedure ListTrim(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListTrim()\n");
    return NULL;

}
