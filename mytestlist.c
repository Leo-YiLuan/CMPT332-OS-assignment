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
#include <stdio.h>
#include "list.h"

int numbers[1000];

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
    if (*(int *)item1 == *(int *)item2) {
      return 1;
    }
    return 0;
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
    /*
    Hack to avoid compiler warnings since this
    function doesn't actually do anything and is
    just for testing.
    */
    *(int*)item = *(int*)item;
    return;
}

void PrintList(LIST *list) {

    int *currItem;
    int *item;
    enum LIST_STATE state = list->state;

    if (ListCount(list) == 0) {
      printf("[BEF -> END] (count 0)\n");
      return;
    }
    currItem = (int*)ListCurr(list);
    item = (int*)ListFirst(list);
    printf("[");
    if (state == BEFORE) {
      printf("*");
    }
    printf("BEF -> ");


    while (item) {
        printf("%d", *item);
        if (ListCurr(list) == currItem) { printf("*"); };
        printf(" -> ");

        item = (int*)ListNext(list);
    }
    if (state == AFTER) {
      printf("*");
    }
    printf("END] (count: %d)\n", ListCount(list));

    /* Reset the cursor. */
    if (state == BEFORE) {
        ListFirst(list);
        ListPrev(list);
    }else if (state == AFTER) {
        ListLast(list);
        ListNext(list);
    }else{
        item = ListFirst(list);
        while (item) {
            if (ListCurr(list) == currItem) {
                break;
              }
        item = ListNext(list);
      }
    }

}

