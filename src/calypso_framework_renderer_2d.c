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

// Primitive assembly draw modes
int _calypso_framework_renderer_draw_mode                           = 0;

unsigned int vao_quad;
unsigned int vbo_quad;
unsigned int ebo_quad;

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
    _calypso_framework_renderer_2d_state = CALYPSO_FRAMEWORK_RENDERER_2D_STATE_INIT;

    // OpenGL (Glad | Clear Color)
    {
        gladLoadGLLoader(open_gl_proc_address);

        // Start Clear Color (Cornflower blue)
        glClearColor(0.392f,0.584f,0.929f,1);
    }

    // OpenGL (Quad)
    {
       float vertices[] = {
		 0.5,  0.5, 0, 0, 0,
		 0.5, -0.5, 0, 0, 1,
		-0.5, -0.5, 0, 1, 1,
		-0.5,  0.5, 0, 1, 0
	    };

	    unsigned int indices[] = {
	    	0, 1, 3,
	    	1, 2, 3
	    };

	    glGenVertexArrays(1, &vao_quad);
	    glGenBuffers(1, &vbo_quad);
	    glGenBuffers(1, &ebo_quad);

	    glBindVertexArray(vao_quad);

	    glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	    // xyz
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
	    glEnableVertexAttribArray(0);

	    // uv
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	    glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }
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
    glClearColor(r,g,b,a);
}

/**
* \brief Set renderer's clear color by byte color array
* \param color_array Uint8[4]
* \return void
*/
void calypso_framework_renderer_2d_set_clear_color_by_byte_color_array(const Uint8 color_array[4])
{
    glClearColor(color_array[0] / 255.0f,color_array[1] / 255.0f,color_array[2] / 255.0f,color_array[3] / 255.0f);
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
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/**
* \brief Begin drawing a primitive
* \return void
*/
void render_quad(float posX, float posY, float sizeX, float sizeY) 
{
	glBindVertexArray(vao_quad);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,NULL);
    glBindVertexArray(0);
}