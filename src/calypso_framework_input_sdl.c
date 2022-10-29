/// <summary>
/// Input module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <SDL2/SDL.h>

// State
#define CALYPSO_FRAMEWORK_INPUT_SDL_STATE_NULL                         0
#define CALYPSO_FRAMEWORK_INPUT_SDL_STATE_INIT                         1
#define CALYPSO_FRAMEWORK_INPUT_SDL_STATE_ERROR                        2
unsigned int _calypso_framework_input_sdl_state                        = CALYPSO_FRAMEWORK_INPUT_SDL_STATE_NULL;

// Input States
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_UNPRESSED               0
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_PRESSED                 1
#define CALYPSO_FRAMEWORK_INPUT_SDL_INPUT_STATE_HELD                    2

// Input Keys
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEY_W                               SDL_SCANCODE_W
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEY_A                               SDL_SCANCODE_A
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEY_D                               SDL_SCANCODE_D
#define CALYPSO_FRAMEWORK_INPUT_SDL_KEY_S                               SDL_SCANCODE_S

// State
Uint8* _calypso_framework_input_sdl_key_states;

// Window
SDL_Window* _calypso_framework_input_sdl_window;

/**
* \brief Initializes input
* \param sdl_window SDL_Window*
* \return void
*/
void calypso_framework_input_sdl_init(SDL_Window* sdl_window)
{
    // Only Init Once
    if (_calypso_framework_input_sdl_state != CALYPSO_FRAMEWORK_INPUT_SDL_STATE_NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Input Error: input already init\n");
        printf("\033[0;00m"); // White
        return;
    }

    // Validate SDL Window
    if (sdl_window == NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_window is NULL\n");
        printf("\033[0;00m"); // White
        _calypso_framework_input_sdl_state = CALYPSO_FRAMEWORK_INPUT_SDL_STATE_ERROR;
        return;
    }

    // Set State Init | Set Window | Alloc Key States
    _calypso_framework_input_sdl_state = CALYPSO_FRAMEWORK_INPUT_SDL_STATE_INIT;
    _calypso_framework_input_sdl_window = sdl_window;
    _calypso_framework_input_sdl_key_states = realloc(_calypso_framework_input_sdl_key_states,255 * sizeof(Uint8));
}

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
* \brief Updates input
* \return void
*/
void calypso_framework_input_sdl_update() 
{
    // Not Init
    if (_calypso_framework_input_sdl_state != CALYPSO_FRAMEWORK_INPUT_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Input Error: input not init\n");
        printf("\033[0;00m"); // White
        return;
    }

    //const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
}

/**
* \brief Get key pressed
* \param key Uint8
* \return bool
*/
bool calypso_framework_input_sdl_get_key_pressed(const Uint8 key) 
{
    return false;
}

/**
* \brief Get key unpressed
* \param key Uint8
* \return bool
*/
bool calypso_framework_input_sdl_get_key_unpressed(const Uint8 key) 
{
    return false;
}

/**
* \brief Get key held
* \param key Uint8
* \return bool
*/
bool calypso_framework_input_sdl_get_key_held(const Uint8 key) 
{
      // Not Init
    if (_calypso_framework_input_sdl_state != CALYPSO_FRAMEWORK_INPUT_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Input Error: input not init\n");
        printf("\033[0;00m"); // White
        return false;
    }

    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    //calypso_framework_input_sdl_update_key_state(keyboard_state,calypso_framework_input_sdl_key_state_w);

    if (keyboard_state[key])
        return true;
    return false;
}