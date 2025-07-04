#include "Utils/ResourceManager.h"

#pragma region Source Only

typedef struct Resource
{
    stringHeap title;
    stringHeap path;
    stringHeap data;
    size_t dataSize;
} Resource;

#pragma endregion Source Only

Resource *Resource_Create(const string path, const string title, unsigned int maxLineCharCount, unsigned int maxLineCount)
{
    DebugAssert(path != NULL, "Null pointer passed as parameter. Path cannot be NULL.");
    DebugAssert(title != NULL, "Null pointer passed as parameter. Title cannot be NULL.");

    Resource *resource = (Resource *)malloc(sizeof(Resource));
    DebugAssert(resource != NULL, "Memory allocation failed for resource %s.", path);

    resource->title = StringDuplicate(title);
    resource->path = StringDuplicate(path);

    FILE *file = fopen(resource->path, "r");
    DebugAssert(file != NULL, "File open failed for %s", resource->path);

    char dataBuffer[maxLineCharCount * maxLineCount];
    char lineBuffer[maxLineCharCount];

    dataBuffer[0] = '\0';
    lineBuffer[0] = '\0';

    while (fgets(lineBuffer, sizeof(lineBuffer), file))
    {
        strcat(dataBuffer, lineBuffer);
    }

    fclose(file);

    resource->dataSize = strlen(dataBuffer) + 1;

    resource->data = (stringHeap)malloc(resource->dataSize);
    DebugAssert(resource->data != NULL, "Memory allocation failed for resource data %s.", resource->path);

    strcpy(resource->data, dataBuffer);

    return resource;
}

stringHeap Resource_GetAsString(Resource *resource)
{
    return (stringHeap)resource->data;
}

ListArray *Resource_GetAsEnvironmentObjectArray(Resource *resource, const string delimeter, unsigned int lineCount)
{
    DebugAssert(resource != NULL, "Null pointer passed as parameter. Resource cannot be NULL.");
    DebugAssert(delimeter != NULL, "Null pointer passed as parameter. delimeter cannot be NULL.");

    ListArray *arrayList = ListArray_Create(sizeof(EnvironmentObject), lineCount);

    stringHeap dataCopy = StringDuplicate(resource->data);
    DebugAssert(dataCopy != NULL, "Memory allocation failed for dataCopy.");

    stringStack lineSave = NULL;
    stringStack pairSave = NULL;

#if PLATFORM_WINDOWS
    stringHeap line = strtok_s(dataCopy, "\n", &lineSave);
#else
    stringHeap line = __strtok_r(dataCopy, "\n", &lineSave);
#endif

    while (line != NULL)
    {
#if PLATFORM_WINDOWS
        stringHeap key = strtok_s(line, delimeter, &pairSave);
        stringHeap value = strtok_s(NULL, delimeter, &pairSave);
#else
        stringHeap key = __strtok_r(line, delimeter, &pairSave);
        stringHeap value = __strtok_r(NULL, delimeter, &pairSave);
#endif

        EnvironmentObject envObj;
        strcpy(envObj.key, key);
        strcpy(envObj.value, value);

        ListArray_Add(arrayList, &envObj);

#if PLATFORM_WINDOWS
        line = strtok_s(NULL, "\n", &lineSave);
#else
        line = __strtok_r(NULL, "\n", &lineSave);
#endif
    }

    free(dataCopy);

    return arrayList;
}

stringHeap Resource_GetEnvironmentObjectValue(const string path, const string key)
{
    DebugAssert(path != NULL, "Null pointer passed as parameter. Path cannot be NULL.");
    DebugAssert(key != NULL, "Null pointer passed as parameter. Key cannot be NULL.");

    Resource *resource = Resource_Create(path, "Environment Objects", 256, RESOURCE_MANAGER_DEFAULT_LINE_COUNT);
    ListArray *envObjects = Resource_GetAsEnvironmentObjectArray(resource, "=", RESOURCE_MANAGER_DEFAULT_LINE_COUNT);

    for (size_t i = 0; i < ListArray_GetSize(envObjects); i++)
    {
        EnvironmentObject envObject = *((EnvironmentObject *)ListArray_Get(envObjects, i));

        if (strcmp(envObject.key, key) == 0)
        {
            DebugInfo("Key '%s' found in resource '%s' in '%s'. Returning value '%s'.", key, resource->title, resource->path, envObject.value);
            Resource_Destroy(resource);
            ListArray_Destroy(envObjects);
            stringHeap valueCopy = StringDuplicate(envObject.value);
            return valueCopy;
        }
    }

    Resource_Destroy(resource);
    ListArray_Destroy(envObjects);
    DebugWarning("Key '%s' not found in resource '%s'. Returning NULL.", key, resource->title);
    return NULL;
}

void Resource_Destroy(Resource *resource)
{
    DebugAssert(resource != NULL, "Null pointer passed as parameter. Resource cannot be NULL.");

    resource->path = NULL;
    resource->dataSize = 0;

    char tempTitle[strlen(resource->title) + 1];
    strcpy(tempTitle, resource->title);
    resource->title = NULL;

    free(resource->data);
    resource->data = NULL;

    free(resource);
    resource = NULL;

    DebugInfo("Resource '%s' destroyed successfully.", tempTitle);
}