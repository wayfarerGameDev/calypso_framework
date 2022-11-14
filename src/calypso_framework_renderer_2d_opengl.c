/// <summary>
/// Renderer module that uses Glad as a base
/// </summary>

#pragma once

#include "dependencies/glad/glad.h"

// Logging Callback
typedef void (*calypso_framework_renderer_2d_opengl_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_renderer_2d_opengl_log_callback_t _calypso_framework_renderer_2d_opengl_log_callback;

// State
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_NULL             0
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT             1
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_ERROR            4
unsigned int _calypso_framework_renderer_2d_opengl_state            = CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_NULL;

// OPen GL Version
#define CALYPSO_FRAMEWORK_RENDERER_OPENGL_MAJOR_VERSION             3
#define CALYPSO_FRAMEWORK_RENDERER_OPENGL_MINOR_VERSION             3
#define CALYPSO_FRAMEWORK_RENDERER_OPENGL_CONTEXT_PROFILE           3

// Open GL Mesh Render Data
unsigned int _calypso_framework_renderer_2d_opengl_vbo_quad;        // Quad
unsigned int _calypso_framework_renderer_2d_opengl_vao_quad;
unsigned int _calypso_framework_renderer_2d_opengl_ibo_quad;

// Current Shader Program
unsigned int calypso_framework_renderer_2d_opengl_current_program;

/**
* \brief Set renderer's log callback
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_log_callback(calypso_framework_renderer_2d_opengl_log_callback_t log_callback)
{
    _calypso_framework_renderer_2d_opengl_log_callback = log_callback;
}

/**
* \brief Do renderer's log callback
* \return void
*/
void calypso_framework_renderer_2d_opengl_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_renderer_2d_opengl_log_callback == NULL)
        return;

    _calypso_framework_renderer_2d_opengl_log_callback(log_msg,log_type);
}

/**
* \brief Compiles shader
* \return unsigned int
*/
unsigned int calypso_framework_renderer_2d_opengl_compile_shader(const char* shader_source, unsigned int shader_type)
{
    // Create And Compile Shader
    unsigned int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id,1,&shader_source,NULL);
    glCompileShader(shader_id);

    // Error Logging
    int shader_compile_result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compile_result);   
    if (shader_compile_result == 0)
    {
        // Get Log Length
        int log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH,&log_length);

        // Get Log Message
        char* log_message = (char*)alloca(log_length * sizeof(char));    
        glGetShaderInfoLog(shader_id,GL_INFO_LOG_LENGTH,&log_length,log_message);

        // log
        if (shader_type == GL_VERTEX_SHADER)
            calypso_framework_renderer_2d_opengl_do_log_callback("Render: Vertex Shader (ERROR)\n",3);
        if (shader_type == GL_FRAGMENT_SHADER)
            calypso_framework_renderer_2d_opengl_do_log_callback("Render: Fragment Shader (ERROR)\n",3);
        calypso_framework_renderer_2d_opengl_do_log_callback(log_message,3);
        calypso_framework_renderer_2d_opengl_do_log_callback("\n",0);
    }

    // Return Shader ID
    return shader_id;
}

/**
* \brief Creates shader program
* \return unsigned int
*/
unsigned int calypso_framework_renderer_2d_opengl_create_shader_program_from_source(const char* vertex_shader_source, const char* fragment_shader_source)
{
    // Compile Shaders (Intermidete Data For Shaders)
    unsigned int vertex_shader = calypso_framework_renderer_2d_opengl_compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = calypso_framework_renderer_2d_opengl_compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

    // Create Shader Program From Compiled Shader
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);
    glValidateProgram(shader_program);

    // Destroy Shaders (No Longer Needed As Shader Program Is Created)
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);    

    // Detach Shader (We Comment Out So We Can Have Debbuging Info, Only SMall Overhead To Keep Around)
    //glDetachShader(vertex_shader);
    //glDetachShader(fragment_shader);

    // Return Shader Program
    return shader_program;
}

/**
* \brief Creates shader program
* \return unsigned int
*/
unsigned int calypso_framework_renderer_2d_opengl_create_default_shader_program()
{
    // Vertex Shader Source
    const char* vertex_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "uniform mat4 mvp_in;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = mvp_in * position;\n"
    "}\n";

    // Fragment Shader Source
    const char* fragment_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color_out;\n"
    "\n"
    "uniform vec4 color_in;"
    "\n"
    "void main()\n"
    "{\n"
    "   color_out = color_in;\n"
    "}\n"; 

    // Create Shader
    return calypso_framework_renderer_2d_opengl_create_shader_program_from_source(vertex_shader_source,fragment_shader_source);
}

/**
* \brief Set current shader program
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_render_shader_program(const unsigned shader_program)
{
    glUseProgram(shader_program);
    calypso_framework_renderer_2d_opengl_current_program = shader_program;
}

/**
* \brief Calculate Ortho Matrix4f
* \return void
*/


