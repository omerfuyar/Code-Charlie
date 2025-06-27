#include "App.h"
#include "Modules/InputManager.h"
#include "Modules/RenderManager.h"

RendererWindow *window = NULL;
RendererTextAttribute *defaultTextAttribute = NULL;

void App_Start()
{
    DebugInfo("Starting the application...");
}

void App_StartLate()
{
    DebugInfo("Late Start");
    window = Renderer_GetMainWindow();
    defaultTextAttribute = RendererTextAttribute_Create(RendererTextAttributeMask_Normal, (RendererColorPair){RendererColor_White, RendererColor_Black});
}

void App_Update()
{
    DebugInfo("Update");

    char **stateStrings = (char *[]){
        "Released",
        "Down",
        "Up",
        "Pressed"};

    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 1}, defaultTextAttribute, true, "z key is down %d", InputManager_GetKey(InputKeyState_Down, InputKeyCode_z));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 2}, defaultTextAttribute, true, "x key is pressed %d", InputManager_GetKey(InputKeyState_Pressed, InputKeyCode_x));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 3}, defaultTextAttribute, true, "c key is up %d", InputManager_GetKey(InputKeyState_Up, InputKeyCode_c));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 4}, defaultTextAttribute, true, "v key is released %d", InputManager_GetKey(InputKeyState_Released, InputKeyCode_v));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 5}, defaultTextAttribute, true, "a key state: %s", stateStrings[InputManager_GetKeyState(InputKeyCode_a)]);
}

void App_UpdateLate()
{
}

void App_Stop(int exitCode)
{
    DebugInfo("Exiting from application...");

    _exit(exitCode);
}