#include "list.h"
#include <stdio.h>

void *ListRemove(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list %s", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListRemove(): Invalid parameter item %s", item);
    }
    
    return 0;
};

void ListFree(LIST *list, void (*itemFree)(void*)){
    if (list == NULL){
        printf("Error in procedure ListFree(): Invalid parameter list %s", list);
        return -1;
    }else if (itemFree == NULL)
    {
        printf("Error in procedure ListFree(): Invalid parameter itemFree() %s", itemFree);
        return -1;
    }
    
    return 0;
};

void *ListTrim(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListTrim(): Invalid parameter list %s", list);
        return -1;
    }
    return 0;
};
