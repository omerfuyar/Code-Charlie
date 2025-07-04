#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"
#include "Modules/NetworkManager.h"
#include "Utils/ResourceManager.h"

char OPEN_AI_API_KEY[256];
Vector2Int terminalSize;
RendererWindow *rightWindow;
RendererWindow *leftTopWindow;
RendererWindow *leftBottomWindow;

void App_OnNetworkResponseFinal(const NetworkResponse *response)
{
    DebugWarning("Network response received finally with code '%d' and size '%zu': \n'%s'", response->code, strlen(response->body), response->body);
}

void App_OnNetworkResponseChunk(void *data, size_t dataSize, void *userData)
{
    DebugWarning("Network response received chunk with size '%zu': \n'%.*s'", dataSize, (int)dataSize, (char *)data);
}

void App_Start()
{
    terminalSize = RendererWindow_GetWindowSize(RENDERER_MAIN_WINDOW);

    rightWindow = RendererWindow_Create("test right", NewVector2Int(terminalSize.x / 2, 0), NewVector2Int(terminalSize.x / 2, terminalSize.y), RENDERER_MAIN_WINDOW);
    leftTopWindow = RendererWindow_Create("test left top", NewVector2Int(0, 0), NewVector2Int(terminalSize.x / 2, terminalSize.y / 2), RENDERER_MAIN_WINDOW);
    leftBottomWindow = RendererWindow_Create("test left bottom", NewVector2Int(0, terminalSize.y / 2), NewVector2Int(terminalSize.x / 2, terminalSize.y / 2), RENDERER_MAIN_WINDOW);

    RendererWindow_SetPosition(leftBottomWindow, NewVector2Int(1, 1), true);
    RendererWindow_UpdateContent(RENDERER_MAIN_WINDOW);
    RendererWindow_UpdateContent(rightWindow);
    RendererWindow_UpdateContent(leftTopWindow);
    RendererWindow_UpdateContent(leftBottomWindow);
}

void App_StartLate()
{
    strcpy(OPEN_AI_API_KEY, Resource_GetEnvironmentObjectValue(NETWORK_MANAGER_ENV_FILE, "OPENAI_API_KEY"));
    stringStack requestData = "{\"model\": \"gpt-3.5-turbo\",\"messages\": [{\"role\": \"user\", \"content\": \"Hello World!\"}]}";
    stringStack requestUrl = "https://api.openai.com/v1/chat/completions";
    char bearerToken[256];
    snprintf(bearerToken, sizeof(bearerToken), "Bearer %s", OPEN_AI_API_KEY);
    NetworkRequestHeader headers[] = {{"Authorization", bearerToken}, {"Content-Type", "application/json"}};

    NetworkRequest *request = NetworkRequest_Create(NetworkRequestType_POST, requestUrl, requestData, strlen(requestData), true, headers, sizeof(headers) / sizeof(NetworkRequestHeader));

    NetworkRequest_Request(request, App_OnNetworkResponseFinal, App_OnNetworkResponseChunk);
}

void App_Update()
{
}

void App_UpdateLate()
{
    if (InputManager_GetKey(InputKeyCode_q, InputKeyState_Pressed))
    {
        DebugInfo("'q' key pressed, stopping the application.");
        App_Stop(0);
    }
}

void App_Stop(int exitCode)
{
    Core_Terminate(exitCode);
}
