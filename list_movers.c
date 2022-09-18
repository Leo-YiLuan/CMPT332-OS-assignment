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

/**
 *  These function just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
int ListCount(LIST *list){
    if (list == NULL){
        printf("Error in procedure listCount(): Invalid parameter list \n");
        return -1;
    }
    printf("Got to procedure ListCount()\n");
    return 0;
}

void *ListFirst(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListFirst(): Invalid parameter list \n");
        return NULL;    
    }
    printf("Got to procedure ListFirst()\n");

    return NULL;
}

void *ListLast(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListLast(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListLast()\n");

    return NULL;
}

void *ListNext(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListNext(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListNext()\n");

    return NULL;
}

void *ListPrev(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListPrev(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListPrev()\n");

    return NULL;
}

void *ListCurr(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListCurr(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListCurr()\n");

    return NULL;
}

void *ListSearch(LIST *list, int (*comparator)(void *, void *), void * comparisonArg){
        if (list == NULL){
        printf("Error in procedure ListSearch(): Invalid parameter list \n");
        return NULL;
    }else if (comparator == NULL)
    {
        printf("Error in procedure ListSearch(): Invalid parameter comparator() \n");
        return NULL;
    }else if (comparisonArg == NULL)
    {
        printf("Error in procedure ListSearch(): Invalid parameter comparisionArg \n");
        return NULL;
    }
    printf("Got to procedure ListSearch()\n");

    return NULL;    
}