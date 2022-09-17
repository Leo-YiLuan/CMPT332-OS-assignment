#include <stdio.h>
#include "list.h" 


int listCount(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
    return list->listCount;
};

void *ListFirst(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
    return 0;
};

void *ListLast(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
};

void *ListNext(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
};

void *ListPrev(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
};

void *ListCurr(LIST *list){
    if (list == NULL){
        printf("argument list shas casue a null pointer exception");
        return -1;
    }
};

void *ListSearch(LIST *list, int (*comparator)(void *, void *), void * comparisonArg);