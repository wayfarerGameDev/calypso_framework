/// <summary>
/// Render module that uses SDL as a base
/// </summary>

#pragma once

// Dependencies
#include <dependencies/SDL2/SDL.h>
#include <dependencies/SDL2/SDL_ttf.h>
#include <dependencies/SDL2/SDL_image.h>

// State
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_NULL                          0b00000000
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_INIT                          0b00000001
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_RUNNING                       0b00000010
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_SHUTDOWN                      0b00000011
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_ERROR                         0b00000100
unsigned int _calypso_framework_sdl2_renderer_state                         = CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_NULL;

// Window | Renderer
SDL_Window* _calypso_framework_sdl2_renderer_window_ptr                     = NULL;
SDL_Renderer* _calypso_framework_sdl2_renderer_renderer_ptr                 = NULL;

// Clear Color (Cornflower Blue By Default)
unsigned char _calypso_framework_sdl2_renderer_clear_color_r                = 100;
unsigned char _calypso_framework_sdl2_renderer_clear_color_g                = 149;
unsigned char _calypso_framework_sdl2_renderer_clear_color_b                = 237;
unsigned char _calypso_framework_sdl2_renderer_clear_color_a                = 255;

// Render Space
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_WORLD                  0
#define CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_SCREEN                 1
unsigned int _calypso_framework_sdl2_renderer_render_space                  = CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_WORLD;
double _calypso_framework_sdl2_renderer_render_space_world_offset_x         = 0;
double _calypso_framework_sdl2_renderer_render_space_world_offset_y         = 0;
double _calypso_framework_sdl2_renderer_render_space_screen_offset_x        = 0;
double _calypso_framework_sdl2_renderer_render_space_screen_offset_y        = 0;
double* _calypso_framework_sdl2_renderer_render_space_offset_x_ptr          = NULL;
double* _calypso_framework_sdl2_renderer_render_space_offset_y_ptr          = NULL;

// Font
void* _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr        = NULL;

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Init | Denint
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_set_to_defaults()
{
    // Set Default Render Space
    _calypso_framework_sdl2_renderer_render_space = CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_WORLD;
    _calypso_framework_sdl2_renderer_render_space_offset_x_ptr = &_calypso_framework_sdl2_renderer_render_space_world_offset_x;
    _calypso_framework_sdl2_renderer_render_space_offset_y_ptr = &_calypso_framework_sdl2_renderer_render_space_world_offset_y;    

    // Set Default Render Values
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr,255,255,255,255);
    SDL_RenderSetScale(_calypso_framework_sdl2_renderer_renderer_ptr, 1, 1);
    SDL_SetRenderDrawBlendMode(_calypso_framework_sdl2_renderer_renderer_ptr, SDL_BLENDMODE_BLEND);
}

void calypso_framework_sdl2_renderer_init(SDL_Window* sdl_window_ptr)
{
    // Validate Window
    if (sdl_window_ptr == NULL)
    {
        return;
    }

    // Only Init Once
    if (_calypso_framework_sdl2_renderer_state != CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_NULL)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("sdl_rednerer->init","Already Initalized",2);
        #endif
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl2_renderer_state = CALYPSO_FRAMEWORK_SDL2_RENDERER_STATE_INIT;

    // Set Window
    _calypso_framework_sdl2_renderer_window_ptr = sdl_window_ptr;

     // Create a renderer
   _calypso_framework_sdl2_renderer_renderer_ptr = SDL_CreateRenderer(sdl_window_ptr, -1, SDL_RENDERER_ACCELERATED);

    // Init Font(TTF)
    {
        TTF_Init();
    }

    // Defaults
    calypso_framework_sdl2_renderer_set_to_defaults();  
}

void calypso_framework_sdl2_renderer_deinit()
{
    // Cleanup Renderer
    SDL_DestroyRenderer(_calypso_framework_sdl2_renderer_renderer_ptr);

    // Cleanup Font (TTF)
    {
        TTF_Quit();
    }
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Draw Color
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_set_draw_color_rgb(const unsigned char r, const unsigned char g, const unsigned char b)
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, r, g, b, 255);
}

