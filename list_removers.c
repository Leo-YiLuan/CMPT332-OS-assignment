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

void *ListRemove(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list %s \n", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListRemove(): Invalid parameter item %s \n", item);
    }
    
    return 0;
};

void ListFree(LIST *list, void (*itemFree)(void*)){
    if (list == NULL){
        printf("Error in procedure ListFree(): Invalid parameter list %s \n", list);
        return -1;
    }else if (itemFree == NULL)
    {
        printf("Error in procedure ListFree(): Invalid parameter itemFree() %s \n", itemFree);
        return -1;
    }
    
    return 0;
};

void *ListTrim(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListTrim(): Invalid parameter list %s \n", list);
        return -1;
    }
    return 0;
};
