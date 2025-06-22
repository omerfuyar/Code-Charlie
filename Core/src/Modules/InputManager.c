#include "Modules/InputManager.h"
#include "Utils/ArrayList.h"

#include <ncurses.h>

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
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 0
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 1
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 2
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 3
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 4
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 5
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 6
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 7
    {Key_Tab, Released, false, INPUT_KEY_DELAY_INIT},              // 8
    {Key_Enter, Released, false, INPUT_KEY_DELAY_INIT},            // 9
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 10
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 11
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 12
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 13
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 14
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 15
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 16
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 17
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 18
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 19
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 20
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 21
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 22
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 23
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 24
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 25
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 26
    {Key_Escape, Released, false, INPUT_KEY_DELAY_INIT},           // 27
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 28
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 29
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 30
    {Key_NULL, Released, false, INPUT_KEY_DELAY_INIT},             // 31
    {Key_Space, Released, false, INPUT_KEY_DELAY_INIT},            // 32
    {Key_Exclamation, Released, false, INPUT_KEY_DELAY_INIT},      // 33
    {Key_QuoteDouble, Released, false, INPUT_KEY_DELAY_INIT},      // 34
    {Key_Hash, Released, false, INPUT_KEY_DELAY_INIT},             // 35
    {Key_Dollar, Released, false, INPUT_KEY_DELAY_INIT},           // 36
    {Key_Percent, Released, false, INPUT_KEY_DELAY_INIT},          // 37
    {Key_Ampersand, Released, false, INPUT_KEY_DELAY_INIT},        // 38
    {Key_Quote, Released, false, INPUT_KEY_DELAY_INIT},            // 39
    {Key_LeftParenthesis, Released, false, INPUT_KEY_DELAY_INIT},  // 40
    {Key_RightParenthesis, Released, false, INPUT_KEY_DELAY_INIT}, // 41
    {Key_Asterisk, Released, false, INPUT_KEY_DELAY_INIT},         // 42
    {Key_Plus, Released, false, INPUT_KEY_DELAY_INIT},             // 43
    {Key_Comma, Released, false, INPUT_KEY_DELAY_INIT},            // 44
    {Key_Minus, Released, false, INPUT_KEY_DELAY_INIT},            // 45
    {Key_Period, Released, false, INPUT_KEY_DELAY_INIT},           // 46
    {Key_Slash, Released, false, INPUT_KEY_DELAY_INIT},            // 47
    {Key_0, Released, false, INPUT_KEY_DELAY_INIT},                // 48
    {Key_1, Released, false, INPUT_KEY_DELAY_INIT},                // 49
    {Key_2, Released, false, INPUT_KEY_DELAY_INIT},                // 50
    {Key_3, Released, false, INPUT_KEY_DELAY_INIT},                // 51
    {Key_4, Released, false, INPUT_KEY_DELAY_INIT},                // 52
    {Key_5, Released, false, INPUT_KEY_DELAY_INIT},                // 53
    {Key_6, Released, false, INPUT_KEY_DELAY_INIT},                // 54
    {Key_7, Released, false, INPUT_KEY_DELAY_INIT},                // 55
    {Key_8, Released, false, INPUT_KEY_DELAY_INIT},                // 56
    {Key_9, Released, false, INPUT_KEY_DELAY_INIT},                // 57
    {Key_Colon, Released, false, INPUT_KEY_DELAY_INIT},            // 58
    {Key_Semicolon, Released, false, INPUT_KEY_DELAY_INIT},        // 59
    {Key_LessThan, Released, false, INPUT_KEY_DELAY_INIT},         // 60
    {Key_Equal, Released, false, INPUT_KEY_DELAY_INIT},            // 61
    {Key_GreaterThan, Released, false, INPUT_KEY_DELAY_INIT},      // 62
    {Key_Question, Released, false, INPUT_KEY_DELAY_INIT},         // 63
    {Key_At, Released, false, INPUT_KEY_DELAY_INIT},               // 64
    {Key_A, Released, false, INPUT_KEY_DELAY_INIT},                // 65
    {Key_B, Released, false, INPUT_KEY_DELAY_INIT},                // 66
    {Key_C, Released, false, INPUT_KEY_DELAY_INIT},                // 67
    {Key_D, Released, false, INPUT_KEY_DELAY_INIT},                // 68
    {Key_E, Released, false, INPUT_KEY_DELAY_INIT},                // 69
    {Key_F, Released, false, INPUT_KEY_DELAY_INIT},                // 70
    {Key_G, Released, false, INPUT_KEY_DELAY_INIT},                // 71
    {Key_H, Released, false, INPUT_KEY_DELAY_INIT},                // 72
    {Key_I, Released, false, INPUT_KEY_DELAY_INIT},                // 73
    {Key_J, Released, false, INPUT_KEY_DELAY_INIT},                // 74
    {Key_K, Released, false, INPUT_KEY_DELAY_INIT},                // 75
    {Key_L, Released, false, INPUT_KEY_DELAY_INIT},                // 76
    {Key_M, Released, false, INPUT_KEY_DELAY_INIT},                // 77
    {Key_N, Released, false, INPUT_KEY_DELAY_INIT},                // 78
    {Key_O, Released, false, INPUT_KEY_DELAY_INIT},                // 79
    {Key_P, Released, false, INPUT_KEY_DELAY_INIT},                // 80
    {Key_Q, Released, false, INPUT_KEY_DELAY_INIT},                // 81
    {Key_R, Released, false, INPUT_KEY_DELAY_INIT},                // 82
    {Key_S, Released, false, INPUT_KEY_DELAY_INIT},                // 83
    {Key_T, Released, false, INPUT_KEY_DELAY_INIT},                // 84
    {Key_U, Released, false, INPUT_KEY_DELAY_INIT},                // 85
    {Key_V, Released, false, INPUT_KEY_DELAY_INIT},                // 86
    {Key_W, Released, false, INPUT_KEY_DELAY_INIT},                // 87
    {Key_X, Released, false, INPUT_KEY_DELAY_INIT},                // 88
    {Key_Y, Released, false, INPUT_KEY_DELAY_INIT},                // 89
    {Key_Z, Released, false, INPUT_KEY_DELAY_INIT},                // 90
    {Key_BracketLeft, Released, false, INPUT_KEY_DELAY_INIT},      // 91
    {Key_Backslash, Released, false, INPUT_KEY_DELAY_INIT},        // 92
    {Key_BracketRight, Released, false, INPUT_KEY_DELAY_INIT},     // 93
    {Key_Caret, Released, false, INPUT_KEY_DELAY_INIT},            // 94
    {Key_Underscore, Released, false, INPUT_KEY_DELAY_INIT},       // 95
    {Key_GraveAccent, Released, false, INPUT_KEY_DELAY_INIT},      // 96
    {Key_a, Released, false, INPUT_KEY_DELAY_INIT},                // 97
    {Key_b, Released, false, INPUT_KEY_DELAY_INIT},                // 98
    {Key_c, Released, false, INPUT_KEY_DELAY_INIT},                // 99
    {Key_d, Released, false, INPUT_KEY_DELAY_INIT},                // 100
    {Key_e, Released, false, INPUT_KEY_DELAY_INIT},                // 101
    {Key_f, Released, false, INPUT_KEY_DELAY_INIT},                // 102
    {Key_g, Released, false, INPUT_KEY_DELAY_INIT},                // 103
    {Key_h, Released, false, INPUT_KEY_DELAY_INIT},                // 104
    {Key_i, Released, false, INPUT_KEY_DELAY_INIT},                // 105
    {Key_j, Released, false, INPUT_KEY_DELAY_INIT},                // 106
    {Key_k, Released, false, INPUT_KEY_DELAY_INIT},                // 107
    {Key_l, Released, false, INPUT_KEY_DELAY_INIT},                // 108
    {Key_m, Released, false, INPUT_KEY_DELAY_INIT},                // 109
    {Key_n, Released, false, INPUT_KEY_DELAY_INIT},                // 110
    {Key_o, Released, false, INPUT_KEY_DELAY_INIT},                // 111
    {Key_p, Released, false, INPUT_KEY_DELAY_INIT},                // 112
    {Key_q, Released, false, INPUT_KEY_DELAY_INIT},                // 113
    {Key_r, Released, false, INPUT_KEY_DELAY_INIT},                // 114
    {Key_s, Released, false, INPUT_KEY_DELAY_INIT},                // 115
    {Key_t, Released, false, INPUT_KEY_DELAY_INIT},                // 116
    {Key_u, Released, false, INPUT_KEY_DELAY_INIT},                // 117
    {Key_v, Released, false, INPUT_KEY_DELAY_INIT},                // 118
    {Key_w, Released, false, INPUT_KEY_DELAY_INIT},                // 119
    {Key_x, Released, false, INPUT_KEY_DELAY_INIT},                // 120
    {Key_y, Released, false, INPUT_KEY_DELAY_INIT},                // 121
    {Key_z, Released, false, INPUT_KEY_DELAY_INIT},                // 122
    {Key_LeftBrace, Released, false, INPUT_KEY_DELAY_INIT},        // 123
    {Key_VerticalBar, Released, false, INPUT_KEY_DELAY_INIT},      // 124
    {Key_RightBrace, Released, false, INPUT_KEY_DELAY_INIT},       // 125
    {Key_Tilde, Released, false, INPUT_KEY_DELAY_INIT},            // 126
    {Key_Delete, Released, false, INPUT_KEY_DELAY_INIT},           // 127
};

