#include "Modules/InputManager.h"

#ifdef PLATFORM_WINDOWS
#include <curses.h>
#else
#include <ncurses.h>
#endif

// todo add cross platform support

#pragma region Source Only

typedef struct InputKey
{
    InputKeyCode keyCode;
    InputKeyState keyState;
} InputKey;

#define INPUT_KEY_DELAY_INIT 99
#define INPUT_KEY_DELAY_TOLERANCE 5

#define INPUT_KEY_STANDARD_SIZE 128
#define INPUT_KEY_ARROW_SIZE 4
#define INPUT_KEY_FUNCTION_SIZE 12

#define INPUT_KEY_STANDARD_OFFSET 0
#define INPUT_KEY_ARROW_OFFSET 258
#define INPUT_KEY_FUNCTION_OFFSET 265

InputKey INPUT_KEY_STANDARDS[INPUT_KEY_STANDARD_SIZE] = {
    {InputKeyCode_NULL, InputKeyState_Released},             // 0
    {InputKeyCode_NULL, InputKeyState_Released},             // 1
    {InputKeyCode_NULL, InputKeyState_Released},             // 2
    {InputKeyCode_NULL, InputKeyState_Released},             // 3
    {InputKeyCode_NULL, InputKeyState_Released},             // 4
    {InputKeyCode_NULL, InputKeyState_Released},             // 5
    {InputKeyCode_NULL, InputKeyState_Released},             // 6
    {InputKeyCode_NULL, InputKeyState_Released},             // 7
    {InputKeyCode_Tab, InputKeyState_Released},              // 8
    {InputKeyCode_Enter, InputKeyState_Released},            // 9
    {InputKeyCode_NULL, InputKeyState_Released},             // 10
    {InputKeyCode_NULL, InputKeyState_Released},             // 11
    {InputKeyCode_NULL, InputKeyState_Released},             // 12
    {InputKeyCode_NULL, InputKeyState_Released},             // 13
    {InputKeyCode_NULL, InputKeyState_Released},             // 14
    {InputKeyCode_NULL, InputKeyState_Released},             // 15
    {InputKeyCode_NULL, InputKeyState_Released},             // 16
    {InputKeyCode_NULL, InputKeyState_Released},             // 17
    {InputKeyCode_NULL, InputKeyState_Released},             // 18
    {InputKeyCode_NULL, InputKeyState_Released},             // 19
    {InputKeyCode_NULL, InputKeyState_Released},             // 20
    {InputKeyCode_NULL, InputKeyState_Released},             // 21
    {InputKeyCode_NULL, InputKeyState_Released},             // 22
    {InputKeyCode_NULL, InputKeyState_Released},             // 23
    {InputKeyCode_NULL, InputKeyState_Released},             // 24
    {InputKeyCode_NULL, InputKeyState_Released},             // 25
    {InputKeyCode_NULL, InputKeyState_Released},             // 26
    {InputKeyCode_Escape, InputKeyState_Released},           // 27
    {InputKeyCode_NULL, InputKeyState_Released},             // 28
    {InputKeyCode_NULL, InputKeyState_Released},             // 29
    {InputKeyCode_NULL, InputKeyState_Released},             // 30
    {InputKeyCode_NULL, InputKeyState_Released},             // 31
    {InputKeyCode_Space, InputKeyState_Released},            // 32
    {InputKeyCode_Exclamation, InputKeyState_Released},      // 33
    {InputKeyCode_QuoteDouble, InputKeyState_Released},      // 34
    {InputKeyCode_Hash, InputKeyState_Released},             // 35
    {InputKeyCode_Dollar, InputKeyState_Released},           // 36
    {InputKeyCode_Percent, InputKeyState_Released},          // 37
    {InputKeyCode_Ampersand, InputKeyState_Released},        // 38
    {InputKeyCode_Quote, InputKeyState_Released},            // 39
    {InputKeyCode_LeftParenthesis, InputKeyState_Released},  // 40
    {InputKeyCode_RightParenthesis, InputKeyState_Released}, // 41
    {InputKeyCode_Asterisk, InputKeyState_Released},         // 42
    {InputKeyCode_Plus, InputKeyState_Released},             // 43
    {InputKeyCode_Comma, InputKeyState_Released},            // 44
    {InputKeyCode_Minus, InputKeyState_Released},            // 45
    {InputKeyCode_Period, InputKeyState_Released},           // 46
    {InputKeyCode_Slash, InputKeyState_Released},            // 47
    {InputKeyCode_0, InputKeyState_Released},                // 48
    {InputKeyCode_1, InputKeyState_Released},                // 49
    {InputKeyCode_2, InputKeyState_Released},                // 50
    {InputKeyCode_3, InputKeyState_Released},                // 51
    {InputKeyCode_4, InputKeyState_Released},                // 52
    {InputKeyCode_5, InputKeyState_Released},                // 53
    {InputKeyCode_6, InputKeyState_Released},                // 54
    {InputKeyCode_7, InputKeyState_Released},                // 55
    {InputKeyCode_8, InputKeyState_Released},                // 56
    {InputKeyCode_9, InputKeyState_Released},                // 57
    {InputKeyCode_Colon, InputKeyState_Released},            // 58
    {InputKeyCode_Semicolon, InputKeyState_Released},        // 59
    {InputKeyCode_LessThan, InputKeyState_Released},         // 60
    {InputKeyCode_Equal, InputKeyState_Released},            // 61
    {InputKeyCode_GreaterThan, InputKeyState_Released},      // 62
    {InputKeyCode_Question, InputKeyState_Released},         // 63
    {InputKeyCode_At, InputKeyState_Released},               // 64
    {InputKeyCode_A, InputKeyState_Released},                // 65
    {InputKeyCode_B, InputKeyState_Released},                // 66
    {InputKeyCode_C, InputKeyState_Released},                // 67
    {InputKeyCode_D, InputKeyState_Released},                // 68
    {InputKeyCode_E, InputKeyState_Released},                // 69
    {InputKeyCode_F, InputKeyState_Released},                // 70
    {InputKeyCode_G, InputKeyState_Released},                // 71
    {InputKeyCode_H, InputKeyState_Released},                // 72
    {InputKeyCode_I, InputKeyState_Released},                // 73
    {InputKeyCode_J, InputKeyState_Released},                // 74
    {InputKeyCode_K, InputKeyState_Released},                // 75
    {InputKeyCode_L, InputKeyState_Released},                // 76
    {InputKeyCode_M, InputKeyState_Released},                // 77
    {InputKeyCode_N, InputKeyState_Released},                // 78
    {InputKeyCode_O, InputKeyState_Released},                // 79
    {InputKeyCode_P, InputKeyState_Released},                // 80
    {InputKeyCode_Q, InputKeyState_Released},                // 81
    {InputKeyCode_R, InputKeyState_Released},                // 82
    {InputKeyCode_S, InputKeyState_Released},                // 83
    {InputKeyCode_T, InputKeyState_Released},                // 84
    {InputKeyCode_U, InputKeyState_Released},                // 85
    {InputKeyCode_V, InputKeyState_Released},                // 86
    {InputKeyCode_W, InputKeyState_Released},                // 87
    {InputKeyCode_X, InputKeyState_Released},                // 88
    {InputKeyCode_Y, InputKeyState_Released},                // 89
    {InputKeyCode_Z, InputKeyState_Released},                // 90
    {InputKeyCode_BracketLeft, InputKeyState_Released},      // 91
    {InputKeyCode_Backslash, InputKeyState_Released},        // 92
    {InputKeyCode_BracketRight, InputKeyState_Released},     // 93
    {InputKeyCode_Caret, InputKeyState_Released},            // 94
    {InputKeyCode_Underscore, InputKeyState_Released},       // 95
    {InputKeyCode_GraveAccent, InputKeyState_Released},      // 96
    {InputKeyCode_a, InputKeyState_Released},                // 97
    {InputKeyCode_b, InputKeyState_Released},                // 98
    {InputKeyCode_c, InputKeyState_Released},                // 99
    {InputKeyCode_d, InputKeyState_Released},                // 100
    {InputKeyCode_e, InputKeyState_Released},                // 101
    {InputKeyCode_f, InputKeyState_Released},                // 102
    {InputKeyCode_g, InputKeyState_Released},                // 103
    {InputKeyCode_h, InputKeyState_Released},                // 104
    {InputKeyCode_i, InputKeyState_Released},                // 105
    {InputKeyCode_j, InputKeyState_Released},                // 106
    {InputKeyCode_k, InputKeyState_Released},                // 107
    {InputKeyCode_l, InputKeyState_Released},                // 108
    {InputKeyCode_m, InputKeyState_Released},                // 109
    {InputKeyCode_n, InputKeyState_Released},                // 110
    {InputKeyCode_o, InputKeyState_Released},                // 111
    {InputKeyCode_p, InputKeyState_Released},                // 112
    {InputKeyCode_q, InputKeyState_Released},                // 113
    {InputKeyCode_r, InputKeyState_Released},                // 114
    {InputKeyCode_s, InputKeyState_Released},                // 115
    {InputKeyCode_t, InputKeyState_Released},                // 116
    {InputKeyCode_u, InputKeyState_Released},                // 117
    {InputKeyCode_v, InputKeyState_Released},                // 118
    {InputKeyCode_w, InputKeyState_Released},                // 119
    {InputKeyCode_x, InputKeyState_Released},                // 120
    {InputKeyCode_y, InputKeyState_Released},                // 121
    {InputKeyCode_z, InputKeyState_Released},                // 122
    {InputKeyCode_LeftBrace, InputKeyState_Released},        // 123
    {InputKeyCode_VerticalBar, InputKeyState_Released},      // 124
    {InputKeyCode_RightBrace, InputKeyState_Released},       // 125
    {InputKeyCode_Tilde, InputKeyState_Released},            // 126
    {InputKeyCode_Delete, InputKeyState_Released},           // 127
};

