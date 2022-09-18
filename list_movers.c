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
#include <stdio.h>
#include "list.h" 


int ListCount(LIST *list){
    if (list == NULL){
        printf("Error in procedure listCount(): Invalid parameter list \n");
        return -1;
    }
    return list->listCount;
}

void *ListFirst(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListFirst(): Invalid parameter list \n");
    }
    return NULL;
}

void *ListLast(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListLast(): Invalid parameter list \n");
    }
    return NULL;
}

void *ListNext(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListNext(): Invalid parameter list \n");
    }
    return NULL;
}

void *ListPrev(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListPrev(): Invalid parameter list \n");
    }
    return NULL;
}

void *ListCurr(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListCurr(): Invalid parameter list \n");
    }
    return NULL;
}

void *ListSearch(LIST *list, int (*comparator)(void *, void *), void * comparisonArg){
        if (list == NULL){
        printf("Error in procedure ListSearch(): Invalid parameter list \n");
    }else if (comparator == NULL)
    {
        printf("Error in procedure ListSearch(): Invalid parameter comparator() \n");
    }else if (comparisonArg)
    {
        printf("Error in procedure ListSearch(): Invalid parameter comparisionArg \n");
    }
    return NULL;    
}