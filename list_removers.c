#include "list.h"
#include <stdio.h>

void *ListRemove(LIST *list, void *item){
    if (list == NULL || item == NULL){
        printf("argument list or item has casue a null pointer exception");
        return -1;
    }
    return 0;
};

void ListFree(LIST *list, void (*itemFree)(void*)){
    if (list == NULL || itemFree==NULL){
        printf("argument list or item has casue a null pointer exception");
        return -1;
    }
    return 0;
};

void *ListTrim(LIST *list){
    if (list == NULL){
        printf("argument list has casue a null pointer exception");
        return -1;
    }
    return 0;
};
