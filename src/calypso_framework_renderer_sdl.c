/// <summary>
/// Renderer module that uses SDL as a base
/// </summary>


#pragma once

// Includes
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

// Render Color
Uint8 _calypso_framework_renderer_sdl_render_color_r = 255;
Uint8 _calypso_framework_renderer_sdl_render_color_g = 255;
Uint8 _calypso_framework_renderer_sdl_render_color_b = 255;
Uint8 _calypso_framework_renderer_sdl_render_color_a = 255;

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

// Fonts (TTF)
TTF_Font* _calypso_framework_renderer_sdl_font_current_ttf;

/**
* \brief Initializes renderer
* \param sdl_window SDL_Window*
* \return void
*/
void calypso_framework_renderer_sdl_init(SDL_Window* sdl_window)
{
    // Only Init Once
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: renderer already init");
        printf("\033[0;00m"); // White
        return;
    }

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

    // Init TTF
    TTF_Init();
}

/**
* \brief Deinitializes renderer
* \return void
*/
void calypso_framework_renderer_sdl_deinit(void)
{
    // Free Fonts
    TTF_CloseFont(_calypso_framework_renderer_sdl_font_current_ttf);

    // Quit TTF
    TTF_Quit();
}

/**
* \brief Set renderer's clear color
* \param r red
* \param g green
* \param b blue
* \param a alpha
* \return void
*/
void calypso_framework_renderer_set_clear_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    _calypso_framework_renderer_sdl_clear_color_r = r;
    _calypso_framework_renderer_sdl_clear_color_g = g;
    _calypso_framework_renderer_sdl_clear_color_b = b;
    _calypso_framework_renderer_sdl_clear_color_a = a;
}

/**
* \brief Set renderer's clear color from color array
* \param color_array Uint8 color_array[4]. {red,green,blue,alpha}
* \return void
*/
void calypso_framework_renderer_set_clear_color_from_color_array(const Uint8 color_array[4])
{
    _calypso_framework_renderer_sdl_clear_color_r = color_array[0];
    _calypso_framework_renderer_sdl_clear_color_g = color_array[1];
    _calypso_framework_renderer_sdl_clear_color_b = color_array[2];
    _calypso_framework_renderer_sdl_clear_color_a = color_array[3];
}

/**
* \brief Set renderer's render color
* \param r red
* \param g green
* \param b blue
* \param a alpha
* \return void
*/
void calypso_framework_renderer_set_render_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    _calypso_framework_renderer_sdl_render_color_r = r;
    _calypso_framework_renderer_sdl_render_color_g = g;
    _calypso_framework_renderer_sdl_render_color_b = b;
    _calypso_framework_renderer_sdl_render_color_a = a;

     SDL_SetRenderDrawColor(_calypso_framework_renderer_sdl_renderer, _calypso_framework_renderer_sdl_render_color_r, _calypso_framework_renderer_sdl_render_color_g, _calypso_framework_renderer_sdl_render_color_b, _calypso_framework_renderer_sdl_render_color_a);
}

/**
* \brief Set renderer's render color from color array
* \param color_array Uint8 color_array[4]. {red,green,blue,alpha}
* \return void
*/
void calypso_framework_renderer_set_render_color_from_color_array(const Uint8 color_array[4])
{
    _calypso_framework_renderer_sdl_render_color_r = color_array[0];
    _calypso_framework_renderer_sdl_render_color_g = color_array[1];
    _calypso_framework_renderer_sdl_render_color_b = color_array[2];
    _calypso_framework_renderer_sdl_render_color_a = color_array[3];

     SDL_SetRenderDrawColor(_calypso_framework_renderer_sdl_renderer, _calypso_framework_renderer_sdl_render_color_r, _calypso_framework_renderer_sdl_render_color_g, _calypso_framework_renderer_sdl_render_color_b, _calypso_framework_renderer_sdl_render_color_a);
}

/**
* \brief Clear renderer.
* \return void
*/
void calypso_framework_renderer_clear(void)
{
    // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_renderer can't clear\n");
        printf("\033[0;00m"); // White
        return;
    }

    //Clear With Color
    SDL_SetRenderDrawColor(_calypso_framework_renderer_sdl_renderer, _calypso_framework_renderer_sdl_clear_color_r, _calypso_framework_renderer_sdl_clear_color_g, _calypso_framework_renderer_sdl_clear_color_b, _calypso_framework_renderer_sdl_clear_color_a);
    SDL_RenderClear(_calypso_framework_renderer_sdl_renderer);
    SDL_SetRenderDrawColor(_calypso_framework_renderer_sdl_renderer, _calypso_framework_renderer_sdl_render_color_r, _calypso_framework_renderer_sdl_render_color_g, _calypso_framework_renderer_sdl_render_color_b, _calypso_framework_renderer_sdl_render_color_a);
}