InputKey INPUT_KEY_ARROWS[INPUT_KEY_ARROW_SIZE] = {
    {InputKeyCode_ArrowDown, InputKeyState_Released}, // 0
    {InputKeyCode_ArrowUp, InputKeyState_Released},   // 1
    {InputKeyCode_ArrowLeft, InputKeyState_Released}, // 2
    {InputKeyCode_ArrowRight, InputKeyState_Released} // 3
};

InputKey INPUT_KEY_FUNCTIONS[INPUT_KEY_FUNCTION_SIZE] = {
    {InputKeyCode_F1, InputKeyState_Released},  // 0
    {InputKeyCode_F2, InputKeyState_Released},  // 1
    {InputKeyCode_F3, InputKeyState_Released},  // 2
    {InputKeyCode_F4, InputKeyState_Released},  // 3
    {InputKeyCode_F5, InputKeyState_Released},  // 4
    {InputKeyCode_F6, InputKeyState_Released},  // 5
    {InputKeyCode_F7, InputKeyState_Released},  // 6
    {InputKeyCode_F8, InputKeyState_Released},  // 7
    {InputKeyCode_F9, InputKeyState_Released},  // 8
    {InputKeyCode_F10, InputKeyState_Released}, // 9
    {InputKeyCode_F11, InputKeyState_Released}, // 10
    {InputKeyCode_F12, InputKeyState_Released}  // 11
};

