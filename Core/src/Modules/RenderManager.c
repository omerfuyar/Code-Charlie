#include "Modules/RenderManager.h"

#include "Modules/InputManager.h"

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
    stringHeap title;
    int colorPairHandle;

    RendererTextAttributeMask mask;
    RendererColorPair colorPair;
} RendererTextAttribute;

typedef struct RendererWindow
{
    stringHeap title;
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
    DebugAssert(window->windowHandle != NULL, "Window handle creation failed for '%s'", window->title);

    box(window->windowHandle, '|', '-');
}

/// @brief Enables the text attribute for the specified attribute.
/// @param attribute Text attribute to enable.
void RendererTextAttribute_Enable(const RendererTextAttribute *attribute)
{
    attron(COLOR_PAIR(attribute->colorPairHandle));
    attron(attribute->mask);
}

/// @brief Disables the text attribute for the specified attribute.
/// @param attribute Text attribute to disable.
void RendererTextAttribute_Disable(const RendererTextAttribute *attribute)
{
    attroff(COLOR_PAIR(attribute->colorPairHandle));
    attroff(attribute->mask);
}

#pragma endregion Source Only

void RendererManager_Initialize()
{
    initscr();     // curses initialize screen
    start_color(); // curses start the color functionality

    RENDERER_DEFAULT_TEXT_ATTRIBUTE = RendererTextAttribute_Create("Default", RendererTextAttributeMask_Normal, (RendererColorPair){RendererColor_White, RendererColor_Black});

    RENDERER_MAIN_WINDOW = (RendererWindow *)malloc(sizeof(RendererWindow));
    DebugAssert(RENDERER_MAIN_WINDOW != NULL, "Memory allocation failed for RENDERER_MAIN_WINDOW.");

    RENDERER_MAIN_WINDOW->windowHandle = stdscr;
    RENDERER_MAIN_WINDOW->title = "Main Window";
    RENDERER_MAIN_WINDOW->size = NewVector2Int(COLS, LINES);
    RENDERER_MAIN_WINDOW->relativePosition = NewVector2Int(0, 0);
    RENDERER_MAIN_WINDOW->globalPosition = NewVector2Int(0, 0);
    RENDERER_MAIN_WINDOW->parent = NULL;

    RendererWindow_SetDefaultAttribute(RENDERER_MAIN_WINDOW, RENDERER_DEFAULT_TEXT_ATTRIBUTE);

    DebugInfo("Main window created successfully. Terminal size : (%d, %d)", RENDERER_MAIN_WINDOW->size.x, RENDERER_MAIN_WINDOW->size.y);
}

void RendererManager_Terminate()
{
    endwin(); // ncurses terminate
}

void RendererManager_ChangeColor(RendererColor color, Vector3Int colorToChangeTo)
{
    DebugAssert(can_change_color(), "Your terminal doesn't have support for changing colors.");

    init_color(color, colorToChangeTo.x, colorToChangeTo.y, colorToChangeTo.z);

    DebugInfo("Terminal color changed successfully.");
}

void RendererManager_SetCursorVisibility(RendererCursorVisibility visibility)
{
    curs_set(visibility);

    DebugInfo("Cursor visibility set successfully.");
}

RendererTextAttribute *RendererTextAttribute_Create(const string title, RendererTextAttributeMask mask, RendererColorPair colorPair)
{
    RendererTextAttribute *attribute = (RendererTextAttribute *)malloc(sizeof(RendererTextAttribute));
    DebugAssert(attribute != NULL, "Memory allocation failed.");

    attribute->title = StringDuplicate(title);
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

    char tempTitle[strlen(attribute->title) + 1];
    strcpy(tempTitle, attribute->title);

    free(attribute->title);
    attribute->title = NULL;

    free(attribute);
    attribute = NULL;

    DebugInfo("Text attribute '%s' destroyed successfully.", tempTitle);
}

void RendererTextAttribute_ChangeColor(RendererTextAttribute *attribute, RendererColorPair colorPair)
{
    DebugAssert(attribute != NULL, "Null pointer passed as parameter.");

    attribute->colorPair = colorPair;
    init_pair(attribute->colorPairHandle, colorPair.x, colorPair.y);

    DebugInfo("Text attribute color changed successfully.");
}

