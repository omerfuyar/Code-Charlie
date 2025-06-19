#pragma once

#include "BaseGlobal.h"

// The resize multiplier used when the ArrayList size reached to the capacity when adding new item
#define ARRAY_LIST_RESIZE_MULTIPLIER 2

/// @brief A dynamic array list implementation. Can be used in any type. Copies passed items to its own property. Shouldn't be used without helper functions.
typedef struct ArrayList ArrayList;

/// @brief Creator function for ArrayList.
/// @param sizeOfItem Size of the item type to store in.
/// @param initialCapacity How many items can hold in this ArrayList. Can be resized later on.
/// @return The created ArrayList struct
ArrayList *ArrayList_Create(size_t sizeOfItem, size_t initialCapacity);

/// @brief Destroyer function for ArrayList.
/// @param list ArrayList to destroy.
void ArrayList_Destroy(ArrayList *list);

/// @brief Resize function for ArrayList. Can enlarge or trunc the ArrayList.
/// @param list ArrayList to resize.
/// @param newCapacity Capacity to increase or decrease.
void ArrayList_Resize(ArrayList *list, size_t newCapacity);

/// @brief Getter function for ArrayList. Should be casted before dereference / usage like : *(ListType*)function...
/// @param list ArrayList to get item in index.
/// @param index Index to get item.
/// @return The item in given index.
void *ArrayList_Get(ArrayList *list, size_t index);

/// @brief Item setter function for ArrayList. Works only in range of size. Uses memcpy to copy the item to the given index.
/// @param list ArrayList to change item in.
/// @param index Index to replace item at.
/// @param item New item at index.
void ArrayList_Set(ArrayList *list, size_t index, const void *item);

/// @brief Adder function for ArrayList. Sets the last last index to given item. Uses memcpy to copy the item to the given index.
/// @param list ArrayList to add item.
/// @param item Item to add to ArrayList.
void ArrayList_Add(ArrayList *list, const void *item);

/// @brief Remover function using index for ArrayList. Removes the item at the given index. Uses memmove to shift all indices of items by -1 after the removed index.
/// @param list ArrayList to remove item from.
/// @param index Index to remove item at.
/// @return The removed item.
void ArrayList_RemoveAtIndex(ArrayList *list, size_t index);

/// @brief Remover function using item pointer for ArrayList. Removes the first appearance of the given item. Uses ArrayList_RemoveAtIndex and ArrayList_IndexOf.
/// @param list ArrayList to remove item from.
/// @param item Item to find and remove.
/// @return The removed item. NULL if the item is absent in the list.
void ArrayList_RemoveItem(ArrayList *list, const void *item);

/// @brief Clear function for ArrayList. Sets all the data unusable and size to 0. Capacity remains the same.
/// @param list ArrayList to clear.
void ArrayList_Clear(ArrayList *list);

/// @brief Index finder for ArrayList. Searches the list linearly. Uses memcmp to compare items.
/// @param list List to search for item.
/// @param item Item to find index of.
/// @return The index of found item. -1 if the item is absent in the list.
long long ArrayList_IndexOf(ArrayList *list, const void *item);

/// @brief Size getter for ArrayList.
/// @param list ArrayList to get size.
/// @return The size of the ArrayList.
size_t ArrayList_GetSize(ArrayList *list);

/// @brief Capacity getter for ArrayList.
/// @param list ArrayList to get capacity.
/// @return The capacity of the ArrayList.
size_t ArrayList_GetCapacity(ArrayList *list);