void calypso_framework_sdl2_renderer_set_draw_color_rgba(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
    // Set Clear Color
     SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, r, g, b, a);
}

void calypso_framework_sdl2_renderer_set_draw_color_rgb_array(const unsigned char color_rgb_array[3])
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, color_rgb_array[0], color_rgb_array[1], color_rgb_array[2], 255);
}

void calypso_framework_sdl2_renderer_set_draw_color_rgba_array(const unsigned char color_rgba_array[4])
{
    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, color_rgba_array[0], color_rgba_array[1], color_rgba_array[2], color_rgba_array[3]);
}

void calypso_framework_sdl2_renderer_set_draw_color_rgb_hex(int hex_value)
{
    // Convert Hex Color to RGB
    unsigned char r = ((hex_value >> 16) & 0xFF);
    unsigned char g = ((hex_value >> 8) & 0xFF);
    unsigned char b = ((hex_value) & 0xFF);

    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, r, g, b, 255);
}

void calypso_framework_sdl2_renderer_set_draw_color_rgba_hex(int hex_value, unsigned char a)
{
    // Convert Hex Color to RGB
    unsigned char r = ((hex_value >> 16) & 0xFF);
    unsigned char g = ((hex_value >> 8) & 0xFF);
    unsigned char b = ((hex_value) & 0xFF);

    // Set Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, r, g, b, a);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Clear
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_set_clear_color_rgb(const float r, const float g, const float b)
{
    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = r;
    _calypso_framework_sdl2_renderer_clear_color_g = g;
    _calypso_framework_sdl2_renderer_clear_color_b = b;
    _calypso_framework_sdl2_renderer_clear_color_a = 255;
}

void calypso_framework_sdl2_renderer_set_clear_color_rgba(const float r, const float g, const float b, const float a)
{
    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = r;
    _calypso_framework_sdl2_renderer_clear_color_g = g;
    _calypso_framework_sdl2_renderer_clear_color_b = b;
    _calypso_framework_sdl2_renderer_clear_color_a = a;
}

void calypso_framework_sdl2_renderer_set_clear_color_rgb_array(const unsigned char color_rgb_array[3])
{
    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = color_rgb_array[0];
    _calypso_framework_sdl2_renderer_clear_color_g = color_rgb_array[1];
    _calypso_framework_sdl2_renderer_clear_color_b = color_rgb_array[2];
    _calypso_framework_sdl2_renderer_clear_color_a = 255;
}

void calypso_framework_sdl2_renderer_set_clear_color_rgba_array(const unsigned char color_rgba_array[4])
{
    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = color_rgba_array[0];
    _calypso_framework_sdl2_renderer_clear_color_g = color_rgba_array[1];
    _calypso_framework_sdl2_renderer_clear_color_b = color_rgba_array[2];
    _calypso_framework_sdl2_renderer_clear_color_a = color_rgba_array[3];
}

void calypso_framework_sdl2_renderer_set_clear_color_rgb_hex(int hex_value)
{
    // Convert Hex Color to RGB
    unsigned char r = ((hex_value >> 16) & 0xFF);
    unsigned char g = ((hex_value >> 8) & 0xFF);
    unsigned char b = ((hex_value) & 0xFF);

    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = r;
    _calypso_framework_sdl2_renderer_clear_color_g = g;
    _calypso_framework_sdl2_renderer_clear_color_b = b;
    _calypso_framework_sdl2_renderer_clear_color_a = 255;
}

void calypso_framework_sdl2_renderer_set_clear_color_rgba_hex(int hex_value, unsigned char a)
{
    // Convert Hex Color to RGB
    unsigned char r = ((hex_value >> 16) & 0xFF);
    unsigned char g = ((hex_value >> 8) & 0xFF);
    unsigned char b = ((hex_value) & 0xFF);

    // Set Clear Color
    _calypso_framework_sdl2_renderer_clear_color_r = r;
    _calypso_framework_sdl2_renderer_clear_color_g = g;
    _calypso_framework_sdl2_renderer_clear_color_b = b;
    _calypso_framework_sdl2_renderer_clear_color_a = a;
}

void calypso_framework_sdl2_renderer_clear()
{
    // Defaults
    calypso_framework_sdl2_renderer_set_to_defaults();   
    
    // Get Current Draw Color
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, &r, &g, &b, &a);

    // Clear With Clear Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr,_calypso_framework_sdl2_renderer_clear_color_r,_calypso_framework_sdl2_renderer_clear_color_g,_calypso_framework_sdl2_renderer_clear_color_b,_calypso_framework_sdl2_renderer_clear_color_a);
    SDL_RenderClear(_calypso_framework_sdl2_renderer_renderer_ptr);

    // Set Draw Color Back To Current Draw Color
    SDL_SetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr,r,g,b,a);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Present
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_present()
{
    // Defaults
    calypso_framework_sdl2_renderer_set_to_defaults();  

    // Render Present
    SDL_RenderPresent(_calypso_framework_sdl2_renderer_renderer_ptr);
}

