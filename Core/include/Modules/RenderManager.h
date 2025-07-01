#pragma once

#include "Core.h"

#include "Maths/Vectors.h"

#pragma region typedefs

/// @brief Representing text attributes to be used in the terminal.
/// @note Values can be combined using bitwise OR operations.
typedef enum RendererTextAttributeMask
{
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

#pragma endregion

/// @brief Global pointer to the main renderer window.
extern RendererWindow *RENDERER_MAIN_WINDOW;

/// @brief Global pointer to the default text attribute.
extern RendererTextAttribute *RENDERER_DEFAULT_TEXT_ATTRIBUTE;

/// @brief Initializes the renderer module. Should not be used by app.
void Renderer_Initialize();

/// @brief Stops the renderer module. Should not be used by app.
void Renderer_Terminate();

/// @brief Changes the color of the terminal.
/// @param color The color to change.
/// @param colorToChangeTo The RGB values to change the color to.
/// @note Should be used within only 0-1000 range. User's terminal should support changing colors.
void Renderer_ChangeColor(RendererColor color, Vector3Int colorToChangeTo);

/// @brief Getter function for the main renderer window.
/// @return The main window application running in the terminal.
RendererWindow *Renderer_GetMainWindow();

/// @brief Sets the visibility of the cursor in the terminal.
/// @param visibility The desired cursor visibility.
void Renderer_SetCursorVisibility(RendererCursorVisibility visibility);

/// @brief Creates a text attribute for rendering text in the terminal.
/// @param mask The text attribute mask (e.g., Bold, Underline).
/// @param colorPair The foreground and background colors.
/// @return A pointer to the created text attribute.
RendererTextAttribute *RendererTextAttribute_Create(const char *title, RendererTextAttributeMask mask, RendererColorPair colorPair);

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
/// @return A pointer to the created renderer window.
/// @note Position origin is always top left corner
RendererWindow *RendererWindow_Create(const char *title, Vector2Int position, Vector2Int size);

/// @brief Creates a renderer window as a child of another window.
/// @param parent The parent renderer window.
/// @param title The title of the child window.
/// @param position The position of the child window relative to the parent.
/// @param size The size of the child window.
/// @return A pointer to the created child window.
RendererWindow *RendererWindow_CreateAsChild(RendererWindow *parentWindow, const char *title, Vector2Int position, Vector2Int size);

/// @brief Destroys a renderer window and releases its resources.
/// @param window The renderer window to destroy.
void RendererWindow_Destroy(RendererWindow *window);

/// @brief Sets the border characters for the renderer window.
/// @param window The renderer window to set the border characters for.
/// @param borders Border chars to set for the renderer window. Read from RendererWindowBorders.
void RendererWindow_SetBorderChars(RendererWindow *window, RendererWindowBorders borders);

/// @brief Updates/renders the renderer window.
/// @param window The renderer window to update/renders.
void RendererWindow_Update(RendererWindow *window);

/// @brief Clears the renderer window. Deletes all the content.
/// @param window The renderer window to clear.
void RendererWindow_Clear(RendererWindow *window);

/// @brief Puts a character at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the character.
/// @param attributeMask The text attribute to apply.
/// @param charToPut The character to put.
/// @note Position origin is always top left corner
void RendererWindow_PutCharToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, char charToPut);

/// @brief Puts a formatted string at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the string.
/// @param attributeMask The text attribute to apply.
/// @param stringToPut The formatted string to put.
/// @param override Override the text that already in position.
/// @param ... Additional arguments for the formatted string.
/// @note Position origin is always top left corner
void RendererWindow_PutStringToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, bool override, const char *stringToPut, ...);

/// @brief Gets the size of the renderer window.
/// @param window The renderer window.
/// @return The size of the window as a Vector2Int.
Vector2Int RendererWindow_GetWindowSize(RendererWindow *window);