int main(){
    int iter = 0;
    LIST *list = NULL;
    /* for ListConcat() testing */
    LIST *list3 = ListCreate();
    /* Test ListCreate */
    {
        LIST *list2 = ListCreate();

        list = ListCreate();
        if (list) {
            printf("ListCreate: Successfully constructed a new list.\n");
        } else {
            printf("ERROR: ListCreate() failed to create a new list!\n");
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
            printf("ERROR: ListCreate failed to return NULL after "
            "exhausting maximum allowed lists!\n");
        }
        printf("\n");
    }
    /* Test ListFree */
    {
        ListFree(list, itemFree);
        list = ListCreate();
        if (list && ListCount(list) == 0) {
            printf("ListFree: Successfully freed a list.\n");
        } else {
            printf("Error: Failed to free a list with ListFree()\n");
        }
        printf("\n");
    }

    {
        int a = 5;
        int b = 7;
        int c = 3;
        int d = 9;
        int e = 19;
        if (ListAdd(NULL, &a) == -1) {
            printf("ListAdd: Successfully received error code when "
            "passing NULL\n");
        } else {
            printf("Error: Didn't receive error from ListAdd when "
            "passing NULL\n");
        }
        printf("\n");

        /* ListCurr */
        ListAdd(list, &a);
        if (*(int*)ListCurr(list) == 5) {
            printf("Successfully added 5 to an empty list.\n");
        } else {
            printf("ERROR: Failed adding to an empty list \n");
        }
        PrintList(list);
        printf("\n");

        ListPrev(list);
        ListAdd(list, &b);
        if (*(int*)ListCurr(list) == 7) {
            printf("Successfully added 7 to a list with 1 element and current"
            " points to BEFORE.\n");
        } else {
            printf("ERROR: Failed adding to a list with one element with "
            "ListAdd() when current points to BEFORE \n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &c);
        if (*(int*)ListCurr(list) == 3) {
            printf("Successfully added 3 to a list with multiple elements, "
            "cur at last.\n");
        } else {
            printf("ERROR: Failed adding to a list with many elements with "
            "ListAdd()\n");
        }
        PrintList(list);
        printf("\n");

        ListLast(list);
        ListNext(list);
        ListAdd(list, &d);
        if (*(int*)ListCurr(list) == 9) {
            printf("Successfully added 9 to a list with multiple elements, "
            "when current points to AFTER.\n");
        } else {
            printf("ERROR: Failed adding to a list with many elements with "
            "ListAdd() when current points to AFTER\n");
        }
        PrintList(list);
        printf("\n");

        ListFirst(list);
        ListAdd(list, &e);
        if (*(int*)ListCurr(list) == 19) {
            printf("Successfully added 19 to a list with multiple elements, "
            "when current points to first\n");
        } else {
            printf("ERROR: Failed adding to a list with many elements with "
            "ListAdd() when current points to first\n");
        }
        PrintList(list);
        printf("\n");
    }

    /* ListRemove */
    {
        int *item = NULL;

        item = ListRemove(list);
        if (*item == 19 && *(int*)ListCurr(list) == 3) {
            printf("ListRemove: Successfully removed 19 from the list with "
            "many elements.\n");
        } else {
            printf("Error: Failed removing element from list of many "
            "elements with ListRemove()\n");
        }
        PrintList(list);
        printf("\n");
        ListLast(list);

        item = ListRemove(list);
        if (*item == 9 && *(int*)ListCurr(list) == 5) {
            printf("ListRemove: Successfully removed 9 from the list with "
            "many elements.\n");
        } else {
            printf("Error: Failed removing element from list of many "
            "elements with ListRemove()\n");
        }
        PrintList(list);
        printf("\n");

        ListFirst(list);
        item = ListRemove(list);
        if (*item == 7 && *(int*)ListCurr(list) == 3) {
            printf("ListRemove: Successfully removed first element from list "
            "with many elements.\n");
        } else {
            printf("Error: Failed removing first element from list of many "
            "elements with ListRemove()\n");
        }
        PrintList(list);
        printf("\n");

        ListLast(list);
        item = ListRemove(list);
        if (*item == 5 && *(int*)ListCurr(list) == 3) {
            printf("ListRemove: Successfully removed last element from list "
            "with multiple elements.\n");
        } else {
            printf("Error: Failed removing last element from list of multiple "
            "elements with ListRemove()\n");
        }
        PrintList(list);
        printf("\n");

        ListNext(list);

        item = ListRemove(list);
        if (item == NULL && ListCurr(list) == NULL) {
            printf("ListRemove: Successfully get NULL return when current "
            "points to AFTER.\n");
        } else {
            printf("Error: Failed removing only element from list with 1 "
            "element with ListRemove() when current points to AFTER\n");
        }
        PrintList(list);
        printf("\n");
        ListPrev(list);

        ListPrev(list);
        item = ListRemove(list);
        if (item == NULL && ListCurr(list) == NULL) {
            printf("ListRemove: Successfully get NULL return when current "
            "points to BEFORE.\n");
        } else {
            printf("Error: Failed removing only element from list with 1 "
            "element with ListRemove() when current points to BEFORE\n");
        }
        PrintList(list);
        printf("\n");
        ListNext(list);


        item = ListRemove(list);
        if (*item == 3 && ListCurr(list) == NULL) {
            printf("ListRemove: Successfully removed only element from list "
            "with one element.\n");
        } else {
            printf("Error: Failed removing only element from list with 1 "
            "element with ListRemove()\n");
        }
        PrintList(list);
        printf("\n");

        item = ListRemove(list);
        if (item == NULL) {
            printf("ListRemove: Successfully received NULL trying to remove "
            "from empty list.\n");
        } else {
            printf("Error: ListRemove on empty list did not return NULL\n");
        }
        PrintList(list);
        printf("\n");
    }

    /* ListInsert */
    {
        int a = 0;
        int b = -5;
        int c = 77;
        int d = 12;
        int e = 19;
        if (ListInsert(NULL, &a) == -1) {
            printf("ListInsert: Successfully received error code when passing "
            "NULL\n");
        } else {
            printf("Error: Didn't receive error from ListInsert when passing "
            "NULL\n");
        }
        printf("\n");

        ListInsert(list, &a);
        if (*(int*)ListCurr(list) == 0) {
            printf("ListInsert: Successfully inserted into empty list.\n");
        } else {
            printf("Error: Failed to ListInsert into empty list.\n");
        }
        PrintList(list);
        printf("\n");

        ListPrev(list);
        ListInsert(list, &b);
        if (*(int*)ListCurr(list) == -5) {
            printf("ListInsert: Successfully inserted into list with one "
            "element. And when current points to BEFORE\n");
        } else {
            printf("Error: Failed to ListInsert into list with one "
            "element when current points to BEFORE.\n");
        }
        PrintList(list);
        printf("\n");

        ListInsert(list, &c);
        if (*(int*)ListCurr(list) == 77) {
            printf("ListInsert: Successfully inserted into list with many "
            "elements, cur at begin.\n");
        } else {
            printf("Error: Failed to ListInsert into list with many elements, "
            "cur at begin.\n");
        }
        PrintList(list);
        printf("\n");

        ListLast(list);
        ListInsert(list, &d);
        if (*(int*)ListCurr(list) == 12) {
            printf("ListInsert: Successfully inserted into list with many "
            "elements, cur at end.\n");
        } else {
            printf("Error: Failed to ListInsert into list with many "
            "elements, cur at end.\n");
        }
        PrintList(list);
        printf("\n");

        ListLast(list);
        ListNext(list);
        ListInsert(list, &e);
        if (*(int*)ListCurr(list) == 19) {
            printf("ListInsert: Successfully inserted into list with many "
            "elements, cur at end. when current points to AFTER\n");
        } else {
            printf("Error: Failed to ListInsert into list with many "
            "elements, cur at end. when current points to AFTER\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();

    /* ListAppend */
    {
        int a = 24;
        int b = 809;
        int c = 111;
        int d = 3;
        if (ListAppend(NULL, &a) == -1) {
            printf("ListAppend: Successfully received error code when passing "
            "NULL\n");
        } else {
            printf("Error: Didn't receive error from ListAppend when passing "
            "NULL\n");
        }
        printf("\n");

        ListAppend(list, &a);
        if (*(int*)ListCurr(list) == 24) {
            printf("ListAppend: Successfully appended item to empty list.\n");
        } else {
            printf("Error: Failed to use ListAppend on empty list\n");
        }
        PrintList(list);
        printf("\n");

        ListAppend(list, &b);
        if (*(int*)ListCurr(list) == 809) {
            printf("ListAppend: Successfully appended item to list with 1 "
            "item.\n");
        } else {
            printf("Error: Failed to use ListAppend on list with 1 "
            "item.\n");
        }
        PrintList(list);
        printf("\n");

        ListAppend(list, &c);
        if (*(int*)ListCurr(list) == 111) {
            printf("ListAppend: Successfully appended item to list with "
            "multiple items, cur at end.\n");
        } else {
            printf("Error: Failed to use ListAppend on list with "
            "multiple items, cur at end.\n");
        }
        PrintList(list);
        printf("\n");

        ListFirst(list);
        ListAppend(list, &d);
        if (*(int*)ListCurr(list) == 3) {
            printf("ListAppend: Successfully appended to list with multiple "
            "items, cur not at end.\n");
        } else {
            printf("Error: Failed to use ListAppend on list with multiple "
            "items, cur not at end.\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();

   /* ListPrepend */
    {
        int a = 24;
        int b = 809;
        int c = 111;
        int d = 3;
        if (ListPrepend(NULL, &a) == -1) {
            printf("ListPrepend: Successfully received error code when "
            "passing NULL\n");
        } else {
            printf("Error: Didn't receive error from ListPrepend when "
            "passing NULL\n");
        }
        printf("\n");

        ListPrepend(list, &a);
        if (*(int*)ListCurr(list) == 24) {
            printf("ListPrepend: Successfully prepended item to empty "
            "list.\n");
        } else {
            printf("Error: Failed to use ListPrepend on empty list\n");
        }
        PrintList(list);
        printf("\n");

        ListPrepend(list, &b);
        if (*(int*)ListCurr(list) == 809) {
            printf("ListPrepend: Successfully prepended item to list with "
            "1 item.\n");
        } else {
            printf("Error: Failed to use ListPrepend on list with 1 item.\n");
        }
        PrintList(list);
        printf("\n");

        ListPrepend(list, &d);
        if (*(int*)ListCurr(list) == 3) {
            printf("ListPrepend: Successfully prepend to list with "
            "multiple items, cur at begin.\n");
        } else {
            printf("Error: Failed to use ListPrepend on list with multiple "
            "items, cur at begin.\n");
        }
        PrintList(list);
        printf("\n");

        ListLast(list);
        ListPrepend(list, &c);
        if (*(int*)ListCurr(list) == 111) {
            printf("ListPrepend: Successfully prepend to list with "
            "multiple item, cur not at begin.\n");
        } else {
            printf("Error: Failed to use ListPrepend on list with multiple "
            "items, cur not at begin.\n");
        }
        PrintList(list);
        printf("\n");
    }

    /* ListTrim */
    {
        int *item = NULL;

        item = ListTrim(list);
        if (*item == 24 && *(int*)ListCurr(list) == 809) {
            printf("ListTrim: Successfully removed last item, cur not at "
            "end.\n");
        } else {
            printf("Error: ListTrim failed to remove last item, cur not at "
            "end.\n");
        }
        PrintList(list);
        printf("\n");

        item = ListTrim(list);
        if (*item == 809 && *(int*)ListCurr(list) == 3) {
            printf("ListTrim: Successfully removed last item, cur at "
            "end.\n");
        } else {
            printf("Error: ListTrim failed to remove last item, cur at "
            "end.\n");
        }
        PrintList(list);
        printf("\n");

        item = ListTrim(list);
        if (*item == 3 && *(int*)ListCurr(list) == 111) {
            printf("ListTrim: Successfully removed last item, list with 2 "
            "elements.\n");
        } else {
            printf("Error: ListTrim failed to remove last item, list with 2 "
            "elements.\n");
        }
        PrintList(list);
        printf("\n");

        item = ListTrim(list);
        if (*item == 111 && ListCurr(list) == NULL) {
            printf("ListTrim: Successfully trimmed list with only 1 "
            "element.\n");
        } else {
            printf("Error: ListTrim failed to trim list with only 1 "
            "element.\n");
        }
        PrintList(list);
        printf("\n");

        item = ListTrim(list);
        if (item == NULL) {
            printf("ListTrim: Successfully received NULL from empty list.\n");
        } else {
            printf("Error: ListTrim didn't return NULL on empty list.\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();

    /* ListCount */
    {
        int a = 2;
        int b = 7;
        int c = 98;
        int d = -44;
        int e = 42;
        if (ListCount(list) == 0) {
            printf("ListCount: Correctly received count for empty list.\n");
        } else {
            printf("Error: Did not receive count 0 for empty list.\n");
        }
        printf("\n");

        ListAdd(list, &a);
        if (ListCount(list) == 1) {
            printf("ListCount: Correctly received count for list with 1 "
            "element\n");
        } else {
            printf("Error: Received wrong count for list with 1 element.\n");
        }
        printf("\n");

        ListAdd(list, &b);
        ListPrepend(list, &c);
        ListAppend(list, &d);
        ListInsert(list, &e);
        if (ListCount(list) == 5) {
            printf("ListCount: Correctly received count for list with many "
            "elements\n");
        } else {
            printf("Error: Received wrong count for list with many "
            "elements.\n");
        }
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();
    /* test ListFirst */
    {
        int *item = NULL;
        int a = 0;
        int b = 1;
        int c = 7;

        item = ListFirst(list);
        if (item == NULL) {
            printf("ListFirst: Correctly received NULL from empty list.\n");
        } else {
            printf("Error: Failed to receive NULL calling ListFirst on empty "
            "list.\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &a);
        item = ListFirst(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListFirst: Correctly received first item 0 from list with "
            "1 element.\n");
        } else {
            printf("Error: Failed calling ListFirst on list with 1 "
            "element.\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &b);
        item = ListFirst(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListFirst: Correctly received first item 0 from list with "
            "multiple elements.\n");
        } else {
            printf("Error: Failed calling ListFirst on list with multiple "
            "elements.\n");
        }
        PrintList(list);
        printf("\n");

        ListAppend(list, &c);
        item = ListFirst(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListFirst: Correctly get first item 0 from list with "
            "multiple item, \ncur not at begin.\n");
        } else {
            printf("Error: Failed calling ListFirst on list with multiple "
            "elements, cur not at begin.\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();
    /* Test ListLast */
    {
        int *item = NULL;
        int a = 0;
        int b = 1;
        int c = 7;

        item = ListLast(list);
        if (item == NULL) {
            printf("ListLast: Correctly received NULL from empty list.\n");
        } else {
            printf("Error: Failed to receive NULL calling ListLast on empty "
            "list.\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &a);
        item = ListLast(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListLast: Correctly received last item 0 from list with "
            "1 element.\n");
        } else {
            printf("Error: Failed calling ListFirst on list with 1 "
            "element.\n");
        }
        PrintList(list);
        printf("\n");

        ListInsert(list, &b);
        item = ListLast(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListLast: Correctly received last item 0 from list with "
            "multiple elements.\n");
        } else {
            printf("Error: Failed calling ListLast on list with multiple "
            "elements.\n");
        }
        PrintList(list);
        printf("\n");

        ListPrepend(list, &c);
        item = ListLast(list);
        if (*item == 0 && *(int*)ListCurr(list) == 0) {
            printf("ListLast: Correctly received last item 0 from list with "
            "multiple elements, \ncur not at begin.\n");
        } else {
            printf("Error: Failed calling ListLast on list with multiple "
            "elements, cur not at begin.\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();
    /* Test ListNext */
    {
        int *item = NULL;
        int a = 55;
        int b = 6;
        int c = 9;

        item = ListNext(list);
        if (item == NULL) {
            printf("ListNext: Successfully received NULL from an empty "
            "list.\n");
        } else {
            printf("Error: Didn't receive NULL from empty list calling "
            "ListNext\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &a);
        ListPrev(list);
        item = ListNext(list);
        if (*item == 55 && *(int *)ListCurr(list) == 55) {
            printf("ListNext: Successfully received first item when current"
            " pointer BEFORE the first node.\n");
        } else {
         printf("Error: Didn't get the first node when at the BEFORE position "
            "calling ListNext\n");
        }
        PrintList(list);
        printf("\n");

        item = ListNext(list);
        if (item == NULL && ListCurr(list) == NULL) {
            printf("ListNext: Successfully received NULL from list with 1 "
            "element.\n");
        } else {
            printf("Error: Didn't receive NULL from list with 1 element "
            "calling ListNext\n");
        }
        PrintList(list);
        printf("\n");

        ListFirst(list);
        ListAdd(list, &b);

        ListFirst(list);
        item = ListNext(list);
        if (*item == 6 && *(int*)ListCurr(list) == 6) {
            printf("ListNext: Successfully received correct element from "
            "list with 2 elements, \ncur at begin.\n");
        } else {
            printf("Error: Didn't receive correct from list with 2 "
            "elements, cur at begin calling ListNext\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &c);
        ListFirst(list);
        ListNext(list);
        item = ListNext(list);
        if (*item == 9 && *(int*)ListCurr(list) == 9) {
            printf("ListNext: Successfully received correct element from "
            "middle of list.\n");
        } else {
            printf("Error: Didn't receive correct item from middle of list "
            "calling ListNext\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();
    /* test ListPrev */
    {
        int *item = NULL;
        int a = 55;
        int b = 6;
        int c = 9;
        PrintList(list);

        if (item == NULL) {
            printf("ListPrev: Successfully received NULL from an empty "
            "list.\n");
        } else {
            printf("Error: Didn't receive NULL from empty list calling "
            "ListPrev\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &a);
        ListNext(list);
        item = ListPrev(list);
        if (*item == 55 && *(int *)ListCurr(list) == 55) {
          printf("ListPrev: Successfully received last item when current "
          "pointer AFTER the last node.\n");
        } else {
          printf("Error: Didn't get the last node when at the AFTER position "
          "calling ListPrev\n");
        }
        PrintList(list);
        printf("\n");


        item = ListPrev(list);
        if (item == NULL && ListCurr(list) == NULL) {
            printf("ListPrev: Successfully received NULL from list with "
            "1 element.\n");
        } else {
            printf("Error: Didn't receive NULL from list with 1 element "
            "calling ListPrev\n");
        }
        PrintList(list);
        printf("\n");


        ListLast(list);
        ListAdd(list, &b);
        item = ListPrev(list);
        if (*item == 55 && *(int*)ListCurr(list) == 55) {
            printf("ListPrev: Successfully received correct element from "
            "list with 2 elements, \ncur at end.\n");
        } else {
            printf("Error: Didn't receive correct from list with 2 "
            "elements, cur at end calling ListPrev\n");
        }
        PrintList(list);
        printf("\n");

        ListPrepend(list, &c);
        ListLast(list);
        ListPrev(list);
        item = ListPrev(list);
        if (*item == 9 && *(int*)ListCurr(list) == 9) {
            printf("ListPrev: Successfully received correct element from "
            "middle of list.\n");
        } else {
            printf("Error: Didn't receive correct item from middle of list "
            "calling ListPrev\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();

    /* ListCurr */
    {
        int *item = NULL;
        int a = 1;
        int b = 0;
        int c = 42;

        item = ListCurr(list);
        if (item == NULL) {
            printf("ListCurr: Correctly received NULL from empty list.\n");
        } else {
            printf("Error: Failed to receive NULL from empty list calling "
            "ListCurr\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &a);
        item = ListCurr(list);
        if (*item == 1) {
            printf("ListCurr: Correctly received element from list with "
            "only 1 item.\n");
        } else {
            printf("Error: Failed to receive corret element from list "
            "with 1 item.\n");
        }
        PrintList(list);
        printf("\n");

        ListAdd(list, &b);
        ListAdd(list, &c);
        item = ListCurr(list);
        if (*item == 42) {
            printf("ListCurr: Correctly received element from list with "
            "many items.\n");
        } else {
            printf("Error: Failed to receive correct element from list with "
            "many items.\n");
        }
        PrintList(list);
        printf("\n");
    }

    ListFree(list, itemFree);
    list = ListCreate();

    /* ListSearch */
    {
        int find = 42;
        int *found = NULL;
        int a = 7;
        int b = 0;
        int c = 12;
        int d = 42;
        int e = 90;

        found = (int*)ListSearch(list, &comparator, &find);
        if (found == NULL) {
            printf("ListSearch: Correctly searched an empty list.\n");
        } else {
            printf("Unexpected Behavior calling ListSearch on empty list.\n");
        }
        printf("\n");

        find = 7;
        ListAdd(list, &a);
        found = ListSearch(list, &comparator, &find);
        if (*found == 7 && *(int*)ListCurr(list)==7) {
            printf("ListSearch: Correctly found element in list with 1 "
            "item.\n");
        } else {
            printf("Error: Failed to search list with 1 item\n");
        }
        printf("\n");

        find = 42;
        found = ListSearch(list, &comparator, &find);

        if (found == NULL && ListCurr(list) == NULL) {
            printf("ListSearch: Correctly failed to find nonexistent "
            "element in list with 1 item.\n");
        } else {
            printf("Error: Failed searching list with 1 item\n");
        }
        printf("\n");
        ListAdd(list, &b);
        ListPrepend(list, &c);
        ListAdd(list, &d);
        ListAppend(list, &e);

        ListLast(list);
        found = ListSearch(list, &comparator, &find);
        if (found == NULL && ListCurr(list)==NULL) {
            printf("ListSearch: Correctly failed to find element that is "
            "before cursor.\n");
        } else {
            printf("Error: Failed searching list when element to find is "
            "before cursor\n");
        }
        printf("\n");

        ListFirst(list);
        found = ListSearch(list, &comparator, &find);
        if (*found == 42 && *(int*)ListCurr(list)== 42) {
            printf("ListSearch: Correctly found element in list with "
            "many items\n");
        } else {
            printf("Error: Failed searching list with many items\n");
        }
        printf("\n");
    }
    /* ListConcat() */
    {
      int a = 10;
      int b = 12;

      /* test case that both lists are not empty */
      int expectListCount;
      int expectCurrItem = 42;
      int expectLastItem = 10;

      printf("\n=====First Test Case of ListConcat()=====\n\n");

      ListAdd(list3,&a);
      expectListCount = ListCount(list) + ListCount(list3);
      printf("First list: \n");
      PrintList(list);
      printf("Second list: \n");
      PrintList(list3);

      ListConcat(list,list3);
      if (expectListCount == ListCount(list)
          && *(int *)list->lastNodep->item == expectLastItem
          && *(int*)list->currNodep->item == expectCurrItem
          && ListCount(list3)==0){
          printf("\nThe count and last node pointer of Concat List is correct,"
           " when both list are not empty, also check correctness by "
           "observation \n\n" );
          printf("First list after concat: \n" );
          PrintList(list);
      }else{
        printf("Failure of concat two list that all have items, \n"
        "expect Current item: %d, get: %d \n"
        "expect Last item: %d, get: %d \n"
        "expect List Count: %d, get: %d\n"
        , expectCurrItem, *(int*)list->currNodep->item
        , expectLastItem, *(int *)list->lastNodep->item
        , expectListCount, ListCount(list));
      }

      printf("\n=====Next Test Case=====\n");
      /* test case that only second list is empty */

      ListRemove(list3);
      expectListCount = ListCount(list) + ListCount(list3);

      expectCurrItem = 42;
      expectLastItem = 10;
      printf("First list: \n");
      PrintList(list);
      printf("Second list: \n");
      PrintList(list3);

      ListConcat(list,list3);
      if (expectListCount == ListCount(list)
          && *(int *)list->lastNodep->item == expectLastItem
          && *(int*)list->currNodep->item == expectCurrItem
          && ListCount(list3)==0){
          printf("\nThe count and last node pointer of Concat List is correct,"
           " when only first list have item, also check correctness by"
           " observation \n\n" );
          printf("First list after concat: \n" );
          PrintList(list);
      }else{
      printf("Failure of concat two list that only first list is not empty,\n"
        "expect Current item: %d, get: %d \n"
        "expect Last item: %d, get: %d \n"
        "expect List Count: %d, get: %d\n"
        , expectCurrItem, *(int*)list->currNodep->item
        , expectLastItem, *(int *)list->lastNodep->item
        , expectListCount, ListCount(list));
      }

      printf("\n=====Next Test Case=====\n");
      /* test case that only first list is empty */

      ListFree(list,itemFree);
      list = ListCreate();
      ListAdd(list3,&a);
      ListAdd(list3,&b);
      ListPrev(list3);
      expectListCount = ListCount(list) + ListCount(list3);

      expectCurrItem = 10;
      expectLastItem = 12;
      printf("First list: \n");
      PrintList(list);
      printf("Second list: \n");
      PrintList(list3);
      /* In this test case first list is empty, so the current pointer
      after concat will set to the current pointer of second list */
      ListConcat(list,list3);
      if (expectListCount == ListCount(list)
          && *(int *)list->lastNodep->item == expectLastItem
          && *(int*)list->currNodep->item == expectCurrItem
          && ListCount(list3)==0){
          printf("\nThe count and last node pointer of Concat List is correct,"
           " when onlt second list is not empty, also check correctness by"
           " observation \n\n" );
          printf("First list after concat: \n" );
          PrintList(list);
      }else{
          printf("Failure of concat two list that only second list is not "
          "empty, \n"
          "expect Current item: %d, get: %d \n"
          "expect Last item: %d, get: %d \n"
          "expect List Count: %d, get: %d\n"
          , expectCurrItem, *(int*)list->currNodep->item
          , expectLastItem, *(int *)list->lastNodep->item
          , expectListCount, ListCount(list));
      }

        printf("\n=====Next Test Case=====\n");
        /* concat two empty list */
        ListFree(list,itemFree);
        ListFree(list3,itemFree);
        list = ListCreate();
        list3 = ListCreate();
        expectListCount = ListCount(list) + ListCount(list3);

        printf("First list: \n");
        PrintList(list);
        printf("Second list: \n");
        PrintList(list3);
        /* In this test case first list is empty, so the current pointer
        after concat will set to the current pointer of second list */
        ListConcat(list,list3);
        if (expectListCount == ListCount(list) && ListCount(list3)==0){
         printf("\nThe count is correct when both lists are empty,"
              " also check correctness by observation \n\n" );
            printf("First list after concat: \n" );
            PrintList(list);
        }else{
            printf("Failure of concat two list that both are empty,\n"
            "expect number of item in list: %d, get: %d"
            , expectListCount, ListCount(list));
        }

      printf("\n++++++++ Function test is over ++++++++\n");


    }

    /* Test exhausting all allocations */
    {
        int i = 0;
        int max = 1001;
        ListFree(list, itemFree);
        ListFree(list3,itemFree);
        list = ListCreate(list);

        for (i = 0; i < 1000; i++) {
            numbers[i] = i;
            if (ListAdd(list, &numbers[i]) == -1) {
                fprintf(stderr, "ERROR: Filling a list with every available"
                        " node failed! %d\n", i);
                break;
            }
        }

        if (ListAdd(list, &max) == -1) {
            printf("Successfully received error when trying to add node "
            "after exhausting all nodes.\n");
        } else {
            printf("ERROR: Didn't receive -1 when trying to allocate "
            "more nodes than exist!\n");
        }
    }

    return 0;
}
