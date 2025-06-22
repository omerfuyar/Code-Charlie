#pragma once

#include "BaseGlobal.h"

#include "Maths/Vectors.h"

/// @brief Representing text attributes to be used in the terminal.
/// @note Values can be combined using bitwise OR operations.
typedef enum RendererTextAttributeMask
{
    Normal = (1U - 1U),               // Normal, plain text.
    Underline = (1U << 17),           // Underlining text.
    Blink = (1U << 19),               // Blinking text.
    Dim = (1U << 20),                 // Half bright text.
    Bold = (1U << 21),                // Extra bright or bold text.
    Invis = (1U << 23),               // Invisible or blank mode.
    Standout = (1U << 16),            // Best highlighting mode of the terminal.
    AlternateCharSet = (1U << 22),    // Alternate character set.
    CharText = ((1U << 8) - 1U) - 1U, // Bit-mask to extract a character.
    Reversed = (1U << 18),            // Reverse foreground and background colors.
    Protected = (1U << 24)            // Protected mode.
} RendererTextAttributeMask;

/// @brief Representing text and background colors to be used in the terminal.
typedef enum RendererColor
{
    Black = 0,
    Red = 1,
    Green = 2,
    Yellow = 3,
    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7
} RendererColor;

/// @brief Represents the visibility of the cursor in the terminal.
typedef enum RendererCursorVisibility
{
    Invisible = 0, // Cursor is invisible
    Default = 1,   // Normal cursor visibility
    Visible = 2    // Cursor is visible
} RendererCursorVisibility;

/// @brief Vector representing text and background colors.
/// @note Should be used with only 'RendererColor' enum.
typedef Vector2Int RendererColorPair;

/// @brief Text attribute structure for rendering text in the terminal. Contains color pair and mask.
typedef struct RendererTextAttribute RendererTextAttribute;

/// @brief Window structure for rendering text in the terminal. Wrapper for ncurses window with some additions.
typedef struct RendererWindow RendererWindow;

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
RendererTextAttribute *RendererTextAttribute_Create(RendererTextAttributeMask mask, RendererColorPair colorPair);

/// @brief Destroys a text attribute and releases its resources.
/// @param attribute The text attribute to destroy.
void RendererTextAttribute_Destroy(RendererTextAttribute *attribute);

/// @brief Creates a renderer window.
/// @param position The position of the window in the terminal.
/// @param size The size of the window.
/// @return A pointer to the created renderer window.
RendererWindow *RendererWindow_Create(Vector2Int position, Vector2Int size);

/// @brief Destroys a renderer window and releases its resources.
/// @param window The renderer window to destroy.
void RendererWindow_Destroy(RendererWindow *window);

/// @brief Updates the renderer window.
/// @param window The renderer window to update.
void RendererWindow_Update(RendererWindow *window);

/// @brief Puts a character at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the character.
/// @param attributeMask The text attribute to apply.
/// @param charToPut The character to put.
void RendererWindow_PutCharToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, char charToPut);

/// @brief Puts a formatted string at a specific position in the renderer window.
/// @param window The renderer window.
/// @param position The position to put the string.
/// @param attributeMask The text attribute to apply.
/// @param stringToPut The formatted string to put.
/// @param ... Additional arguments for the formatted string.
void RendererWindow_PutStringToPosition(RendererWindow *window, Vector2Int position, RendererTextAttribute *attributeMask, const char *stringToPut, ...);

/// @brief Gets the size of the renderer window.
/// @param window The renderer window.
/// @return The size of the window as a Vector2Int.
Vector2Int RendererWindow_GetWindowSize(RendererWindow *window);