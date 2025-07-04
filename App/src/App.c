#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"
#include "Modules/NetworkManager.h"
#include "Utils/ResourceManager.h"

Vector2Int terminalSize;
RendererWindow *rightWindow;
RendererWindow *leftTopWindow;
RendererWindow *leftBottomWindow;

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

void App_OnNetworkResponse(const NetworkResponse *response)
{
    DebugWarning("Data received: \n%s", response->body);
}

void App_StartLate()
{
    stringStack data = "{"
                       "\"model\": \"gpt-3.5-turbo\","
                       "\"messages\": [{\"role\": \"user\", \"content\": \"Hello World!\"}]"
                       "}";
    NetworkRequest *request = NetworkRequest_Create(NetworkRequestType_POST, "https://api.openai.com/v1/chat/completions", data, strlen(data), true);

    NetworkManager_Request(request, App_OnNetworkResponse);
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
