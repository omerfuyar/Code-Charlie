#pragma once

#include "BaseGlobal.h"

/// @brief A dynamic linked list implementation. Can store any type of data. Copies passed items to its own property. Shouldn't be used without helper functions.
typedef struct LinkedList LinkedList;

/// @brief Creator function for LinkedList.
/// @param sizeOfItem Size of the item type to store in the list.
/// @return The created LinkedList struct.
LinkedList *LinkedList_Create(size_t sizeOfItem);

/// @brief Destroyer function for LinkedList. Frees all nodes and the list itself recursively.
/// @param list LinkedList to destroy.
void LinkedList_Destroy(LinkedList *list);

/// @brief Head getter function for LinkedList.
/// @param list LinkedList to get the head node from.
/// @return Pointer to the head node of the LinkedList.
void *LinkedList_Head(LinkedList *list);

/// @brief Getter function for LinkedList. Retrieves the item at the specified index. Works only in range of size.
/// @param list LinkedList to get the item from.
/// @param index Index of the item to retrieve.
/// @return Pointer to the item at the given index. Should be cast before dereferencing.
void *LinkedList_Get(LinkedList *list, size_t index);

/// @brief Item setter function for LinkedList. Replaces the item at the specified index.
/// @param list LinkedList to modify.
/// @param index Index of the item to replace.
/// @param item Pointer to the new item to set at the index.
void LinkedList_Set(LinkedList *list, size_t index, const void *item);

/// @brief Adder function for LinkedList. Appends the item to the end of the list.
/// @param list LinkedList to add the item to.
/// @param item Pointer to the item to add.
void LinkedList_Add(LinkedList *list, const void *item);

/// @brief Remover function using index for LinkedList. Removes the item at the specified index.
/// @param list LinkedList to remove the item from.
/// @param index Index of the item to remove.
/// @return Pointer to the removed item.
void LinkedList_RemoveAtIndex(LinkedList *list, size_t index);

/// @brief Remover function using item pointer for LinkedList. Removes the first occurrence of the specified item.
/// @param list LinkedList to remove the item from.
/// @param item Pointer to the item to find and remove.
/// @return Pointer to the removed item. NULL if the item is not found in the list.
void LinkedList_RemoveItem(LinkedList *list, const void *item);

/// @brief Clear function for LinkedList. Removes all nodes and resets the size to 0.
/// @param list LinkedList to clear.
void LinkedList_Clear(LinkedList *list);

/// @brief Index finder for LinkedList. Searches the list linearly for the specified item.
/// @param list LinkedList to search in.
/// @param item Pointer to the item to find.
/// @return The index of the found item. -1 if the item is not found in the list.
long long LinkedList_IndexOf(LinkedList *list, const void *item);

/// @brief Size getter for LinkedList.
/// @param list LinkedList to get the size of.
/// @return The number of items in the LinkedList.
size_t LinkedList_GetSize(LinkedList *list);