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

LIST* ListCreate(){
    /* Take the next available position off our stack. */
    LIST_ENTRY *entry = freeLists;
    LIST *list = &(entry->list);

    /* 
     If the next entry is null, it is defined to mean that the next
     index in the array is free, so we need to set that now. 
     This avoids an O(n) initialization of the stack.
    */
    if (entry->next == NULL) {
        entry->next = entry + 1;
    } 
    /* Remove the free pos we just utilized. */
    freeLists = freeLists->next;

    return list;
}


int ListAdd(LIST *list,void *item){
    NODE_ENTRY *entry = NULL;
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }else if (item == NULL)
    {
        return -1;
    }

    /* Grab a free node. */
    entry = freeNodes;
    node = &(entry->node);
    node->item = item;

    /* Time to do book-keeping to update the free list correctly. */
    if (entry->nextEntry == NULL) {
        entry->nextEntry = entry + 1;
    }
    freeNodes = freeNodes->nextEntry;

    /* List is empty, treat it as if we are at the end. */
    if (list->listSize == 0) {
        list->currNodep = node;
        list->firstNodep = node;
        list->lastNodep = node;
    } else {
        NODE *currNode = list->currNodep;
        node->next = currNode->next;
        node->prev = currNode;
        currNode->next = node;
        list->currNodep = node;

        if (node->next == NULL) {
            /* Just inserted at the end of the list, update lastNodep */
            list->lastNodep = node;
        }
    }

    list->listSize += 1;

    return 0;
}

int ListInsert(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListInsert(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListInsert(): Invalid parameter item \n");
        return -1;

    }
    printf("Got to procedure ListInsert\n");

    return 0;
}

int ListAppend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListAppend(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListAppend(): Invalid parameter item \n");
        return -1;
    }
    printf("Got to procedure ListAppend\n");

    return 0;
}

int ListPrepend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListPrepend(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListPrepend(): Invalid parameter item \n");
        return -1;
    }
    printf("Got to procedure ListPrepend\n");
    return 0;
}

void ListConcat(LIST *list1, LIST *list2){
    if (list1 == NULL){
        printf("Error in procedure ListConcat(): Invalid parameter list1 \n");
        return;
    }else if (list2 == NULL)
    {
        printf("Error in procedure ListConcat(): Invalid parameter list2 \n");
        return;
    }
    printf("Got to procedure ListConcat\n");

}
