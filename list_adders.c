/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2
*/
#include "list.h"
#include <stdio.h>
#include <string.h>

#include "list_data.h"

LIST* ListCreate(){
    static int initialized = 0;
    LIST *list = NULL;

    if (!initialized) {
        /* First time library initialization. */
        int i = 0;
        int j = 0;
        for (i = 0; i < MAX_LISTS - 1; i++) {
            /*
                For each entry, we re-interpret it as a LIST**,
                then store the address of the next free entry in that pointer.
                This gives us the effect of a very simple linked list
                of free entries stored within the entries themselves.
                This means no additional storage is necessary.
            */
            /* Reinterpret cast this LIST* as a LIST** */
            LIST **next = (LIST**)&lists[i];
            /* Dereference and store the next entry in the chain */
            *next = &lists[i+1];
        }
        for (j = 0; j < MAX_NODES - 1; j++) {
            /* Same as above. */
            NODE **next = (NODE**)&nodes[j];
            *next = &nodes[j+1];
        }
        initialized = 1;
    }

    if (freeLists == NULL) {
        /* Out of memory! */
        return NULL;
    }

    /*
     Pull a new list off the stack.
     Then set the next free entry to be the top of the stack.
    */
    list = freeLists;
    freeLists = *(LIST**)freeLists;
    memset(list, 0, sizeof(LIST));

    return list;
}


int ListAdd(LIST *list,void *item){
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }else if (item == NULL)
    {
        return -1;
    }

    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    /* Grab a new node */
    node = freeNodes;
    freeNodes = *(NODE**)freeNodes;
    memset(node, 0, sizeof(NODE));

    /* Where to insert? */
    if (list->listCount == 0) {
        /* List is empty, add to end! */
        list->currNodep = node;
        list->firstNodep = node;
        list->lastNodep = node;
    } else {
        NODE *after = list->currNodep->next;
        NODE *before = list->currNodep;
        node->prev = before;
        node->next = after;

        before->next = node;
        /*
         Semi-special case: behavior differs depending on whether
         we are adding to the end of a non-empty list, or elsewhere
         in a non-empty list.
         */
        if (after) { after->prev = node; } else { list->lastNodep = node; }

        list->currNodep = node;
    }

    list->listCount += 1;
    node->item = item;

    return 0;
}

int ListInsert(LIST *list, void *item){
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }else if (item == NULL)
    {
        return -1;
    }

    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    /* Grab a new node */
    node = freeNodes;
    freeNodes = *(NODE**)freeNodes;
    memset(node, 0, sizeof(NODE));

    /* Where to insert? */
    if (list->listCount == 0) {
        /* List is empty, insert first. */
        list->currNodep = node;
        list->firstNodep = node;
        list->lastNodep = node;
    } else {
        NODE *before = list->currNodep->prev;
        NODE *after = list->currNodep;
        node->prev = before;
        node->next = after;

        if (before) { before->next = node; } else { list->firstNodep = node; }
        after->prev = node;
    }

    list->listCount += 1;
    list->currNodep = node;
    node->item = item;

    return 0;
}

int ListAppend(LIST *list, void *item){
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }else if (item == NULL)
    {
        return -1;
    }
    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    /* Grab a new node */
    node = freeNodes;
    freeNodes = *(NODE**)freeNodes;
    memset(node, 0, sizeof(NODE));

    if (list->listCount == 0) {
        /* Empty list, just add the node simply. 8*/
        list->currNodep = node;
        list->lastNodep = node;
        list->firstNodep = node;
    } else {
        node->prev = list->lastNodep;
        node->next = NULL;

        list->lastNodep->next = node;
        list->lastNodep = node;
        list->currNodep = node;
    }

    list->listCount += 1;
    node->item = item;
    return 0;
}

int ListPrepend(LIST *list, void *item){
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }else if (item == NULL)
    {
        return -1;
    }
    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    /* Grab a new node */
    node = freeNodes;
    freeNodes = *(NODE**)freeNodes;
    memset(node, 0, sizeof(NODE));

    if (list->listCount == 0) {
        /* Empty list, just add the node simply. */
        list->currNodep = node;
        list->lastNodep = node;
        list->firstNodep = node;
    } else {
        node->next = list->firstNodep;
        list->firstNodep->prev = node;

        list->firstNodep = node;
        list->currNodep = node;
    }

    list->listCount += 1;
    node->item = item;

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

    list1->lastNodep->next = list2->firstNodep;
    list2->firstNodep->prev = list1->lastNodep;
    list1->lastNodep = list2->lastNodep;
    memset(list2,0,sizeof(LIST));
    *(LIST**)list2 = freeLists;
    freeLists = list2;
}
