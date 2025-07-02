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

    Vector2Int size;
    Vector2Int relativePosition;
    Vector2Int globalPosition;

    RendererTextAttribute *defaultAttribute;
    chtype borderChars[8];

    struct RendererWindow *parent;
} RendererWindow;

/// @brief Destroys and cleans the handle of the window.
/// @param window Window to destroy handle.
void RendererWindow_DestroyHandle(RendererWindow *window)
{
    wborder(window->windowHandle, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(window->windowHandle);

    window->windowHandle = NULL;
}

/// @brief Creates and sets the handle of the RendererWindow.
/// @param window window to set handle to.
void RendererWindow_CreateHandle(RendererWindow *window)
{
    window->windowHandle = newwin(window->size.y, window->size.x, window->globalPosition.y, window->globalPosition.x);
    DebugAssert(window->windowHandle, "Window handle creation failed for '%s'", window->title);

    box(window->windowHandle, '|', '-');
}

/// @brief Moves the cursor to the specified position in the window.
/// @param window Window to move the cursor in.
/// @param position Position to move the cursor to.
void RendererWindow_SetCursorPosition(RendererWindow *window, Vector2Int position)
{
    if (position.x < 0 || position.x > window->size.x ||
        position.y < 0 || position.y > window->size.y)
    {
        DebugWarning("Renderer window '%s': Invalid cursor position (%d, %d). Position must be within the window size (%d, %d).", window->title, position.x, position.y, window->size.x, window->size.y);
        position.x = position.x < 0 ? 0 : (position.x > window->size.x ? window->size.x - 1 : position.x);
        position.y = position.y < 0 ? 0 : (position.y > window->size.y ? window->size.y - 1 : position.y);
    }

    wmove(window->windowHandle, position.y, position.x);
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
        RENDERER_MAIN_WINDOW->title = "Main Window";
        RENDERER_MAIN_WINDOW->size = NewVector2Int(COLS, LINES);
        RENDERER_MAIN_WINDOW->relativePosition = NewVector2Int(0, 0);
        RENDERER_MAIN_WINDOW->globalPosition = NewVector2Int(0, 0);
        RENDERER_MAIN_WINDOW->parent = NULL;

        RendererWindow_SetDefaultAttribute(RENDERER_MAIN_WINDOW, RENDERER_DEFAULT_TEXT_ATTRIBUTE);

        DebugInfo("Main window created successfully. Terminal size : (%d, %d)", RENDERER_MAIN_WINDOW->size.x, RENDERER_MAIN_WINDOW->size.y);
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

    DebugInfo("Text attribute '%s' created successfully.", attribute->title);
    return attribute;
}

void RendererTextAttribute_Destroy(RendererTextAttribute *attribute)
{
    DebugAssert(attribute != NULL, "Null pointer passed as parameter.");

    attribute->colorPairHandle = -1;
    attribute->mask = RendererTextAttributeMask_Kolpa;
    attribute->colorPair = (RendererColorPair){RendererColor_Kolpa, RendererColor_Kolpa};
    attribute->title = NULL;

    free(attribute);
    attribute = NULL;

    DebugInfo("Text attribute '%s' destroyed successfully.", attribute->title);
}

void RendererTextAttribute_ChangeColor(RendererTextAttribute *attribute, RendererColorPair colorPair)
{
    DebugAssert(attribute != NULL, "Null pointer passed as parameter.");

    attribute->colorPair = colorPair;
    init_pair(attribute->colorPairHandle, colorPair.x, colorPair.y);

    DebugInfo("Text attribute color changed successfully.");
}

RendererWindow *RendererWindow_Create(const char *title, Vector2Int position, Vector2Int size, RendererWindow *parentWindow)
{
    DebugAssert(title != NULL, "Null pointer passed as parameter. Title cannot be NULL.");

    RendererWindow *window = (RendererWindow *)malloc(sizeof(RendererWindow));
    DebugAssert(window != NULL, "Memory allocation failed.");

    window->title = title;

    RendererWindow_SetSize(window, size);
    RendererWindow_SetPosition(window, position, false);
    RendererWindow_SetParent(window, parentWindow);
    RendererWindow_SetDefaultAttribute(window, RENDERER_DEFAULT_TEXT_ATTRIBUTE);
    RendererWindow_CreateHandle(window);
    RendererWindow_UpdateAppearance(window);

    DebugInfo("Renderer window '%s' created with parent '%s' successfully.", window->title, window->parent->title);
    return window;
}

void RendererWindow_Destroy(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    RendererWindow_DestroyHandle(window);
    window->defaultAttribute = NULL;
    window->parent = NULL;
    window->title = NULL;

    free(window);
    window = NULL;

    DebugInfo("Renderer window '%s' destroyed successfully.", window->title);
}

void RendererWindow_UpdateContent(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    wrefresh(window->windowHandle);

    DebugInfo("Renderer window '%s' updated.", window->title);
}

void RendererWindow_UpdateAppearance(RendererWindow *window)
{
    window->globalPosition = Vector2Int_Add(window->relativePosition, window->parent->globalPosition);

    if (window->globalPosition.x + window->size.x > COLS ||
        window->globalPosition.y + window->size.y > LINES)
    {
        Vector2Int newPosition = NewVector2Int(
            window->globalPosition.x + window->size.x > COLS ? COLS - window->size.x : window->globalPosition.x,
            window->globalPosition.y + window->size.y > LINES ? LINES - window->size.y : window->globalPosition.y);

        DebugWarning("Renderer window '%s' has invalid boundaries. (%d, %d) is not allowed. Moving to (%d, %d).",
                     window->title, window->globalPosition.x, window->globalPosition.y, newPosition.x, newPosition.y);

        window->relativePosition = newPosition;
    }

    RendererWindow_DestroyHandle(window);
    RendererWindow_CreateHandle(window);
}

void RendererWindow_Clear(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    wclear(window->windowHandle);

    DebugInfo("Renderer window '%s' cleared successfully.", window->title);
}

void RendererWindow_PutCharToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, bool override, char charToPut)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    RendererWindow_SetCursorPosition(window, position);
    RendererTextAttribute_Enable(attributeMask);
    if (override)
    {
        waddch(window->windowHandle, '\b');
    }
    waddch(window->windowHandle, charToPut);
    RendererTextAttribute_Disable(attributeMask);

    DebugInfo("Window '%s': Character %c put to position (%d, %d) successfully.", window->title, charToPut, position.x, position.y);
}