/**
* \brief Render present frame.
* \return void
*/
void calypso_framework_renderer_render_present(void)
{
     // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: sdl_renderer can't render present\n");
        printf("\033[0;00m"); // White
        return;
    }

    SDL_RenderPresent(_calypso_framework_renderer_sdl_renderer);
}

/**
* \brief Add font to use by name (TTF).
* \param font_name A font loaded with that name
* \return font_index (int)
*/
int calypso_framework_renderer_sdl_render_add_font_ttf(const char* font_file_path, const unsigned int font_size)
{
    // Load Font
    _calypso_framework_renderer_sdl_font_current_ttf = TTF_OpenFont(font_file_path,font_size);
    if (_calypso_framework_renderer_sdl_font_current_ttf == NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: font not added (file path is not valid)\n");
        printf("\033[0;00m"); // White
        return -1;
    }

    return 0;
}

/**
* \brief Sets current font to use by index. (TTF)
* \param font_index A font loaded with that index
* \return void
*/
void calypso_framework_renderer_sdl_render_set_current_font_by_index_ttf(const int font_index)
{
}

/**
* \brief Draw a line.
* \param x1 The x coordinate of the start point.
* \param y1 The y coordinate of the start point.
* \param x2 The x coordinate of the end point.
* \param y2 The y coordinate of the end point.
* \return 0 on success, or -1 on error
*/
void calypso_framework_renderer_sdl_render_draw_text_ttf(const char* text, const int x, const int y)
{
    // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: can't draw font (renderer not init)\n");
        printf("\033[0;00m"); // White
        return;
    }

    // Not Valid Current Font
    if (_calypso_framework_renderer_sdl_font_current_ttf == NULL)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: can't draw font (current font is NULL)\n");
        printf("\033[0;00m"); // White
        return;
    }

    // Make Color
    SDL_Color color;
    color.r = _calypso_framework_renderer_sdl_render_color_r;
    color.g = _calypso_framework_renderer_sdl_render_color_g;
    color.b = _calypso_framework_renderer_sdl_render_color_b;
    color.a = _calypso_framework_renderer_sdl_render_color_a;

    // Create Surface
    SDL_Surface* surf = TTF_RenderText_Solid(_calypso_framework_renderer_sdl_font_current_ttf,text,color);

    // Create Texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(_calypso_framework_renderer_sdl_renderer,surf);

    // Create Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;

    SDL_FreeSurface(surf);
    SDL_RenderCopy(_calypso_framework_renderer_sdl_renderer,tex,NULL,&rect);
    SDL_DestroyTexture(tex);

}

/**
* \brief Draw a line.
* \param x1 The x coordinate of the start point.
* \param y1 The y coordinate of the start point.
* \param x2 The x coordinate of the end point.
* \param y2 The y coordinate of the end point.
* \return 0 on success, or -1 on error
*/
int calypso_framework_renderer_sdl_draw_line(const int x1, const int y1, const int x2, const int y2)
{
     // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: can't draw line (renderer is not init)\n");
        printf("\033[0;00m"); // White
        return -1;
    }

    return SDL_RenderDrawLine(_calypso_framework_renderer_sdl_renderer,x1,y1,x2,y2);
}

/**
* \brief Draw a line.
* \param x1 The x coordinate of the start point.
* \param y1 The y coordinate of the start point.
* \param x2 The x coordinate of the end point.
* \param y2 The y coordinate of the end point.
* \return 0 on success, or -1 on error
*/
int calypso_framework_renderer_sdl_draw_lines(const int x1, const int y1, const int x2, const int y2)
{
     // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: can't draw line (renderer is not init)\n");
        printf("\033[0;00m"); // White
        return -1;
    }

    return SDL_RenderDrawLine(_calypso_framework_renderer_sdl_renderer,x1,y1,x2,y2);
}

/**
* \brief Draw a line (floats).
* \param x1 The x coordinate of the start point.
* \param y1 The y coordinate of the start point.
* \param x2 The x coordinate of the end point.
* \param y2 The y coordinate of the end point.
* \return 0 on success, or -1 on error
*/
int calypso_framework_renderer_sdl_draw_line_f(const float x1, const float y1, const float x2, const float y2)
{
     // Not Valid State
    if (_calypso_framework_renderer_sdl_state != CALYPSO_FRAMEWORK_RENDERER_SDL_STATE_INIT)
    {
        printf("\033[0;31m"); // Red
        printf("Renderer Error: can't draw line (renderer not init)\n");
        printf("\033[0;00m"); // White
        return -1;
    }

    return SDL_RenderDrawLineF(_calypso_framework_renderer_sdl_renderer,x1,y1,x2,y2);
}