InputKey INPUT_KEYS_ARROW[INPUT_KEY_ARROW_SIZE] = {
    {Key_ArrowDown, Released, false, INPUT_KEY_DELAY_INIT}, // 0
    {Key_ArrowUp, Released, false, INPUT_KEY_DELAY_INIT},   // 1
    {Key_ArrowLeft, Released, false, INPUT_KEY_DELAY_INIT}, // 2
    {Key_ArrowRight, Released, false, INPUT_KEY_DELAY_INIT} // 3
};

InputKey INPUT_KEYS_FUNCTION[INPUT_KEY_FUNCTION_SIZE] = {
    {Key_F1, Released, false, INPUT_KEY_DELAY_INIT},  // 0
    {Key_F2, Released, false, INPUT_KEY_DELAY_INIT},  // 1
    {Key_F3, Released, false, INPUT_KEY_DELAY_INIT},  // 2
    {Key_F4, Released, false, INPUT_KEY_DELAY_INIT},  // 3
    {Key_F5, Released, false, INPUT_KEY_DELAY_INIT},  // 4
    {Key_F6, Released, false, INPUT_KEY_DELAY_INIT},  // 5
    {Key_F7, Released, false, INPUT_KEY_DELAY_INIT},  // 6
    {Key_F8, Released, false, INPUT_KEY_DELAY_INIT},  // 7
    {Key_F9, Released, false, INPUT_KEY_DELAY_INIT},  // 8
    {Key_F10, Released, false, INPUT_KEY_DELAY_INIT}, // 9
    {Key_F11, Released, false, INPUT_KEY_DELAY_INIT}, // 10
    {Key_F12, Released, false, INPUT_KEY_DELAY_INIT}  // 11
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
    bool wasPressed = (key->keyState == Down || key->keyState == Pressed);

    if (key->isDownThisFrame) // The key is physically low
    {
        key->frameSinceEvent = 0;

        if (!wasPressed)
        {
            key->keyState = Down;
        }
        else if (key->keyState == Down)
        {
            key->keyState = Pressed;
        }
    }
    else // The key is physically high
    {
        key->frameSinceEvent++;

        if (wasPressed)
        {
            key->keyState = Up;
        }
        else if (key->keyState == Up)
        {
            key->keyState = Released;
        }
    }
}

#pragma endregion

bool InputManager_GetKey(InputKeyState stateToCompare, InputKeyCode keyToGet)
{
    if (keyToGet >= INPUT_KEY_STANDARD_OFFSET && keyToGet < INPUT_KEY_STANDARD_OFFSET + INPUT_KEY_STANDARD_SIZE) // standard keys, 0 offset
    {
        return stateToCompare == INPUT_KEYS_STANDARD[keyToGet - INPUT_KEY_STANDARD_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_ARROW_OFFSET && keyToGet < INPUT_KEY_ARROW_OFFSET + INPUT_KEY_ARROW_SIZE) // arrow keys, 258 offset
    {
        return stateToCompare == INPUT_KEYS_ARROW[keyToGet - INPUT_KEY_ARROW_OFFSET].keyState;
    }
    else if (keyToGet >= INPUT_KEY_FUNCTION_OFFSET && keyToGet < INPUT_KEY_FUNCTION_OFFSET + INPUT_KEY_FUNCTION_SIZE) // function keys, 265 offset
    {
        return stateToCompare == INPUT_KEYS_FUNCTION[keyToGet - INPUT_KEY_FUNCTION_OFFSET].keyState;
    }
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

    return Released;
}

void InputManager_PollInputs()
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
