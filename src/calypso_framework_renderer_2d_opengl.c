/// <summary>
/// 2D Renderer module that uses Glad as a base
/// </summary>

#pragma once

#include <dependencies/glad/glad.h>
#include <stdint.h>     // uint8_t
#include <stdbool.h>    // bool

// Logging Callback
typedef void (*calypso_framework_renderer_2d_opengl_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_renderer_2d_opengl_log_callback_t _calypso_framework_renderer_2d_opengl_log_callback;

struct calypso_framework_renderer_2d_opengl_quad_batch 
{
    float* vertices;
    int* indicies;
    int instance_count;
    int data_size;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
};

// State
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_NULL                    0b00000000
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT                    0b00000001
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_ERROR                   0b00000010
unsigned int _calypso_framework_renderer_2d_opengl_state =                 CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_NULL;

// OPen GL Version
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MAJOR_VERSION                 3
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MINOR_VERSION                 3
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_CONTEXT_PROFILE               3

// Open GL Mesh Render Data
unsigned int _calypso_framework_renderer_2d_opengl_vao_quad_immediate;    // Quad (Immediate)
unsigned int _calypso_framework_renderer_2d_opengl_vbo_quad_immediate;
unsigned int _calypso_framework_renderer_2d_opengl_ibo_quad_immediate;

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
void calypso_framework_renderer_2d_opengl_do_log_callback(const char* log_msg, const uint8_t log_type)
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
* \brief Creates shader program (immediate)
* \return unsigned int
*/
unsigned int calypso_framework_renderer_2d_opengl_create_default_immediate_shader_program()
{
    // Vertex Shader Source
    const char* vertex_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "uniform mat4 projection_view_in;\n"
    "uniform mat4 model_in;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection_view_in * model_in * position;\n"
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
* \brief Creates shader program (Batched)
* \return unsigned int
*/
unsigned int calypso_framework_renderer_2d_opengl_create_default_batched_shader_program()
{
    // Vertex Shader Source
    const char* vertex_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 a_position;\n"
    "layout(location = 1) in vec4 a_color;\n"
    "layout(location = 2) in vec2 a_tex_coord;\n"
    "layout(location = 3) in float a_tex_index;\n"
    "\n"
    "uniform mat4 projection_view_in;\n"
    "uniform mat4 model_in;\n"
    "\n"
    "out vec4 v_color;\n"
    "out vec2 v_tex_coord;\n"
    "out float v_tex_index;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   v_color = a_color;\n"
    "   v_tex_coord = a_tex_coord;\n"
    "   v_tex_index = a_tex_index;\n"
    "   gl_Position = projection_view_in * model_in * a_position;\n"
    "}\n";

    // Fragment Shader Source
    const char* fragment_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color_out;\n"
    "in vec4 v_color;"
    "in vec2 v_tex_coord;"
    "in float v_tex_index;"
    "\n"
    "void main()\n"
    "{\n"
    "   color_out = v_color;\n"
    "   //color_out = vec4(v_tex_coord,0,1);\n"
    "   //color_out = vec4(v_tex_index,v_tex_index,v_tex_index,1);\n"
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
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater float(",2);
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
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec2f(",2);
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
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec3f(",2);
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
        calypso_framework_renderer_2d_opengl_do_log_callback("Renderer: Can't set shader program paramater vec4f(",2);
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
bool calypso_framework_renderer_2d_opengl_is_init()
{
    return _calypso_framework_renderer_2d_opengl_state == CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_STATE_INIT;
}

void calypso_framework_renderer_2d_opengl_set_batch_instance_data(struct calypso_framework_renderer_2d_opengl_quad_batch* batch, const int instance, const float pos[2], const float color[4], int texture_index)
{
    if (instance < 0 || instance >= batch->instance_count)
        return;

    // Vertices
    {
        //    POS (XYZ)           COLOR (RGBA)                    Texture (UV)        Texture (Index/ID)
        //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
        //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
        //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
        //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,

        const int vertex_data_stride = 40 * instance;
        const float size = 1;
        float* vertices = batch->vertices;

        // Row One                                                  // Row Two
        vertices[vertex_data_stride + 0] = pos[0];                 vertices[vertex_data_stride + 10] = pos[0] + size;
        vertices[vertex_data_stride + 1] = pos[1];                 vertices[vertex_data_stride + 11] = pos[1];
        vertices[vertex_data_stride + 2] = 0;                      vertices[vertex_data_stride + 12] = 0;
        vertices[vertex_data_stride + 3] = color[0];               vertices[vertex_data_stride + 13] = color[0];
        vertices[vertex_data_stride + 4] = color[1];               vertices[vertex_data_stride + 14] = color[1];
        vertices[vertex_data_stride + 5] = color[2];               vertices[vertex_data_stride + 15] = color[2];
        vertices[vertex_data_stride + 6] = color[3];               vertices[vertex_data_stride + 16] = color[3];
        vertices[vertex_data_stride + 7] = 0;                      vertices[vertex_data_stride + 17] = 1;
        vertices[vertex_data_stride + 8] = 0;                      vertices[vertex_data_stride + 18] = 0;
        vertices[vertex_data_stride + 9] = texture_index;          vertices[vertex_data_stride + 19] = texture_index;

         // Row Three                                                // Row Four
        vertices[vertex_data_stride + 20] = pos[0] + size;          vertices[vertex_data_stride + 30] = pos[0];
        vertices[vertex_data_stride + 21] = pos[1] + size;          vertices[vertex_data_stride + 31] = pos[1] + size;
        vertices[vertex_data_stride + 22] = 0;                      vertices[vertex_data_stride + 32] = 0;
        vertices[vertex_data_stride + 23] = color[0];               vertices[vertex_data_stride + 33] = color[0];
        vertices[vertex_data_stride + 24] = color[1];               vertices[vertex_data_stride + 34] = color[1];
        vertices[vertex_data_stride + 25] = color[2];               vertices[vertex_data_stride + 35] = color[2];
        vertices[vertex_data_stride + 26] = color[3];               vertices[vertex_data_stride + 36] = color[3];
        vertices[vertex_data_stride + 27] = 1;                      vertices[vertex_data_stride + 37] = 0;
        vertices[vertex_data_stride + 28] = 1;                      vertices[vertex_data_stride + 38] = 1;
        vertices[vertex_data_stride + 29] = texture_index;          vertices[vertex_data_stride + 39] = texture_index;
    }

    // Indicies
    {

    }
}

void calypso_framework_renderer_2d_opengl_build_batch(struct calypso_framework_renderer_2d_opengl_quad_batch* batch)
{
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,0,batch->data_size,batch->vertices);
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

    // Quad (Immediate)
    {
         // Vertices (XYZ UV)
        const float vertices[] = {

            // POS (XYZ)        // Texture (UV)
             1,  1, 0,          0, 0,
             1, -1, 0,          0, 1,
            -1, -1, 0,          1, 1,
            -1,  1, 0,          1, 0

        };
        const int vertex_data_stride = 5;

        // Indicies
        const unsigned int indices[] = {
             0, 1, 2, 2, 3, 0
        };

        // VAO
        glGenVertexArrays(1, &_calypso_framework_renderer_2d_opengl_vao_quad_immediate);
        glBindVertexArray(_calypso_framework_renderer_2d_opengl_vao_quad_immediate);

        // VBO
        glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_vbo_quad_immediate);
        glBindBuffer(GL_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_vbo_quad_immediate);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float),vertices, GL_STATIC_DRAW);

        // IBO
        glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_ibo_quad_immediate);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_ibo_quad_immediate);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),indices, GL_STATIC_DRAW);

        // Vertex Attributes (XYZ)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Vertex Attributes (UV)
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
 
        glBindVertexArray(0);
    }
}

