#include "Modules/RenderManager.h"

#include <ncurses.h>

//! Source only code should be used consciously.
//! as it is not meant to be used outside of this file,
//! there is no error checking, and it is not part of the app side.
#pragma region Source Only

/// @brief Global index for color pairs. Used to assign unique handles to color pairs.
int COLOR_PAIR_INDEX = 0;

/// @brief Global pointer to the main renderer window.
RendererWindow *mainWindow = NULL;

typedef struct RendererTextAttribute
{
    RendererTextAttributeMask mask;
    RendererColorPair colorPair;
    int colorPairHandle;
} RendererTextAttribute;

typedef struct RendererWindow
{
    WINDOW *windowHandle;

    Vector2Int windowSize;
    Vector2Int windowPosition;
    Vector2Int cursorPosition;

    // short _flags; /* window state flags */
    //
    // struct ldat *_line; /* the actual line data */
    //
    // NCURSES_SIZE_T _regtop;    /* top line of scrolling region */
    // NCURSES_SIZE_T _regbottom; /* bottom line of scrolling region */
    //
    ///* these are used only if this is a sub-window */
    // int _parx;       /* x coordinate of this window in parent */
    // int _pary;       /* y coordinate of this window in parent */
    // WINDOW *_parent; /* pointer to parent if a sub-window */
    //
    ///* these are used only if this is a pad */
    // struct pdat
    //{
    //     NCURSES_SIZE_T _pad_y, _pad_x;
    //     NCURSES_SIZE_T _pad_top, _pad_left;
    //     NCURSES_SIZE_T _pad_bottom, _pad_right;
    // } _pad;
    //
    // NCURSES_SIZE_T _yoffset; /* real begy is _begy + _yoffset */
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
    initscr();             // ncurses initialize screen
    noecho();              // ncurses echo disable, no writing while getting input
    start_color();         // ncurses start the color functionality
    cbreak();              // ncurses disable line buffering but take CTRL^C commands
    keypad(stdscr, true);  // ncurses enable keys like arrow and function
    nodelay(stdscr, true); // ncurses disable blocking on getch()
    // timeout(TARGET_SLEEP_NANOSECONDS * 1000000);
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

// todo
RendererWindow *Renderer_GetMainWindow()
{
    if (mainWindow == NULL)
    {
        mainWindow = (RendererWindow *)malloc(sizeof(RendererWindow));
        DebugAssert(mainWindow != NULL, "Memory allocation failed.");

        mainWindow->windowHandle = stdscr;
        // todo ...
    }

    DebugInfo("Main window returned successfully");
    return mainWindow;
}

void Renderer_SetCursorVisibility(RendererCursorVisibility visibility)
{
    curs_set(visibility);

    DebugInfo("Cursor visibility set successfully.");
}

RendererTextAttribute *RendererTextAttribute_Create(RendererTextAttributeMask mask, RendererColorPair colorPair)
{
    RendererTextAttribute *attribute = (RendererTextAttribute *)malloc(sizeof(RendererTextAttribute));
    DebugAssert(attribute != NULL, "Memory allocation failed.");

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

// todo
RendererWindow *RendererWindow_Create(Vector2Int position, Vector2Int size)
{
    RendererWindow *window = (RendererWindow *)malloc(sizeof(RendererWindow));
    DebugAssert(window != NULL, "Memory allocation failed.");

    window->windowHandle = newwin(size.y, size.x, position.y, position.x);
    box(window->windowHandle, 0, 0);

    // todo ...

    DebugInfo("Renderer window created successfully.");
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

    DebugInfo("Renderer window destroyed successfully.");
}

void RendererWindow_Update(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    wrefresh(window->windowHandle);

    DebugInfo("Renderer window updated successfully.");
}

void RendererWindow_Clear(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    wclear(window->windowHandle);

    DebugInfo("Renderer window cleared successfully.");
}

void RendererWindow_PutCharToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, char charToPut)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    RendererWindow_MoveCursorToPosition(window, position);
    RendererTextAttribute_Enable(attributeMask);
    waddch(window->windowHandle, charToPut);
    RendererTextAttribute_Disable(attributeMask);

    DebugInfo("Character %c put to position (%d, %d) successfully.", charToPut, position.x, position.y);
}

void RendererWindow_PutStringToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, bool override, const char *stringToPut, ...)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

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

    DebugInfo("String '%s' put to position (%d, %d) successfully.", stringToPut, position.x, position.y);
}

Vector2Int RendererWindow_GetWindowSize(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter.");

    DebugInfo("Renderer window size retrieved successfully.");
    return window->windowSize;
}