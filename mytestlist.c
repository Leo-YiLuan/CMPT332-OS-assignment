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
    if (item == NULL){
        printf("Error in procedure itemFree(): "
    "Invalid parameter item \n");
        return;

    }
    printf("Got to procedure itemFree()\n");
}

int main(){
    LIST *list1 = NULL;
    NODE *test = NULL;
    int a = 42;
    int b = 71;
    int c = 44;
    int d = 4;
    list1 = ListCreate();


    ListAdd(list1, &a);
    ListAdd(list1, &b);
    ListAdd(list1, &c);
    ListAdd(list1, &d);

    /*
     Emulate setting the cursor back to the beginning f
     for testing 
    */
    list1->currNodep = list1->firstNodep;

    
    test = list1->firstNodep;
    printf("Node: %d\n", *((int*)test->item));
    test = test->next;
    printf("Node: %d\n", *((int*)test->item));
    test = test->next;
    printf("Node: %d\n", *((int*)test->item));
    test = test->next;
    printf("Node: %d\n", *((int*)test->item));
    test = list1->firstNodep;
    printf("Node: %d\n", *((int*)test->item));
        test = list1->lastNodep;
    printf("Node: %d\n", *((int*)test->item));
    return 0;
}