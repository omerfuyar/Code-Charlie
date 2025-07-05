#pragma once

#include "Core.h"

#include "Maths/Vectors.h"

#pragma region typedefs

/// @brief Representing text attributes to be used in the terminal.
/// @note Values can be combined using bitwise OR operations.
typedef enum RendererTextAttributeMask
{
    RendererTextAttributeMask_Kolpa = -1,                       // Invalid attributes.
    RendererTextAttributeMask_Normal = (1U - 1U),               // Normal, plain text.
    RendererTextAttributeMask_Underline = (1U << 17),           // Underlining text.
    RendererTextAttributeMask_Blink = (1U << 19),               // Blinking text.
    RendererTextAttributeMask_Dim = (1U << 20),                 // Half bright text.
    RendererTextAttributeMask_Bold = (1U << 21),                // Extra bright or bold text.
    RendererTextAttributeMask_Invis = (1U << 23),               // Invisible or blank mode.
    RendererTextAttributeMask_Standout = (1U << 16),            // Best highlighting mode of the terminal.
    RendererTextAttributeMask_AlternateCharSet = (1U << 22),    // Alternate character set.
    RendererTextAttributeMask_CharText = ((1U << 8) - 1U) - 1U, // Bit-mask to extract a character.
    RendererTextAttributeMask_Reversed = (1U << 18),            // Reverse foreground and background colors.
    RendererTextAttributeMask_Protected = (1U << 24)            // Protected mode.
} RendererTextAttributeMask;

/// @brief Representing text and background colors to be used in the terminal.
typedef enum RendererColor
{
    RendererColor_Kolpa = -1,
    RendererColor_Black = 0,
    RendererColor_Red = 1,
    RendererColor_Green = 2,
    RendererColor_Yellow = 3,
    RendererColor_Blue = 4,
    RendererColor_Magenta = 5,
    RendererColor_Cyan = 6,
    RendererColor_White = 7
} RendererColor;

/// @brief Represents the visibility of the cursor in the terminal.
typedef enum RendererCursorVisibility
{
    RendererCursorVisibility_Invisible = 0, // Cursor is invisible
    RendererCursorVisibility_Default = 1,   // Normal cursor visibility
    RendererCursorVisibility_Visible = 2    // Cursor is visible
} RendererCursorVisibility;

/// @brief Vector representing text and background colors.
/// @note Should be used with only 'RendererColor' enum.
typedef Vector2Int RendererColorPair;

/// @brief Vector representing the borders of a renderer window.
/// @note X : Vertical borders, Y : Horizontal borders, Z : All 4 corners
typedef Vector3Int RendererWindowBorders;

/// @brief Text attribute structure for rendering text in the terminal. Contains color pair and mask.
typedef struct RendererTextAttribute RendererTextAttribute;

/// @brief Window structure for rendering text in the terminal. Wrapper for ncurses window with some additions.
typedef struct RendererWindow RendererWindow;

#pragma endregion typedefs

/// @brief Global pointer to the main renderer window.
extern RendererWindow *RENDERER_MAIN_WINDOW;

/// @brief Global pointer to the default text attribute.
extern RendererTextAttribute *RENDERER_DEFAULT_TEXT_ATTRIBUTE;

/// @brief Initializes the renderer module. Should not be used by app.
void RendererManager_Initialize();

/// @brief Stops the renderer module. Should not be used by app.
void RendererManager_Terminate();

/// @brief Changes the color of the terminal.
/// @param color The color to change.
/// @param colorToChangeTo The RGB values to change the color to.
/// @note Should be used within only 0-1000 range. User's terminal should support changing colors.
void RendererManager_ChangeColor(RendererColor color, Vector3Int colorToChangeTo);

/// @brief Sets the visibility of the cursor in the terminal.
/// @param visibility The desired cursor visibility.
void RendererManager_SetCursorVisibility(RendererCursorVisibility visibility);

/// @brief Creates a text attribute for rendering text in the terminal.
/// @param mask The text attribute mask (e.g., Bold, Underline).
/// @param colorPair The foreground and background colors.
/// @return A pointer to the created text attribute.
RendererTextAttribute *RendererTextAttribute_Create(const string title, RendererTextAttributeMask mask, RendererColorPair colorPair);

/// @brief Destroys a text attribute and releases its resources.
/// @param attribute The text attribute to destroy.
void RendererTextAttribute_Destroy(RendererTextAttribute *attribute);

/// @brief Changes the color pair of a text attribute.
/// @param attribute The text attribute to change.
/// @param colorPair The new color pair to assign.
void RendererTextAttribute_ChangeColor(RendererTextAttribute *attribute, RendererColorPair colorPair);

