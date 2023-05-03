/// <summary>
/// Minimal imgui that uses callbacks to render
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t

// Logging Callback
typedef void (*calypso_framework_imgui_minimal_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_imgui_minimal_log_callback_t _calypso_framework_imgui_minimal_log_callback;

// Callback
typedef void (*calypso_framework_imgui_minimal_int_callback_t)(int hex_value);
typedef void (*calypso_framework_imgui_minimal_set_font_callback_t)(void* void_ptr);
typedef void (*calypso_framework_imgui_minimal_texture_callback_t)(void* texture_ptr, float x, float y);
typedef void (*calypso_framework_imgui_minimal_texture_sized_callback_t)(void* texture_ptr, float x, float y, float w, float h);
typedef void (*calypso_framework_imgui_minimal_rect_callback_t)(float x, float y, float w, float h);
typedef void (*calypso_framework_imgui_minimal_text_callback_t)(const char* string, float x, float y);
typedef int (*calypso_framework_imgui_minimal_text_width_height_callback_t)(const char* string);
typedef int (*calypso_framework_imgui_minimal_listner_callback_t)();
calypso_framework_imgui_minimal_int_callback_t _calypso_framework_imgui_minimal_set_color_callback;
calypso_framework_imgui_minimal_set_font_callback_t _calypso_framework_imgui_minimal_set_font_callback;
calypso_framework_imgui_minimal_texture_callback_t _calypso_framework_imgui_minimal_texture_callback;
calypso_framework_imgui_minimal_texture_sized_callback_t _calypso_framework_imgui_minimal_texture_sized_callback;
calypso_framework_imgui_minimal_rect_callback_t _calypso_framework_imgui_minimal_rect_callback;
calypso_framework_imgui_minimal_text_callback_t _calypso_framework_imgui_minimal_text_callback;
calypso_framework_imgui_minimal_text_width_height_callback_t _calypso_framework_imgui_minimal_text_width_callback;
calypso_framework_imgui_minimal_text_width_height_callback_t _calypso_framework_imgui_minimal_text_height_callback;
calypso_framework_imgui_minimal_listner_callback_t _calypso_framework_imgui_minimal_mouse_left_pressed_listner_callback;   

// Bindings
int* _calypso_framework_imgui_minimal_mouse_position_ptr                                  = NULL;

// Style
int _calypso_framework_imgui_minimal_style_normal_color_pair[2]                           = {0x212428,0xa2a7ae};
int _calypso_framework_imgui_minimal_style_normal_secondary_color_pair[2]                 = {0x2c2f34,0xa2a7ae};
int _calypso_framework_imgui_minimal_style_hover_color_pair[2]                            = {0x2c2f34,0x909090};
int _calypso_framework_imgui_minimal_style_hover_secondary_color_pair[2]                  = {0x2c2f34,0x909090};
int _calypso_framework_imgui_minimal_style_active_color_pair[2]                           = {0x000000,0xffffff};
int _calypso_framework_imgui_minimal_style_active_secondary_color_pair[2]                 = {0x000000,0xffffff};
int _calypso_framework_imgui_minimal_style_focused_color_pair[2]                          = {0x500000,0xffffff};
int _calypso_framework_imgui_minimal_style_focused_secondary_color_pair[2]                = {0x500000,0xffffff};

/*------------------------------------------------------------------------------
Calypso Framework Imgui(Minimal) : Log
------------------------------------------------------------------------------*/

void calypso_framework_imgui_minimal_set_log_callback(calypso_framework_imgui_minimal_log_callback_t log_callback)
{
    _calypso_framework_imgui_minimal_log_callback = log_callback;
}

void calypso_framework_imgui_minimal_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_imgui_minimal_log_callback == NULL)
        return;

    _calypso_framework_imgui_minimal_log_callback(log_msg,log_type);
}

/*------------------------------------------------------------------------------
Calypso Framework Imgui(Minimal) : Callbacks
------------------------------------------------------------------------------*/

void calypso_framework_imgui_minimal_set_callbacks(
calypso_framework_imgui_minimal_int_callback_t set_color_callback, 
calypso_framework_imgui_minimal_set_font_callback_t set_font_callback,
calypso_framework_imgui_minimal_texture_callback_t texture_callback,
calypso_framework_imgui_minimal_texture_sized_callback_t texture_sized_callback,
calypso_framework_imgui_minimal_rect_callback_t rect_callback, 
calypso_framework_imgui_minimal_text_callback_t text_callback,
calypso_framework_imgui_minimal_text_width_height_callback_t text_width_callback,
calypso_framework_imgui_minimal_text_width_height_callback_t text_height_callback,
calypso_framework_imgui_minimal_listner_callback_t mouse_left_pressed_listner_callback)
{
    _calypso_framework_imgui_minimal_set_color_callback = set_color_callback;
    _calypso_framework_imgui_minimal_set_font_callback = set_font_callback;
    _calypso_framework_imgui_minimal_texture_callback = texture_callback;
    _calypso_framework_imgui_minimal_texture_sized_callback = texture_sized_callback;
    _calypso_framework_imgui_minimal_rect_callback = rect_callback;
    _calypso_framework_imgui_minimal_text_callback = text_callback;
    _calypso_framework_imgui_minimal_text_width_callback = text_width_callback;
    _calypso_framework_imgui_minimal_text_height_callback = text_height_callback;
    _calypso_framework_imgui_minimal_mouse_left_pressed_listner_callback = mouse_left_pressed_listner_callback;
}

/*------------------------------------------------------------------------------
Calypso Framework Imgui(Minimal) : Bindings
------------------------------------------------------------------------------*/

