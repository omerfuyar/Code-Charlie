#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"

static const char *stateStrings[] = {
    "Released",
    "Down",
    "Up",
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

    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 1}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "z key is down %d", InputManager_GetKey(InputKeyState_Down, InputKeyCode_z));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 2}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "x key is pressed %d", InputManager_GetKey(InputKeyState_Pressed, InputKeyCode_x));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 3}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "c key is up %d", InputManager_GetKey(InputKeyState_Up, InputKeyCode_c));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 4}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "v key is released %d", InputManager_GetKey(InputKeyState_Released, InputKeyCode_v));
    RendererWindow_PutStringToPosition(RENDERER_MAIN_WINDOW, (Vector2Int){0, 5}, RENDERER_DEFAULT_TEXT_ATTRIBUTE, true, "a key state: %s", stateStrings[InputManager_GetKeyState(InputKeyCode_a)]);
}

void App_UpdateLate()
{
}

void App_Stop(int exitCode)
{
    _exit(exitCode);
}
