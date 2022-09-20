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

#include "list_data.h"

/**
 *  These functions just test parameters, no functional implemented
 *  All the comments or designs are in list.h and partC.design.txt
 */
void *ListRemove(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListRemove(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListRemove()\n"); 
    return NULL;
}

void ListFree(LIST *list, void (*itemFree)(void*)){
    LIST_ENTRY *entryToFree = NULL;
    if (list == NULL){
        printf("Error in procedure ListFree(): Invalid parameter list \n");
        return;
   }else if (itemFree == NULL)
    {
        printf("Error in procedure ListFree(): "
        "Invalid parameter itemFree() \n");
        return;
    }

    /* TODO: Call the provided function pointer to free everything. */

    /* Add the list we were given to the beginning of our stack. */
    entryToFree = (LIST_ENTRY*)((char*)list - sizeof(LIST*));
    entryToFree->next = freeLists->next;
    freeLists = entryToFree;
}

void *ListTrim(LIST *list){
    if (list == NULL){
        printf("Error in procedure ListTrim(): Invalid parameter list \n");
        return NULL;
    }
    printf("Got to procedure ListTrim()\n");
    return NULL;

}
