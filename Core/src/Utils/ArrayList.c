#include "Utils/ArrayList.h"

#include <stdlib.h>
#include <string.h>

typedef struct ArrayList
{
    void *data;
    size_t capacity;
    size_t size;
    size_t sizeOfItem;
} ArrayList;

ArrayList *ArrayList_Create(size_t sizeOfItem, size_t initialCapacity)
{
    ArrayList *list = malloc(sizeof(ArrayList));
    DebugAssert(list != NULL, "Memory allocation failed.");

    list->capacity = initialCapacity;
    list->size = 0;
    list->sizeOfItem = sizeOfItem;
    list->data = malloc(initialCapacity * sizeOfItem);
    DebugAssert(list->data != NULL, "Memory allocation failed.");

    return list;
}

void ArrayList_Destroy(ArrayList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    free(list->data);
    list->data = NULL;

    free(list);
    list = NULL;
}

void ArrayList_Resize(ArrayList *list, size_t newCapacity)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    void *newData = realloc(list->data, newCapacity * list->sizeOfItem);
    DebugAssert(newData != NULL, "Memory allocation failed.");

    list->data = newData;
    list->capacity = newCapacity;

    if (list->size > newCapacity)
    {
        list->size = newCapacity;
    }
}

void *ArrayList_Get(ArrayList *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    return (char *)(list->data) + index * list->sizeOfItem;
}

void ArrayList_Set(ArrayList *list, size_t index, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    void *targetLocation = ArrayList_Get(list, index);

    memcpy(targetLocation, item, list->sizeOfItem);
}

void ArrayList_Add(ArrayList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    if (list->size >= list->capacity)
    {
        ArrayList_Resize(list, list->capacity * ARRAY_LIST_RESIZE_MULTIPLIER);
    }

    char *targetLocation = (char *)(list->data) + list->size * list->sizeOfItem;

    memcpy(targetLocation, item, list->sizeOfItem);

    list->size++;
}

void ArrayList_RemoveAtIndex(ArrayList *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    char *targetLocation = ArrayList_Get(list, index);

    size_t bytesToMove = (list->size - index - 1) * list->sizeOfItem;

    if (bytesToMove > 0)
    {
        memmove(targetLocation, targetLocation + list->sizeOfItem, bytesToMove);
    }

    list->size--;
}

void ArrayList_RemoveItem(ArrayList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    ArrayList_RemoveAtIndex(list, ArrayList_IndexOf(list, item));
}

void ArrayList_Clear(ArrayList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    list->size = 0;
}

long long ArrayList_IndexOf(ArrayList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    for (size_t i = 0; i < list->size; i++)
    {
        char *currentItem = ArrayList_Get(list, i);

        if (memcmp(currentItem, item, list->sizeOfItem) == 0)
        {
            return i;
        }
    }

    return -1;
}

size_t ArrayList_GetSize(ArrayList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    return list->size;
}

size_t ArrayList_GetCapacity(ArrayList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    return list->capacity;
}