#pragma endregion

void Input_Initialize()
{
    noecho();              // curses echo disable, no writing while getting input
    cbreak();              // curses disable line buffering but take CTRL^C commands
    keypad(stdscr, true);  // curses enable keys like arrow and function
    nodelay(stdscr, true); // curses disable blocking on getch()
}

void Input_Terminate()
{
}

void Input_PollInputs()
{
    int character;

    // reset keys
    for (int i = 0; i < INPUT_KEY_STANDARD_SIZE; i++)
    {
        INPUT_KEY_STANDARDS[i].keyState = InputKeyState_Released;
    }

    for (int i = 0; i < INPUT_KEY_ARROW_SIZE; i++)
    {
        INPUT_KEY_ARROWS[i].keyState = InputKeyState_Released;
    }

    for (int i = 0; i < INPUT_KEY_FUNCTION_SIZE; i++)
    {
        INPUT_KEY_FUNCTIONS[i].keyState = InputKeyState_Released;
    }

    // get inputs
    while ((character = getch()) != ERR)
    {
        if (character >= INPUT_KEY_STANDARD_OFFSET && character < INPUT_KEY_STANDARD_OFFSET + INPUT_KEY_STANDARD_SIZE) // standard keys, 0 offset
        {
            INPUT_KEY_STANDARDS[character - INPUT_KEY_STANDARD_OFFSET].keyState = InputKeyState_Pressed;
        }
        else if (character >= INPUT_KEY_ARROW_OFFSET && character < INPUT_KEY_ARROW_OFFSET + INPUT_KEY_ARROW_SIZE) // arrow keys, 258 offset
        {
            INPUT_KEY_ARROWS[character - INPUT_KEY_ARROW_OFFSET].keyState = InputKeyState_Pressed;
        }
        else if (character >= INPUT_KEY_FUNCTION_OFFSET && character < INPUT_KEY_FUNCTION_OFFSET + INPUT_KEY_FUNCTION_SIZE) // function keys, 265 offset
        {
            INPUT_KEY_FUNCTIONS[character - INPUT_KEY_FUNCTION_OFFSET].keyState = InputKeyState_Pressed;
        }
    }
}

bool Input_GetKey(InputKeyState stateToCompare, InputKeyCode keyToGet)
{
    return Input_GetKeyState(keyToGet) == stateToCompare;
}

InputKeyState Input_GetKeyState(InputKeyCode keyToGet)
{
    if (keyToGet >= INPUT_KEY_STANDARD_OFFSET && keyToGet < INPUT_KEY_STANDARD_OFFSET + INPUT_KEY_STANDARD_SIZE) // standard keys, 0 offset
    {
        return INPUT_KEY_STANDARDS[keyToGet - INPUT_KEY_STANDARD_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_ARROW_OFFSET && keyToGet < INPUT_KEY_ARROW_OFFSET + INPUT_KEY_ARROW_SIZE) // arrow keys, 258 offset
    {
        return INPUT_KEY_ARROWS[keyToGet - INPUT_KEY_ARROW_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_FUNCTION_OFFSET && keyToGet < INPUT_KEY_FUNCTION_OFFSET + INPUT_KEY_FUNCTION_SIZE) // function keys, 265 offset
    {
        return INPUT_KEY_FUNCTIONS[keyToGet - INPUT_KEY_FUNCTION_OFFSET].keyState;
    }

    return InputKeyState_Released;
}
