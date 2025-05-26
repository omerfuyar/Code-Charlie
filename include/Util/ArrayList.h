#pragma once
#include <stddef.h>

/// @brief A dynamic array list implementation in C for managing a collection of items.
typedef struct ArrayList ArrayList;

ArrayList *ArrayList_Create(size_t sizeOfItem, size_t initialCapacity);
