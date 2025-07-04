#include "AI/AIManager.h"

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
}

stringHeap AIChat_SendAndReceive(const AIChat *chat, const string message)
{
}