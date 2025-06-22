#pragma once

#include "Core.h"

// #define INPUT_KEY_BUFFER_SIZE 8

typedef enum InputMode
{
    Key,
    Text
} InputMode;

typedef enum InputKeyState
{
    Released = 0,
    Down = 1,
    Up = 2,
    Pressed = 3,
} InputKeyState;

typedef enum InputKeyCode
{
    Key_NULL = 0,
    Key_Tab = 9,
    Key_Enter = 10,
    Key_Escape = 27,

    Key_Space = 32,
    Key_Exclamation = 33,
    Key_QuoteDouble = 34,
    Key_Hash = 35,
    Key_Dollar = 36,
    Key_Percent = 37,
    Key_Ampersand = 38,
    Key_Quote = 39,
    Key_LeftParenthesis = 40,
    Key_RightParenthesis = 41,
    Key_Asterisk = 42,
    Key_Plus = 43,
    Key_Comma = 44,
    Key_Minus = 45,
    Key_Period = 46,
    Key_Slash = 47,

    Key_0 = 48,
    Key_1 = 49,
    Key_2 = 50,
    Key_3 = 51,
    Key_4 = 52,
    Key_5 = 53,
    Key_6 = 54,
    Key_7 = 55,
    Key_8 = 56,
    Key_9 = 57,

    Key_Colon = 58,
    Key_Semicolon = 59,
    Key_LessThan = 60,
    Key_Equal = 61,
    Key_GreaterThan = 62,
    Key_Question = 63,
    Key_At = 64,

    Key_A = 65,
    Key_B = 66,
    Key_C = 67,
    Key_D = 68,
    Key_E = 69,
    Key_F = 70,
    Key_G = 71,
    Key_H = 72,
    Key_I = 73,
    Key_J = 74,
    Key_K = 75,
    Key_L = 76,
    Key_M = 77,
    Key_N = 78,
    Key_O = 79,
    Key_P = 80,
    Key_Q = 81,
    Key_R = 82,
    Key_S = 83,
    Key_T = 84,
    Key_U = 85,
    Key_V = 86,
    Key_W = 87,
    Key_X = 88,
    Key_Y = 89,
    Key_Z = 90,

    Key_BracketLeft = 91,
    Key_Backslash = 92,
    Key_BracketRight = 93,
    Key_Caret = 94,
    Key_Underscore = 95,
    Key_GraveAccent = 96,

    Key_a = 97,
    Key_b = 98,
    Key_c = 99,
    Key_d = 100,
    Key_e = 101,
    Key_f = 102,
    Key_g = 103,
    Key_h = 104,
    Key_i = 105,
    Key_j = 106,
    Key_k = 107,
    Key_l = 108,
    Key_m = 109,
    Key_n = 110,
    Key_o = 111,
    Key_p = 112,
    Key_q = 113,
    Key_r = 114,
    Key_s = 115,
    Key_t = 116,
    Key_u = 117,
    Key_v = 118,
    Key_w = 119,
    Key_x = 120,
    Key_y = 121,
    Key_z = 122,

    Key_LeftBrace = 123,
    Key_VerticalBar = 124,
    Key_RightBrace = 125,
    Key_Tilde = 126,
    Key_Delete = 127,

    Key_ArrowDown = 258,
    Key_ArrowUp = 259,
    Key_ArrowLeft = 260,
    Key_ArrowRight = 261,

    Key_F1 = 265,
    Key_F2 = 266,
    Key_F3 = 267,
    Key_F4 = 268,
    Key_F5 = 269,
    Key_F6 = 270,
    Key_F7 = 271,
    Key_F8 = 272,
    Key_F9 = 273,
    Key_F10 = 274,
    Key_F11 = 275,
    Key_F12 = 276
} InputKeyCode;

bool InputManager_GetKey(InputKeyState stateToCompare, InputKeyCode keyToGet);

InputKeyState InputManager_GetKeyState(InputKeyCode keyToGet);

void InputManager_PollInputs();
