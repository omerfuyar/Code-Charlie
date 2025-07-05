#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"
#include "AI/AIManager.h"
#include "Utils/ResourceManager.h"

char OPEN_AI_API_KEY[256];
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

    RendererWindow_SetCursorPosition(leftTopWindow, NewVector2Int(1, 1));

    RendererWindow_UpdateContent(RENDERER_MAIN_WINDOW);
    RendererWindow_UpdateContent(rightWindow);
    RendererWindow_UpdateContent(leftTopWindow);
    RendererWindow_UpdateContent(leftBottomWindow);
}

void App_StartLate()
{
    strcpy(OPEN_AI_API_KEY, Resource_GetEnvironmentObjectValue(NETWORK_MANAGER_ENV_FILE, "OPENAI_API_KEY"));

    stringStack chatMessage = "Hello, AI! How are you today?";
    stringStack chatUrl = "https://api.openai.com/v1/chat/completions";

    AIChat *chat = AIChat_Create("My Test Chat", "gpt-3.5-turbo", chatUrl, OPEN_AI_API_KEY, NULL);

    stringHeap response = AIChat_SendAndReceive(chat, chatMessage);
    DebugWarning("AI Response: %s", response);
    RendererWindow_PutStringToPositionWrap(leftTopWindow, NewVector2Int(1, 1), NULL, false, "AI Response: %s", response);
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

    RendererWindow_UpdateContent(RENDERER_MAIN_WINDOW);
    RendererWindow_UpdateContent(rightWindow);
    RendererWindow_UpdateContent(leftTopWindow);
    RendererWindow_UpdateContent(leftBottomWindow);
}

void App_Stop(int exitCode)
{
    Core_Terminate(exitCode);
}