void calypso_framework_imgui_minimal_set_bindings(int* mouse_position_ptr)
{
    _calypso_framework_imgui_minimal_mouse_position_ptr = mouse_position_ptr;
}

/*------------------------------------------------------------------------------
Calypso Framework Imgui(Minimal) : UI
------------------------------------------------------------------------------*/

void calypso_framework_imgui_minimal_set_font(void* font_ptr)
{
    _calypso_framework_imgui_minimal_set_font_callback(font_ptr);
}

void calypso_framework_imgui_minimal_texture(void* texture_ptr, float x, float y)
{
    _calypso_framework_imgui_minimal_texture_callback(texture_ptr,x,y);
}

void calypso_framework_imgui_minimal_texture_sized(void* texture_ptr, float x, float y, float w, float h)
{
    _calypso_framework_imgui_minimal_texture_sized_callback(texture_ptr,x,y,w,h);
}

void calypso_framework_imgui_minimal_rect(float x, float y, float w, float h, int use_secondary_color)
{
     int* style = use_secondary_color == 0 ? _calypso_framework_imgui_minimal_style_normal_color_pair : _calypso_framework_imgui_minimal_style_normal_secondary_color_pair;
    _calypso_framework_imgui_minimal_set_color_callback(style[0]);
    _calypso_framework_imgui_minimal_rect_callback(x,y,w,h);
}

void calypso_framework_imgui_minimal_text(const char* string, float x, float y, int use_secondary_color)
{
    int* style = use_secondary_color == 0 ? _calypso_framework_imgui_minimal_style_normal_color_pair : _calypso_framework_imgui_minimal_style_normal_secondary_color_pair;
    _calypso_framework_imgui_minimal_set_color_callback(style[1]);
    _calypso_framework_imgui_minimal_text_callback(string,x,y);
}

void calypso_framework_imgui_minimal_text_rect_centred(const char* string, float x, float y, float w, float h, int use_secondary_color)
{
    // Get X,Y,W, From Text (Centered)
    float text_w = _calypso_framework_imgui_minimal_text_width_callback(string);
    float text_h = _calypso_framework_imgui_minimal_text_height_callback(string);
    float text_x = ( x + w / 2) - text_w / 2;
    float text_y = (y + h / 2) - text_h / 2;

    calypso_framework_imgui_minimal_text(string, text_x, text_y, use_secondary_color);
}


int calypso_framework_imgui_minimal_button_text(const char* string, float x, float y, float w, float h, int use_secondary_color)
{    
    // Get Mouse Position
    int mouse_position_x = -999;
    int mouse_position_y = -999;
    if (_calypso_framework_imgui_minimal_mouse_position_ptr != NULL)
    {
        mouse_position_x = _calypso_framework_imgui_minimal_mouse_position_ptr[0];
        mouse_position_y = _calypso_framework_imgui_minimal_mouse_position_ptr[1];
    }

    // Get X,Y,W, From Text (Centered)
    float text_w = _calypso_framework_imgui_minimal_text_width_callback(string);
    float text_h = _calypso_framework_imgui_minimal_text_height_callback(string);
    float text_x = ( x + w / 2) - text_w / 2;
    float text_y = (y + h / 2) - text_h / 2;

    // Get Is Mouse Over
    int is_mouse_over = 0;
    if (mouse_position_x >= x && mouse_position_x < x + w && mouse_position_y >= y && mouse_position_y < y + h)
        is_mouse_over = 1;

    // Get Mouse Pressed
    int is_mouse_pressed = _calypso_framework_imgui_minimal_mouse_left_pressed_listner_callback();
    if (!is_mouse_over)
        is_mouse_pressed = 0;


    // Get Style
    int* style = use_secondary_color == 0 ? _calypso_framework_imgui_minimal_style_normal_color_pair : _calypso_framework_imgui_minimal_style_normal_secondary_color_pair;
    if (is_mouse_over == 1)
        style = use_secondary_color == 0 ? _calypso_framework_imgui_minimal_style_hover_color_pair : _calypso_framework_imgui_minimal_style_hover_secondary_color_pair;
    
    // Draw
    _calypso_framework_imgui_minimal_set_color_callback(style[0]);
    _calypso_framework_imgui_minimal_rect_callback(x,y,w,h);
    _calypso_framework_imgui_minimal_set_color_callback(style[1]);
    _calypso_framework_imgui_minimal_text_callback(string,text_x,text_y);

    return is_mouse_pressed;
}

int calypso_framework_imgui_minimal_window_titlebar(void* icon_ptr, char* title_string, int titlebar_w, int titlebar_h, int icon_size, int button_w, int button_h, int use_secondary_color)
{
    // Titlebar
    calypso_framework_imgui_minimal_rect(0,0,titlebar_w,titlebar_h,use_secondary_color);

    // Icon
    if (icon_ptr != NULL)
        calypso_framework_imgui_minimal_texture_sized(icon_ptr,10,5, icon_size,icon_size);

    // Title
    calypso_framework_imgui_minimal_text_rect_centred(title_string,0,0,titlebar_w,titlebar_h,0);

    // Buttons
    int s = 0;
    if (calypso_framework_imgui_minimal_button_text("X",titlebar_w - button_w,0,button_w,button_h,use_secondary_color))
        s = 1;
    if (calypso_framework_imgui_minimal_button_text("[]",titlebar_w - button_w * 2,0,button_w,button_h,use_secondary_color))
        s = 2;
    if (calypso_framework_imgui_minimal_button_text("--",titlebar_w - button_w * 3,0,button_w,button_h,use_secondary_color))
        s = 3;

    return s;
}