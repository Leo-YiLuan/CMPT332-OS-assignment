#include "list.h"
#include <stdio.h>

LIST* ListCreate(){
    printf("List created here");
    return NULL;
}


int ListAdd(LIST *list,void *item){
    if (list == NULL || item == NULL){
        printf("argument list or item has a null pointer exception");
    }
    return 0;
};

int ListInsert(LIST *list, void *item){
    if (list == NULL || item == NULL)
    {
        printf("argument list or item has a null pointer exception");
    }
    
    return 0;
};

int ListAppend(LIST *list, void *item){
    if (list == NULL || item == NULL)
    {
        printf("ERROR: argument list or item has a null pointer exception");
        return -1;
    }
    return 0;
};

int ListPrepend(LIST *list, void *item){
    if (list == NULL || item == NULL)
    {
        printf("ERROR: argument list or item has a null pointer exception");
        return -1;
    }
    return 0;
};

void ListConcat(LIST *list1, LIST *list2){
    if (list1 == NULL || list2 == NULL)
    {
        printf("argument list1 or list2 has cause a null pointer exception");
        return -1;
    }

};