struct calypso_framework_renderer_2d_opengl_quad_batch calypso_framework_renderer_2d_opengl_create_quad_batch(int batch_instance_count)
{
    // Quad (Batched)
    {
        // Vertices (XYZ UV RGBA(Color))
        //float vertices[] = {
        //
        //    // POS (XYZ)        // COLOR (RGBA)                 // Texture (UV)     // Texture (Index/ID)
        //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
        //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
        //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
        //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,
        //
        //    1, -1, 0,           1.0f, 0.93f, 0.24f, 1.0f,       0,0,                1,
        //    3, -1, 0,           1.0f, 0.93f, 0.24f, 1.0f,       1,0,                1,
        //    3,  1, 0,           1.0f, 0.93f, 0.24f, 1.0f,       1,1,                1,
        //    1,  1, 0,           1.0f, 0.93f, 0.24f, 1.0f,       0,1,                1,
        //};
        const int vertex_data_stride = 10;

        // Indicies
        const unsigned int indices[] = {
        
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
        };

        
        struct calypso_framework_renderer_2d_opengl_quad_batch _batch;
        
        _batch.instance_count = batch_instance_count;
        const int batch_data_size = _batch.data_size = 40 * _batch.instance_count * sizeof(float);
        _batch.vertices = malloc(batch_data_size);

        // VAO
        glGenVertexArrays(1, &_batch.vao);
        glBindVertexArray(_batch.vao);

        // VBO
        glGenBuffers(1, &_batch.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _batch.vbo);
        glBufferData(GL_ARRAY_BUFFER,batch_data_size,NULL, GL_DYNAMIC_DRAW);

        // IBO
        glGenBuffers(1, &_batch.ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _batch.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),indices, GL_STATIC_DRAW);

        // Vertex Attributes (XYZ)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Vertex Attributes (RGBA(Color))
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        // Vertex Attributes (Texture(UV))
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)28);
        glEnableVertexAttribArray(2);

         // Vertex Attributes (Texture(Pos))
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)36);
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);

        return _batch;
  
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
* \param color_array uint8_t[4]
* \return void
*/
void calypso_framework_renderer_2d_opengl_set_clear_color_by_byte_color_array(const uint8_t color_array[4])
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
* \brief Render a Quad
* \return void
*/
void calypso_framework_renderer_2d_opengl_render_quad_immediate() 
{
    // OpenGL
    glBindVertexArray(_calypso_framework_renderer_2d_opengl_vao_quad_immediate);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/**
* \brief Render a Quad (Batched)
* \return void
*/
void calypso_framework_renderer_2d_opengl_render_quad_batched(struct calypso_framework_renderer_2d_opengl_quad_batch* batch) 
{
    // OpenGL
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, 6 * batch->instance_count, GL_UNSIGNED_INT, 0);
}