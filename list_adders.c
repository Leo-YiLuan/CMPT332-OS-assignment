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

/**
 *  These function just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
LIST* ListCreate(){
    printf("Got to procedure ListCreated\n");
    return NULL;
}


int ListAdd(LIST *list,void *item){
    if (list == NULL){
        printf("Error in procedure ListAdd(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListAdd(): Invalid parameter item \n");
        return -1;
    }
    printf("Got to procedure ListAdd\n");

    return 0;
}

int ListInsert(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListInsert(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListInsert(): Invalid parameter item \n");
        return -1;

    }
    printf("Got to procedure ListInsert\n");

    return 0;
}

int ListAppend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListAppend(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListAppend(): Invalid parameter item \n");
        return -1;
    }
    printf("Got to procedure ListAppend\n");

    return 0;
}

int ListPrepend(LIST *list, void *item){
    if (list == NULL){
        printf("Error in procedure ListPrepend(): Invalid parameter list \n");
        return -1;
    }else if (item == NULL)
    {
        printf("Error in procedure ListPrepend(): Invalid parameter item \n");
        return -1;
    }
    printf("Got to procedure ListPrepend\n");
    return 0;
}

void ListConcat(LIST *list1, LIST *list2){
    if (list1 == NULL){
        printf("Error in procedure ListConcat(): Invalid parameter list1 \n");
        return;
    }else if (list2 == NULL)
    {
        printf("Error in procedure ListConcat(): Invalid parameter list2 \n");
        return;
    }
    printf("Got to procedure ListConcat\n");

}
