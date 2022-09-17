#include "list.h"
#include <stdio.h>

LIST* ListCreate(){
    printf("List created here");
    return NULL;
}


int ListAdd(LIST *list,void *item){
    if (list == NULL){
        printf("Error in procedure ListAdd(): Invalid parameter list %s", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListAdd(): Invalid parameter item %s", item);
        return -1;
    }
    
    return 0;
};

int ListInsert(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListInsert(): Invalid parameter list %s", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListInsert(): Invalid parameter item %s", item);
        return -1;

    }
    
    return 0;
};

int ListAppend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListAppend(): Invalid parameter list %s", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListAppend(): Invalid parameter item %s", item);
        return -1;
    }
    return 0;
};

int ListPrepend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListPrepend(): Invalid parameter list %s", list);
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListPrepend(): Invalid parameter item %s", item);
        return -1;
    }
    return 0;
};

void ListConcat(LIST *list1, LIST *list2){
    if (list1 == NULL){
        printf("Error in procedure ListConcat(): Invalid parameter list1 %s", list1);
        return -1;
    }else if (list2 == NULL)
    {
        printf("Error in procedure ListConcat(): Invalid parameter list2 %s", list2);
        return -1;
    }

};
