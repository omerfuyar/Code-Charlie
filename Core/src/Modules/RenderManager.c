#include "Modules/RenderManager.h"

#if PLATFORM_WINDOWS
#include <curses.h>
#else
#include <ncurses.h>
#endif

#pragma region Source Only

/// @brief Global index for color pairs. Used to assign unique handles to color pairs.
int COLOR_PAIR_INDEX = 0;

/// @brief The main renderer window.
RendererWindow *RENDERER_MAIN_WINDOW = NULL;

/// @brief The default text attribute for the renderer.
RendererTextAttribute *RENDERER_DEFAULT_TEXT_ATTRIBUTE = NULL;

typedef struct RendererTextAttribute
{
    const char *title;
    int colorPairHandle;

    RendererTextAttributeMask mask;
    RendererColorPair colorPair;
} RendererTextAttribute;

typedef struct RendererWindow
{
    const char *title;
    WINDOW *windowHandle;

    Vector2Int windowSize;
    Vector2Int windowPosition;
    Vector2Int cursorPosition;

    RendererTextAttribute *defaultAttribute;
    chtype borderChars[8];

    struct RendererWindow *parent;
} RendererWindow;

/// @brief Moves the cursor to the specified position in the window.
/// @param window Window to move the cursor in.
/// @param position Position to move the cursor to.
void RendererWindow_MoveCursorToPosition(RendererWindow *window, Vector2Int position)
{
    wmove(window->windowHandle, position.y, position.x);
    window->cursorPosition = position;
}

/// @brief Enables the text attribute for the specified attribute.
/// @param attribute Text attribute to enable.
void RendererTextAttribute_Enable(RendererTextAttribute *attribute)
{
    attron(COLOR_PAIR(attribute->colorPairHandle));
    attron(attribute->mask);
}

/// @brief Disables the text attribute for the specified attribute.
/// @param attribute Text attribute to disable.
void RendererTextAttribute_Disable(RendererTextAttribute *attribute)
{
    attroff(COLOR_PAIR(attribute->colorPairHandle));
    attroff(attribute->mask);
}

#pragma endregion

void Renderer_Initialize()
{
    initscr();     // curses initialize screen
    start_color(); // curses start the color functionality

    RENDERER_DEFAULT_TEXT_ATTRIBUTE = RendererTextAttribute_Create("Default", RendererTextAttributeMask_Normal, (RendererColorPair){RendererColor_White, RendererColor_Black});
    RENDERER_MAIN_WINDOW = Renderer_GetMainWindow();

    DebugInfo("main window : %p, main window handle : %p, default text attribute : %p", RENDERER_MAIN_WINDOW, RENDERER_MAIN_WINDOW->windowHandle, RENDERER_DEFAULT_TEXT_ATTRIBUTE);
}

void Renderer_Terminate()
{
    endwin(); // ncurses terminate
}

void Renderer_ChangeColor(RendererColor color, Vector3Int colorToChangeTo)
{
    DebugAssert(can_change_color(), "Your terminal doesn't have support for changing colors.");

    init_color(color, colorToChangeTo.x, colorToChangeTo.y, colorToChangeTo.z);

    DebugInfo("Terminal color changed successfully.");
}

RendererWindow *Renderer_GetMainWindow()
{
    if (RENDERER_MAIN_WINDOW == NULL)
    {
        RENDERER_MAIN_WINDOW = (RendererWindow *)malloc(sizeof(RendererWindow));
        DebugAssert(RENDERER_MAIN_WINDOW != NULL, "Memory allocation failed.");

        RENDERER_MAIN_WINDOW->windowHandle = stdscr;
        RENDERER_MAIN_WINDOW->windowSize = (Vector2Int){COLS, LINES};
        RENDERER_MAIN_WINDOW->windowPosition = (Vector2Int){0, 0};
        RENDERER_MAIN_WINDOW->cursorPosition = (Vector2Int){0, 0};
        RENDERER_MAIN_WINDOW->title = "Main Window";
        RENDERER_MAIN_WINDOW->defaultAttribute = RENDERER_DEFAULT_TEXT_ATTRIBUTE;
        RENDERER_MAIN_WINDOW->parent = NULL;

        DebugInfo("Main window created successfully");
    }

    return RENDERER_MAIN_WINDOW;
}

void Renderer_SetCursorVisibility(RendererCursorVisibility visibility)
{
    curs_set(visibility);

    DebugInfo("Cursor visibility set successfully.");
}

RendererTextAttribute *RendererTextAttribute_Create(const char *title, RendererTextAttributeMask mask, RendererColorPair colorPair)
{
    RendererTextAttribute *attribute = (RendererTextAttribute *)malloc(sizeof(RendererTextAttribute));
    DebugAssert(attribute != NULL, "Memory allocation failed.");

    attribute->title = title;
    attribute->mask = mask;

    attribute->colorPairHandle = COLOR_PAIR_INDEX++;
    init_pair(attribute->colorPairHandle, colorPair.x, colorPair.y);

    DebugInfo("Text attribute created successfully.");
    return attribute;
}