RendererWindow *RendererWindow_Create(const string title, Vector2Int position, Vector2Int size, RendererWindow *parentWindow)
{
    DebugAssert(title != NULL, "Null pointer passed as parameter. Title cannot be NULL.");
    DebugAssert(parentWindow != NULL, "Null pointer passed as parameter. Parent window cannot be NULL.");

    RendererWindow *window = (RendererWindow *)malloc(sizeof(RendererWindow));
    DebugAssert(window != NULL, "Memory allocation failed.");

    window->title = StringDuplicate(title);

    RendererWindow_SetSize(window, size);
    RendererWindow_SetPosition(window, position, false);
    RendererWindow_SetParent(window, parentWindow);
    RendererWindow_SetDefaultAttribute(window, RENDERER_DEFAULT_TEXT_ATTRIBUTE);
    RendererWindow_CreateHandle(window);

    RendererWindow_UpdateAppearance(window);
    RendererWindow_UpdateContent(window);

    DebugInfo("Renderer window '%s' created successfully.", window->title);
    return window;
}

void RendererWindow_Destroy(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    RendererWindow_DestroyHandle(window);
    free(window->title);
    window->parent = NULL;
    window->windowHandle = NULL;
    window->defaultAttribute = NULL;

    char tempTitle[strlen(window->title) + 1];
    strcpy(tempTitle, window->title);
    window->title = NULL;

    free(window);
    window = NULL;

    DebugInfo("Renderer window '%s' destroyed successfully.", tempTitle);
}

void RendererWindow_UpdateContent(const RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    if (window->parent != NULL)
    {
        RendererWindow_UpdateContent(window->parent);
    }
    wrefresh(window->windowHandle);

    DebugInfo("Renderer window '%s' content updated successfully.", window->title);
}

void RendererWindow_UpdateAppearance(RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");
    DebugAssert(window->parent != NULL, "Renderer window '%s' has no parent. Parent cannot be NULL.", window->title);

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

    DebugInfo("Renderer window '%s' appearance updated successfully.", window->title);
}

void RendererWindow_Clear(const RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    wclear(window->windowHandle);
    box(window->windowHandle, '|', '-');

    DebugInfo("Renderer window '%s' cleared successfully.", window->title);
}

void RendererWindow_SetCursorPosition(const RendererWindow *window, Vector2Int position)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    if (position.x < 0 || position.x > window->size.x ||
        position.y < 0 || position.y > window->size.y)
    {
        DebugWarning("Renderer window '%s': Invalid cursor position (%d, %d). Position must be within the window size (%d, %d).", window->title, position.x, position.y, window->size.x, window->size.y);
        position.x = position.x < 0 ? 0 : (position.x > window->size.x ? window->size.x - 1 : position.x);
        position.y = position.y < 0 ? 0 : (position.y > window->size.y ? window->size.y - 1 : position.y);
    }

    wmove(window->windowHandle, position.y, position.x);

    // DebugInfo("Renderer window '%s': Cursor moved to position (%d, %d) successfully.", window->title, position.x, position.y);
}

Vector2Int RendererWindow_GetCursorPosition(const RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    int y, x;
    getyx(window->windowHandle, y, x);
    Vector2Int cursorPosition = NewVector2Int(x, y);

    return cursorPosition;
}

void RendererWindow_PutCharToPosition(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attribute, char charToPut)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    RendererWindow_SetCursorPosition(window, position);
    RendererTextAttribute_Enable(attribute ? attribute : window->defaultAttribute);
    waddch(window->windowHandle, charToPut);
    RendererTextAttribute_Disable(attribute ? attribute : window->defaultAttribute);

    RendererWindow_UpdateContent(window);
}

