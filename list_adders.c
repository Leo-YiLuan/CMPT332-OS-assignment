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

/* Static allocation pool */
LIST lists[MAX_LISTS];
LIST *freeLists = &lists[0];

NODE nodes[MAX_NODES];
NODE *freeNodes = &nodes[0];

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
    list->state = NORMAL;

    return list;
}


int ListAdd(LIST *list,void *item){
    NODE *node = NULL;
    if (list == NULL){
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
    }
    /* current node befor the first node */
    else if (list->state == BEFORE) {
        node->next = list->firstNodep;
        list->firstNodep->prev = node;
        list->firstNodep = node;
        list->currNodep = node;
        node->item = item;

    /* current node after the last node */
    }else if (list->state == AFTER) {
        node->prev = list->lastNodep;
        node->next = NULL;

        list->lastNodep->next = node;
        list->lastNodep = node;
        list->currNodep = node;
      }
      else {
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
    list->state = NORMAL;
    list->listCount += 1;
    node->item = item;

    return 0;
}

int ListInsert(LIST *list, void *item){
    NODE *node = NULL;
    if (list == NULL){
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
    }
    /* current node befor the first node */
    else if (list->state == BEFORE) {
        node->next = list->firstNodep;
        list->firstNodep->prev = node;
        list->firstNodep = node;
        list->currNodep = node;
        node->item = item;

    /* current node after the last node */
    }else if (list->state == AFTER) {
        node->prev = list->lastNodep;
        node->next = NULL;

        list->lastNodep->next = node;
        list->lastNodep = node;
        list->currNodep = node;
      }
      else {
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
    list->state = NORMAL;
    return 0;
}

int ListAppend(LIST *list, void *item){
    NODE *node = NULL;
    if (list == NULL){
        return -1;
    }
    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    list->state = NORMAL;
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
    }
    if (freeNodes == NULL) {
        /* Out of memory! */
        return -1;
    }
    list->state = NORMAL;
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

    /* when list2 is empty just free list2*/
    if (list2->listCount == 0) {
      memset(list2,0,sizeof(LIST));
      *(LIST**)list2 = freeLists;
      freeLists = list2;

    /* when list1 is empty copy list2 to list1, free list2 */
    }else if (list1->listCount == 0) {
      list1->firstNodep = list2->firstNodep;
      list1->lastNodep = list2->lastNodep;
      /* When list1 is empty, it's current pointer will be NULL,
        in that case, I made list2's current pointer as the
        concated list's current pointer

        make concated list exactly same as list2
        */
      list1->currNodep = list2->currNodep;
      list1->listCount = list2->listCount;
      list1->state = list2->state;
      memset(list2,0,sizeof(LIST));
      *(LIST**)list2 = freeLists;
      freeLists = list2;

    /* when both list1 list2 are not empty, free list2 */
    }else{
      list1->lastNodep->next = list2->firstNodep;
      list2->firstNodep->prev = list1->lastNodep;
      list1->lastNodep = list2->lastNodep;
      list1->listCount += list2->listCount;

      memset(list2,0,sizeof(LIST));
      *(LIST**)list2 = freeLists;
      freeLists = list2;
    }
}
