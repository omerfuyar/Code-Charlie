#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"
#include "AI/AIManager.h"
#include "Utils/ResourceManager.h"

#if PLATFORM_WINDOWS
#define NETWORK_MANAGER_ENV_FILE "C:\\Users\\omruyr\\Documents\\Programming\\Code-Charlie\\.env"
#else
#define NETWORK_MANAGER_ENV_FILE "/home/omruyr/Projects/Code-Charlie/.env"
#endif

char OPEN_AI_API_KEY[256];
Vector2Int terminalSize;
RendererWindow *rightWindow;
RendererWindow *leftTopWindow;
RendererWindow *leftBottomWindow;
AIChat *chat;
stringHeap response;
stringHeap query;

void App_Start()
{
    terminalSize = RendererWindow_GetWindowSize(RENDERER_MAIN_WINDOW);

    rightWindow = RendererWindow_Create("test right", NewVector2Int(terminalSize.x * 3 / 4, 0), NewVector2Int(terminalSize.x / 4, terminalSize.y), RENDERER_MAIN_WINDOW);
    leftTopWindow = RendererWindow_Create("test left top", NewVector2Int(0, 0), NewVector2Int(terminalSize.x * 3 / 4, terminalSize.y / 2), RENDERER_MAIN_WINDOW);
    leftBottomWindow = RendererWindow_Create("test left bottom", NewVector2Int(0, terminalSize.y / 2), NewVector2Int(terminalSize.x * 3 / 4, terminalSize.y / 2), RENDERER_MAIN_WINDOW);
}

void App_StartLate()
{
    strcpy(OPEN_AI_API_KEY, Resource_GetEnvironmentObjectValue(NETWORK_MANAGER_ENV_FILE, "OPENAI_API_KEY"));

    stringStack chatUrl = "https://api.openai.com/v1/chat/completions";

    chat = AIChat_Create("My Test Chat", "gpt-3.5-turbo", chatUrl, OPEN_AI_API_KEY, NULL);

    RendererWindow_PutCharToPosition(rightWindow, NewVector2Int(1, 1), RENDERER_DEFAULT_TEXT_ATTRIBUTE, '>');
    RendererWindow_PutCharToPosition(leftBottomWindow, NewVector2Int(1, 1), RENDERER_DEFAULT_TEXT_ATTRIBUTE, '>');
}

void App_Update()
{
    query = RendererManager_GetStringAtPositionWrap(rightWindow, NewVector2Int(2, 1));
    response = AIChat_SendAndReceive(chat, query);

    // response = "hey there, Im a fake AI assistant";

    RendererWindow_Clear(rightWindow);
    RendererWindow_PutCharToPosition(rightWindow, NewVector2Int(1, 1), RENDERER_DEFAULT_TEXT_ATTRIBUTE, '>');

    RendererWindow_Clear(leftBottomWindow);
    RendererWindow_PutCharToPosition(leftBottomWindow, NewVector2Int(1, 1), RENDERER_DEFAULT_TEXT_ATTRIBUTE, '>');

    RendererWindow_PutStringToPositionWrap(leftBottomWindow, NewVector2Int(2, 1), NULL, "AI Response: %s", response);

    free(query);
    free(response);
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
