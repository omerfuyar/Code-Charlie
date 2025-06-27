#include "Modules/InputManager.h"

#include <ncurses.h>

// todo add cross platform support

#pragma region Source Only

typedef struct InputKey
{
    InputKeyCode keyCode;
    InputKeyState keyState;
    bool isDownThisFrame;
    unsigned char frameSinceEvent;
} InputKey;

#define INPUT_KEY_DELAY_INIT 99
#define INPUT_KEY_DELAY_TOLERANCE -1

#define INPUT_KEY_STANDARD_SIZE 128
#define INPUT_KEY_ARROW_SIZE 4
#define INPUT_KEY_FUNCTION_SIZE 12

#define INPUT_KEY_STANDARD_OFFSET 0
#define INPUT_KEY_ARROW_OFFSET 258
#define INPUT_KEY_FUNCTION_OFFSET 265

InputKey INPUT_KEYS_STANDARD[INPUT_KEY_STANDARD_SIZE] = {
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 0
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 1
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 2
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 3
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 4
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 5
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 6
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 7
    {InputKeyCode_Tab, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},              // 8
    {InputKeyCode_Enter, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 9
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 10
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 11
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 12
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 13
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 14
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 15
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 16
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 17
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 18
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 19
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 20
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 21
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 22
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 23
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 24
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 25
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 26
    {InputKeyCode_Escape, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},           // 27
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 28
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 29
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 30
    {InputKeyCode_NULL, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 31
    {InputKeyCode_Space, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 32
    {InputKeyCode_Exclamation, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 33
    {InputKeyCode_QuoteDouble, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 34
    {InputKeyCode_Hash, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 35
    {InputKeyCode_Dollar, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},           // 36
    {InputKeyCode_Percent, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},          // 37
    {InputKeyCode_Ampersand, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},        // 38
    {InputKeyCode_Quote, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 39
    {InputKeyCode_LeftParenthesis, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 40
    {InputKeyCode_RightParenthesis, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}, // 41
    {InputKeyCode_Asterisk, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},         // 42
    {InputKeyCode_Plus, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},             // 43
    {InputKeyCode_Comma, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 44
    {InputKeyCode_Minus, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 45
    {InputKeyCode_Period, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},           // 46
    {InputKeyCode_Slash, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 47
    {InputKeyCode_0, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 48
    {InputKeyCode_1, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 49
    {InputKeyCode_2, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 50
    {InputKeyCode_3, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 51
    {InputKeyCode_4, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 52
    {InputKeyCode_5, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 53
    {InputKeyCode_6, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 54
    {InputKeyCode_7, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 55
    {InputKeyCode_8, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 56
    {InputKeyCode_9, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 57
    {InputKeyCode_Colon, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 58
    {InputKeyCode_Semicolon, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},        // 59
    {InputKeyCode_LessThan, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},         // 60
    {InputKeyCode_Equal, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 61
    {InputKeyCode_GreaterThan, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 62
    {InputKeyCode_Question, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},         // 63
    {InputKeyCode_At, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},               // 64
    {InputKeyCode_A, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 65
    {InputKeyCode_B, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 66
    {InputKeyCode_C, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 67
    {InputKeyCode_D, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 68
    {InputKeyCode_E, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 69
    {InputKeyCode_F, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 70
    {InputKeyCode_G, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 71
    {InputKeyCode_H, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 72
    {InputKeyCode_I, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 73
    {InputKeyCode_J, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 74
    {InputKeyCode_K, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 75
    {InputKeyCode_L, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 76
    {InputKeyCode_M, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 77
    {InputKeyCode_N, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 78
    {InputKeyCode_O, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 79
    {InputKeyCode_P, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 80
    {InputKeyCode_Q, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 81
    {InputKeyCode_R, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 82
    {InputKeyCode_S, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 83
    {InputKeyCode_T, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 84
    {InputKeyCode_U, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 85
    {InputKeyCode_V, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 86
    {InputKeyCode_W, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 87
    {InputKeyCode_X, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 88
    {InputKeyCode_Y, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 89
    {InputKeyCode_Z, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 90
    {InputKeyCode_BracketLeft, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 91
    {InputKeyCode_Backslash, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},        // 92
    {InputKeyCode_BracketRight, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},     // 93
    {InputKeyCode_Caret, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 94
    {InputKeyCode_Underscore, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},       // 95
    {InputKeyCode_GraveAccent, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 96
    {InputKeyCode_a, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 97
    {InputKeyCode_b, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 98
    {InputKeyCode_c, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 99
    {InputKeyCode_d, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 100
    {InputKeyCode_e, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 101
    {InputKeyCode_f, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 102
    {InputKeyCode_g, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 103
    {InputKeyCode_h, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 104
    {InputKeyCode_i, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 105
    {InputKeyCode_j, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 106
    {InputKeyCode_k, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 107
    {InputKeyCode_l, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 108
    {InputKeyCode_m, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 109
    {InputKeyCode_n, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 110
    {InputKeyCode_o, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 111
    {InputKeyCode_p, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 112
    {InputKeyCode_q, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 113
    {InputKeyCode_r, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 114
    {InputKeyCode_s, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 115
    {InputKeyCode_t, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 116
    {InputKeyCode_u, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 117
    {InputKeyCode_v, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 118
    {InputKeyCode_w, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 119
    {InputKeyCode_x, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 120
    {InputKeyCode_y, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 121
    {InputKeyCode_z, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},                // 122
    {InputKeyCode_LeftBrace, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},        // 123
    {InputKeyCode_VerticalBar, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},      // 124
    {InputKeyCode_RightBrace, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},       // 125
    {InputKeyCode_Tilde, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},            // 126
    {InputKeyCode_Delete, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},           // 127
};

InputKey INPUT_KEYS_ARROW[INPUT_KEY_ARROW_SIZE] = {
    {InputKeyCode_ArrowDown, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}, // 0
    {InputKeyCode_ArrowUp, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},   // 1
    {InputKeyCode_ArrowLeft, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}, // 2
    {InputKeyCode_ArrowRight, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT} // 3
};

InputKey INPUT_KEYS_FUNCTION[INPUT_KEY_FUNCTION_SIZE] = {
    {InputKeyCode_F1, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 0
    {InputKeyCode_F2, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 1
    {InputKeyCode_F3, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 2
    {InputKeyCode_F4, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 3
    {InputKeyCode_F5, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 4
    {InputKeyCode_F6, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 5
    {InputKeyCode_F7, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 6
    {InputKeyCode_F8, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 7
    {InputKeyCode_F9, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT},  // 8
    {InputKeyCode_F10, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}, // 9
    {InputKeyCode_F11, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}, // 10
    {InputKeyCode_F12, InputKeyState_Released, false, INPUT_KEY_DELAY_INIT}  // 11
};

/// @brief Resets the key state based on its current state and whether it is pressed this frame
/// @param key Key to reset.
void InputKey_Reset(InputKey *key)
{
    key->isDownThisFrame = false;
}

/// @brief Updates the state of the key based on its current state and whether it is pressed this frame.
/// @param key Key to update.
void InputKey_Update(InputKey *key)
{
    bool wasPressed = (key->keyState == InputKeyState_Down || key->keyState == InputKeyState_Pressed);

    if (key->isDownThisFrame) // The key is physically low
    {
        key->frameSinceEvent = 0;

        if (!wasPressed)
        {
            key->keyState = InputKeyState_Down;
        }
        else if (key->keyState == InputKeyState_Down)
        {
            key->keyState = InputKeyState_Pressed;
        }
    }
    else // The key is physically high
    {
        key->frameSinceEvent++;

        if (wasPressed)
        {
            key->keyState = InputKeyState_Up;
        }
        else if (key->keyState == InputKeyState_Up)
        {
            key->keyState = InputKeyState_Released;
        }
    }
}

#pragma endregion

void Input_Initialize()
{
}

void Input_Terminate()
{
}

void Input_PollInputs()
{
    int character;
    InputKey *key;

    // reset keys
    for (int i = 0; i < INPUT_KEY_STANDARD_SIZE; i++)
    {
        InputKey_Reset(&INPUT_KEYS_FUNCTION[i]);
    }

    for (int i = 0; i < INPUT_KEY_ARROW_SIZE; i++)
    {
        InputKey_Reset(&INPUT_KEYS_FUNCTION[i]);
    }

    for (int i = 0; i < INPUT_KEY_FUNCTION_SIZE; i++)
    {
        InputKey_Reset(&INPUT_KEYS_FUNCTION[i]);
    }

    // get inputs
    while ((character = getch()) != ERR)
    {
        if (character >= INPUT_KEY_STANDARD_OFFSET && character < INPUT_KEY_STANDARD_OFFSET + INPUT_KEY_STANDARD_SIZE) // standard keys, 0 offset
        {
            INPUT_KEYS_STANDARD[character - INPUT_KEY_STANDARD_OFFSET].isDownThisFrame = true;
        }
        else if (character >= INPUT_KEY_ARROW_OFFSET && character < INPUT_KEY_ARROW_OFFSET + INPUT_KEY_ARROW_SIZE) // arrow keys, 258 offset
        {
            INPUT_KEYS_ARROW[character - INPUT_KEY_ARROW_OFFSET].isDownThisFrame = true;
        }
        else if (character >= INPUT_KEY_FUNCTION_OFFSET && character < INPUT_KEY_FUNCTION_OFFSET + INPUT_KEY_FUNCTION_SIZE) // function keys, 265 offset
        {
            INPUT_KEYS_FUNCTION[character - INPUT_KEY_FUNCTION_OFFSET].isDownThisFrame = true;
        }
    }

    // update keys
    for (int i = 0; i < INPUT_KEY_STANDARD_SIZE; i++)
    {
        InputKey_Update(&INPUT_KEYS_STANDARD[i]);
    }

    for (int i = 0; i < INPUT_KEY_ARROW_SIZE; i++)
    {
        InputKey_Update(&INPUT_KEYS_ARROW[i]);
    }

    for (int i = 0; i < INPUT_KEY_FUNCTION_SIZE; i++)
    {
        InputKey_Update(&INPUT_KEYS_FUNCTION[i]);
    }
}

bool InputManager_GetKey(InputKeyState stateToCompare, InputKeyCode keyToGet)
{
    return InputManager_GetKeyState(keyToGet) == stateToCompare;
}

InputKeyState InputManager_GetKeyState(InputKeyCode keyToGet)
{
    if (keyToGet >= INPUT_KEY_STANDARD_OFFSET && keyToGet < INPUT_KEY_STANDARD_OFFSET + INPUT_KEY_STANDARD_SIZE) // standard keys, 0 offset
    {
        return INPUT_KEYS_STANDARD[keyToGet - INPUT_KEY_STANDARD_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_ARROW_OFFSET && keyToGet < INPUT_KEY_ARROW_OFFSET + INPUT_KEY_ARROW_SIZE) // arrow keys, 258 offset
    {
        return INPUT_KEYS_ARROW[keyToGet - INPUT_KEY_ARROW_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_FUNCTION_OFFSET && keyToGet < INPUT_KEY_FUNCTION_OFFSET + INPUT_KEY_FUNCTION_SIZE) // function keys, 265 offset
    {
        return INPUT_KEYS_FUNCTION[keyToGet - INPUT_KEY_FUNCTION_OFFSET].keyState;
    }

    return InputKeyState_Released;
}
