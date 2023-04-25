/// <summary>
/// Pixel Renderer module that uses Glad (OpenGL Driver) as a base
/// </summary>

#pragma once

#include <dependencies/glad/glad.h>
#include <stdint.h>     // uint8_t
#include <stdbool.h>    // bool

/*------------------------------------------------------------------------------
Calypso Framework Renderer Pixel OpenGL : Data
------------------------------------------------------------------------------*/

// Logging Callback
typedef void (*calypso_framework_renderer_pixel_opengl_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_renderer_pixel_opengl_log_callback_t _calypso_framework_renderer_pixel_opengl_log_callback;

// State
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_NULL                         0b00000000
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT                         0b00000001
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_ERROR                        0b00000010
unsigned int _calypso_framework_renderer_pixel_opengl_state =                      CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_NULL;

// Open GL Version
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE                    3

// OpenGL Object
unsigned int _calypso_framework_renderer_pixel_opengl_vao;
unsigned int _calypso_framework_renderer_pixel_opengl_vbo;
unsigned int _calypso_framework_renderer_pixel_opengl_ibo;

// Shader Program
unsigned int _calypso_framework_renderer_pixel_opengl_shader_program;

// Texture
unsigned int _calypso_framework_renderer_pixel_opengl_texture;

// Pixel Buffer
#define CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_PIXEL_BUFFER_CHANNEL_COUNT        3
typedef struct calypso_framework_renderer_pixel_opengl_pixel_buffer_t
{
    GLubyte* buffer;
    unsigned int buffer_width;
    unsigned int buffer_height;
    unsigned int buffer_length;
} calypso_framework_renderer_pixel_opengl_pixel_buffer_t;

/*------------------------------------------------------------------------------
Calypso Framework Renderer PIXEL OpenGL : Log Callback
------------------------------------------------------------------------------*/

void calypso_framework_renderer_pixel_opengl_set_log_callback(calypso_framework_renderer_pixel_opengl_log_callback_t log_callback)
{
    _calypso_framework_renderer_pixel_opengl_log_callback = log_callback;
}

void calypso_framework_renderer_pixel_opengl_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_renderer_pixel_opengl_log_callback == NULL)
        return;

    _calypso_framework_renderer_pixel_opengl_log_callback(log_msg,log_type);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer PIXEL OpenGL : Init / Deinit
------------------------------------------------------------------------------*/
  
bool calypso_framework_renderer_pixel_opengl_is_init()
{
    return _calypso_framework_renderer_pixel_opengl_state == CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT;
}

