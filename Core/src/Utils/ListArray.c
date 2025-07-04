#include "Utils/ListArray.h"

// todo add cross platform support

#pragma region Source Only

typedef struct ListArray
{
    void *data;
    size_t capacity;
    size_t size;
    size_t sizeOfItem;
} ListArray;

#pragma endregion Source Only

ListArray *ListArray_Create(size_t sizeOfItem, size_t initialCapacity)
{
    ListArray *list = (ListArray *)malloc(sizeof(ListArray));
    DebugAssert(list != NULL, "Memory allocation failed for ListArray.");

    list->capacity = initialCapacity;
    list->size = 0;
    list->sizeOfItem = sizeOfItem;
    list->data = (void *)malloc(initialCapacity * sizeOfItem);
    DebugAssert(list->data != NULL, "Memory allocation failed for ListArray data.");

    DebugInfo("ListArray created with initial capacity: %zu, size of item: %zu", initialCapacity, sizeOfItem);
    return list;
}

void ListArray_Destroy(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter. ListArray cannot be NULL.");

    free(list->data);
    list->data = NULL;

    free(list);
    list = NULL;

    DebugInfo("ListArray destroyed.");
}

void ListArray_Resize(ListArray *list, size_t newCapacity)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter. ListArray cannot be NULL.");

    void *newData = realloc(list->data, newCapacity * list->sizeOfItem);
    DebugAssert(newData != NULL, "Memory allocation failed for ListArray data.");

    list->data = newData;
    list->capacity = newCapacity;

    if (list->size > newCapacity)
    {
        list->size = newCapacity;
    }

    DebugWarning("ListArray resized from %zu to %zu", list->capacity, newCapacity);
}

void *ListArray_Get(const ListArray *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter. ListArray cannot be NULL.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    void *itemLocation = (void *)(list->data) + index * list->sizeOfItem;
    DebugAssert(itemLocation != NULL, "Failed to get item location. Item location is NULL.");

    return itemLocation;
}

void ListArray_Set(const ListArray *list, size_t index, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    void *targetLocation = ListArray_Get(list, index);

    memcpy(targetLocation, item, list->sizeOfItem);
}

void ListArray_Add(ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    void *targetLocation = (void *)(list->data) + list->size * list->sizeOfItem;

    memcpy(targetLocation, item, list->sizeOfItem);

    list->size++;

    if (list->size >= list->capacity)
    {
        DebugWarning("ListArray is full. Resizing it from %du to %du.", list->capacity, list->capacity * ARRAY_LIST_RESIZE_MULTIPLIER);
        ListArray_Resize(list, list->capacity * ARRAY_LIST_RESIZE_MULTIPLIER);
    }
}

void ListArray_RemoveAtIndex(ListArray *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter. ListArray cannot be NULL.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    void *targetLocation = ListArray_Get(list, index);

    memset(targetLocation, 0, list->sizeOfItem);

    size_t bytesToMove = (list->size - index - 1) * list->sizeOfItem;

    if (bytesToMove > 0)
    {
        memmove(targetLocation, targetLocation + list->sizeOfItem, bytesToMove);
    }

    list->size--;

    if (list->size < list->capacity / ARRAY_LIST_MIN_DECIMAL_LIMIT)
    {
        DebugWarning("ListArray is less than 1/%d full. Resizing it from %du to %du.", ARRAY_LIST_MIN_DECIMAL_LIMIT, list->capacity, list->capacity / ARRAY_LIST_RESIZE_MULTIPLIER);
        ListArray_Resize(list, list->capacity / ARRAY_LIST_RESIZE_MULTIPLIER);
    }
}

void ListArray_RemoveItem(ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    int itemIndex = ListArray_IndexOf(list, item);
    if (itemIndex == -1)
    {
        DebugWarning("Item not found in ListArray. Cannot remove.");
        return;
    }

    ListArray_RemoveAtIndex(list, itemIndex);
}

void *ListArray_Pop(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    void *item = ListArray_Get(list, list->size - 1);
    ListArray_RemoveAtIndex(list, list->size - 1);

    return item;
}

void ListArray_Clear(ListArray *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    list->size = 0;

    if (list->data != NULL)
    {
        memset(list->data, 0, list->capacity * list->sizeOfItem);
    }
}

long long ListArray_IndexOf(const ListArray *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    void *currentItem = list->data;

    for (size_t i = 0; i < list->size; i++)
    {
        currentItem = (void *)((char *)currentItem + i * list->sizeOfItem);

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
