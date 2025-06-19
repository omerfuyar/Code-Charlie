#include "Utils/LinkedList.h"

#include <stdlib.h>
#include <string.h>

// todo make better error checks

/// @brief A node in the linked list.
typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList
{
    LinkedListNode *head;
    size_t size;
    size_t sizeOfItem;
} LinkedList;

#pragma region LinkedListNode

/// @brief Creator function for LinkedListNode. Uses memcpy to copy the data.
/// @param sizeOfData Size of the data to be stored in the node.
/// @param data Pointer to the data to store inside the node.
/// @return The created LinkedListNode struct.
LinkedListNode *LinkedListNode_Create(size_t sizeOfData, const void *data)
{
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    DebugAssert(node != NULL, "Memory allocation failed for node.");

    node->data = malloc(sizeOfData);
    DebugAssert(node->data != NULL, "Memory allocation failed for node data.");

    memcpy(node->data, data, sizeOfData);

    node->next = NULL;

    return node;
}

/// @brief Destroyer function for LinkedListNode. Frees the data and the node itself.
/// @param node Pointer to the LinkedListNode to destroy.
void LinkedListNode_Destroy(LinkedListNode *node)
{
    DebugAssert(node != NULL, "Null pointer passed as parameter.");

    if (node->data != NULL)
    {
        free(node->data);
    }
    node->data = NULL;
    node->next = NULL;

    free(node);
    node = NULL;
}

/// @brief Destroyer function for LinkedListNode. Destroys itself and the next node recursively.
/// @param node Pointer to the head node of the linked list to destroy.
void LinkedListNode_DestroyAll(LinkedListNode *node)
{
    DebugAssert(node != NULL, "Null pointer passed as parameter.");

    if (node->next != NULL)
    {
        LinkedListNode_DestroyAll(node->next);
    }

    LinkedListNode_Destroy(node);
}

/// @brief Connects the node to nextNode.
/// @param node Node to connect to next.
/// @param nextNode Next node to connect.
void LinkedListNode_Connect(LinkedListNode *node, LinkedListNode *nextNode)
{
    DebugAssert(node != NULL, "Null pointer passed as parameter for node.");
    DebugAssert(nextNode != NULL, "Null pointer passed as parameter for next node.");

    node->next = nextNode;
}

/// @brief Connects two linked list nodes if the next is null recursively.
/// @param node Pointer to the current node to set next node of.
/// @param nextNode Pointer to the next node to connect.
void LinkedListNode_Append(LinkedListNode *node, LinkedListNode *nextNode)
{
    if (node->next == NULL)
    {
        LinkedListNode_Connect(node->next, nextNode);
    }
    else
    {
        LinkedListNode_Append(node->next, nextNode);
    }
}

/// @brief Gets the index of the given item from start index recursively.
/// @param node Node to search.
/// @param sizeOfItem Size of an item in the list.
/// @param data Data to compare with node's data.
/// @param startIndex Index to pass until the item is found. Incremented by one if the data didn't match.
/// @return The index which is incremented from previous calls. Returns -1 if item is not found in the sequence.
long long LinkedListNode_GetIndexIfMatch(LinkedListNode *node, size_t sizeOfItem, const void *data, long long startIndex)
{
    if (memcmp(node->data, data, sizeOfItem) == 0)
    {
        return startIndex;
    }
    else if (node->next == NULL)
    {
        return -1;
    }
    else
    {
        startIndex++;
        return LinkedListNode_GetIndexIfMatch(node->next, sizeOfItem, data, startIndex);
    }
}

#pragma endregion

LinkedList *LinkedList_Create(size_t sizeOfItem)
{
    LinkedList *list = malloc(sizeof(LinkedList));
    DebugAssert(list != NULL, "Memory allocation failed.");

    list->size = 0;
    list->sizeOfItem = sizeOfItem;

    return list;
}

void LinkedList_Destroy(LinkedList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    if (list->head != NULL)
    {
        LinkedListNode_DestroyAll(list->head);
    }

    free(list);
    list = NULL;
}

void *LinkedList_Get(LinkedList *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    LinkedListNode *currentNode = list->head;

    for (size_t i = 0; i < index; i++)
    {
        currentNode = currentNode->next;
    }

    return currentNode;
}

void LinkedList_Set(LinkedList *list, size_t index, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    LinkedListNode *nodeToSet = LinkedList_Get(list, index);
    memcpy(nodeToSet->data, item, list->sizeOfItem);
}

void LinkedList_Add(LinkedList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    LinkedListNode *newNode = LinkedListNode_Create(list->sizeOfItem, item);

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        LinkedListNode_Append(list->head, newNode);
    }

    list->size++;
}

void LinkedList_RemoveAtIndex(LinkedList *list, size_t index)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(index < list->size, "Index out of range. List size : %du, index : %du", list->size, index);

    if (index == 0)
    {
        list->head = list->head->next;
        LinkedListNode_Destroy(list->head);
    }
    else
    {
        LinkedListNode *previousNodeToRemove = LinkedList_Get(list, index - 1);
        LinkedListNode_Connect(previousNodeToRemove, previousNodeToRemove->next->next);
        LinkedListNode_Destroy(previousNodeToRemove->next);
    }

    list->size--;
}

void LinkedList_RemoveItem(LinkedList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    LinkedList_RemoveAtIndex(list, LinkedList_IndexOf(list, item));
}

void LinkedList_Clear(LinkedList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    LinkedListNode_DestroyAll(list->head);
}

long long LinkedList_IndexOf(LinkedList *list, const void *item)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");
    DebugAssert(list->head != NULL, "Head of the list is null.");

    return LinkedListNode_GetIndexIfMatch(list->head, list->sizeOfItem, item, 0);
}

size_t LinkedList_GetSize(LinkedList *list)
{
    DebugAssert(list != NULL, "Null pointer passed as parameter.");

    return list->size;
}