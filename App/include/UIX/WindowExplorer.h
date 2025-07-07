#pragma once

#include "Core.h"

#include "Modules/RenderManager.h"
#include "Modules/InputManager.h"

void WindowExplorer_AddWindow(RendererWindow *window);

void WindowExplorer_SetFocus(RendererWindow *window);

void WindowExplorer_SplitHorizontal(RendererWindow *window);

void WindowExplorer_SplitVertical(RendererWindow *window);
