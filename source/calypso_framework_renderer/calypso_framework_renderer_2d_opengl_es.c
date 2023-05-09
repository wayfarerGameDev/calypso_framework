/// <summary>
/// 2D Renderer module that uses Glad (OpenGL Driver) as a base
/// </summary>

#pragma once

#include <stdlib.h> // free, malloc
#include <dependencies/glad/glad.h>

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Data
------------------------------------------------------------------------------*/

// Logging Callback
typedef void (*calypso_framework_renderer_2d_opengl_es_log_callback_t)(const char* log_msg, const unsigned char log_type);
calypso_framework_renderer_2d_opengl_es_log_callback_t _calypso_framework_renderer_2d_opengl_es_log_callback;

// State
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_NULL                         0b00000000
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT                         0b00000001
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_ERROR                        0b00000010
unsigned int _calypso_framework_renderer_2d_opengl_es_state =                      CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_NULL;

// OPen GL Version
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MAJOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MINOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_CONTEXT_PROFILE                    3

// Quad (Immediate)
unsigned int _calypso_framework_renderer_2d_opengl_es_vao_quad_immediate;
unsigned int _calypso_framework_renderer_2d_opengl_es_vbo_quad_immediate;
unsigned int _calypso_framework_renderer_2d_opengl_es_ibo_quad_immediate;

// Quad (Batch)
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INDICIES_DATA_STRIDE    6
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT      1024 * 10
#define CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INDEX_BUFFER_SIZE       CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INDICIES_DATA_STRIDE * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT
struct calypso_framework_renderer_2d_opengl_es_quad_batch
{
    float* vertex_buffer;
    // int* idnex_buffer;                   // IBO contains this data and it only needs to be set once and is static
    int vertex_buffer_data_size;
    unsigned int vao;                       // Vertex array object (Encapsulates VBO and IBO)
    unsigned int vbo;                       // Vertex buffer object
    unsigned int ibo;                       // Index buffer object
};

// Current Shader Program
unsigned int _calypso_framework_renderer_2d_opengl_es_current_program;

// Other
int _calypso_framework_renderer_2d_opengl_es_transpose_matrix =                    0;

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Log Callback
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_set_log_callback(calypso_framework_renderer_2d_opengl_es_log_callback_t log_callback)
{
    _calypso_framework_renderer_2d_opengl_es_log_callback = log_callback;
}

void calypso_framework_renderer_2d_opengl_es_do_log_callback(const char* log_msg, const unsigned char  log_type)
{
    if (_calypso_framework_renderer_2d_opengl_es_log_callback == NULL)
        return;

    _calypso_framework_renderer_2d_opengl_es_log_callback(log_msg,log_type);
}

void calypso_framework_renderer_2d_opengl_es_log_graphics_card()
{
    // Check If We Are Init
    if (_calypso_framework_renderer_2d_opengl_es_state != CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT)
    {
        _calypso_framework_renderer_2d_opengl_es_log_callback("Renderer Not init : calypso_framework_renderer_2d_opengl_es_log_graphics_card\n",3);
        return;
    }

    // Log
    const char* vendor = (const char*)glGetString(GL_VENDOR);
    const char* renderer = (const char*)glGetString(GL_RENDERER);
    calypso_framework_renderer_2d_opengl_es_do_log_callback("Graphics Card\n",1);
    calypso_framework_renderer_2d_opengl_es_do_log_callback(vendor,1);
    calypso_framework_renderer_2d_opengl_es_do_log_callback("\n",1);
    calypso_framework_renderer_2d_opengl_es_do_log_callback(renderer,1);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Init / Deinit
------------------------------------------------------------------------------*/
  
int calypso_framework_renderer_2d_opengl_es_is_init()
{
    return _calypso_framework_renderer_2d_opengl_es_state == CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT ? 1 : 0;
}

void calypso_framework_renderer_2d_opengl_es_init(void* opengl_proc_address)
{
    _calypso_framework_renderer_2d_opengl_es_state = CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT;

    // OpenGL (Glad)
    gladLoadGLLoader(opengl_proc_address);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // Start Clear Color (Cornflower blue)
    glClearColor(0.392f,0.584f,0.929f,1);
}

void calypso_framework_renderer_2d_opengl_es_deinit(void)
{
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Compile Shader | Default Shader Programs
------------------------------------------------------------------------------*/

unsigned int calypso_framework_renderer_2d_opengl_es_compile_shader(const char* shader_source, unsigned int shader_type)
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
            calypso_framework_renderer_2d_opengl_es_do_log_callback("Render: Vertex Shader (ERROR)\n",3);
        if (shader_type == GL_FRAGMENT_SHADER)
            calypso_framework_renderer_2d_opengl_es_do_log_callback("Render: Fragm9ent Shader (ERROR)\n",3);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(log_message,3);
        calypso_framework_renderer_2d_opengl_es_do_log_callback("\n",0);
    }

    // Return Shader ID
    return shader_id;
}