/*-----------------------------------------------------------------------------
Calypso Framework SDL Renderer : Viewport
------------------------------------------------------------------------------*/

void calpyso_framework_sdl2_renderer_set_viewport(const int x, const int y, int w, int h)
{
    // Set Viewport
    SDL_Rect viewport = { x, y, w, h };
    SDL_RenderSetViewport(_calypso_framework_sdl2_renderer_renderer_ptr, &viewport);
}

void calpyso_framework_sdl2_renderer_set_viewport_scaled(const int x, const int y, int w, int h)
{
    // Set Viewport
    SDL_Rect viewport = { x, y, w, h };
    SDL_RenderSetViewport(_calypso_framework_sdl2_renderer_renderer_ptr, &viewport);

    // Set Logical Size (This scales what is rendered to viewport by width and height)
    SDL_RenderSetLogicalSize(_calypso_framework_sdl2_renderer_renderer_ptr, viewport.w, viewport.h);

    // Update the Viewport Immediately
    SDL_RenderClear(_calypso_framework_sdl2_renderer_renderer_ptr);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Render Scale
------------------------------------------------------------------------------*/

void calpyso_framework_sdl2_renderer_set_render_scale(float x, float y)
{
    SDL_RenderSetScale(_calypso_framework_sdl2_renderer_renderer_ptr, x, y);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Render Space
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_set_render_space(const unsigned int render_space)
{
    // Set Render Space
    _calypso_framework_sdl2_renderer_render_space = render_space;

    // Apply Render Space (Screen)
    if (render_space == CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_SCREEN)
    {
        _calypso_framework_sdl2_renderer_render_space_offset_x_ptr = &_calypso_framework_sdl2_renderer_render_space_screen_offset_x;
        _calypso_framework_sdl2_renderer_render_space_offset_y_ptr = &_calypso_framework_sdl2_renderer_render_space_screen_offset_y;
    }

    // Apply Render Space (World)
    if (render_space == CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_WORLD)
    {
        _calypso_framework_sdl2_renderer_render_space_offset_x_ptr = &_calypso_framework_sdl2_renderer_render_space_world_offset_x;
        _calypso_framework_sdl2_renderer_render_space_offset_y_ptr = &_calypso_framework_sdl2_renderer_render_space_world_offset_y;    
    }
}


void calypso_framework_sdl2_renderer_set_render_space_world_offset(const double x, const double y)
{
    // Apply Render Space World Offset
    _calypso_framework_sdl2_renderer_render_space_world_offset_x = x;
    _calypso_framework_sdl2_renderer_render_space_world_offset_y = y;    
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Font (TTF)
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_load_font_ttf(void** font_ptr_ref, char* file_path, int font_size)
{
    // Do Not Do If Not Init
    if (!TTF_WasInit())
        return;

    // Free
    free(*font_ptr_ref);

    // Open Font
    *font_ptr_ref = TTF_OpenFont(file_path, font_size);
}

void calypso_framework_sdl2_renderer_set_font_current(void* font_ptr)
{
    // Do Not Do If Not Init
    if (!TTF_WasInit())
        return;

    // Set Current Font
    _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr = font_ptr;
}

int calypso_framework_sdl2_renderer_get_text_width_i(const char* string)
{
     // Do Not Do If Not Init 
    if (!TTF_WasInit())
        return 0;

    // Get Font
    TTF_Font* font = _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr;
    if (font == NULL)
        return 0;

    // Create Surface
    SDL_Color color = {0,0,0,0};
    SDL_Surface* string_surface = TTF_RenderText_Solid(font,string, color);

    // Get Width
    int width = string_surface->w;

    // Free Surface And Texture
    SDL_FreeSurface(string_surface);

    // Return Width
    return width;
}

int calypso_framework_sdl2_renderer_get_text_height_i(const char* string)
{
     // Do Not Do If Not Init 
    if (!TTF_WasInit())
        return 0;

    // Get Font
    TTF_Font* font = _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr;
    if (font == NULL)
        return 0;

    // Create Surface
    SDL_Color color = {0,0,0,0};
    SDL_Surface* string_surface = TTF_RenderText_Solid(font,string, color);

    // Get Height
    int height = string_surface->h;

    // Free Surface And Texture
    SDL_FreeSurface(string_surface);

    // Return Height
    return height;
}

void calypso_framework_sdl2_renderer_render_text_ttf_i(const char* string, int x, int y)
{
    // Do Not Do If Not Init 
    if (!TTF_WasInit())
        return;

    // Get Font
    TTF_Font* font = _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr;
    if (font == NULL)
        return;

    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Get Render Color
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, &r, &g, &b, &a);
    SDL_Color color = {r,g,b,a};

    // Create Surface
    SDL_Surface* string_surface = TTF_RenderText_Solid(font,string, color);

    // Create Texture From Surface
    SDL_Texture* string_texture = SDL_CreateTextureFromSurface(_calypso_framework_sdl2_renderer_renderer_ptr, string_surface);

    // Render String
    SDL_Rect dest_rect = {x, y, string_surface->w, string_surface->h};
    SDL_RenderCopy(_calypso_framework_sdl2_renderer_renderer_ptr, string_texture, NULL, &dest_rect);

    // Free Surface And Texture
    SDL_FreeSurface(string_surface);
    SDL_DestroyTexture(string_texture);
}

void calypso_framework_sdl2_renderer_render_text_ttf_f(const char* string, float x, float y)
{
    // Do Not Do If Not Init
    if (!TTF_WasInit())
        return;

    // Get Font
    TTF_Font* font = _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr;
    if (font == NULL)
        return;

    // Apply Render Space
    x -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Get Render Color
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, &r, &g, &b, &a);
    SDL_Color color = {r,g,b,a};

    // Create Surface
    SDL_Surface* string_surface = TTF_RenderText_Solid(font,string, color);

    // Create Texture From Surface
    SDL_Texture* string_texture = SDL_CreateTextureFromSurface(_calypso_framework_sdl2_renderer_renderer_ptr, string_surface);

    // Render String
    SDL_FRect dest_rect = {x, y, string_surface->w, string_surface->h};
    SDL_RenderCopyF(_calypso_framework_sdl2_renderer_renderer_ptr, string_texture, NULL, &dest_rect);

    // Free Surface And Texture
    SDL_FreeSurface(string_surface);
    SDL_DestroyTexture(string_texture);
}

void calypso_framework_sdl2_renderer_render_text_ttf_d(const char* string, double x, double y)
{
    // Do Not Do If Not Init
    if (!TTF_WasInit())
        return;

    // Get Font
    TTF_Font* font = _calypso_framework_sdl2_renderer_font_map_item_ttf_current_ptr;
    if (font == NULL)
        return;
    
    // Apply Render Space
    x -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Get Render Color
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(_calypso_framework_sdl2_renderer_renderer_ptr, &r, &g, &b, &a);
    SDL_Color color = {r,g,b,a};

    // Create Surface
    SDL_Surface* string_surface = TTF_RenderText_Solid(font,string, color);

    // Create Texture From Surface
    SDL_Texture* string_texture = SDL_CreateTextureFromSurface(_calypso_framework_sdl2_renderer_renderer_ptr, string_surface);

    // Render String
    SDL_FRect dest_rect = {x, y, string_surface->w, string_surface->h};
    SDL_RenderCopyF(_calypso_framework_sdl2_renderer_renderer_ptr, string_texture, NULL, &dest_rect);

    // Free Surface And Texture
    SDL_FreeSurface(string_surface);
    SDL_DestroyTexture(string_texture);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Render (Texture)
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_load_texture_bmp(void** texture_ptr_ref, char* file_path)
{
    // Free
    free(*texture_ptr_ref);
    
    // Load BMP | Create texture | Free
    SDL_Surface* surface = SDL_LoadBMP(file_path);
    *texture_ptr_ref = SDL_CreateTextureFromSurface(_calypso_framework_sdl2_renderer_renderer_ptr,surface);
}

void calypso_framework_sdl2_renderer_load_texture(void** texture_ptr_ref, char* file_path)
{
    // Free
    free(*texture_ptr_ref);

    SDL_Surface* surface =  IMG_Load(file_path);
    *texture_ptr_ref = SDL_CreateTextureFromSurface(_calypso_framework_sdl2_renderer_renderer_ptr,surface);
}

void calypso_framework_sdl2_renderer_render_texture_i(void* texture_ptr, int x, int y)
{
    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture_ptr,NULL,NULL,&rect.w,&rect.h);

    // Render
    SDL_RenderCopy(_calypso_framework_sdl2_renderer_renderer_ptr,texture_ptr,NULL,&rect);
}

void calypso_framework_sdl2_renderer_render_texture_f(void* texture_ptr, float x, float y)
{
    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture_ptr,NULL,NULL,&rect.w,&rect.h);

    // Render
    SDL_RenderCopy(_calypso_framework_sdl2_renderer_renderer_ptr,texture_ptr,NULL,&rect);
}