/// @brief Creates a renderer window.
/// @param position The position of the window in the terminal.
/// @param size The size of the window.
/// @param title The title of the window.
/// @param parentWindow The parent renderer window. if NULL, the main window will be used.
/// @return A pointer to the created renderer window.
/// @note Position origin is always top left corner
RendererWindow *RendererWindow_Create(const string title, Vector2Int position, Vector2Int size, RendererWindow *parentWindow);

/// @brief Destroys a renderer window and releases its resources.
/// @param window The renderer window to destroy.
void RendererWindow_Destroy(RendererWindow *window);

/// @brief Updates/renders the renderer window. Used for redrawing the curses window content.
/// @param window The renderer window to update/renders.
void RendererWindow_UpdateContent(const RendererWindow *window);

/// @brief Updates the global position of the window based on its relative position and parent's global position. Used for tasks that destroy and create the curses window.
/// @param window Window to update global position for.
/// @note This function should be called after the curses window is created.
void RendererWindow_UpdateAppearance(RendererWindow *window);

/// @brief Clears the renderer window. Deletes all the content.
/// @param window The renderer window to clear.
void RendererWindow_Clear(const RendererWindow *window);

/// @brief Moves the cursor to the specified position in the window.
/// @param window Window to move the cursor in.
/// @param position Position to move the cursor to.
void RendererWindow_SetCursorPosition(const RendererWindow *window, Vector2Int position);

/// @brief Gets the current cursor position in the window.
/// @param window The renderer window.
/// @return The current cursor position as a Vector2Int.
Vector2Int RendererWindow_GetCursorPosition(const RendererWindow *window);

/// @brief Puts a character at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the character. Relative to the window's position.
/// @param attributeMask The text attribute to apply. If NULL, window default will be used.
/// @param override Override the text that already in position.
/// @param charToPut The character to put.
/// @note Position origin is always top left corner
void RendererWindow_PutCharToPosition(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attributeMask, bool override, char charToPut);

/// @brief Puts a formatted string at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the string.
/// @param attributeMask The text attribute to apply. If NULL, window default will be used.
/// @param stringToPut The formatted string to put.
/// @param override Override the text that already in position.
/// @param ... Additional arguments for the formatted string.
/// @note Position origin is always top left corner
void RendererWindow_PutStringToPosition(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attributeMask, bool override, const string stringToPut, ...);

/// @brief Puts a formatted string at a specific position in the renderer window. Wraps the text if it exceeds the window width.
/// @param window The renderer window.
/// @param position The position to put the string.
/// @param attributeMask The text attribute to apply. If NULL, window default will be used.
/// @param override Override the text that already in position.
/// @param stringToPut The formatted string to put.
/// @param ... Additional arguments for the formatted string.
/// @note Position origin is always top left corner
void RendererWindow_PutStringToPositionWrap(const RendererWindow *window, Vector2Int position, const RendererTextAttribute *attributeMask, bool override, const string stringToPut, ...);

/// @brief Gets the size of the renderer window.
/// @param window The renderer window.
/// @return The size of the window as a Vector2Int.
Vector2Int RendererWindow_GetWindowSize(const RendererWindow *window);

/// @brief Gets the position of the renderer window.
/// @param window The renderer window.
/// @return The position of the window as a Vector2Int.
Vector2Int RendererWindow_GetWindowPosition(const RendererWindow *window);

/// @brief Sets the border characters for the renderer window.
/// @param window Renderer window to set the border characters for.
/// @param borders Border chars to set for the renderer window. Read from RendererWindowBorders.
void RendererWindow_SetBorderChars(RendererWindow *window, RendererWindowBorders borders);

/// @brief Sets the size of the window to new size.
/// @param window Renderer window to change size.
/// @param newSize New size to set for renderer window.
void RendererWindow_SetSize(RendererWindow *window, Vector2Int newSize);

/// @brief Sets the position of the window to new position.
/// @param window Renderer window to change position.
/// @param newPosition New position to set for renderer window.
/// @param add If true, the new position will be added to the current position.
void RendererWindow_SetPosition(RendererWindow *window, Vector2Int newPosition, bool add);

/// @brief Sets the parent window for the renderer window.
/// @param window The renderer window.
/// @param parentWindow The parent window to set.
void RendererWindow_SetParent(RendererWindow *window, RendererWindow *parentWindow);

/// @brief Sets the default text attribute for the renderer window.
/// @param window The renderer window to set the default attribute for.
/// @param defaultAttribute The default text attribute to set.
void RendererWindow_SetDefaultAttribute(RendererWindow *window, RendererTextAttribute *defaultAttribute);
