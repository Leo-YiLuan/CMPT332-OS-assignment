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


#ifndef __LIST_H__
#define __LIST_H__

typedef struct _node NODE;
struct NODE {
	void *item;
	NODE *next;
    NODE *prev;
    int nodeSize;
};

typedef struct _list
{
    NODE *currNodep;
    NODE *firstNodep;
    NODE *lastNodep;
    int listCount;
    int listSize;
}LIST;

/*
 * Create an empty list
 * return: The address of the list 
 */
LIST *ListCreate();

/*
 * get the number of nodes in the list
 * return: The number of nodes in the list if success. -1 if faliure
 */
int listCount(LIST *list);

/*
 * get the first node in the list
 * return: The number of nodes in the list if success. -1 if faliure
 */
void *ListFirst(LIST *list);

void *ListLast(LIST *list);

void *ListNext(LIST *list);

void *ListPrev(LIST *list);

void *ListCurr(LIST *list);

int ListAdd(LIST *list,void *item);

int ListInsert(LIST *list, void *item);

int ListAppend(LIST *list, void *item);

int ListPrepend(LIST *list, void *item);

void *ListRemove(LIST *lists);

void ListConcat(LIST *list, LIST *list2);

void ListFree(LIST *list, void (*itemFree)(void*));

void *ListTrim(LIST *list);

void *ListSearch(LIST *list, int (*comparator)(void *, void *), void * comparisonArg);

#endif