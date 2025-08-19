#pragma once

#include "Core.h"

#pragma region typedefs

#define AI_MANAGER_MAX_QUERY_LENGTH 1024

typedef struct AIChat AIChat;

#pragma endregion typedefs

/// @brief Creates a new ready to use AI Chat.
/// @param title Name of the AI Chat. Used to identify the AI Chat in the system.
/// @param model Model of the AI Chat.
/// @param apiUrl API endpoint for the AI Chat.
/// @param apiKey API key for authenticating requests to the AI Chat.
/// @param systemPrompt System prompt for the AI Chat. Can be NULL.
/// @return Pointer to the created AI Chat.
AIChat *AIChat_Create(const string title, const string model, const string apiUrl, const string apiKey, const string systemPrompt);

/// @brief Destroys the AI Chat and frees its resources.
/// @param chat Pointer to the AI Chat to destroy.
void AIChat_Destroy(AIChat *chat);

/// @brief Sends a message to the AI Chat and receives the response.
/// @param chat Pointer to the AI Chat to use.
/// @param message Message to send to the AI Chat.
/// @return Response from the AI Chat. The response is allocated on the heap and must be freed by the caller.
stringHeap AIChat_SendAndReceive(const AIChat *chat, const string message);
