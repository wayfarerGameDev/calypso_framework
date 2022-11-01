/// <summary>
/// Renderer module that uses Glad as a base
/// </summary>

#pragma once

#include "dependencies/glad/glad.h"

// Logging Callback
typedef void (*calypso_framework_renderer_2d_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_renderer_2d_log_callback_t _calypso_framework_renderer_2d_log_callback;

// State
#define CALYPSO_FRAMEWORK_RENDERER_2D_STATE_NULL                    0
#define CALYPSO_FRAMEWORK_RENDERER_2D_STATE_INIT                    1
#define CALYPSO_FRAMEWORK_RENDERER_2D_STATE_ERROR                   4
unsigned int _calypso_framework_renderer_2d_state                   = CALYPSO_FRAMEWORK_RENDERER_2D_STATE_NULL;

#define CALYPSO_FRAMEWORK_RENDERER_GL_MAJOR_VERSION                 3
#define CALYPSO_FRAMEWORK_RENDERER_GL_MINOR_VERSION                 3
#define CALYPSO_FRAMEWORK_RENDERER_GL_CONTEXT_PROFILE               3

// Clear Color
float _calypso_framework_renderer_2d_clear_color[4]                  = {0,0,0,1};
float _calypso_framework_renderer_2d_render_color[4]                 = {1,1,1,1};

// Primitive assembly draw modes
#define CALYPSO_FRAMEWORK_RENDERER_2D_PRIMITIVE_DRAW_MODE_NONE        0x0000 // GL_NONE
#define CALYPSO_FRAMEWORK_RENDERER_2D_PRIMITIVE_DRAW_MODE_LINES       0x0001 // GL_LINES
#define CALYPSO_FRAMEWORK_RENDERER_2D_PRIMITIVE_DRAW_MODE_TRIANGLES   0x0004 // GL_TRIANGLES
#define CALYPSO_FRAMEWORK_RENDERER_2D_PRIMITIVE_DRAW_MODE_QUADS       0x0007 // GL_QUADS
int _calypso_framework_renderer_draw_mode                              = CALYPSO_FRAMEWORK_RENDERER_2D_PRIMITIVE_DRAW_MODE_NONE;

/**
* \brief Set renderer's log callback
* \return void
*/
void calypso_framework_renderer_2d_set_log_callback(calypso_framework_renderer_2d_log_callback_t log_callback)
{
    _calypso_framework_renderer_2d_log_callback = log_callback;
}

/**
* \brief Do renderer's log callback
* \return void
*/
void calypso_framework_renderer_2d_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_renderer_2d_log_callback == NULL)
        return;

    _calypso_framework_renderer_2d_log_callback(log_msg,log_type);
}

/**
* \brief Initializes renderer
* \return void
*/
void calypso_framework_renderer_2d_init(void* open_gl_proc_address)
{
    gladLoadGLLoader(open_gl_proc_address);
    _calypso_framework_renderer_2d_state = CALYPSO_FRAMEWORK_RENDERER_2D_STATE_INIT;
}

/**
* \brief Deinitializes renderer
* \return void
*/
void calypso_framework_renderer_2d_deinit(void)
{
}

/**
* \brief Set renderer's clear color
* \param x int
* \param y int 
* \param width int
* \param height int
* \return void
*/
void calypso_framework_renderer_2d_set_viewport(const int x, const int y, const int width, const int height)
{
    glViewport(x,y,width,height);
}

/**
* \brief Set renderer's clear color
* \param r float
* \param g float
* \param b float
* \param a float
* \return void
*/
void calypso_framework_renderer_2d_set_clear_color(const float r, const float g, const float b, const float a)
{
    _calypso_framework_renderer_2d_clear_color[0] = r;
    _calypso_framework_renderer_2d_clear_color[1] = g;
    _calypso_framework_renderer_2d_clear_color[2] = b;
    _calypso_framework_renderer_2d_clear_color[3] = a;
}

/**
* \brief Set renderer's clear color
* \param color_array Uint8[4]
* \return void
*/
void calypso_framework_renderer_2d_set_clear_color_by_byte_color_array(const Uint8 color_array[4])
{
    _calypso_framework_renderer_2d_clear_color[0] = color_array[0] / 255.0f;
    _calypso_framework_renderer_2d_clear_color[1] = color_array[1] / 255.0f;
    _calypso_framework_renderer_2d_clear_color[2] = color_array[2] / 255.0f;
    _calypso_framework_renderer_2d_clear_color[3] = color_array[3] / 255.0f;
}

/**
* \brief Clear renderer
* \return void
*/
void calypso_framework_renderer_2d_clear()
{
    // Only Init Once
    if (_calypso_framework_renderer_2d_state != CALYPSO_FRAMEWORK_RENDERER_2D_STATE_INIT)
    {
        _calypso_framework_renderer_2d_log_callback("Renderer GL 2D: Not init\n",3);
        return;
    }

    glClearColor(_calypso_framework_renderer_2d_clear_color[0],_calypso_framework_renderer_2d_clear_color[1],_calypso_framework_renderer_2d_clear_color[2],_calypso_framework_renderer_2d_clear_color[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/**
* \brief Begin drawing a primitive
* \return void
*/
void calypso_framework_renderer_2d_draw_primitive_begin(int draw_mode)
{
     // Only Init Once
    if (_calypso_framework_renderer_2d_state != CALYPSO_FRAMEWORK_RENDERER_2D_STATE_INIT)
    {
        _calypso_framework_renderer_2d_log_callback("Renderer GL 2D: Not init\n",3);
        return;
    }

    // Set Current Draw Mode
    _calypso_framework_renderer_draw_mode = draw_mode;
}