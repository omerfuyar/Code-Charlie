#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"

static const char *stateStrings[] = {
    "Released",
    "Pressed"};

void App_Start()
{
}

void App_StartLate()
{
}

void App_Update()
{
    DebugInfo("%p, %p", RENDERER_MAIN_WINDOW, RENDERER_DEFAULT_TEXT_ATTRIBUTE);

    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 2}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "x key is pressed %d", InputManager_GetKey(InputKeyState_Pressed, InputKeyCode_x));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 4}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "v key is released %d", InputManager_GetKey(InputKeyState_Released, InputKeyCode_v));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 5}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "c key state: %s", stateStrings[InputManager_GetKeyState(InputKeyCode_c)]);
}

void App_UpdateLate()
{
}

void App_Stop(int exitCode)
{
}
