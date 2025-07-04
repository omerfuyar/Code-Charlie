#include "Modules/NetworkManager.h"
#include "Utils/ResourceManager.h"
#include "Utils/Timer.h"

#include <curl/curl.h>

// todo add multithreading

#pragma region Source Only

NetworkResponseChunkCallback CURRENT_CHUNK_CALLBACK = NULL;

typedef struct NetworkRequest
{
    NetworkRequestType type;
    stringHeap url;
    stringHeap data;
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

NetworkRequest *NetworkRequest_Create(NetworkRequestType type, const string url, const void *data, size_t dataSize, bool singleUse, NetworkRequestHeader *headers, size_t headerCount)
{
    DebugAssert(url != NULL, "Null pointer passed as parameter. URL cannot be NULL.");
    DebugAssert(type == NetworkRequestType_POST ? data != NULL : true, "Null pointer passed as parameter. Data cannot be NULL.");

    NetworkRequest *request = (NetworkRequest *)malloc(sizeof(NetworkRequest));
    DebugAssert(request != NULL, "Memory allocation failed for network request.");

    request->type = type;
    request->url = StringDuplicate(url);

    request->data = (stringHeap)malloc(dataSize);
    DebugAssert(request->data != NULL, "Memory allocation failed for network request data.");
    memcpy(request->data, data, dataSize);

    request->dataSize = dataSize;
    request->singleUse = singleUse;

    request->headers = (NetworkRequestHeader *)malloc(headerCount * sizeof(NetworkRequestHeader));
    DebugAssert(request->headers != NULL, "Memory allocation failed for network request headers.");
    memcpy(request->headers, headers, headerCount * sizeof(NetworkRequestHeader));

    request->headerCount = headerCount;

    DebugInfo("Network request created. Type: %d, URL: '%s', Data size: %zu, Single use: %s, Header count: %zu",
              request->type, request->url, request->dataSize, request->singleUse ? "true" : "false", request->headerCount);
    return request;
}

void NetworkRequest_Destroy(NetworkRequest *request)
{
    DebugAssert(request != NULL, "Null pointer passed as parameter. Network Request cannot be NULL.");

    char tempUrl[strlen(request->url) + 1];
    strcpy(tempUrl, request->url);

    free(request->url);
    free(request->data);
    free(request->headers);
    request->headers = NULL;
    request->data = NULL;
    request->url = NULL;

    free(request);
    request = NULL;

    DebugInfo("Network request destroyed. URL: '%s'", tempUrl);
}

NetworkResponse *NetworkRequest_Request(NetworkRequest *request, NetworkResponseFinishCallback finishCallback, NetworkResponseChunkCallback chunkCallback)
{
    DebugAssert(request != NULL, "Null pointer passed as parameter. Network Request cannot be NULL.");

    CURL *requestHandle = curl_easy_init();
    DebugAssert(requestHandle != NULL, "Failed to get CURL request handle.");

    NetworkResponse *response = (NetworkResponse *)malloc(sizeof(NetworkResponse));
    DebugAssert(response != NULL, "Memory allocation failed for Network Response.");

    response->body = (stringHeap)malloc(NETWORK_MANAGER_MAX_RESPONSE_DATA_LENGTH);
    DebugAssert(response->body != NULL, "Memory allocation failed for Network Response body.");

    response->code = NetworkResponseCode_Kolpa;

    struct curl_slist *headers = NULL;

    curl_easy_setopt(requestHandle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    // curl_easy_setopt(requestHandle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_3);
    curl_easy_setopt(requestHandle, CURLOPT_URL, request->url);
    curl_easy_setopt(requestHandle, CURLOPT_WRITEFUNCTION, NetworkManager_WriteCallback);
    curl_easy_setopt(requestHandle, CURLOPT_WRITEDATA, response->body);

    switch (request->type)
    {
    case NetworkRequestType_GET:
        break;

    case NetworkRequestType_POST:
    {
        for (size_t i = 0; i < request->headerCount; i++)
        {
            NetworkRequestHeader *header = &request->headers[i];
            // DebugAssert(header->key != NULL && header->value != NULL, "Header key or value cannot be NULL.");
            char headerString[256];
            snprintf(headerString, sizeof(headerString), "%s: %s", header->key, header->value);
            headers = curl_slist_append(headers, headerString);
        }

        curl_easy_setopt(requestHandle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(requestHandle, CURLOPT_POSTFIELDS, request->data);
        curl_easy_setopt(requestHandle, CURLOPT_POSTFIELDSIZE, request->dataSize);
    }
    break;

    default:
        free(response->body);
        response->body = NULL;

        free(response);
        response = NULL;

        curl_easy_cleanup(requestHandle);

        CURRENT_CHUNK_CALLBACK = NULL;

        DebugError("Unsupported NetworkRequestType: %d", request->type);
        return NULL;
    }

    if (finishCallback != NULL)
    {
        CURRENT_CHUNK_CALLBACK = chunkCallback;
    }

    DebugInfo("Network request sent to '%s'. Body: \n'%s'", request->url, (char *)request->data);
    Timer timer = Timer_CreateStack("Network Request Timer");
    Timer_Start(&timer);
    response->code = (NetworkResponseCode)curl_easy_perform(requestHandle);
    Timer_Stop(&timer);
    DebugInfo("CURL request response received. Time taken: %f ms, Response code: %d", Timer_GetElapsedNanoseconds(&timer) / 1000000.0f, response->code);

    if (response->code != NetworkResponseCode_Ok)
    {
        CURLcode tempCode = response->code;

        free(response->body);
        response->body = NULL;

        free(response);
        response = NULL;

        curl_easy_cleanup(requestHandle);

        CURRENT_CHUNK_CALLBACK = NULL;

        DebugError("CURL request failed with error code: %s", curl_easy_strerror(tempCode));
        return NULL;
    }

    if (request->singleUse)
    {
        NetworkRequest_Destroy(request);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(requestHandle);
    CURRENT_CHUNK_CALLBACK = NULL;

    response->bodySize = strlen(response->body);

    if (finishCallback != NULL)
    {
        finishCallback(response);
    }

    return response;
}
