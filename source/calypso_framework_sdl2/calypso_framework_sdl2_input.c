/// <summary>
/// Input module that uses SDL as a base
/// </summary>

#pragma once

// Dependencies
#include <dependencies/SDL2/SDL.h>

// Input States
#define CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP                      0b00000000
#define CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN                    0b00000001
#define CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED                 0b00000010
#define CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_RELEASED                0b00000011

// Input Keys (Keyboard)(Arrows)
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_LEFT                        SDL_SCANCODE_LEFT
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_RIGHT                       SDL_SCANCODE_RIGHT
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_UP                          SDL_SCANCODE_UP
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_DOWN                        SDL_SCANCODE_DOWN

// Input Keys (Keyboard)(Numbers)
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_0                           SDL_SCANCODE_0
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_1                           SDL_SCANCODE_1
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_2                           SDL_SCANCODE_2
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_3                           SDL_SCANCODE_3
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_4                           SDL_SCANCODE_4
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_5                           SDL_SCANCODE_5  
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_6                           SDL_SCANCODE_6
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_7                           SDL_SCANCODE_7
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_8                           SDL_SCANCODE_8
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_9                           SDL_SCANCODE_9

// Input Keys (Keyboard)(Keypad Numbers)
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_0                    SDL_SCANCODE_KP_0
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_00                   SDL_SCANCODE_KP_00
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_000                  SDL_SCANCODE_KP_000
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_1                    SDL_SCANCODE_KP_1
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_2                    SDL_SCANCODE_KP_2
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_3                    SDL_SCANCODE_KP_3
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_4                    SDL_SCANCODE_KP_4
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_5                    SDL_SCANCODE_KP_5  
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_6                    SDL_SCANCODE_KP_6
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_7                    SDL_SCANCODE_KP_7
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_8                    SDL_SCANCODE_KP_8
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_KEYPAD_9                    SDL_SCANCODE_KP_9

// Input Keys (Keyboard)(Alphabet)
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_A                           SDL_SCANCODE_A
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_B                           SDL_SCANCODE_B
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_C                           SDL_SCANCODE_C
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_D                           SDL_SCANCODE_D
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_E                           SDL_SCANCODE_E  
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_F                           SDL_SCANCODE_F
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_G                           SDL_SCANCODE_G
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_H                           SDL_SCANCODE_H
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_I                           SDL_SCANCODE_I
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_J                           SDL_SCANCODE_J
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_K                           SDL_SCANCODE_K
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_L                           SDL_SCANCODE_L
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_M                           SDL_SCANCODE_M
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_N                           SDL_SCANCODE_N
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_O                           SDL_SCANCODE_O
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_P                           SDL_SCANCODE_P
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_Q                           SDL_SCANCODE_Q
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_R                           SDL_SCANCODE_R
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_S                           SDL_SCANCODE_S
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_T                           SDL_SCANCODE_T
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_U                           SDL_SCANCODE_U
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_V                           SDL_SCANCODE_V
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_W                           SDL_SCANCODE_W
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_X                           SDL_SCANCODE_X
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_Y                           SDL_SCANCODE_Y
#define CALYPSO_FRAMEWORK_SDL2_INPUT_KEYCODE_Z                           SDL_SCANCODE_Z

// Keyboard
unsigned char _calypso_framework_sdl2_input_keycode_state_array[255];          // SDL HAS 255 KEYS

// Mouse
int _calypso_framework_sdl_input_mouse_position[2]                       = {0,0};
int _calypso_framework_sdl2_input_mouse_button_left_state                = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP;

void calypso_framework_sdl2_input_show_mouse_cursor(void) 
{
    SDL_ShowCursor(SDL_ENABLE);
}

void calypso_framework_sdl2_input_hide_mouse_cursor(void) 
{
    SDL_ShowCursor(SDL_DISABLE);
}

int calypso_framework_sdl2_app_get_mouse_position_x()
{
    int x,y;
    SDL_GetMouseState(&x, &y);
    return x;
}

int calypso_framework_sdl2_app_get_mouse_position_y()
{
    int x,y;
    SDL_GetMouseState(&x, &y);
    return y;
}

int* calypso_framework_sdl2_app_get_mouse_position_ptr()
{
    return _calypso_framework_sdl_input_mouse_position;
}

int* calypso_framework_sdl2_app_get_mouse_button_left_state_ptr()
{
    return &_calypso_framework_sdl2_input_mouse_button_left_state;
}

int calypso_framework_sdl2_app_get_mouse_button_left_state_is_pressed()
{
    return _calypso_framework_sdl2_input_mouse_button_left_state == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED;
}

int calypso_framework_sdl2_app_get_mouse_button_left_state_is_released()
{
    return _calypso_framework_sdl2_input_mouse_button_left_state == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_RELEASED;
}


void calypso_framework_sdl2_input_update() 
{
    // Keyboard State
    {
        const unsigned char* keyboard_state = SDL_GetKeyboardState(NULL);

        for (int i = 0; i < 255; i++)
        {
            if (keyboard_state[i])
            {
                if (_calypso_framework_sdl2_input_keycode_state_array[i] != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP)
                    _calypso_framework_sdl2_input_keycode_state_array[i] = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN;
                else 
                     _calypso_framework_sdl2_input_keycode_state_array[i] = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED;
            }
            else
            {
                if (_calypso_framework_sdl2_input_keycode_state_array[i] != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN && _calypso_framework_sdl2_input_keycode_state_array[i] != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED)
                    _calypso_framework_sdl2_input_keycode_state_array[i] = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP;
                else
                    _calypso_framework_sdl2_input_keycode_state_array[i] = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_RELEASED;
            }
        }
    }

    // Mouse State (Position)
    {
        _calypso_framework_sdl_input_mouse_position[0] = calypso_framework_sdl2_app_get_mouse_position_x();
        _calypso_framework_sdl_input_mouse_position[1] = calypso_framework_sdl2_app_get_mouse_position_y();
    }

    // Mouse (Left Mouse Button)
    {
        int mouse_state = SDL_GetMouseState(NULL, NULL);
        if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if (_calypso_framework_sdl2_input_mouse_button_left_state != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP)
                _calypso_framework_sdl2_input_mouse_button_left_state = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN;
            else 
                _calypso_framework_sdl2_input_mouse_button_left_state = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED;
        }
        else
        {
             if (_calypso_framework_sdl2_input_mouse_button_left_state != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN && _calypso_framework_sdl2_input_mouse_button_left_state != CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED)
                _calypso_framework_sdl2_input_mouse_button_left_state = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP;
            else
                _calypso_framework_sdl2_input_mouse_button_left_state = CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_RELEASED;
        }
    }
}

int calypso_framework_sdl2_input_get_key_up(const unsigned char key_code) 
{
    return _calypso_framework_sdl2_input_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_UP;
}

int calypso_framework_sdl2_input_get_key_down(const unsigned char key_code) 
{
    return _calypso_framework_sdl2_input_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_DOWN;
}

int calypso_framework_sdl2_input_get_key_pressed(const unsigned char key_code) 
{
    return _calypso_framework_sdl2_input_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_PRESSED;
}

int calypso_framework_sdl2_input_get_key_released(const unsigned char key_code) 
{
    return _calypso_framework_sdl2_input_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_SDL2_INPUT_INPUT_STATE_RELEASED;
}