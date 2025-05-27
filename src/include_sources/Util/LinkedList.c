#include "Util/LinkedList.h"
#include <stdio.h>

typedef struct LinkedList
{
    LinkedListNode *head;
    size_t size;
    size_t sizeOfItem;
} LinkedList;

typedef struct LinkedListNode
{
    void *data;
    LinkedListNode *next;
} LinkedListNode;

LinkedListNode *LinkedListNode_Create(size_t sizeOfData, const void *data)
{
    LinkedListNode *node = malloc(sizeOfData + sizeof(LinkedListNode));

    assert(node != NULL);
}

LinkedList *LinkedList_Create(size_t sizeOfItem)
{
    // todo make better error checks
    printf("%d", sizeof(LinkedList));
    printf("%d", sizeof(LinkedListNode));
    assert(sizeOfItem > 0);

    LinkedList *list = malloc(sizeof(LinkedList));

    assert(list != NULL);

    list->size = 0;
    list->sizeOfItem = sizeOfItem;

    return list;
}

void LinkedList_Destroy(LinkedList *list)
{
}

void *LinkedList_Get(LinkedList *list, size_t index)
{
}

void LinkedList_Set(LinkedList *list, size_t index, const void *item)
{
}

void LinkedList_Add(LinkedList *list, const void *item)
{
}

void LinkedList_RemoveAtIndex(LinkedList *list, size_t index)
{
}

void LinkedList_RemoveItem(LinkedList *list, const void *item)
{
}

void LinkedList_Clear(LinkedList *list)
{
}

long long LinkedList_IndexOf(LinkedList *list, const void *item)
{
}

size_t LinkedList_GetSize(LinkedList *list)
{
}