/**
* \brief Set current shader float parameter
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_float(char* paramter_name, const float v0)
{
    int location = glGetUniformLocation(calypso_framework_renderer_2d_opengl_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec3(",2);
        calypso_framework_renderer_2d_opengl_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_do_log_callback(")\n",2);
        return;
    }

    glUniform1f(location,v0);
}

/**
* \brief Set current shader vec2 parameter
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec2f(char* paramter_name, const float v0, const float v1)
{
    int location = glGetUniformLocation(calypso_framework_renderer_2d_opengl_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec3(",2);
        calypso_framework_renderer_2d_opengl_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_do_log_callback(")\n",2);
        return;
    }

    glUniform2f(location,v0,v1);
}

/**
* \brief Set current shader vec3 parameter
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec3f(char* paramter_name, const float v0, const float v1, const float v2)
{
    int location = glGetUniformLocation(calypso_framework_renderer_2d_opengl_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec3(",2);
        calypso_framework_renderer_2d_opengl_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_do_log_callback(")\n",2);
        return;
    }

    glUniform3f(location,v0,v1,v2);
}

/**
* \brief Set current shader vec4 parameter
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f(char* paramter_name, const float v0, const float v1, const float v2, const float v3)
{
    int location = glGetUniformLocation(calypso_framework_renderer_2d_opengl_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec4(",2);
        calypso_framework_renderer_2d_opengl_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_do_log_callback(")\n",2);
        return;
    }

    glUniform4f(location,v0,v1,v2,v3);
}

/**
* \brief Set current shader vec4 parameter
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f(char* paramter_name, float matrix4f[4][4])
{
    int location = glGetUniformLocation(calypso_framework_renderer_2d_opengl_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater mat4f(",2);
        calypso_framework_renderer_2d_opengl_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_do_log_callback(")\n",2);
        return;
    }

    glUniformMatrix4fv(location,1,GL_FALSE,&matrix4f[0][0]);
}

/**
* \brief Initializes renderer
* \return void
*/  
void calypso_framework_renderer_2d_opengl_init(void* opengl_proc_address)
{
    _calypso_framework_renderer_2d_opengl_state = CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT;

    // OpenGL (Glad | Clear Color)
    {  
        gladLoadGLLoader(opengl_proc_address);

        // Start Clear Color (Cornflower blue)
        glClearColor(0.392f,0.584f,0.929f,1);
    }

    // OpenGL (Quad)
    {
         // Vertices (XYZ UV)
        float vertices[] = {
             0.5,  0.5, 0, 0, 0,
             0.5, -0.5, 0, 0, 1,
            -0.5, -0.5, 0, 1, 1,
            -0.5,  0.5, 0, 1, 0
        };

        // Indicies
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        // VAO
        glGenVertexArrays(1, &_calypso_framework_renderer_2d_opengl_vao_quad);
        glBindVertexArray(_calypso_framework_renderer_2d_opengl_vao_quad);

        // VBO
        glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_vbo_quad);
        glBindBuffer(GL_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_vbo_quad);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float),vertices, GL_STATIC_DRAW);

        // IBO
        glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_ibo_quad);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_ibo_quad);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),indices, GL_STATIC_DRAW);

        // Vertex Attributes (XYZ)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Vertex Attributes (UV)
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }    
}

/**
* \brief Deinitializes renderer
* \return void
*/
void calypso_framework_renderer_2d_opengl_deinit(void)
{
}

/**
* \brief Set renderer's clear color
* \param r float
* \param g float
* \param b float
* \param a float
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_clear_color(const float r, const float g, const float b, const float a)
{
    glClearColor(r,g,b,a);
}

/**
* \brief Set renderer's clear color by byte color array
* \param color_array Uint8[4]
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_clear_color_by_byte_color_array(const Uint8 color_array[4])
{
    glClearColor(color_array[0] / 255.0f,color_array[1] / 255.0f,color_array[2] / 255.0f,color_array[3] / 255.0f);
}

/**
* \brief Clear renderer
* \return void
*/
void calypso_framework_renderer_2d_opengl_clear()
{
    // Check If We Are Init
    if (_calypso_framework_renderer_2d_opengl_state != CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT)
    {
        _calypso_framework_renderer_2d_opengl_log_callback("Renderer GL 2D: Not init\n",3);
        return;
    }
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/**
* \brief Render a Box
* \return void
*/
void calypso_framework_renderer_2d_opengl_render_box(float posX, float posY, float sizeX, float sizeY) 
{
    // Check If We Are Init
    if (_calypso_framework_renderer_2d_opengl_state != CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT)
    {
        _calypso_framework_renderer_2d_opengl_log_callback("Renderer GL 2D: Not init\n",3);
        return;
    }

    // OpenGL
    {
        glBindVertexArray(_calypso_framework_renderer_2d_opengl_vao_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}