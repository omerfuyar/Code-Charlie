#include "Utils/ListArray.h"

#pragma region Source Only

typedef struct ListArray
{
    void *data;
    size_t capacity;
    size_t size;
    size_t sizeOfItem;
} ListArray;

#pragma endregion

ListArray *ListArray_Create(size_t sizeOfItem, size_t initialCapacity)
{
    ListArray *list = malloc(sizeof(ListArray));
    DebugAssert(list != NULL, "Memory allocation failed.");

    list->capacity = initialCapacity;
    list->size = 0;
    list->sizeOfItem = sizeOfItem;
    list->data = malloc(initialCapacity * sizeOfItem);
    DebugAssert(list->data != NULL, "Memory allocation failed.");

    return list;
}

void ListArray_Destroy(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    free(list->data);
    list->data = NULL;

    free(list);
    list = NULL;
}

void ListArray_Resize(ListArray *list, size_t newCapacity)
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

void *ListArray_Get(ListArray *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    return (char *)(list->data) + index * list->sizeOfItem;
}

void ListArray_Set(ListArray *list, size_t index, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    void *targetLocation = ListArray_Get(list, index);

    memcpy(targetLocation, item, list->sizeOfItem);
}

void ListArray_Add(ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    if (list->size >= list->capacity)
    {
        DebugWarning("ListArray is full. Resizing it from %du to %du.", list->capacity, list->capacity * ARRAY_LIST_RESIZE_MULTIPLIER);
        ListArray_Resize(list, list->capacity * ARRAY_LIST_RESIZE_MULTIPLIER);
    }

    char *targetLocation = (char *)(list->data) + list->size * list->sizeOfItem;

    memcpy(targetLocation, item, list->sizeOfItem);

    list->size++;
}

void ListArray_RemoveAtIndex(ListArray *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    char *targetLocation = ListArray_Get(list, index);

    size_t bytesToMove = (list->size - index - 1) * list->sizeOfItem;

    if (bytesToMove > 0)
    {
        memmove(targetLocation, targetLocation + list->sizeOfItem, bytesToMove);
    }

    list->size--;
}

void ListArray_RemoveItem(ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    ListArray_RemoveAtIndex(list, ListArray_IndexOf(list, item));
}

void *ListArray_Pop(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    if (list->size == 0)
    {
        DebugWarning("ListArray is empty. Cannot pop an item. Returning NULL.");
        return NULL;
    }

    void *item = ListArray_Get(list, list->size - 1);
    ListArray_RemoveAtIndex(list, list->size - 1);

    return item;
}

void ListArray_Clear(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    list->size = 0;
}

long long ListArray_IndexOf(ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    for (size_t i = 0; i < list->size; i++)
    {
        char *currentItem = ListArray_Get(list, i);

        if (memcmp(currentItem, item, list->sizeOfItem) == 0)
        {
            return i;
        }
    }

    DebugWarning("Item not found in ListArray. Returning -1.");
    return -1;
}

size_t ListArray_GetSize(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    return list->size;
}

size_t ListArray_GetCapacity(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    return list->capacity;
}