void RendererTextAttribute_Destroy(RendererTextAttribute *attribute)
{
    DebugAssert(attribute != NULL, "Null pointer passed as parameter.");

    attribute->colorPairHandle = -1;

    free(attribute);
    attribute = NULL;

    DebugInfo("Text attribute destroyed successfully.");
}

void RendererTextAttribute_ChangeColor(RendererTextAttribute *attribute, RendererColorPair colorPair)
{
    DebugAssert(attribute != NULL, "Null pointer passed as parameter.");

    attribute->colorPair = colorPair;
    init_pair(attribute->colorPairHandle, colorPair.x, colorPair.y);

    DebugInfo("Text attribute color changed successfully.");
}

RendererWindow *RendererWindow_Create(const char *title, Vector2Int position, Vector2Int size)
{
    RendererWindow *window = (RendererWindow *)malloc(sizeof(RendererWindow));
    DebugAssert(window != NULL, "Memory allocation failed.");

    window->windowHandle = newwin(size.y, size.x, position.y, position.x);

    window->windowSize = (Vector2Int){COLS, LINES};
    window->windowPosition = (Vector2Int){0, 0};
    window->cursorPosition = (Vector2Int){0, 0};
    window->title = title;
    window->defaultAttribute = RENDERER_DEFAULT_TEXT_ATTRIBUTE;
    window->parent = NULL;

    // todo ...

    box(window->windowHandle, 0, 0);

    DebugInfo("Renderer window '%s' created successfully.", window->title);
    return window;
}

RendererWindow *RendererWindow_CreateAsChild(RendererWindow *parentWindow, const char *title, Vector2Int position, Vector2Int size)
{
    RendererWindow *window = RendererWindow_Create(title, position, size);
    window->parent = parentWindow;

    DebugInfo("Renderer window '%s' created as child of '%s'.", window->title, parentWindow->title);
    return window;
}

void RendererWindow_Destroy(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    wborder(window->windowHandle, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window->windowHandle);
    delwin(window->windowHandle);
    free(window);
    window = NULL;

    DebugInfo("Renderer window '%s' destroyed successfully.", window->title);
}

void RendererWindow_SetBorderChars(RendererWindow *window, RendererWindowBorders borders)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    window->borderChars[0] = borders.x; // Left vertical border
    window->borderChars[1] = borders.x; // Right vertical border
    window->borderChars[2] = borders.y; // Top horizontal border
    window->borderChars[3] = borders.y; // Bottom horizontal border
    window->borderChars[4] = borders.z; // Top left corner
    window->borderChars[5] = borders.z; // Top right corner
    window->borderChars[6] = borders.z; // Bottom left corner
    window->borderChars[7] = borders.z; // Bottom right corner

    wborder(window->windowHandle, window->borderChars[0], window->borderChars[1], window->borderChars[2], window->borderChars[3],
            window->borderChars[4], window->borderChars[5], window->borderChars[6], window->borderChars[7]);

    DebugInfo("Renderer window '%s' border characters set successfully.", window->title);
}

void RendererWindow_Update(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");
    DebugAssert(window->windowHandle != NULL, "Null pointer passed as parameter.");

    wrefresh(window->windowHandle);

    DebugInfo("Renderer window '%s' updated successfully.", window->title);
}

void RendererWindow_Clear(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    wclear(window->windowHandle);

    DebugInfo("Renderer window '%s' cleared successfully.", window->title);
}

void RendererWindow_PutCharToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, char charToPut)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    RendererWindow_MoveCursorToPosition(window, position);
    RendererTextAttribute_Enable(attributeMask);
    waddch(window->windowHandle, charToPut);
    RendererTextAttribute_Disable(attributeMask);

    DebugInfo("Window '%s': Character %c put to position (%d, %d) successfully.", window->title, charToPut, position.x, position.y);
}

void RendererWindow_PutStringToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, bool override, const char *stringToPut, ...)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");
    DebugAssert(attributeMask != NULL, "Null pointer passed as parameter.");

    RendererWindow_MoveCursorToPosition(window, position);
    RendererTextAttribute_Enable(attributeMask);
    va_list args;
    va_start(args, stringToPut);
    if (override)
    {
        wclrtoeol(window->windowHandle);
    }
    vw_printw(window->windowHandle, stringToPut, args);
    va_end(args);
    RendererTextAttribute_Disable(attributeMask);

    DebugInfo("Window '%s': String '%s' put to position (%d, %d) successfully.", window->title, stringToPut, position.x, position.y);
}

Vector2Int RendererWindow_GetWindowSize(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    DebugInfo("Renderer window '%s' size retrieved successfully.", window->title);
    return window->windowSize;
}