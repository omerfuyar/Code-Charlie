#include "Util/ArrayList.h"

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// todo make better error checks

typedef struct ArrayList
{
    void *data;
    size_t capacity;
    size_t size;
    size_t sizeOfItem;
} ArrayList;

ArrayList *ArrayList_Create(size_t sizeOfItem, size_t initialCapacity)
{
    assert(initialCapacity > 0);
    assert(sizeOfItem > 0);

    ArrayList *list = malloc(sizeof(ArrayList));

    assert(list != NULL);

    list->capacity = initialCapacity;
    list->size = 0;
    list->sizeOfItem = sizeOfItem;
    list->data = malloc(initialCapacity * sizeOfItem);

    assert(list->data != NULL);

    return list;
}

void ArrayList_Destroy(ArrayList *list)
{
    assert(list != NULL);

    free(list->data);
    list->data = NULL;

    free(list);
    list = NULL;
}

void ArrayList_Resize(ArrayList *list, size_t newCapacity)
{
    assert(list != NULL);
    assert(newCapacity > 0);

    void *newData = realloc(list->data, newCapacity * list->sizeOfItem);
    assert(newData != NULL);

    list->data = newData;
    list->capacity = newCapacity;

    if (list->size > newCapacity)
    {
        list->size = newCapacity;
    }
}

void *ArrayList_Get(ArrayList *list, size_t index)
{
    assert(list != NULL);
    assert(index < list->size);

    return (char *)(list->data) + index * list->sizeOfItem;
}

void ArrayList_Set(ArrayList *list, size_t index, const void *item)
{
    assert(list != NULL);
    assert(index < list->size);

    void *targetLocation = ArrayList_Get(list, index);

    memcpy(targetLocation, item, list->sizeOfItem);
}

void ArrayList_Add(ArrayList *list, const void *item)
{
    assert(list != NULL);

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
    assert(list != NULL);
    assert(index < list->size);

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
    assert(list != NULL);

    ArrayList_RemoveAtIndex(list, ArrayList_IndexOf(list, item));
}

void ArrayList_Clear(ArrayList *list)
{
    list->size = 0;
}

long long ArrayList_IndexOf(ArrayList *list, const void *item)
{
    assert(list != NULL);

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
    return list->size;
}

size_t ArrayList_GetCapacity(ArrayList *list)
{
    return list->capacity;
}
