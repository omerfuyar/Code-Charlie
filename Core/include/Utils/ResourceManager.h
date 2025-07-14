#pragma once

#include "Core.h"
#include "Utils/ListArray.h"

#pragma region typedefs

#define RESOURCE_MANAGER_MAX_PAIR_ELEMENT_LENGTH 256
#define RESOURCE_MANAGER_DEFAULT_LINE_COUNT 128

typedef struct Resource Resource;

typedef struct EnvironmentObject
{
    char key[RESOURCE_MANAGER_MAX_PAIR_ELEMENT_LENGTH];
    char value[RESOURCE_MANAGER_MAX_PAIR_ELEMENT_LENGTH];
} EnvironmentObject;

#pragma endregion typedefs

Resource *Resource_Create(const string path, const string name, unsigned int maxLineCharCount, unsigned int maxLineCount);

/// @brief Retrieves the resource as a string.
/// @param resource The resource to retrieve.
/// @return The resource data as a string. Not guaranteed to be null-terminated.
stringHeap Resource_GetAsString(Resource *resource);

/// @brief Retrieves the resource as an array of environment objects.
/// @param resource The resource to retrieve.
/// @param delimeter The delimiter used to split the resource data into lines.
/// @param lineCount The maximum number of lines to retrieve.
/// @return An array of environment objects representing the resource data. Must be freed by the caller.
ListArray *Resource_GetAsEnvironmentObjectArray(Resource *resource, const string delimeter, unsigned int lineCount);

/// @brief Retrieves the value associated with a key in an environment object file.
/// @param path The path to the environment object file.
/// @param key The key to search for.
/// @return A dynamically allocated string containing the value associated with the key in the environment object file. It must be freed by the caller.
stringHeap Resource_GetEnvironmentObjectValue(const string path, const string key);

/// @brief Destroys a resource and frees its memory.
/// @param resource The resource to destroy.
void Resource_Destroy(Resource *resource);