void RendererWindow_PutStringToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, bool override, const char *stringToPut, ...)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(attributeMask != NULL, "Null pointer passed as parameter. Renderer text attribute cannot be NULL.");

    RendererWindow_SetCursorPosition(window, position);
    RendererTextAttribute_Enable(attributeMask);
    va_list args;
    va_start(args, stringToPut);
    if (override)
    {
        for (int i = 0; i < (int)strlen(stringToPut); i++)
        {
            waddch(window->windowHandle, '\b');
        }
    }
    vw_printw(window->windowHandle, stringToPut, args);
    va_end(args);
    RendererTextAttribute_Disable(attributeMask);

    DebugInfo("Window '%s': String '%s' put to position (%d, %d) successfully.", window->title, stringToPut, position.x, position.y);
}

Vector2Int RendererWindow_GetWindowSize(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    DebugInfo("Renderer window '%s' size retrieved successfully.", window->title);
    return window->size;
}

Vector2Int RendererWindow_GetWindowPosition(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    DebugInfo("Renderer window '%s' position retrieved successfully.", window->title);
    return window->relativePosition;
}

void RendererWindow_SetBorderChars(RendererWindow *window, RendererWindowBorders borders)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

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

void RendererWindow_SetSize(RendererWindow *window, Vector2Int newSize)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(newSize.x > 0 && newSize.x <= COLS && newSize.y > 0 && newSize.y <= LINES, "Invalid size (%d, %d) passed.", newSize.x, newSize.y);

    Vector2Int oldSize = window->size;
    window->size = newSize;

    DebugInfo("Renderer window '%s' resized from (%d, %d) to (%d, %d)", window->title, oldSize.x, oldSize.y, newSize.x, newSize.y);
}

void RendererWindow_SetPosition(RendererWindow *window, Vector2Int newPosition, bool add)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(newPosition.x >= 0 && newPosition.x < COLS && newPosition.y >= 0 && newPosition.y < LINES, "Invalid position (%d, %d) passed.", newPosition.x, newPosition.y);

    Vector2Int oldPosition = window->relativePosition;
    window->relativePosition = add ? Vector2Int_Add(window->relativePosition, newPosition) : newPosition;

    DebugInfo("Renderer window '%s' moved from (%d, %d) to (%d, %d)", window->title, oldPosition.x, oldPosition.y, newPosition.x, newPosition.y);
}

void RendererWindow_SetParent(RendererWindow *window, RendererWindow *parentWindow)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(parentWindow != NULL, "Null pointer passed as parameter. Parent window cannot be NULL.");

    window->parent = parentWindow;

    DebugInfo("Renderer window '%s' parent set to '%s' successfully.", window->title, parentWindow->title);
}

void RendererWindow_SetDefaultAttribute(RendererWindow *window, RendererTextAttribute *defaultAttribute)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(defaultAttribute != NULL, "Null pointer passed as parameter. Default text attribute cannot be NULL.");

    window->defaultAttribute = defaultAttribute;

    DebugInfo("Renderer window '%s' default attribute set to '%s' successfully.", window->title, defaultAttribute->title);
}
