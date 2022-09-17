#ifndef __LIST_H__
#define __LIST_H__

typedef struct _node NODE;
struct NODE {
	void *item;
	NODE *next;
};

typedef struct _list
{
    NODE *currNodep;
    NODE *firstNodep;
    NODE *lastNodep;
    int listCount;
    int listSize;
}LIST;




LIST *ListCreate();

int listCount();

void *ListFirst(LIST *list);

void *ListLast(LIST *list);

void *ListNext(LIST *list);

void *ListPrev(LIST *list);

void *ListCurr(LIST *list);

int ListAdd(LIST *list,void *item);

int ListInsert(LIST *list, void *item);

int ListAppend(LIST *list, void *item);

int ListPrepend(LIST *list, void *item);

void *ListRemove(LIST *list, void *item);

void ListConcat(LIST *list, LIST *list2);

void ListFree(LIST *list, void (*itemFree)(void*));

void *ListTrim(LIST *list);

void *ListSearch(LIST *list, int (*comparator)(void *, void *), void * comparisonArg);

#endif