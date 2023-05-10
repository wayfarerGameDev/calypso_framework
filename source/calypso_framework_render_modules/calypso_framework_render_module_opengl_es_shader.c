#pragma once

// Dependencies
#include <dependencies/glad/glad.h>

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Compile Shader | Create Shader
------------------------------------------------------------------------------*/

unsigned int calypso_framework_render_module_opengl_es_shader_compile_shader(const char* shader_source, unsigned int shader_type)
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
        {
            #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
            CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad->compile_shader","Vertex Shader(ERROR)",3);
            #endif
        }
        if (shader_type == GL_FRAGMENT_SHADER)
        {
            #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
            CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad->compile_shader","Fragment Shader(ERROR)",3);
            #endif
        }
    }

    // Return Shader ID
    return shader_id;
}

unsigned int calypso_framework_render_module_opengl_es_shader_create_shader(const char* vertex_shader_source, const char* fragment_shader_source)
{
    // Compile Shaders (Intermidete Data For Shaders)
    unsigned int vertex_shader = calypso_framework_render_module_opengl_es_shader_compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = calypso_framework_render_module_opengl_es_shader_compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

    // Create Shader Program From Compiled Shader
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);
    glValidateProgram(shader_program);
  
    // Destroy Shaders (No Longer Needed As Shader Program Is Created)
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);  

    // Detach Shader (We Comment Out So We Can Have Debbuging Info, Only Small Overhead To Keep Around)
    #ifndef CALYPSO_FRAMEWORK_OPENGL_ES_SHADER_DEBUGGING_ENABLED
    glDetachShader(shader_program,vertex_shader);
    glDetachShader(shader_program,fragment_shader);
    #endif

    // Return Shader Program
    return shader_program;
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Current Shader Program
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program(const unsigned shader_program)
{
    glUseProgram(shader_program);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Current Shader Program Paramters
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_i(const char*  parameter_name, const int value)
{
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater int",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;
    }

    // Set Uniform
    glUniform1i(location,value);
}

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_f(const char* parameter_name, const float v0)
{ 
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater float",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;
    }

    // Set Uniform
    glUniform1f(location,v0);
}

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec2_f(const char* parameter_name, const float v0, const float v1)
{
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater vec2_f",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;   
    }

    // Set Uniform
    glUniform2f(location,v0,v1);
}

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec3_f(const char* parameter_name, const float v0, const float v1, const float v2)
{
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater vec3_f",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;
    }

    // Set Uniform
    glUniform3f(location,v0,v1,v2);
}

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f(const char* parameter_name, const float v0, const float v1, const float v2, const float v3)
{
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater vec4_f",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;
    }

    // Set Uniform
    glUniform4f(location,v0,v1,v2,v3);
}

void calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f(const char* parameter_name, const float* matrix4f, const int transpose_matrix)
{
    // Get Current Shader Program
    GLuint current_shader_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current_shader_program);

    // Get Uniform Location
    int location = glGetUniformLocation(current_shader_program,parameter_name);
    if (location == -1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_quad","Can't set shader program paramater mat4_f",2);
        CALYPSO_FRAMEWORK_LOG_MESSAGE("\t",parameter_name,2);
        #endif
        return;
    }

    // Set Uniform
    glUniformMatrix4fv(location,1,transpose_matrix,&matrix4f[0]);
}

/*------------------------------------------------------------------------------
license
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