void RendererWindow_PutStringToPosition(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attribute, const string stringToPut, ...)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    char buffer[RENDERER_PRINT_STRING_BUFFER_SIZE];
    va_list args;
    va_start(args, stringToPut);
    vsnprintf(buffer, sizeof(buffer), stringToPut, args);
    va_end(args);

    RendererWindow_SetCursorPosition(window, position);
    RendererTextAttribute_Enable(attribute ? attribute : window->defaultAttribute);
    wprintw(window->windowHandle, "%s", buffer);
    RendererTextAttribute_Disable(attribute ? attribute : window->defaultAttribute);

    RendererWindow_UpdateContent(window);

    DebugInfo("Window '%s': String '%s' put to position (%d, %d) successfully.", window->title, stringToPut, position.x, position.y);
}

void RendererWindow_PutStringToPositionWrap(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attribute, const string stringToPut, ...)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    Vector2Int maxBounds = NewVector2Int(window->size.x - 2, window->size.y - 2);

    char buffer[RENDERER_PRINT_STRING_BUFFER_SIZE];
    va_list args;
    va_start(args, stringToPut);
    vsnprintf(buffer, sizeof(buffer), stringToPut, args);
    va_end(args);

    stringStack word = strtok(buffer, " ");

    while (word != NULL)
    {
        Vector2Int cursorPos = RendererWindow_GetCursorPosition(window);

        if (cursorPos.x + (int)strlen(word) > maxBounds.x)
        {
            cursorPos.y++;
            cursorPos.x = position.x;

            if (cursorPos.y > maxBounds.y)
            {
                DebugError("Not enough vertical space.");
                return;
            }
        }

        DebugInfo("word : %s ", word);
        RendererWindow_PutStringToPosition(window, cursorPos, attribute, "%s ", word);

        word = strtok(NULL, " ");
    }

    RendererWindow_UpdateContent(window);

    DebugInfo("Window '%s': Wrapped string put to position (%d, %d) successfully.", window->title, position.x, position.y);
}

void RendererWindow_DeleteRangeInPosition(const RendererWindow *window, Vector2Int position, size_t range)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    RendererWindow_SetCursorPosition(window, position);
    RendererTextAttribute_Enable(window->defaultAttribute);
    for (size_t i = 0; i < range; i++)
    {
        waddch(window->windowHandle, ' ');
    }
    RendererTextAttribute_Disable(window->defaultAttribute);

    RendererWindow_UpdateContent(window);
}

stringHeap RendererManager_GetStringAtPosition(const RendererWindow *window, Vector2Int position, int *endKey)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    stringHeap finalString = NULL;

    char inputString[INPUT_STRING_WORD_BUFFER_SIZE] = {0};
    inputString[0] = '\0';
    size_t inputIndex = 0;

    Vector2Int cursorPos = position;

    int character;

    RendererWindow_SetCursorPosition(window, cursorPos);

    while ((character = wgetch(window->windowHandle)) != ERR)
    {
        if (inputIndex >= INPUT_STRING_WORD_BUFFER_SIZE - 2 || inputIndex < 0) // error
        {
            DebugError("Index error. Returning uncompleted string.");
            *endKey = InputKeyCode_Kolpa;
            break;
        }
        else if (character == InputKeyCode_Enter || character == '\n') // enter
        {
            *endKey = InputKeyCode_Enter;
            break;
        }
        else if (character == InputKeyCode_Space || character == ' ') // space
        {
            RendererWindow_PutCharToPosition(window, cursorPos, NULL, (char)character);
            inputString[inputIndex] = ' ';
            inputIndex++;
            cursorPos.x++;
            *endKey = InputKeyCode_Space;
            break;
        }
        else if (character == InputKeyCode_Delete || character == '\b' || character == InputKeyCode_Backspace) // backspace
        {
            *endKey = InputKeyCode_Backspace;
            break;
        }
        else if (character == InputKeyCode_Kolpa || character < 0) // invalid character
        {
            DebugWarning("Invalid character received: %d. Ignoring.", character);
            continue;
        }
        else if (character < InputKeyCode_Delete && character > InputKeyCode_Space) // normal characters
        {
            RendererWindow_PutCharToPosition(window, cursorPos, NULL, (char)character);
            inputString[inputIndex] = (char)character;
            inputIndex++;
            cursorPos.x++;
        }
    }

    inputString[inputIndex] = '\0';
    finalString = StringDuplicate(inputString);
    DebugWarning("Final string: '%s', endKey: %ld", finalString, *endKey);
    return finalString;
}

