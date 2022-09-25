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
    list->currNodep = list->firstNodep;

    return list->currNodep->item;
}

void *ListLast(LIST *list){
    if (list == NULL){
        return NULL;
    }

    list->currNodep = list->lastNodep;

    return list->currNodep->item;
}

void *ListNext(LIST *list){
    if (list == NULL){
        return NULL;
    }
    if (list->currNodep->next == NULL) {
        return NULL;
    }

    list->currNodep = list->currNodep->next;
    return list->currNodep->item;
}

void *ListPrev(LIST *list){
    if (list == NULL){
        return NULL;
    }

    if (list->currNodep->prev == NULL) {
        return NULL;
    }

    list->currNodep = list->currNodep->prev;
    return list->currNodep->item;
}

void *ListCurr(LIST *list){
    if (list == NULL){
        return NULL;
    }

    return list->currNodep->item;
}

void *ListSearch(LIST *list, int (*comparator)(void *, void *),
 void * comparisonArg){
        if (list == NULL){
        printf("Error in procedure ListSearch(): Invalid parameter list \n");
        return NULL;
    }else if (comparator == NULL)
    {
        printf("Error in procedure ListSearch(): "
        "Invalid parameter comparator() \n");
        return NULL;
    }else if (comparisonArg == NULL)
    {
        printf("Error in procedure ListSearch(): "
        "Invalid parameter comparisionArg \n");
        return NULL;
    }
    printf("Got to procedure ListSearch()\n");

    return NULL;
}