unsigned int calypso_framework_renderer_2d_opengl_es_create_shader_program_from_source(const char* vertex_shader_source, const char* fragment_shader_source)
{
    // Compile Shaders (Intermidete Data For Shaders)
    unsigned int vertex_shader = calypso_framework_renderer_2d_opengl_es_compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = calypso_framework_renderer_2d_opengl_es_compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

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
    //glDetachShader(vertex_shader);
    //glDetachShader(fragment_shader);

    // Return Shader Program
    return shader_program;
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Quad (Immediate)
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_create_build_quad_immediate(void)
{
    // Vertices (XYZ UV)
    const float vertices[] = 
    {
        // POS (XYZ)        // Texture (UV)
         1,  1, 0,          0, 0,
         1, -1, 0,          0, 1,
        -1, -1, 0,          1, 1,
        -1,  1, 0,          1, 0
    };
    const int vertex_data_stride = 5;

    // Indicies
    const unsigned int indices[] = 
    {
         0, 1, 2, // 1st Triangle
         2, 3, 0 // Second Triangle
    };

    // VAO (Vertex Array Object)
    glGenVertexArrays(1, &_calypso_framework_renderer_2d_opengl_es_vao_quad_immediate);
    glBindVertexArray(_calypso_framework_renderer_2d_opengl_es_vao_quad_immediate);

    // VBO (Vertex Buffer Object)
    glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_es_vbo_quad_immediate);
    glBindBuffer(GL_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_es_vbo_quad_immediate);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float),vertices, GL_STATIC_DRAW);

    // IBO (Index Buffer Object)
    glGenBuffers(1, &_calypso_framework_renderer_2d_opengl_es_ibo_quad_immediate);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _calypso_framework_renderer_2d_opengl_es_ibo_quad_immediate);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),indices, GL_STATIC_DRAW);

    // Vertex Attributes (XYZ)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex Attributes (UV)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void calypso_framework_renderer_2d_opengl_es_render_quad_immediate() 
{
    // OpenGL
    glBindVertexArray(_calypso_framework_renderer_2d_opengl_es_vao_quad_immediate);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_renderer_2d_opengl_es_create_default_immediate_shader_program()
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
    return calypso_framework_renderer_2d_opengl_es_create_shader_program_from_source(vertex_shader_source,fragment_shader_source);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Quad (Batch)
------------------------------------------------------------------------------*/

struct calypso_framework_renderer_2d_opengl_es_quad_batch calypso_framework_renderer_2d_opengl_es_create_quad_batch()
{
    // Create Batch | Set batch instance count
    struct calypso_framework_renderer_2d_opengl_es_quad_batch batch;

    // Vertex
    const int vertex_data_stride = 7;
    const int batch_vertex_data_size = batch.vertex_buffer_data_size = (vertex_data_stride  * 4) * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(float); // 4 because quad has 4 vertices
    batch.vertex_buffer = malloc(batch_vertex_data_size);

    // Indicies / Index Buffer
    //const unsigned int indices[] =
    //{
    //    0, 1, 2, 2, 3, 0,         // Quad 0
    //    4, 5, 6, 6, 7, 4,         // Quad 1
    //    8, 9, 10, 10, 11, 8,      // Quad 2
    //    12, 13, 14, 14, 15, 12,   // Quad 3
    //};
    const int indicies_data_stride = 6;
    unsigned int index_buffer[CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INDEX_BUFFER_SIZE];
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
    {
        const int offset = indicies_data_stride * i;
        const int offsetV = 4 * i;

        index_buffer[offset + 0] = offsetV + 0;           index_buffer[offset + 3] = offsetV + 2;
        index_buffer[offset + 1] = offsetV + 1;           index_buffer[offset + 4] = offsetV + 3;
        index_buffer[offset + 2] = offsetV + 2;           index_buffer[offset + 5] = offsetV + 0;
    }

    //const int batch_data_size = batch.vertex_data_size = 40 * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(int);
    
    // VAO (Vertex Array Object)
    glGenVertexArrays(1, &batch.vao);
    glBindVertexArray(batch.vao);
    
    // VBO (Vertex Buffer Object)
    glGenBuffers(1, &batch.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
    glBufferData(GL_ARRAY_BUFFER,batch_vertex_data_size,NULL, GL_DYNAMIC_DRAW);
    
    // IBO (Index Buffer Object)
    glGenBuffers(1, &batch.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer),index_buffer, GL_STATIC_DRAW);
    
    // Vertex Attributes (XYZ)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Vertex Attributes (RGBA(Color))
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    return batch;
}

void calypso_framework_renderer_2d_opengl_es_build_quad_batch(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,0,batch->vertex_buffer_data_size,batch->vertex_buffer);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float position[2], const float size, const float color[4])
{
    if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

    // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                   
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,

    const int offset = 28 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 0] = position[0];                vertex_buffer[offset + 7] = position[0] + size;
    vertex_buffer[offset + 1] = position[1];                vertex_buffer[offset + 8] = position[1];
    vertex_buffer[offset + 2] = 0;                          vertex_buffer[offset + 9] = 0;
    vertex_buffer[offset + 3] = color[0];                   vertex_buffer[offset + 10] = color[0];
    vertex_buffer[offset + 4] = color[1];                   vertex_buffer[offset + 11] = color[1];
    vertex_buffer[offset + 5] = color[2];                   vertex_buffer[offset + 12] = color[2];
    vertex_buffer[offset + 6] = color[3];                   vertex_buffer[offset + 13] = color[3];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 14] = position[0] + size;        vertex_buffer[offset + 21] = position[0];
    vertex_buffer[offset + 15] = position[1] + size;        vertex_buffer[offset + 22] = position[1] + size;
    vertex_buffer[offset + 16] = 0;                         vertex_buffer[offset + 23] = 0;
    vertex_buffer[offset + 17] = color[0];                  vertex_buffer[offset + 24] = color[0];
    vertex_buffer[offset + 18] = color[1];                  vertex_buffer[offset + 25] = color[1];
    vertex_buffer[offset + 19] = color[2];                  vertex_buffer[offset + 26] = color[2];
    vertex_buffer[offset + 20] = color[3];                  vertex_buffer[offset + 27] = color[3];
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_transform(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float position[2], const float size)
{
     if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

     // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                   
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,

    const int offset = 28 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

       // Row One                                              // Row Two
    vertex_buffer[offset + 0] = position[0];                vertex_buffer[offset + 7] = position[0] + size;
    vertex_buffer[offset + 1] = position[1];                vertex_buffer[offset + 8] = position[1];
    vertex_buffer[offset + 2] = 0;                          vertex_buffer[offset + 9] = 0;

     // Row Three                                           // Row Four
    vertex_buffer[offset + 14] = position[0] + size;        vertex_buffer[offset + 21] = position[0];
    vertex_buffer[offset + 15] = position[1] + size;        vertex_buffer[offset + 22] = position[1] + size;
    vertex_buffer[offset + 16] = 0;                         vertex_buffer[offset + 23] = 0;
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_color(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float color[4])
{
     if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

    // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                   
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,      
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,

    const int offset = 28 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 3] = color[0];                   vertex_buffer[offset + 10] = color[0];
    vertex_buffer[offset + 4] = color[1];                   vertex_buffer[offset + 11] = color[1];
    vertex_buffer[offset + 5] = color[2];                   vertex_buffer[offset + 12] = color[2];
    vertex_buffer[offset + 6] = color[3];                   vertex_buffer[offset + 13] = color[3];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 17] = color[0];                  vertex_buffer[offset + 24] = color[0];
    vertex_buffer[offset + 18] = color[1];                  vertex_buffer[offset + 25] = color[1];
    vertex_buffer[offset + 19] = color[2];                  vertex_buffer[offset + 26] = color[2];
    vertex_buffer[offset + 20] = color[3];                  vertex_buffer[offset + 27] = color[3];
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_data_default(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Cache Repeated Values
    float position[2] = {0,0};
    float color[4] = {1,1,1,1};

    //Set Instance Data (Default)
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
        calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data(batch,i,position,10,color);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_data_zeroed(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Cache Repeated Values
    float position[2] = {0,0};
    float color[4] = {0,0,0,0};

    //Set Instance Data (Default)
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
        calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data(batch,i,position,0,color);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_default(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance)
{
    float position[2] = {0,0};
    float color[4] = {1,1,1,1};
    calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data(batch,instance,position,10,color);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_zeroed(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance)
{
    float position[2] = {0,0};
    float color[4] = {0,0,0,0};
    calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data(batch,instance,position,10,color);
}

void calypso_framework_renderer_2d_opengl_es_render_quad_batched(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch) 
{
    // OpenGL
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, 6 * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_renderer_2d_opengl_es_create_default_batched_shader_program()
{
    // Vertex Shader Source
    const char* vertex_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 a_position;\n"
    "layout(location = 1) in vec4 a_color;\n"
    "\n"
    "uniform mat4 projection_view_in;\n"
    "uniform mat4 model_in;\n"
    "\n"
    "out vec4 v_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   v_color = a_color;\n"
    "   gl_Position = projection_view_in * model_in * a_position;\n"
    "}\n";

    // Fragment Shader Source
    const char* fragment_shader_source = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color_out;\n"
    "in vec4 v_color;"
    "\n"
    "void main()\n"
    "{\n"
    "   color_out = v_color;\n"
    "}\n"; 

    // Create Shader
    return calypso_framework_renderer_2d_opengl_es_create_shader_program_from_source(vertex_shader_source,fragment_shader_source);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Quad (Batch)(Textured)
------------------------------------------------------------------------------*/

struct calypso_framework_renderer_2d_opengl_es_quad_batch calypso_framework_renderer_2d_opengl_es_create_quad_batch_textured()
{
    // Create Batch | Set batch instance count
    struct calypso_framework_renderer_2d_opengl_es_quad_batch batch;

    // Vertex
    const int vertex_data_stride = 10;
    const int batch_vertex_data_size = batch.vertex_buffer_data_size = (vertex_data_stride  * 4) * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(float); // 4 because quad has 4 vertices
    batch.vertex_buffer = malloc(batch_vertex_data_size);

    // Indicies / Index Buffer
    //const unsigned int indices[] =
    //{
    //    0, 1, 2, 2, 3, 0,         // Quad 0
    //    4, 5, 6, 6, 7, 4,         // Quad 1
    //    8, 9, 10, 10, 11, 8,      // Quad 2
    //    12, 13, 14, 14, 15, 12,   // Quad 3
    //};
    const int indicies_data_stride = 6;
    unsigned int index_buffer[CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INDEX_BUFFER_SIZE];
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
    {
        const int offset = indicies_data_stride * i;
        const int offsetV = 4 * i;

        index_buffer[offset + 0] = offsetV + 0;           index_buffer[offset + 3] = offsetV + 2;
        index_buffer[offset + 1] = offsetV + 1;           index_buffer[offset + 4] = offsetV + 3;
        index_buffer[offset + 2] = offsetV + 2;           index_buffer[offset + 5] = offsetV + 0;
    }

    //const int batch_data_size = batch.vertex_data_size = 40 * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(int);
    
    // VAO (Vertex Array Object)
    glGenVertexArrays(1, &batch.vao);
    glBindVertexArray(batch.vao);
    
    // VBO (Vertex Buffer Object)
    glGenBuffers(1, &batch.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
    glBufferData(GL_ARRAY_BUFFER,batch_vertex_data_size,NULL, GL_DYNAMIC_DRAW);
    
    // IBO (Index Buffer Object)
    glGenBuffers(1, &batch.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer),index_buffer, GL_STATIC_DRAW);
    
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
    
    // Unbind
    glBindVertexArray(0);

    return batch;
}

void calypso_framework_renderer_2d_opengl_es_build_quad_batch_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,0,batch->vertex_buffer_data_size,batch->vertex_buffer);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float position[2], const float size, const float color[4], int texture_index)
{
    if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

    // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                    Texture (UV)        Texture (Index/ID)
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,

    const int offset = 40 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 0] = position[0];                vertex_buffer[offset + 10] = position[0] + size;
    vertex_buffer[offset + 1] = position[1];                vertex_buffer[offset + 11] = position[1];
    vertex_buffer[offset + 2] = 0;                          vertex_buffer[offset + 12] = 0;
    vertex_buffer[offset + 3] = color[0];                   vertex_buffer[offset + 13] = color[0];
    vertex_buffer[offset + 4] = color[1];                   vertex_buffer[offset + 14] = color[1];
    vertex_buffer[offset + 5] = color[2];                   vertex_buffer[offset + 15] = color[2];
    vertex_buffer[offset + 6] = color[3];                   vertex_buffer[offset + 16] = color[3];
    vertex_buffer[offset + 7] = 0;                          vertex_buffer[offset + 17] = 1;
    vertex_buffer[offset + 8] = 0;                          vertex_buffer[offset + 18] = 0;
    vertex_buffer[offset + 9] = texture_index;              vertex_buffer[offset + 19] = texture_index;

     // Row Three                                           // Row Four
    vertex_buffer[offset + 20] = position[0] + size;        vertex_buffer[offset + 30] = position[0];
    vertex_buffer[offset + 21] = position[1] + size;        vertex_buffer[offset + 31] = position[1] + size;
    vertex_buffer[offset + 22] = 0;                         vertex_buffer[offset + 32] = 0;
    vertex_buffer[offset + 23] = color[0];                  vertex_buffer[offset + 33] = color[0];
    vertex_buffer[offset + 24] = color[1];                  vertex_buffer[offset + 34] = color[1];
    vertex_buffer[offset + 25] = color[2];                  vertex_buffer[offset + 35] = color[2];
    vertex_buffer[offset + 26] = color[3];                  vertex_buffer[offset + 36] = color[3];
    vertex_buffer[offset + 27] = 1;                         vertex_buffer[offset + 37] = 0;
    vertex_buffer[offset + 28] = 1;                         vertex_buffer[offset + 38] = 1;
    vertex_buffer[offset + 29] = texture_index;             vertex_buffer[offset + 39] = texture_index;
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_transform_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float position[2], const float size)
{
     if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

     // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                    Texture (UV)        Texture (Index/ID)
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,

    const int offset = 40 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 0] = position[0];                vertex_buffer[offset + 10] = position[0] + size;
    vertex_buffer[offset + 1] = position[1];                vertex_buffer[offset + 11] = position[1];
    vertex_buffer[offset + 2] = 0;                          vertex_buffer[offset + 12] = 0;

     // Row Three                                           // Row Four
    vertex_buffer[offset + 20] = position[0] + size;        vertex_buffer[offset + 30] = position[0];
    vertex_buffer[offset + 21] = position[1] + size;        vertex_buffer[offset + 31] = position[1] + size;
    vertex_buffer[offset + 22] = 0;                         vertex_buffer[offset + 32] = 0;
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_color_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, const float color[4])
{
     if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

    // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                    Texture (UV)        Texture (Index/ID)
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,

    const int offset = 40 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 3] = color[0];                   vertex_buffer[offset + 13] = color[0];
    vertex_buffer[offset + 4] = color[1];                   vertex_buffer[offset + 14] = color[1];
    vertex_buffer[offset + 5] = color[2];                   vertex_buffer[offset + 15] = color[2];
    vertex_buffer[offset + 6] = color[3];                   vertex_buffer[offset + 16] = color[3];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 23] = color[0];                  vertex_buffer[offset + 33] = color[0];
    vertex_buffer[offset + 24] = color[1];                  vertex_buffer[offset + 34] = color[1];
    vertex_buffer[offset + 25] = color[2];                  vertex_buffer[offset + 35] = color[2];
    vertex_buffer[offset + 26] = color[3];                  vertex_buffer[offset + 36] = color[3];
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_texture_index_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance, int texture_index)
{
     if (instance < 0 || instance >= CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT)
        return;

    // Vertices (One Quad)
    //    POS (XYZ)           COLOR (RGBA)                    Texture (UV)        Texture (Index/ID)
    //    -3, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,0,                0,
    //    -1, -1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,0,                0,
    //    -1,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       1,1,                0,
    //    -3,  1, 0,          1.0f, 0.0f,  0.0f,  1.0f,       0,1,                0,

    const int offset = 40 * instance; // 40 Is How many floats/ values used for 4 vertices of each quad (10 values per vertex)
    float* vertex_buffer = batch->vertex_buffer;

    // Row One                                              // Row Two
    vertex_buffer[offset + 9] = texture_index;              vertex_buffer[offset + 19] = texture_index;

     // Row Three                                           // Row Four
    vertex_buffer[offset + 29] = texture_index;             vertex_buffer[offset + 39] = texture_index;
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_data_default_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Cache Repeated Values
    float position[2] = {0,0};
    float color[4] = {1,1,1,1};

    //Set Instance Data (Default)
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
        calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_textured(batch,i,position,10,color,0);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_data_zeroed_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch)
{
    // Cache Repeated Values
    float position[2] = {0,0};
    float color[4] = {0,0,0,0};

    //Set Instance Data (Default)
    for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
        calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_textured(batch,i,position,0,color,0);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_default_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance)
{
    float position[2] = {0,0};
    float color[4] = {1,1,1,1};
    calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_textured(batch,instance,position,10,color,0);
}

void calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_zeroed_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch, const int instance)
{
    float position[2] = {0,0};
    float color[4] = {0,0,0,0};
    calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_textured(batch,instance,position,10,color,0);
}

void calypso_framework_renderer_2d_opengl_es_render_quad_batched_textured(struct calypso_framework_renderer_2d_opengl_es_quad_batch* batch) 
{
    // OpenGL
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, 6 * CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_renderer_2d_opengl_es_create_default_batched_shader_program_textured()
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
    "\n"
    "uniform sampler2D u_texture;"
    "\n"
    "void main()\n"
    "{\n"
    "   color_out = texture(u_texture,v_tex_coord) * v_color;\n"
    "   // color_out = v_color;\n"
    "   // color_out = vec4(v_tex_coord,0,1);\n"
    "   // color_out = vec4(v_tex_index,v_tex_index,v_tex_index,1);\n"
    "}\n"; 

    // Create Shader
    return calypso_framework_renderer_2d_opengl_es_create_shader_program_from_source(vertex_shader_source,fragment_shader_source);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Texture(2D)
------------------------------------------------------------------------------*/

const unsigned int calypso_framework_renderer_2d_opengl_es_create_texture_2d_rgba(unsigned char* bytes, const int width, const int height)
{
    // Create | Bind Texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set TExture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set Texture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Create Texture From Bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    // Generate Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D,0);

    // Return
    return texture;
}

const unsigned int calypso_framework_renderer_2d_opengl_es_create_texture_2d_bgra(unsigned char* bytes, const int width, const int height)
{
    // Create | Bind Texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set TExture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set Texture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Create Texture From Bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bytes);

    // Generate Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D,0);

    // Return
    return texture;
}

void calypso_framework_renderer_2d_opengl_es_bind_texture_2d(const unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D,texture);
}

