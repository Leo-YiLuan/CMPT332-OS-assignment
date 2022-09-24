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
#include <stdio.h>
#include "list.h"

/**
 * compare two items, check if they match
 * 
 * Parameters: 
 *      item1: pointer to an item
 *      item2: pointer to an item
 * Return: 1 on success, 0 on failure, -1 means error
 */
int comparator(void *item1, void *item2){
    if (item1==NULL||item2==NULL)
    {
        printf("Error in procedure comparator(): "
    "Invalid parameter item1 or item2 \n");

        return -1;
    }
    printf("Got to procedure comparator()\n");
    return 1;
}

/**
 * free a space of a pointer points to an item
 * 
 * Parameters: 
 *      item: pointer to an item
 * 
 * Return: none
 */
void itemFree(void *item){
    return;
}

void PrintList(LIST *list) {
    int *currItem = (int*)ListCurr(list);
    int *item = (int*)ListFirst(list);

    printf("[");

    while (item) {
        printf("%d", *item);
        if (ListCurr(list) == currItem) { printf("*"); };
        printf(" -> ");

        item = (int*)ListNext(list);
    }

    printf("END]\n");

    /* Reset the cursor. */
    item = ListFirst(list);
    while (item) {
        if (ListCurr(list) == currItem) {
            break;
        }
        item = ListNext(list);
    }
}

int main(){
    int iter = 0;

    /****** TEST ListCreate ******/
    LIST *list1 = ListCreate();
    LIST *list2 = NULL;
    if (list1) { 
        printf("ListCreate: Successfully received a new valid list.\n");
    } else {
        fprintf(stderr, "ERROR: ListCreate failed to create a valid list!\n");
    }
    printf("\n");
    /* Allocate up all our other lists... */
    for (iter = 1; iter < 10; iter++) {
        ListCreate();
    }
    list2 = ListCreate();
    if (!list2) {
        printf("ListCreate: Successfully received NULL after reaching "
       "max allocated lists.\n");
    } else {
        fprintf(stderr, "ERROR: ListCreate failed to return NULL after "
        "exhausting maximum allowed lists!\n");
    }
    printf("\n");

    /****** TEST ListAdd ******/
    {
        LIST *list3 = NULL;
        int first = 5;
        int second = 16;
        int third = 27;
        int fourth = 42;
        if (ListAdd(list3, &first) == -1) {
            printf("ListAdd: Successfully received error -1 after "
            "passing a NULL list parameter.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListAdd after "
            "passing a NULL list parameter!\n");
        }
        printf("\n");
        if (ListAdd(list1, NULL) == -1) {
            printf("ListAdd: Successfully received error -1 after "
            "passing a NULL item.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListAdd after "
            "passing a NULL item!\n");
        }
        printf("\n");

        printf("ListAdd: Add 5 to empty list: \n");
        ListAdd(list1, &first);
        PrintList(list1);
        printf("\n");

        printf("ListAdd: Add 16 to list with 1 element: \n");
        ListAdd(list1, &second);
        PrintList(list1);
        printf("\n");

        printf("ListAdd: Add 27 to list with multiple elems, cur at end: \n");
        ListAdd(list1, &third);
        PrintList(list1);
        printf("\n");

        printf("ListAdd: Add 42 to the middle of a list with multiple "
               "elements: \n");
        ListPrev(list1);
        ListAdd(list1, &fourth);
        PrintList(list1);
        printf("\n");
    }

    {
        int next = 0;
        int first = 512;
        int second = 1;
        int third = 22;
        int fourth = 5000;
        if (ListInsert(NULL, &next) == -1) {
            printf("ListInsert: Successfully received error -1 after "
            "passing a NULL list parameter.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListInsert after "
            "passing a NULL list parameter!\n");
        }
        printf("\n");
        if (ListAdd(list1, NULL) == -1) {
            printf("ListInsert: Successfully received error -1 after "
            "passing a NULL item.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListInsert after "
            "passing a NULL item!\n");
        }
        printf("\n");
        
        printf("ListInsert: Insert 0 to the middle of a list with multiple elems:\n");
        ListInsert(list1, &next);
        PrintList(list1);
        printf("\n");

        ListFree(list1, itemFree);
        list1 = ListCreate();

        printf("ListInsert: Insert 512 to empty list:\n");
        ListInsert(list1, &first);
        PrintList(list1);
        printf("\n");

        printf("ListInsert: Insert 1 to a list with one element:\n");
        ListInsert(list1, &second);
        PrintList(list1);
        printf("\n");

        printf("ListInsert: Insert 22 to a list with multiple elements, cur at begin:\n");
        ListInsert(list1, &third);
        PrintList(list1);
        printf("\n");

        printf("ListInsert: insert 5000 to a list with multiple elements in the middle:\n");
        ListNext(list1);
        ListInsert(list1, &fourth);
        PrintList(list1);
        printf("\n");
    }

    {
        int first = 2;
        if (ListAppend(NULL, &first) == -1) {
            printf("ListInsert: Successfully received error -1 after "
            "passing a NULL list parameter.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListInsert after "
            "passing a NULL list parameter!\n");
        }
        printf("\n");
        if (ListAdd(list1, NULL) == -1) {
            printf("ListInsert: Successfully received error -1 after "
            "passing a NULL item.\n");
        } else {
            fprintf(stderr, "Failed to receive error -1 from ListInsert after "
            "passing a NULL item!\n");
        }
        printf("\n");
    }

    return 0;
}