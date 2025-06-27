#pragma once

#include "Core.h"

// #define INPUT_KEY_BUFFER_SIZE 8

typedef enum InputMode
{
    InputMode_Key,
    InputMode_Text
} InputMode;

typedef enum InputKeyState
{
    InputKeyState_Released = 0,
    InputKeyState_Down = 1,
    InputKeyState_Up = 2,
    InputKeyState_Pressed = 3,
} InputKeyState;

typedef enum InputKeyCode
{
    InputKeyCode_NULL = 0,
    InputKeyCode_Tab = 9,
    InputKeyCode_Enter = 10,
    InputKeyCode_Escape = 27,

    InputKeyCode_Space = 32,
    InputKeyCode_Exclamation = 33,
    InputKeyCode_QuoteDouble = 34,
    InputKeyCode_Hash = 35,
    InputKeyCode_Dollar = 36,
    InputKeyCode_Percent = 37,
    InputKeyCode_Ampersand = 38,
    InputKeyCode_Quote = 39,
    InputKeyCode_LeftParenthesis = 40,
    InputKeyCode_RightParenthesis = 41,
    InputKeyCode_Asterisk = 42,
    InputKeyCode_Plus = 43,
    InputKeyCode_Comma = 44,
    InputKeyCode_Minus = 45,
    InputKeyCode_Period = 46,
    InputKeyCode_Slash = 47,

    InputKeyCode_0 = 48,
    InputKeyCode_1 = 49,
    InputKeyCode_2 = 50,
    InputKeyCode_3 = 51,
    InputKeyCode_4 = 52,
    InputKeyCode_5 = 53,
    InputKeyCode_6 = 54,
    InputKeyCode_7 = 55,
    InputKeyCode_8 = 56,
    InputKeyCode_9 = 57,

    InputKeyCode_Colon = 58,
    InputKeyCode_Semicolon = 59,
    InputKeyCode_LessThan = 60,
    InputKeyCode_Equal = 61,
    InputKeyCode_GreaterThan = 62,
    InputKeyCode_Question = 63,
    InputKeyCode_At = 64,

    InputKeyCode_A = 65,
    InputKeyCode_B = 66,
    InputKeyCode_C = 67,
    InputKeyCode_D = 68,
    InputKeyCode_E = 69,
    InputKeyCode_F = 70,
    InputKeyCode_G = 71,
    InputKeyCode_H = 72,
    InputKeyCode_I = 73,
    InputKeyCode_J = 74,
    InputKeyCode_K = 75,
    InputKeyCode_L = 76,
    InputKeyCode_M = 77,
    InputKeyCode_N = 78,
    InputKeyCode_O = 79,
    InputKeyCode_P = 80,
    InputKeyCode_Q = 81,
    InputKeyCode_R = 82,
    InputKeyCode_S = 83,
    InputKeyCode_T = 84,
    InputKeyCode_U = 85,
    InputKeyCode_V = 86,
    InputKeyCode_W = 87,
    InputKeyCode_X = 88,
    InputKeyCode_Y = 89,
    InputKeyCode_Z = 90,

    InputKeyCode_BracketLeft = 91,
    InputKeyCode_Backslash = 92,
    InputKeyCode_BracketRight = 93,
    InputKeyCode_Caret = 94,
    InputKeyCode_Underscore = 95,
    InputKeyCode_GraveAccent = 96,

    InputKeyCode_a = 97,
    InputKeyCode_b = 98,
    InputKeyCode_c = 99,
    InputKeyCode_d = 100,
    InputKeyCode_e = 101,
    InputKeyCode_f = 102,
    InputKeyCode_g = 103,
    InputKeyCode_h = 104,
    InputKeyCode_i = 105,
    InputKeyCode_j = 106,
    InputKeyCode_k = 107,
    InputKeyCode_l = 108,
    InputKeyCode_m = 109,
    InputKeyCode_n = 110,
    InputKeyCode_o = 111,
    InputKeyCode_p = 112,
    InputKeyCode_q = 113,
    InputKeyCode_r = 114,
    InputKeyCode_s = 115,
    InputKeyCode_t = 116,
    InputKeyCode_u = 117,
    InputKeyCode_v = 118,
    InputKeyCode_w = 119,
    InputKeyCode_x = 120,
    InputKeyCode_y = 121,
    InputKeyCode_z = 122,

    InputKeyCode_LeftBrace = 123,
    InputKeyCode_VerticalBar = 124,
    InputKeyCode_RightBrace = 125,
    InputKeyCode_Tilde = 126,
    InputKeyCode_Delete = 127,

    InputKeyCode_ArrowDown = 258,
    InputKeyCode_ArrowUp = 259,
    InputKeyCode_ArrowLeft = 260,
    InputKeyCode_ArrowRight = 261,

    InputKeyCode_F1 = 265,
    InputKeyCode_F2 = 266,
    InputKeyCode_F3 = 267,
    InputKeyCode_F4 = 268,
    InputKeyCode_F5 = 269,
    InputKeyCode_F6 = 270,
    InputKeyCode_F7 = 271,
    InputKeyCode_F8 = 272,
    InputKeyCode_F9 = 273,
    InputKeyCode_F10 = 274,
    InputKeyCode_F11 = 275,
    InputKeyCode_F12 = 276
} InputKeyCode;

/// @brief Initialize the input manager. Should not be used by app.
void Input_Initialize();

/// @brief Terminate the input manager. Should not be used by app.
void Input_Terminate();

/// @brief Poll the input manager for new input events. Should not be used by app.
void Input_PollInputs();

/// @brief Get whether a specific key is in a certain state.
/// @param stateToCompare The state to compare against.
/// @param keyToGet The key to get the state of.
/// @return True if the key is in the specified state, false otherwise.
bool InputManager_GetKey(InputKeyState stateToCompare, InputKeyCode keyToGet);

/// @brief Get the state of a specific key.
/// @param keyToGet The key to get the state of.
/// @return The state of the specified key.
InputKeyState InputManager_GetKeyState(InputKeyCode keyToGet);
