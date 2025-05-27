#pragma once

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/// @brief A dynamic linked list implementation. Can be used for any type. Shouldn't be used without helper functions.
typedef struct LinkedList LinkedList;

/// @brief A node in the linked list.
typedef struct LinkedListNode LinkedListNode;

/// @brief Creator function for LinkedListNode.
/// @param sizeOfData Size of the data will be stored.
/// @param data Data to store inside the node.
/// @return The created LinkedListNode struct.
LinkedListNode *LinkedListNode_Create(size_t sizeOfData, const void *data);

/// @brief Creator function for LinkedList.
/// @param sizeOfItem Size of the item type to store in.
/// @return The created LinkedList struct.
LinkedList *LinkedList_Create(size_t sizeOfItem);

/// @brief Destroyer function for LinkedList.
/// @param list LinkedList to destroy.
void LinkedList_Destroy(LinkedList *list);

/// @brief Head getter function for LinkedList.
/// @param list LinkedList to get head.
/// @return Head of the LinkedList.
void *LinkedList_Head(LinkedList *list);

/// @brief Getter function for LinkedList. Should be casted before dereference/usage like: *(ListType*)function...
/// @param list LinkedList to get item from.
/// @param index Index to get item.
/// @return The item at the given index.
void *LinkedList_Get(LinkedList *list, size_t index);

/// @brief Item setter function for LinkedList. Works only in range of size.
/// @param list LinkedList to change item in.
/// @param index Index to replace item at.
/// @param item New item at index.
void LinkedList_Set(LinkedList *list, size_t index, const void *item);

/// @brief Adder function for LinkedList. Adds the item to the end of the list.
/// @param list LinkedList to add item.
/// @param item Item to add to LinkedList.
void LinkedList_Add(LinkedList *list, const void *item);

/// @brief Remover function using index for LinkedList.
/// @param list LinkedList to remove item from.
/// @param index Index to remove item at.
/// @return The removed item.
void LinkedList_RemoveAtIndex(LinkedList *list, size_t index);

/// @brief Remover function using item pointer for LinkedList. Removes the first appearance of the given item.
/// @param list LinkedList to remove item from.
/// @param item Item to find and remove.
/// @return The removed item. NULL if the item is absent in the list.
void LinkedList_RemoveItem(LinkedList *list, const void *item);

/// @brief Clear function for LinkedList. Removes all nodes and sets size to 0.
/// @param list LinkedList to clear.
void LinkedList_Clear(LinkedList *list);

/// @brief Index finder for LinkedList. Searches the list linearly.
/// @param list List to search for item.
/// @param item Item to find index of.
/// @return The index of the found item. -1 if the item is absent in the list.
long long LinkedList_IndexOf(LinkedList *list, const void *item);

/// @brief Size getter for LinkedList.
/// @param list LinkedList to get size.
/// @return The size of the LinkedList.
size_t LinkedList_GetSize(LinkedList *list);