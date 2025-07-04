#include "Modules/NetworkManager.h"
#include "Utils/ResourceManager.h"

#include <curl/curl.h>

// todo add multithreading

#pragma region Source Only

NetworkResponseChunkCallback CURRENT_CHUNK_CALLBACK = NULL;

typedef struct NetworkRequest
{
    NetworkRequestType type;
    CURL *handle;
    stringHeap url;
    void *data;
    size_t dataSize;
    bool singleUse;
    NetworkRequestHeader *headers;
    size_t headerCount;
} NetworkRequest;

/// @brief Callback function for writing data received from a network request.
/// @param data Received data from the network request. Not null terminated.
/// @param elementCount Number of elements in the data. (curl says it is always 1)
/// @param dataSize Size of the data element.
/// @param userData User data which setted with CURLOPT_WRITEDATA option. Null terminated.
/// @return Number of bytes processed.
size_t NetworkManager_WriteCallback(void *data, size_t elementCount, size_t dataSize, void *userData)
{
    if (CURRENT_CHUNK_CALLBACK != NULL)
    {
        CURRENT_CHUNK_CALLBACK(data, elementCount * dataSize, userData);
    }

    strncat((string)userData, (string)data, elementCount * dataSize);

    return elementCount * dataSize;
}

#pragma endregion Source Only

void NetworkManager_Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void NetworkManager_Terminate()
{
    curl_global_cleanup();
}

NetworkRequest *NetworkRequest_Create(NetworkRequestType type, string url, void *data, size_t dataSize, bool singleUse, NetworkRequestHeader *headers, size_t headerCount)
{
    DebugAssert(url != NULL, "Null pointer passed as parameter. URL cannot be NULL.");

    NetworkRequest *request = malloc(sizeof(NetworkRequest));
    DebugAssert(request != NULL, "Memory allocation failed for Network Request.");

    request->type = type;
    request->url = url;
    request->data = data;
    request->dataSize = dataSize;
    request->singleUse = singleUse;
    request->headers = headers;
    request->headerCount = headerCount;
    request->handle = NULL;

    return request;
}

void NetworkRequest_Destroy(NetworkRequest *request)
{
    DebugAssert(request != NULL, "Null pointer passed as parameter. Network Request cannot be NULL.");

    free(request);
}

void NetworkRequest_Request(NetworkRequest *request, NetworkResponseFinishCallback finishCallback, NetworkResponseChunkCallback chunkCallback)
{
    DebugAssert(request != NULL, "Null pointer passed as parameter. Network Request cannot be NULL.");

    request->handle = curl_easy_init();
    DebugAssert(request->handle != NULL, "Failed to get CURL request handle.");

    NetworkResponse response = {
        "",
        NetworkResponseCode_Kolpa,
    };

    struct curl_slist *headers = NULL;

    curl_easy_setopt(request->handle, CURLOPT_URL, request->url);
    curl_easy_setopt(request->handle, CURLOPT_WRITEFUNCTION, NetworkManager_WriteCallback);
    curl_easy_setopt(request->handle, CURLOPT_WRITEDATA, response.body);

    switch (request->type)
    {
    case NetworkRequestType_GET:
        break;

    case NetworkRequestType_POST:
    {

        headers = curl_slist_append(headers, "Content-Type: application/json");
        for (size_t i = 0; i < request->headerCount; i++)
        {
            NetworkRequestHeader *header = &request->headers[i];
            DebugAssert(header->key != NULL && header->value != NULL, "Header key or value cannot be NULL.");
            char headerString[256];
            snprintf(headerString, sizeof(headerString), "%s: %s", header->key, header->value);
            headers = curl_slist_append(headers, headerString);
        }

        curl_easy_setopt(request->handle, CURLOPT_HTTPHEADER, headers);

        // Set the POST data directly from the request struct
        DebugAssert(request->data != NULL, "POST request data cannot be NULL.");
        curl_easy_setopt(request->handle, CURLOPT_POSTFIELDS, request->data);
        curl_easy_setopt(request->handle, CURLOPT_POSTFIELDSIZE, request->dataSize);
    }
    break;

    default:
        DebugError("Unsupported NetworkRequestType: %d", request->type);
        curl_easy_cleanup(request->handle);
        return;
    }

    DebugInfo("Network request sent to '%s'. Body: \n'%s'", request->url, (char *)request->data);

    if (finishCallback != NULL)
    {
        CURRENT_CHUNK_CALLBACK = chunkCallback;
    }
    response.code = (NetworkResponseCode)curl_easy_perform(request->handle);
    if (response.code != NetworkResponseCode_Ok)
    {
        DebugError("CURL request failed with error code: %s", curl_easy_strerror((CURLcode)response.code));
    }

    if (finishCallback != NULL)
    {
        finishCallback(&response);
    }

    CURRENT_CHUNK_CALLBACK = NULL;

    if (request->singleUse)
    {
        NetworkRequest_Destroy(request);
    }

    if (headers)
    {
        curl_slist_free_all(headers);
    }

    if (request->handle)
    {
        curl_easy_cleanup(request->handle);
    }
}
