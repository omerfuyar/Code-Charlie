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
    defaultTextAttribute = RendererTextAttribute_Create(Normal, (RendererColorPair){White, Black});
}

void App_Update()
{
    DebugInfo("Update");

    char **stateStrings = (char *[]){
        "Released",
        "Down",
        "Up",
        "Pressed"};

    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 1}, defaultTextAttribute, true, "z key is down %d", InputManager_GetKey(Down, Key_z));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 2}, defaultTextAttribute, true, "x key is pressed %d", InputManager_GetKey(Pressed, Key_x));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 3}, defaultTextAttribute, true, "c key is up %d", InputManager_GetKey(Up, Key_c));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 4}, defaultTextAttribute, true, "v key is released %d", InputManager_GetKey(Released, Key_v));
    RendererWindow_PutStringToPosition(window, (Vector2Int){0, 5}, defaultTextAttribute, true, "a key state: %s", stateStrings[InputManager_GetKeyState(Key_a)]);
}

void App_UpdateLate()
{
    // DebugInfo("Late Update");
    InputManager_PollInputs();
}

void App_Stop(int exitCode)
{
    DebugInfo("Exiting from application...");

    _exit(exitCode);
}