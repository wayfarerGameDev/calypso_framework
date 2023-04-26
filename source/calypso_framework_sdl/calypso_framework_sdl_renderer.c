/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t
#include <dependencies/SDL2/SDL.h>

// Logging Callback
typedef void (*calypso_framework_sdl_renderer_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_sdl_renderer_log_callback_t _calypso_framework_sdl_renderer_log_callback;

// State
#define CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_NULL                 0b00000000
#define CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_INIT                 0b00000001
#define CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_RUNNING              0b00000010
#define CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_SHUTDOWN             0b00000011
#define CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_ERROR                0b00000100
unsigned int _calypso_framework_sdl_renderer_state =              CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_NULL;

// Window | Renderer
SDL_Window* _calypso_framework_sdl_renderer_window =              NULL;
SDL_Renderer* _calypso_framework_sdl_renderer_renderer =          NULL;

// Clear Color (Cornflower Blue By Default)
uint8_t _calypso_framework_sdl_renderer_clear_color_r =           100;
uint8_t _calypso_framework_sdl_renderer_clear_color_g =           149;
uint8_t _calypso_framework_sdl_renderer_clear_color_b =           237;
uint8_t _calypso_framework_sdl_renderer_clear_color_a =           255;

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Log
------------------------------------------------------------------------------*/

void calypso_framework_sdl_renderer_set_log_callback(calypso_framework_sdl_renderer_log_callback_t log_callback)
{
    _calypso_framework_sdl_renderer_log_callback = log_callback;
}

void calypso_framework_sdl_renderer_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_sdl_renderer_log_callback == NULL)
        return;

    _calypso_framework_sdl_renderer_log_callback(log_msg,log_type);
}

void* calypso_framework_sdl_renderer_get_open_gl_proc_address()
{
    return SDL_GL_GetProcAddress;
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Init
------------------------------------------------------------------------------*/

void calypso_framework_sdl_renderer_init(SDL_Window* sdl_window)
{
    // Validate Window
    if (sdl_window == NULL)
    {
        return;
    }

    // Only Init Once
    if (_calypso_framework_sdl_renderer_state != CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_NULL)
    {
        calypso_framework_sdl_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl_renderer_state = CALYPSO_FRAMEWORK_SDL_RENDERER_STATE_INIT;

    // Set Window
    _calypso_framework_sdl_renderer_window = sdl_window;

     // Create a renderer
   _calypso_framework_sdl_renderer_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void calypso_framework_sdl_renderer_deinit()
{
     SDL_DestroyRenderer(_calypso_framework_sdl_renderer_renderer);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Draw Color
------------------------------------------------------------------------------*/

void calypso_framework_sdl_renderer_set_draw_color_rgb(const float r, const float g, const float b)
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, r, g, b, 255);
}

void calypso_framework_sdl_renderer_set_draw_color_rgba(const float r, const float g, const float b, const float a)
{
    // Set Clear Color
     SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, r, g, b, a);
}

void calypso_framework_sdl_renderer_set_draw_color_rgb_array(const uint8_t color_rgb_array[3])
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, color_rgb_array[0], color_rgb_array[1], color_rgb_array[2], 255);
}

void calypso_framework_sdl_renderer_set_draw_color_rgba_array(const uint8_t color_rgba_array[4])
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, color_rgba_array[0], color_rgba_array[1], color_rgba_array[2], color_rgba_array[3]);
}

void calypso_framework_sdl_renderer_set_draw_color_rgb_hex(int hex_value)
{
    // Convert Hex Color to RGB
    uint8_t r = ((hex_value >> 16) & 0xFF);
    uint8_t g = ((hex_value >> 8) & 0xFF);
    uint8_t b = ((hex_value) & 0xFF);

    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, r, g, b, 255);
}

