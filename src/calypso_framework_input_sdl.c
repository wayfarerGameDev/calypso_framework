/// <summary>
/// Input module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <dependencies/SDL2/SDL.h>

// Input States
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_UP                      0
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_DOWN                    1
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_PRESSED                 2
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_RELEASED                3

// Input Keys (Keyboard)(Arrows)
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_LEFT                        SDL_SCANCODE_LEFT
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_RIGHT                       SDL_SCANCODE_RIGHT
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_UP                          SDL_SCANCODE_UP
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_DOWN                        SDL_SCANCODE_DOWN

// Input Keys (Keyboard)(Numbers)
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_0                           SDL_SCANCODE_0
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_1                           SDL_SCANCODE_1
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_2                           SDL_SCANCODE_2
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_3                           SDL_SCANCODE_3
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_4                           SDL_SCANCODE_4
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_5                           SDL_SCANCODE_5  
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_6                           SDL_SCANCODE_6
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_7                           SDL_SCANCODE_7
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_8                           SDL_SCANCODE_8
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_9                           SDL_SCANCODE_9

// Input Keys (Keyboard)(Keypad Numbers)
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_0                    SDL_SCANCODE_KP_0
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_00                   SDL_SCANCODE_KP_00
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_000                  SDL_SCANCODE_KP_000
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_1                    SDL_SCANCODE_KP_1
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_2                    SDL_SCANCODE_KP_2
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_3                    SDL_SCANCODE_KP_3
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_4                    SDL_SCANCODE_KP_4
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_5                    SDL_SCANCODE_KP_5  
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_6                    SDL_SCANCODE_KP_6
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_7                    SDL_SCANCODE_KP_7
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_8                    SDL_SCANCODE_KP_8
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_KEYPAD_9                    SDL_SCANCODE_KP_9

// Input Keys (Keyboard)(Alphabet)
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_A                           SDL_SCANCODE_A
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_B                           SDL_SCANCODE_B
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_C                           SDL_SCANCODE_C
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_D                           SDL_SCANCODE_D
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_E                           SDL_SCANCODE_E  
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_F                           SDL_SCANCODE_F
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_G                           SDL_SCANCODE_G
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_H                           SDL_SCANCODE_H
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_I                           SDL_SCANCODE_I
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_J                           SDL_SCANCODE_J
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_K                           SDL_SCANCODE_K
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_L                           SDL_SCANCODE_L
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_M                           SDL_SCANCODE_M
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_N                           SDL_SCANCODE_N
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_O                           SDL_SCANCODE_O
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_P                           SDL_SCANCODE_P
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_Q                           SDL_SCANCODE_Q
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_R                           SDL_SCANCODE_R
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_S                           SDL_SCANCODE_S
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_T                           SDL_SCANCODE_T
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_U                           SDL_SCANCODE_U
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_V                           SDL_SCANCODE_V
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_W                           SDL_SCANCODE_W
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_X                           SDL_SCANCODE_X
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_Y                           SDL_SCANCODE_Y
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_Z                           SDL_SCANCODE_Z

// State
Uint8 _calypso_framework_input_sdl_keycode_states[255]; // SDL HAS 255 KEYS

/**
* \brief Show mouse cursor
* \return void
*/
void calypso_framework_input_sdl_show_mouse_cursor(void) 
{
    SDL_ShowCursor(SDL_ENABLE);
}

/**
* \brief Hide mouse cursor
* \return void
*/
void calypso_framework_input_sdl_hide_mouse_cursor(void) 
{
    SDL_ShowCursor(SDL_DISABLE);
}

/**
* \brief Get mouse cursor x
* \return int
*/
int calypso_framework_input_sdl_get_mouse_cursor_x() 
{
    int x;
    SDL_GetMouseState(&x,NULL);
    return x;
}

/**
* \brief Get mouse cursor y
* \return int
*/
int calypso_framework_input_sdl_get_mouse_cursor_y() 
{
    int y;
    SDL_GetMouseState(NULL,&y);
    return y;
}

/**
* \brief Updates input
* \return void
*/
void calypso_framework_input_sdl_update() 
{
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

    for (int i = 0; i < 255; i++)
    {
        if (keyboard_state[i])
        {
            if (_calypso_framework_input_sdl_keycode_states[i] != CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_UP)
                _calypso_framework_input_sdl_keycode_states[i] = CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_DOWN;
            else 
                 _calypso_framework_input_sdl_keycode_states[i] = CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_PRESSED;
        }
        else
        {
            if (_calypso_framework_input_sdl_keycode_states[i] != CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_DOWN && _calypso_framework_input_sdl_keycode_states[i] != CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_PRESSED)
                _calypso_framework_input_sdl_keycode_states[i] = CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_UP;
            else
                _calypso_framework_input_sdl_keycode_states[i] = CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_RELEASED;
        }
    }
}

/**
* \brief Get key up
* \param key_code Uint8
* \return int
*/
int calypso_framework_input_sdl_get_key_up(const Uint8 key_code) 
{
    return _calypso_framework_input_sdl_keycode_states[key_code] == CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_UP;
}

/**
* \brief Get key down
* \param key_code Uint8
* \return int
*/
int calypso_framework_input_sdl_get_key_down(const Uint8 key_code) 
{
    return _calypso_framework_input_sdl_keycode_states[key_code] == CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_DOWN;
}

/**
* \brief Get key pressed
* \param key_code Uint8
* \return int
*/
int calypso_framework_input_sdl_get_key_pressed(const Uint8 key_code) 
{
    return _calypso_framework_input_sdl_keycode_states[key_code] == CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_PRESSED;
}

/**
* \brief Get key released
* \param key_code Uint8
* \return int
*/
int calypso_framework_input_sdl_get_key_released(const Uint8 key_code) 
{
    return _calypso_framework_input_sdl_keycode_states[key_code] == CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_RELEASED;
}