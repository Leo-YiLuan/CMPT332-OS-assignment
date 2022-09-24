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
#include <stdio.h>

#include "list_data.h"

/**
 *  These functions just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
void *ListRemove(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListRemove()\n"); 
    return NULL;
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