void calypso_framework_sdl_renderer_set_draw_color_rgba_hex(int hex_value, uint8_t a)
{
    // Convert Hex Color to RGB
    uint8_t r = ((hex_value >> 16) & 0xFF);
    uint8_t g = ((hex_value >> 8) & 0xFF);
    uint8_t b = ((hex_value) & 0xFF);

    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, r, g, b, a);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Clear
------------------------------------------------------------------------------*/

void calypso_framework_sdl_renderer_set_clear_color_rgb(const float r, const float g, const float b)
{
    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = r;
    _calypso_framework_sdl_renderer_clear_color_g = g;
    _calypso_framework_sdl_renderer_clear_color_b = b;
    _calypso_framework_sdl_renderer_clear_color_a = 255;
}

void calypso_framework_sdl_renderer_set_clear_color_rgba(const float r, const float g, const float b, const float a)
{
    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = r;
    _calypso_framework_sdl_renderer_clear_color_g = g;
    _calypso_framework_sdl_renderer_clear_color_b = b;
    _calypso_framework_sdl_renderer_clear_color_a = a;
}

void calypso_framework_sdl_renderer_set_clear_color_rgb_array(const uint8_t color_rgb_array[3])
{
    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = color_rgb_array[0];
    _calypso_framework_sdl_renderer_clear_color_g = color_rgb_array[1];
    _calypso_framework_sdl_renderer_clear_color_b = color_rgb_array[2];
    _calypso_framework_sdl_renderer_clear_color_a = 255;
}

void calypso_framework_sdl_renderer_set_clear_color_rgba_array(const uint8_t color_rgba_array[4])
{
    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = color_rgba_array[0];
    _calypso_framework_sdl_renderer_clear_color_g = color_rgba_array[1];
    _calypso_framework_sdl_renderer_clear_color_b = color_rgba_array[2];
    _calypso_framework_sdl_renderer_clear_color_a = color_rgba_array[3];
}

void calypso_framework_sdl_renderer_set_clear_color_rgb_hex(int hex_value)
{
    // Convert Hex Color to RGB
    uint8_t r = ((hex_value >> 16) & 0xFF);
    uint8_t g = ((hex_value >> 8) & 0xFF);
    uint8_t b = ((hex_value) & 0xFF);

    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = r;
    _calypso_framework_sdl_renderer_clear_color_g = g;
    _calypso_framework_sdl_renderer_clear_color_b = b;
    _calypso_framework_sdl_renderer_clear_color_a = 255;
}

void calypso_framework_sdl_renderer_set_clear_color_rgba_hex(int hex_value, uint8_t a)
{
    // Convert Hex Color to RGB
    uint8_t r = ((hex_value >> 16) & 0xFF);
    uint8_t g = ((hex_value >> 8) & 0xFF);
    uint8_t b = ((hex_value) & 0xFF);

    // Set Clear Color
    _calypso_framework_sdl_renderer_clear_color_r = r;
    _calypso_framework_sdl_renderer_clear_color_g = g;
    _calypso_framework_sdl_renderer_clear_color_b = b;
    _calypso_framework_sdl_renderer_clear_color_a = a;
}

void calypso_framework_sdl_renderer_clear()
{
    // Get Current Draw Color
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(_calypso_framework_sdl_renderer_renderer, &r, &g, &b, &a);

    // Clear With Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer,_calypso_framework_sdl_renderer_clear_color_r,_calypso_framework_sdl_renderer_clear_color_g,_calypso_framework_sdl_renderer_clear_color_b,_calypso_framework_sdl_renderer_clear_color_a);
    SDL_RenderClear(_calypso_framework_sdl_renderer_renderer);

    // Set Draw Color Back To Current Draw Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl_renderer_renderer,r,g,b,a);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Present
------------------------------------------------------------------------------*/

void calypso_framework_sdl_renderer_present()
{
    // Render Present
    SDL_RenderPresent(_calypso_framework_sdl_renderer_renderer);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Draw (Rect)
------------------------------------------------------------------------------*/