void calypso_framework_sdl2_renderer_render_texture_sized_i(void* texture_ptr, int x, int y, int w, int h)
{
    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Render
    SDL_RenderCopy(_calypso_framework_sdl2_renderer_renderer_ptr,texture_ptr,NULL,&rect);
}

void calypso_framework_sdl2_renderer_render_texture_sized_f(void* texture_ptr, float x, float y, float w, float h)
{
    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Render
    SDL_RenderCopy(_calypso_framework_sdl2_renderer_renderer_ptr,texture_ptr,NULL,&rect);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Render (Rect)
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_render_rect_i(int x, int y, int w, int h)
{
    // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Points
    SDL_Point points[5];
    points[0].x = x;
    points[0].y = y;
    points[1].x = x + w - 1;
    points[1].y = y;
    points[2].x = x + w - 1;
    points[2].y = y + h - 1;
    points[3].x = x;
    points[3].y = y + h - 1;
    points[4].x = x;
    points[4].y = y;
    
    // Render
    SDL_RenderDrawLines(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
}

void calypso_framework_sdl2_renderer_render_rect_f(float x, float y, float w, float h)
{
    // Apply Render Space
    x -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Points
    SDL_FPoint points[5];
    points[0].x = x;
    points[0].y = y;
    points[1].x = x + w - 1;
    points[1].y = y;
    points[2].x = x + w - 1;
    points[2].y = y + h - 1;
    points[3].x = x;
    points[3].y = y + h - 1;
    points[4].x = x;
    points[4].y = y;
    
    // Render
    SDL_RenderDrawLinesF(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
}

void calypso_framework_sdl2_renderer_render_rect_d(double x, double y, double w, double h)
{
    // Apply Render Space
    x -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Points
    SDL_FPoint points[5];
    points[0].x = x;
    points[0].y = y;
    points[1].x = x + w - 1;
    points[1].y = y;
    points[2].x = x + w - 1;
    points[2].y = y + h - 1;
    points[3].x = x;
    points[3].y = y + h - 1;
    points[4].x = x;
    points[4].y = y;
    
    // Render
    SDL_RenderDrawLinesF(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
}

void calypso_framework_sdl2_renderer_render_rect_filled_i(int x, int y, int w, int h)
{
     // Apply Render Space
    x -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Render
    SDL_RenderFillRect(_calypso_framework_sdl2_renderer_renderer_ptr,&rect);
}

void calypso_framework_sdl2_renderer_render_rect_filled_f(float x, float y, float w, float h)
{
    // Apply Render Space
    x -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (float)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Construct Rect
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Render
    SDL_RenderFillRectF(_calypso_framework_sdl2_renderer_renderer_ptr,&rect);
}

void calypso_framework_sdl2_renderer_render_rect_filled_d(double x, double y, const double w, double h)
{
    // Apply Render Space
    x -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    y -= (double)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

   // Construct Rect
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Render
    SDL_RenderFillRectF(_calypso_framework_sdl2_renderer_renderer_ptr,&rect);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL Renderer : Render (Rect Buffer)
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_renderer_create_rect_buffer_i(int** rect_buffer_ptr, const int count)
{
    *rect_buffer_ptr = malloc(sizeof(int) * 4 * count);
}

void calypso_framework_sdl2_renderer_create_rect_buffer_f(float** rect_buffer_ptr, const int count)
{
    *rect_buffer_ptr = malloc(sizeof(float) * 4 * count);
}

void calypso_framework_sdl2_renderer_create_rect_buffer_d(double** rect_buffer_ptr, const int count)
{
    *rect_buffer_ptr = malloc(sizeof(double) * 4 * count);
}

void calypso_framework_sdl2_renderer_set_rect_buffer_element_i(int* rect_buffer, const int element_index, const int x, const int y, int w, int h)
{
    rect_buffer[element_index * 4 + 0] = x;
    rect_buffer[element_index * 4 + 1] = y;
    rect_buffer[element_index * 4 + 2] = w;
    rect_buffer[element_index * 4 + 3] = h;
}

void calypso_framework_sdl2_renderer_set_rect_buffer_element_f(float* rect_buffer, const int element_index, const float x, const float y, float w, float h)
{
    rect_buffer[element_index * 4 + 0] = x;
    rect_buffer[element_index * 4 + 1] = y;
    rect_buffer[element_index * 4 + 2] = w;
    rect_buffer[element_index * 4 + 3] = h;
}

void calypso_framework_sdl2_renderer_set_rect_buffer_element_d(double* rect_buffer, const int element_index, const double x, const double y, const double w, double h)
{
    rect_buffer[element_index * 4 + 0] = x;
    rect_buffer[element_index * 4 + 1] = y;
    rect_buffer[element_index * 4 + 2] = w;
    rect_buffer[element_index * 4 + 3] = h;
}

void calypso_framework_sdl2_renderer_render_rect_buffer_i(const int* rect_buffer, const int count)
{
    // Get Offset
    const int offset_x = (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const int offset_y = (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_Point points[5];
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Get XYWH
        int x = rect_buffer[i * stride] - offset_x;
        int y = rect_buffer[i * stride + 1] - offset_y;
        int w = rect_buffer[i * stride + 2];
        int h = rect_buffer[i * stride + 3];

        // Construct Points
        points[0].x = x;
        points[0].y = y;
        points[1].x = x + w - 1;
        points[1].y = y;
        points[2].x = x + w - 1;
        points[2].y = y + h - 1;
        points[3].x = x;
        points[3].y = y + h - 1;
        points[4].x = x;
        points[4].y = y;

        // Render
        SDL_RenderDrawLines(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
    }
}

void calypso_framework_sdl2_renderer_render_rect_buffer_f(const float* rect_buffer, const int count)
{
   // Get Offset
    const float offset_x = (float)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const float offset_y = (float)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_FPoint points[5];
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Get XYWH
        float x = rect_buffer[i * stride] - offset_x;
        float y = rect_buffer[i * stride + 1] - offset_y;
        float w = rect_buffer[i * stride + 2];
        float h = rect_buffer[i * stride + 3];

        // Construct Points
        points[0].x = x;
        points[0].y = y;
        points[1].x = x + w - 1;
        points[1].y = y;
        points[2].x = x + w - 1;
        points[2].y = y + h - 1;
        points[3].x = x;
        points[3].y = y + h - 1;
        points[4].x = x;
        points[4].y = y;

        // Render
        SDL_RenderDrawLinesF(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
    }
}

void calypso_framework_sdl2_renderer_render_rect_buffer_d(const double* rect_buffer, const int count)
{
    // Get Offset
    const double offset_x = (double)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const double offset_y = (double)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_FPoint points[5];
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Get XYWH
        double x = rect_buffer[i * stride] - offset_x;
        double y = rect_buffer[i * stride + 1] - offset_y;
        double w = rect_buffer[i * stride + 2];
        double h = rect_buffer[i * stride + 3];

        // Construct Points
        points[0].x = x;
        points[0].y = y;
        points[1].x = x + w - 1;
        points[1].y = y;
        points[2].x = x + w - 1;
        points[2].y = y + h - 1;
        points[3].x = x;
        points[3].y = y + h - 1;
        points[4].x = x;
        points[4].y = y;

        // Render
        SDL_RenderDrawLinesF(_calypso_framework_sdl2_renderer_renderer_ptr, points, 5);
    }
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_i(const int* rect_buffer, const int count)
{
    // Get Offset
    const int offset_x = (int)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const int offset_y = (int)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_Rect rect;
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Construct Rect
        rect.x = rect_buffer[i * stride] - offset_x;
        rect.y = rect_buffer[i * stride + 1] - offset_y;
        rect.w = rect_buffer[i * stride + 2];
        rect.h = rect_buffer[i * stride + 3];

        // Render
        SDL_RenderFillRect(_calypso_framework_sdl2_renderer_renderer_ptr, &rect);
    }
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_f(const float* rect_buffer, const int count)
{
    // Get Offset
    const float offset_x = (float)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const float offset_y = (float)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_FRect rect;
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Construct Rect
        rect.x = rect_buffer[i * stride] - offset_x;
        rect.y = rect_buffer[i * stride + 1] - offset_y;
        rect.w = rect_buffer[i * stride + 2];
        rect.h = rect_buffer[i * stride + 3];

        // Render
        SDL_RenderFillRectF(_calypso_framework_sdl2_renderer_renderer_ptr, &rect);
    }
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_d(const double* rect_buffer, const int count)
{
    // Get Offset
    const double offset_x = (double)*_calypso_framework_sdl2_renderer_render_space_offset_x_ptr;
    const double offset_y = (double)*_calypso_framework_sdl2_renderer_render_space_offset_y_ptr;

    // Render
    SDL_FRect rect;
    int stride = 4;
    for (int i = 0; i < count; i++)
    {
        // Construct Rect
        rect.x = rect_buffer[i * stride] - offset_x;
        rect.y = rect_buffer[i * stride + 1] - offset_y;
        rect.w = rect_buffer[i * stride + 2];
        rect.h = rect_buffer[i * stride + 3];

        // Render
        SDL_RenderFillRectF(_calypso_framework_sdl2_renderer_renderer_ptr, &rect);
    }
}

void calypso_framework_sdl2_renderer_render_rect_buffer_range_i(const int* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_buffer_i(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}

void calypso_framework_sdl2_renderer_render_rect_buffer_range_f(const float* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_buffer_f(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}

void calypso_framework_sdl2_renderer_render_rect_buffer_range_d(const double* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_buffer_d(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_range_i(const int* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_filled_buffer_i(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_range_f(const float* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_filled_buffer_f(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}

void calypso_framework_sdl2_renderer_render_rect_filled_buffer_range_d(const double* rect_buffer, int element_start_index, const int element_end_index)
{
    calypso_framework_sdl2_renderer_render_rect_filled_buffer_d(rect_buffer + (element_start_index * 4), element_end_index); // 4 Values in rect
}