stringHeap RendererManager_GetStringAtPositionWrap(const RendererWindow *window, Vector2Int position)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    stringHeap finalString = NULL;

    char inputString[INPUT_STRING_FULL_BUFFER_SIZE] = {0};
    inputString[0] = '\0';
    size_t inputIndex = 0;

    const Vector2Int maxBounds = NewVector2Int(window->size.x - 2, window->size.y - 2);
    Vector2Int cursorPos = position;
    size_t wordLength = 0;

    stringHeap word = NULL;
    int endKey = InputKeyCode_Kolpa;

    RendererManager_SetCursorVisibility(RendererCursorVisibility_Visible);

    do
    {
        word = RendererManager_GetStringAtPosition(window, cursorPos, &endKey);
        wordLength = strlen(word);

        RendererWindow_DeleteRangeInPosition(window, cursorPos, wordLength);

        if (endKey == InputKeyCode_Space || endKey == InputKeyCode_Enter)
        {
            if (inputIndex + wordLength >= INPUT_STRING_FULL_BUFFER_SIZE - 1)
            {
                DebugError("Input string buffer overflow. Returning uncompleted string.");
                free(word);
                break;
            }

            strcat(inputString, word);
            inputIndex += wordLength;

            if (cursorPos.x + (int)wordLength > maxBounds.x)
            {
                cursorPos.y++;
                cursorPos.x = 2;

                if (cursorPos.y > maxBounds.y)
                {
                    DebugError("Not enough vertical space. Returning uncompleted string.");
                    free(word);
                    break;
                }
            }

            RendererWindow_PutStringToPosition(window, cursorPos, NULL, word);
            cursorPos.x += wordLength;
        }
        else if (endKey == InputKeyCode_Backspace)
        {
            if (inputIndex + wordLength == 0)
            {
                free(word);
                continue;
            }
            else if (inputIndex + wordLength >= INPUT_STRING_FULL_BUFFER_SIZE - 1 && inputIndex < 0)
            {
                DebugError("Input string buffer overflow. Returning uncompleted string.");
                free(word);
                break;
            }

            strcat(inputString, word);
            inputIndex += wordLength - 1;
            inputString[inputIndex] = '\0';

            if (cursorPos.x + wordLength < 2)
            {
                cursorPos.x = maxBounds.x;
                cursorPos.y--;

                if (cursorPos.y < 2)
                {
                    DebugError("Not enough vertical space. Returning uncompleted string.");
                    free(word);
                    break;
                }

                RendererWindow_PutStringToPosition(window, cursorPos, NULL, word);
            }
            else
            {
                RendererWindow_PutStringToPosition(window, cursorPos, NULL, word);
                cursorPos.x += wordLength - 1;
            }

            RendererWindow_DeleteRangeInPosition(window, cursorPos, 1);
        }
        else
        {
            DebugWarning("Unrecognized end key: %d. Continuing.", endKey);
            free(word);
            continue;
        }

        free(word);
    } while (endKey == InputKeyCode_Space || endKey == InputKeyCode_Backspace);

    RendererManager_SetCursorVisibility(RendererCursorVisibility_Default);

    inputString[inputIndex] = '\0';
    finalString = StringDuplicate(inputString);

    DebugWarning("Final input string: '%s'", finalString);
    return finalString;
}

Vector2Int RendererWindow_GetWindowSize(const RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    // DebugInfo("Renderer window '%s' size (%d, %d) retrieved successfully.", window->title, window->size.x, window->size.y);
    return window->size;
}

Vector2Int RendererWindow_GetWindowPosition(const RendererWindow *window)
{
    DebugAssert(window != NULL, "Null pointer passed as parameter. Renderer window cannot be NULL.");

    // DebugInfo("Renderer window '%s' position retrieved successfully.", window->title);
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
