/// <summary>
/// Renderer module that uses SDL as a base
/// </summary>


#pragma once

// Includes
#include <SDL2/SDL.h>

// State
#define CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_NULL        0
#define CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT        1
#define CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_ERROR       4
unsigned int _calypso_framework_renderer_sdl_state = CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_NULL;

// Clear Color
Uint8 _calypso_framework_renderer_sdl_clear_color_r = 0;
Uint8 _calypso_framework_renderer_sdl_clear_color_g = 0;
Uint8 _calypso_framework_renderer_sdl_clear_color_b = 0;
Uint8 _calypso_framework_renderer_sdl_clear_color_a = 255;

// Renderer
SDL_Renderer* _calypso_framework_renderer_sdl_renderer;

// Color Arrays (Main)
const Uint8 _c_calypso_framework_renderer_sdl_color_array_black[4]              = {0,0,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_white[4]              = {255,255,255,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_silver[4]             = {192,192,192};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_gray[4]               = {128,128,128};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_red[4]                = {255,0,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_blue[4]               = {0,255,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_green[4]              = {0,128,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_yellow[4]             = {255,255,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_purple[4]             = {128,0,128,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_orange[4]             = {255,165,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_pink[4]               = {255,192,203};

// Color Arrays (Other)
const Uint8 _c_calypso_framework_renderer_sdl_color_array_aqua[4]               = {0,255,255,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_cornflower_blue[4]    = {100,149,237,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_magenta[4]            = {255,0,255,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_lime[4]               = {0,255,0,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_teal[4]               = {0,128,128,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_navy[4]               = {0,0,128,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_olive[4]              = {128,128,255};
const Uint8 _c_calypso_framework_renderer_sdl_color_array_turquoise[4]          = {64,224,208,255};

/**
* Initializes renderer
* @return void
*/
void calypso_framework_renderer_sdl_init(SDL_Window* sdl_window)
{
    // Only Init Once
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_NULL)
        return;

    // Validate SDL Window
    if (sdl_window == NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_window is NULL");
        printf("\033[0;00m"); // White
        _calypso_framework_renderer_sdl_state = CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_ERROR;
        return;
    }

    // Set State To Init By Default
    _calypso_framework_renderer_sdl_state = CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT;

    // Create SDL Renderer
    _calypso_framework_renderer_sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_calypso_framework_renderer_sdl_renderer == NULL) 
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        printf("\033[0;00m"); // White
        _calypso_framework_renderer_sdl_state = CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_ERROR;
        return;
    }
}

/**
* Set renderer's clear color
* @return void
*/
void calypso_framework_renderer_set_clear_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    _calypso_framework_renderer_sdl_clear_color_r = r;
    _calypso_framework_renderer_sdl_clear_color_g = g;
    _calypso_framework_renderer_sdl_clear_color_b = b;
    _calypso_framework_renderer_sdl_clear_color_a = a;
}

/**
* Set renderer's clear color from color array
* @return void
*/
void calypso_framework_renderer_set_clear_color_from_color_array(const Uint8 color_array[4])
{
    _calypso_framework_renderer_sdl_clear_color_r = color_array[0];
    _calypso_framework_renderer_sdl_clear_color_g = color_array[1];
    _calypso_framework_renderer_sdl_clear_color_b = color_array[2];
    _calypso_framework_renderer_sdl_clear_color_a = color_array[3];
}

/**
* Clears renderer
* @return void
*/
void calypso_framework_renderer_clear()
{
    // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_renderer can't clear");
        printf("\033[0;00m"); // White
        return;
    }

    //Clear With Color
    SDL_SetRenderDrawColor(_calypso_framework_renderer_sdl_renderer, _calypso_framework_renderer_sdl_clear_color_r, _calypso_framework_renderer_sdl_clear_color_g, _calypso_framework_renderer_sdl_clear_color_b, _calypso_framework_renderer_sdl_clear_color_a);
    SDL_RenderClear(_calypso_framework_renderer_sdl_renderer);
}

/**
* Renderer present render
* @return void
*/
void calypso_framework_renderer_render_present()
{
     // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_renderer can't render present");
        printf("\033[0;00m"); // White
        return;
    }

    SDL_RenderPresent(_calypso_framework_renderer_sdl_renderer);
}