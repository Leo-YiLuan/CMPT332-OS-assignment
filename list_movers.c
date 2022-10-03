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
#include <stdio.h>
#include "list.h"

/*
 For extended info on how our stacks of free lists/nodes works,
 please see the partC documentation.
*/
extern LIST lists[MAX_LISTS];
extern LIST *freeLists;
extern NODE nodes[MAX_NODES];
extern NODE *freeNodes;

/**
 *  These function just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
int ListCount(LIST *list){
    if (list == NULL){
        return -1;
    }

    return list->listCount;
}

void *ListFirst(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    list->state = NORMAL;
    list->currNodep = list->firstNodep;

    return list->currNodep->item;
}

void *ListLast(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    list->state = NORMAL;
    list->currNodep = list->lastNodep;

    return list->currNodep->item;
}

void *ListNext(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    /* if in NULL pointer after the last one */
    if (list->state == AFTER) {
        return NULL;
    }
    /* if in NULL pointer BEFORE the first one
       set current node pointer to first node*/
    if (list->state == BEFORE) {
        list->currNodep = list->firstNodep;
        list->state = NORMAL;
        return list->firstNodep->item;
    }
    /* if at last node, set state to AFTER and return NULL*/
    if (list->currNodep->next == NULL) {
        list->state = AFTER;
        list->currNodep = NULL;
        return NULL;
    }

    list->currNodep = list->currNodep->next;
    return list->currNodep->item;
}

void *ListPrev(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    /* if in NULL pointer before the first one */
    if (list->state == BEFORE) {
        return NULL;
    }
    /* if in NULL pointer after the last one
       set current node pointer to last node*/
    if (list->state == AFTER) {
        list->currNodep = list->lastNodep;
        list->state = NORMAL;
        return list->lastNodep->item;
    }
    /* if at first node, set state to BEFORE and return NULL*/
    if (list->currNodep->prev == NULL) {
        list->state = BEFORE;
        list->currNodep = NULL;
        return NULL;
    }

    list->currNodep = list->currNodep->prev;
    return list->currNodep->item;
}

void *ListCurr(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    if (list->currNodep == NULL) {
        return NULL;
    }

    return list->currNodep->item;
}

void *ListSearch(LIST *list, int (*comparator)(void *, void *),
 void * comparisionArg){
    if (list == NULL){
        printf("Error in procedure ListSearch(): Invalid parameter list \n");
        return NULL;
    }else if (comparator == NULL)
    {
        printf("Error in procedure ListSearch(): "
        "Invalid parameter comparator() \n");
        return NULL;
    }else if (comparisionArg == NULL)
    {
        printf("Error in procedure ListSearch(): "
        "Invalid parameter comparisionArg \n");
        return NULL;
    }
    if (list->listCount == 0) {
        return NULL;
    }
    /* if the current pointer is NULL after the lastNode */
    if (list->state == AFTER) {
        return NULL;
    }
    /* if the current pointer is NULL before the firstnode
       start searching from first node */
    if (list->state == BEFORE) {
       list->currNodep = list->firstNodep;
       list->state = NORMAL;
    }

    /* base case that found item */
    if (comparator(list->currNodep->item,comparisionArg)) {
        return list->currNodep->item;
    }

    /* base case that did not find item */
    if (list->currNodep == list->lastNodep) {
        list->currNodep = NULL;
        list->state = AFTER;
        return NULL;
    }

    list->currNodep = list->currNodep->next;
    return ListSearch(list,comparator,comparisionArg);
}
