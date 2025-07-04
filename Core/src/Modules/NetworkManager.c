#include "Modules/NetworkManager.h"
#include "Utils/ResourceManager.h"

#include <curl/curl.h>

// todo add multithreading

#pragma region Source Only

#if PLATFORM_WINDOWS
#define NETWORK_MANAGER_ENV_FILE "C:\\Users\\omruyr\\Documents\\Programming\\Code-Charlie\\.env"
#else
#define NETWORK_MANAGER_ENV_FILE "/home/omruyr/Documents/Programming/Code-Charlie/.env"
#endif

char openAIAPIKey[256];
NetworkResponseCallback currentCallback = NULL;

typedef struct NetworkRequest
{
    NetworkRequestType type;
    CURL *handle;
    stringHeap url;
    void *data;
    size_t dataSize;
    bool singleUse;
} NetworkRequest;

/// @brief Callback function for writing data received from a network request.
/// @param data Received data from the network request.
/// @param dataSize Size of the received data in bytes.
/// @param elementCount Number of elements in the received data.
/// @param userData User data which setted with CURLOPT_WRITEDATA option.
/// @return Number of bytes processed.
size_t NetworkManager_WriteCallback(void *data, size_t dataSize, size_t elementCount, void *userData)
{
    DebugInfo("NetworkManager_WriteCallback called with dataSize: %zu, elementCount: %zu", dataSize, elementCount);
    strncat((string)userData, (string)data, dataSize * elementCount);
    return dataSize * elementCount;
}

#pragma endregion

void NetworkManager_Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    strcpy(openAIAPIKey, Resource_GetEnvironmentObjectValue(NETWORK_MANAGER_ENV_FILE, "OPENAI_API_KEY"));
}

void NetworkManager_Terminate()
{
    curl_global_cleanup();
}

NetworkRequest *NetworkRequest_Create(NetworkRequestType type, string url, void *data, size_t dataSize, bool singleUse)
{
    DebugAssert(url != NULL, "Null pointer passed as parameter. URL cannot be NULL.");

    NetworkRequest *request = malloc(sizeof(NetworkRequest));
    DebugAssert(request != NULL, "Memory allocation failed for Network Request.");

    request->type = type;
    request->url = url;
    request->data = data;
    request->dataSize = dataSize;
    request->singleUse = singleUse;
    request->handle = NULL;

    return request;
}

void NetworkManager_Request(NetworkRequest *request, NetworkResponseCallback callback)
{
    DebugAssert(request != NULL, "Null pointer passed as parameter. Network Request cannot be NULL.");

    request->handle = curl_easy_init();
    DebugAssert(request->handle != NULL, "Failed to initialize CURL request handle.");

    NetworkResponse response = {
        "",
        NetworkResponseCode_Kolpa,
    };

    struct curl_slist *headers = NULL;

    char headerAuthorization[256];
    snprintf(headerAuthorization, sizeof(headerAuthorization), "Authorization: Bearer %s", openAIAPIKey);

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, headerAuthorization);

    DebugAssert(request->dataSize < NETWORK_MANAGER_MAX_REQUEST_DATA_LENGTH, "Data size exceeds maximum request data length.");
    char dataBuffer[NETWORK_MANAGER_MAX_REQUEST_DATA_LENGTH] = {0};
    strncpy(dataBuffer, request->data, request->dataSize);
    request->data = dataBuffer;

    curl_easy_setopt(request->handle, CURLOPT_URL, request->url);
    curl_easy_setopt(request->handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(request->handle, CURLOPT_POSTFIELDS, request->data);
    curl_easy_setopt(request->handle, CURLOPT_POSTFIELDSIZE, request->dataSize);
    curl_easy_setopt(request->handle, CURLOPT_WRITEFUNCTION, NetworkManager_WriteCallback);
    curl_easy_setopt(request->handle, CURLOPT_WRITEDATA, response.body);

    response.code = (NetworkResponseCode)curl_easy_perform(request->handle);
    if (response.code != NetworkResponseCode_Ok)
    {
        DebugWarning("CURL request failed with error code: %s", curl_easy_strerror((CURLcode)response.code));
    }

    callback(&response);

    if (request->singleUse)
    {
        free(request);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(request->handle);
}
