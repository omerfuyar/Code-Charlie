#include "AI/AIManager.h"
#include "Modules/NetworkManager.h"
#include "Utils/cJSON.h"

#pragma region Source Only

// todo make all objects the way that they will copy the strings instead of using the pointers directly. they will have their own data
typedef struct AIChat
{
    stringHeap title;
    stringHeap model;
    stringHeap apiUrl;
    stringHeap apiKey;
    stringHeap systemPrompt; // Can be NULL
} AIChat;

#pragma endregion Source Only

AIChat *AIChat_Create(const string title, const string model, const string apiUrl, const string apiKey, const string systemPrompt)
{
    DebugAssert(title != NULL, "Null pointer passed as parameter. Title cannot be NULL.");
    DebugAssert(model != NULL, "Null pointer passed as parameter. Model cannot be NULL.");
    DebugAssert(apiUrl != NULL, "Null pointer passed as parameter. API URL cannot be NULL.");
    DebugAssert(apiKey != NULL, "Null pointer passed as parameter. API Key cannot be NULL.");

    AIChat *chat = (AIChat *)malloc(sizeof(AIChat));
    DebugAssert(chat != NULL, "Memory allocation failed for AI Chat.");

    chat->title = StringDuplicate(title);
    chat->model = StringDuplicate(model);
    chat->apiUrl = StringDuplicate(apiUrl);
    chat->apiKey = StringDuplicate(apiKey);
    chat->systemPrompt = systemPrompt == NULL ? NULL : StringDuplicate(systemPrompt);

    DebugInfo("AI Chat created successfully with title '%s', model '%s', API URL '%s'.", chat->title, chat->model, chat->apiUrl);
    return chat;
}

void AIChat_Destroy(AIChat *chat)
{
    DebugAssert(chat != NULL, "Null pointer passed as parameter. Chat cannot be NULL.");

    char tempTitle[strlen(chat->title) + 1];
    strcpy(tempTitle, chat->title);

    free(chat->title);
    free(chat->model);
    free(chat->apiUrl);
    free(chat->apiKey);

    if (chat->systemPrompt != NULL)
    {
        free(chat->systemPrompt);
    }

    chat->title = NULL;
    chat->model = NULL;
    chat->apiUrl = NULL;
    chat->apiKey = NULL;
    chat->systemPrompt = NULL;

    free(chat);
    chat = NULL;

    DebugInfo("AI Chat %s destroyed successfully.", tempTitle);
}

stringHeap AIChat_SendAndReceive(const AIChat *chat, const string message)
{
    DebugAssert(chat != NULL, "Null pointer passed as parameter. Chat cannot be NULL.");
    DebugAssert(message != NULL, "Null pointer passed as parameter. Message cannot be NULL.");

    char query[1024];
    snprintf(query, sizeof(query), "{\"model\": \"%s\",\"messages\": [{\"role\": \"user\", \"content\": \"%s\"}]}", chat->model, message);

    char bearerToken[256];
    snprintf(bearerToken, sizeof(bearerToken), "Bearer %s", chat->apiKey);

    NetworkRequestHeader headers[] = {
        {"Authorization", bearerToken},
        {"Content-Type", "application/json"}};

    NetworkRequest *request = NetworkRequest_Create(NetworkRequestType_POST, chat->apiUrl, query, strlen(query), false, headers, sizeof(headers) / sizeof(NetworkRequestHeader));

    NetworkResponse *response = NetworkRequest_Request(request, NULL, NULL);

    stringHeap responseString = StringDuplicate(response->body);

    NetworkResponse_Destroy(response);
    NetworkRequest_Destroy(request);

    cJSON *jsonResponse = cJSON_Parse(responseString);
    DebugAssert(jsonResponse != NULL, "Failed to parse JSON response from AI Chat : '%s'", cJSON_GetErrorPtr());

    cJSON *choices = cJSON_GetObjectItemCaseSensitive(jsonResponse, "choices");
    DebugAssert(cJSON_IsArray(choices), "Expected 'choices' to be an array.");

    cJSON *choice = cJSON_GetArrayItem(choices, 0);
    DebugAssert(choice != NULL, "No choices found in the response from AI Chat.");

    cJSON *messageItem = cJSON_GetObjectItemCaseSensitive(choice, "message");
    DebugAssert(messageItem != NULL, "No message found in the choice from AI Chat.");

    cJSON *content = cJSON_GetObjectItemCaseSensitive(messageItem, "content");
    DebugAssert(content != NULL, "No content found in the message from AI Chat.");

    free(responseString);
    responseString = StringDuplicate(cJSON_GetStringValue(content));

    cJSON_Delete(jsonResponse);

    DebugInfo("Message sent to AI Chat '%s'. Response received.", chat->title);
    return responseString;
}