void calypso_framework_renderer_2d_opengl_es_unbind_texture_2d()
{
    glBindTexture(GL_TEXTURE_2D,0);
}


/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Current Shader Program
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_set_current_render_shader_program(const unsigned shader_program)
{
    glUseProgram(shader_program);
    _calypso_framework_renderer_2d_opengl_es_current_program = shader_program;
}

void calypso_framework_renderer_2d_opengl_es_bind_current_shader_program_texture(char* texture_parameter_name, const unsigned int texture)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,texture_parameter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater float(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(texture_parameter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniform1i(location,0);
}

void calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_float(char* paramter_name, const float v0)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater float(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniform1f(location,v0);
}

void calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec2f(char* paramter_name, const float v0, const float v1)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater vec2f(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniform2f(location,v0,v1);
}

void calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec3f(char* paramter_name, const float v0, const float v1, const float v2)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater vec3f(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniform3f(location,v0,v1,v2);
}

void calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec4f(char* paramter_name, const float v0, const float v1, const float v2, const float v3)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater vec4f(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniform4f(location,v0,v1,v2,v3);
}

void calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f(char* paramter_name, float* matrix4f)
{
    int location = glGetUniformLocation(_calypso_framework_renderer_2d_opengl_es_current_program,paramter_name);
    if (location == -1)
    {
        calypso_framework_renderer_2d_opengl_es_do_log_callback("Renderer: Can't set shader program paramater mat4f(",2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(paramter_name,2);
        calypso_framework_renderer_2d_opengl_es_do_log_callback(")\n",2);
        return;
    }

    glUniformMatrix4fv(location,1,_calypso_framework_renderer_2d_opengl_es_transpose_matrix,&matrix4f[0]);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Other
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_set_transpose_matrix(int value)
{
    _calypso_framework_renderer_2d_opengl_es_transpose_matrix = value;
}


/*------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : Renderer (Clear)
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_set_clear_color(const float r, const float g, const float b, const float a)
{
    glClearColor(r,g,b,a);
}

void calypso_framework_renderer_2d_opengl_es_set_clear_color_by_byte_color_array(const unsigned char  color_array[4])
{
    glClearColor(color_array[0] / 255.0f,color_array[1] / 255.0f,color_array[2] / 255.0f,color_array[3] / 255.0f);
}

void calypso_framework_renderer_2d_opengl_es_clear()
{
    // Check If We Are Init
    if (_calypso_framework_renderer_2d_opengl_es_state != CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT)
    {
        _calypso_framework_renderer_2d_opengl_es_log_callback("Renderer GL 2D: Not init\n",3);
        return;
    }
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/*------------------------------------------------------------------------------
Calypso Framework Renderer Pixel OpenGL : Renderer (Resize)
------------------------------------------------------------------------------*/

void calypso_framework_renderer_2d_opengl_es_renderer_resize(const int width, const int height)
{
     // Check If We Are Init
    if (_calypso_framework_renderer_2d_opengl_es_state != CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_STATE_INIT)
    {
        _calypso_framework_renderer_2d_opengl_es_log_callback("Renderer Not init : calypso_framework_renderer_2d_opengl_es_renderer_resize\n",3);
        return;
    }

    // Set Viewport
    glViewport(0,0,width,height);
}

/*
------------------------------------------------------------------------------
Calypso Framework Renderer 2D OpenGL : license
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