void calypso_framework_renderer_pixel_opengl_init(void* opengl_proc_address, unsigned int width, unsigned int height)
{
    // Set State
    _calypso_framework_renderer_pixel_opengl_state = CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT;

    // OpenGL (Glad)
    gladLoadGLLoader(opengl_proc_address);

    // Generate shaders
    {
        // Vertex Shader Source
        const char* vertex_shader_source =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "layout(location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "    TexCoord = aTexCoord;\n"
        "}\n";

        // Fragment Shader Source
        const char* fragment_shader_source =
        "#version 330 core \n"
        "out vec4 FragColor; \n"
        "in vec3 ourColor; \n"
        "in vec2 TexCoord; \n"
        "uniform sampler2D ourTexture; \n"
        "void main() \n"
        "{\n"
        "  FragColor = texture(ourTexture, TexCoord);\n"
        "}\n";

        // Define Vertex Shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Define Fragment Shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

         // Compile Vertex Shader
        glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
        glCompileShader(vertexShader);

         // Compile Fragment Shader
        glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragmentShader);

        // Create Shader Program | Link shaders
        _calypso_framework_renderer_pixel_opengl_shader_program = glCreateProgram();
        glAttachShader(_calypso_framework_renderer_pixel_opengl_shader_program, vertexShader);
        glAttachShader(_calypso_framework_renderer_pixel_opengl_shader_program, fragmentShader);
        glLinkProgram(_calypso_framework_renderer_pixel_opengl_shader_program);

        // Delete Shaders (No Longer Needed When Program Is Created)
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // OpenGl Object
    {
        // Vertex buffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void *)0);
        glEnableVertexAttribArray(0);

        // Assign verticies
        float vertices[] = 
        {
            // positions // colors // texture coords
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
        };

        unsigned int indices[] = 
        {
            0, 1, 3, // first Triangle
            1, 2, 3, // second Triangle
        };

        // Generate objects
        glGenVertexArrays(1, &_calypso_framework_renderer_pixel_opengl_vao);
        glGenBuffers(1, &_calypso_framework_renderer_pixel_opengl_vbo);
        glGenBuffers(1, &_calypso_framework_renderer_pixel_opengl_ibo);
        glBindVertexArray(_calypso_framework_renderer_pixel_opengl_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _calypso_framework_renderer_pixel_opengl_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _calypso_framework_renderer_pixel_opengl_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // Texture
    {
        // Generate | Bind Texture
        glGenTextures(1, &_calypso_framework_renderer_pixel_opengl_texture);
        glBindTexture(GL_TEXTURE_2D, _calypso_framework_renderer_pixel_opengl_texture);

        // Texture Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void calypso_framework_renderer_pixel_opengl_deinit(void)
{
    // De-allocate OpenGl Object
    glDeleteVertexArrays(1, &_calypso_framework_renderer_pixel_opengl_vao);
    glDeleteBuffers(1, &_calypso_framework_renderer_pixel_opengl_vbo);
    glDeleteBuffers(1, &_calypso_framework_renderer_pixel_opengl_ibo);

    // De-allocate OpenGl Shader Programs
    glDeleteProgram(_calypso_framework_renderer_pixel_opengl_shader_program);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer Pixel OpenGL : Renderer (Pixel Buffer)
------------------------------------------------------------------------------*/

void calypso_framework_renderer_pixel_opengl_create_pixel_buffer(calypso_framework_renderer_pixel_opengl_pixel_buffer_t* pixel_buffer, const int width, const int height)
{
    // Create Pixel Buffer
    pixel_buffer->buffer = (GLubyte*) malloc(width * height * 3); // 3 Is number of channels (rgb)
    pixel_buffer->buffer_width = width;
    pixel_buffer->buffer_height = height;
    pixel_buffer->buffer_length = width * height * CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_PIXEL_BUFFER_CHANNEL_COUNT;

    // Set Default Values (White)
    for (int i = 0; i < pixel_buffer->buffer_length; i+= CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_PIXEL_BUFFER_CHANNEL_COUNT)
    {
        pixel_buffer->buffer[i] = 255;
        pixel_buffer->buffer[i + 1] = 255;
        pixel_buffer->buffer[i + 2] = 255;
    }
}

/**
* \brief Set Pixel
* \return void
*/
void calypso_framework_renderer_pixel_opengl_renderer_set_pixel_buffer_pixel(calypso_framework_renderer_pixel_opengl_pixel_buffer_t* pixel_buffer, const int x, const int y, uint8_t r,uint8_t g,uint8_t b)
{
    // Make sure we are in range
    if (x < 0 || x > pixel_buffer->buffer_width || y < 0 || y > pixel_buffer->buffer_height)
        return;

    // Get Index
    uint32_t index = ((y * pixel_buffer->buffer_width) + x) * CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_PIXEL_BUFFER_CHANNEL_COUNT;

    // Set Pixel Data
    pixel_buffer->buffer[index] = r;
    pixel_buffer->buffer[index + 1] = g;
    pixel_buffer->buffer[index + 2] = b;
}

/**
* \brief Set pixel fill screen
* \return void
*/
void calypso_framework_renderer_pixel_opengl_renderer_set_pixel_fill_screen(calypso_framework_renderer_pixel_opengl_pixel_buffer_t* pixel_buffer, uint8_t r,uint8_t g,uint8_t b)
{
    // Set Pixel Data
    for (int i = 0; i < pixel_buffer->buffer_length; i+= 3)
    {
        pixel_buffer->buffer[i] = r;
        pixel_buffer->buffer[i + 1] = g;
        pixel_buffer->buffer[i + 2] = b;
    }
}

/**
* \brief renderer render
* \return void
*/
void calypso_framework_renderer_pixel_opengl_render_pixel_buffer(calypso_framework_renderer_pixel_opengl_pixel_buffer_t* pixel_buffer)
{
    // Check If We Are Init
    if (_calypso_framework_renderer_pixel_opengl_state != CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT)
    {
        _calypso_framework_renderer_pixel_opengl_log_callback("Renderer Pixel(OpengGl) Not init\n",3);
        return;
    }

    // Use Our Shader Program
    glUseProgram(_calypso_framework_renderer_pixel_opengl_shader_program);

    // Create Texture From Pixels | Bind It
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixel_buffer->buffer_width, pixel_buffer->buffer_height, 0, GL_RGB, GL_UNSIGNED_BYTE,pixel_buffer->buffer);
    glBindTexture(GL_TEXTURE_2D,_calypso_framework_renderer_pixel_opengl_texture);
        
    // Render    
    glBindVertexArray(_calypso_framework_renderer_pixel_opengl_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer Pixel OpenGL : Renderer (Clear)
------------------------------------------------------------------------------*/

/**
* \brief Clear renderer
* \return void
*/
void calypso_framework_renderer_pixel_opengl_renderer_clear()
{
    // Check If We Are Init
    if (_calypso_framework_renderer_pixel_opengl_state != CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT)
    {
        _calypso_framework_renderer_pixel_opengl_log_callback("Renderer Pixel(OpengGl) Not init\n",3);
        return;
    }

    // Clear
    glClearColor(255,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer PIXEL OpenGL : Renderer (Resize)
------------------------------------------------------------------------------*/

/**
* \brief Resize renderer
* \return void
*/
void calypso_framework_renderer_pixel_opengl_renderer_resize(const int width, const int height)
{
     // Check If We Are Init
    if (_calypso_framework_renderer_pixel_opengl_state != CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_STATE_INIT)
    {
        _calypso_framework_renderer_pixel_opengl_log_callback("Renderer Pixel(OpengGl) Not init\n",3);
        return;
    }

    // Set Viewport
    glViewport(0,0,width,height);
}


/*
------------------------------------------------------------------------------
Calypso Framework Renderer Pixel OpenGL : license
------------------------------------------------------------------------------

MIT License
Copyright (c) 2023 Nicholas Gennady Korta
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/