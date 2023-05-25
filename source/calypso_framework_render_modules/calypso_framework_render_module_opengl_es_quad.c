/// <summary>
/// 2D Renderer module that uses Glad (OpenGL Driver) as a base
/// </summary>

#pragma once

#include <dependencies/glad/glad.h>
#include <stdlib.h> // free, malloc

// Quad (Immediate)
unsigned int _calypso_framework_render_module_opengl_es_quad_vao_immediate;
unsigned int _calypso_framework_render_module_opengl_es_quad_vbo_immediate;
unsigned int _calypso_framework_render_module_opengl_es_quad_ibo_immediate;

// Quad (Batch)
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_BATCH_INDICIES_DATA_STRIDE           6
typedef struct calypso_framework_render_module_opengl_es_quad_batch_t
{
    float* vertex_buffer;
    // int* idnex_buffer;                   // IBO contains this data and it only needs to be set once and is static
    int batch_size_max;
    int batch_size_current;
    int vertex_buffer_data_size;
    unsigned int vao;                       // Vertex array object (Encapsulates VBO and IBO)
    unsigned int vbo;                       // Vertex buffer object
    unsigned int ibo;                       // Index buffer object
} calypso_framework_render_module_opengl_es_quad_batch_t;
calypso_framework_render_module_opengl_es_quad_batch_t* _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
calypso_framework_render_module_opengl_es_quad_batch_t* _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Quad (Immediate)
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_quad_build_quad_immediate(void)
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
    glGenVertexArrays(1, &_calypso_framework_render_module_opengl_es_quad_vao_immediate);
    glBindVertexArray(_calypso_framework_render_module_opengl_es_quad_vao_immediate);

    // VBO (Vertex Buffer Object)
    glGenBuffers(1, &_calypso_framework_render_module_opengl_es_quad_vbo_immediate);
    glBindBuffer(GL_ARRAY_BUFFER, _calypso_framework_render_module_opengl_es_quad_vbo_immediate);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float),vertices, GL_STATIC_DRAW);

    // IBO (Index Buffer Object)
    glGenBuffers(1, &_calypso_framework_render_module_opengl_es_quad_ibo_immediate);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _calypso_framework_render_module_opengl_es_quad_ibo_immediate);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),indices, GL_STATIC_DRAW);

    // Vertex Attributes (XYZ)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex Attributes (UV)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_data_stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void calypso_framework_render_module_opengl_es_quad_free_quad_immediate(void)
{
    glDeleteBuffers(1, &_calypso_framework_render_module_opengl_es_quad_vbo_immediate);
    glDeleteVertexArrays(1, &_calypso_framework_render_module_opengl_es_quad_vao_immediate);
    glDeleteBuffers(1, &_calypso_framework_render_module_opengl_es_quad_ibo_immediate);
}

void calypso_framework_render_module_opengl_es_quad_render_quad_immediate() 
{
    // OpenGL
    glBindVertexArray(_calypso_framework_render_module_opengl_es_quad_vao_immediate);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_render_module_opengl_es_quad_create_default_shader_program_quad_immediate(unsigned int (*operation)(const char*, const char*))
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
    return operation(vertex_shader_source,fragment_shader_source);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Quad (Batch)
------------------------------------------------------------------------------*/

calypso_framework_render_module_opengl_es_quad_batch_t calypso_framework_render_module_opengl_es_quad_create_quad_batch(const unsigned int batch_size_max)
{
    // Create Batch | Set batch instance count
    calypso_framework_render_module_opengl_es_quad_batch_t batch;

    // Set Size Max
    batch.batch_size_max = batch_size_max;

    // Vertex
    const int vertex_data_stride = 7;
    const int batch_vertex_data_size = batch.vertex_buffer_data_size = (vertex_data_stride  * 4) * batch.batch_size_max * sizeof(float); // 4 because quad has 4 vertices
    batch.vertex_buffer = malloc(batch_vertex_data_size);

    // Indicies / Index Buffer
    //const unsigned int indices[] =
    //{
    //    0, 1, 2, 2, 3, 0,         // Quad 0
    //    4, 5, 6, 6, 7, 4,         // Quad 1
    //    8, 9, 10, 10, 11, 8,      // Quad 2
    //    12, 13, 14, 14, 15, 12,   // Quad 3
    //};
    const unsigned int index_buffer_size = batch.batch_size_max * 6 * sizeof(unsigned int);
    unsigned int* index_buffer = malloc(index_buffer_size);
    for (int i = 0; i < batch.batch_size_max; i++)
    {
        const int offset = CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_BATCH_INDICIES_DATA_STRIDE * i;
        const int offsetV = 4 * i;

        index_buffer[offset + 0] = offsetV + 0;           index_buffer[offset + 3] = offsetV + 2;
        index_buffer[offset + 1] = offsetV + 1;           index_buffer[offset + 4] = offsetV + 3;
        index_buffer[offset + 2] = offsetV + 2;           index_buffer[offset + 5] = offsetV + 0;
    }

    //const int batch_data_size = batch.vertex_data_size = 40 * CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(int);
    
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

void calypso_framework_render_module_opengl_es_quad_bind_quad_batch(calypso_framework_render_module_opengl_es_quad_batch_t* batch)
{
    _calypso_framework_renderer_module_opengl_es_quad_batch_binded = batch;
}

void calypso_framework_render_module_opengl_es_quad_build_quad_batch()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;
        
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,0,batch->vertex_buffer_data_size,batch->vertex_buffer);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data(const int instance, const float position[3], const float size, const float color[4])
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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
    vertex_buffer[offset + 2] = position[2];                vertex_buffer[offset + 9] = position[2];
    vertex_buffer[offset + 3] = color[0];                   vertex_buffer[offset + 10] = color[0];
    vertex_buffer[offset + 4] = color[1];                   vertex_buffer[offset + 11] = color[1];
    vertex_buffer[offset + 5] = color[2];                   vertex_buffer[offset + 12] = color[2];
    vertex_buffer[offset + 6] = color[3];                   vertex_buffer[offset + 13] = color[3];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 14] = position[0] + size;        vertex_buffer[offset + 21] = position[0];
    vertex_buffer[offset + 15] = position[1] + size;        vertex_buffer[offset + 22] = position[1] + size;
    vertex_buffer[offset + 16] = position[2];               vertex_buffer[offset + 23] = position[2];  ;
    vertex_buffer[offset + 17] = color[0];                  vertex_buffer[offset + 24] = color[0];
    vertex_buffer[offset + 18] = color[1];                  vertex_buffer[offset + 25] = color[1];
    vertex_buffer[offset + 19] = color[2];                  vertex_buffer[offset + 26] = color[2];
    vertex_buffer[offset + 20] = color[3];                  vertex_buffer[offset + 27] = color[3];
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_transform(const int instance, const float position[3], const float size)
{
     // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

     // Validate   
     if (instance < 0 || instance >= batch->batch_size_max)
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
    vertex_buffer[offset + 2] = position[2];                vertex_buffer[offset + 9] = position[2];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 14] = position[0] + size;        vertex_buffer[offset + 21] = position[0];
    vertex_buffer[offset + 15] = position[1] + size;        vertex_buffer[offset + 22] = position[1] + size;
    vertex_buffer[offset + 16] = position[2];               vertex_buffer[offset + 23] = position[2];
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_color(const int instance, const float color[4])
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_default()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

    // Cache Repeated Values
    float position[3] = {0,0,0};
    float color[4] = {1,1,1,1};

    //Set Instance Data (Default)
    for (int i = 0; i < batch->batch_size_max; i++)
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data(i,position,10,color);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_zeroed()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

    // Cache Repeated Values
    float position[3] = {0,0,0};
    float color[4] = {0,0,0,0};

    //Set Instance Data (Default)
    for (int i = 0; i < batch->batch_size_max; i++)
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data(i,position,0,color);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_default(const int instance)
{

    float position[3] = {0,0,0};
    float color[4] = {1,1,1,1};
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data(instance,position,10,color);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_zeroed(const int instance)
{
    float position[3] = {0,0,0};
    float color[4] = {0,0,0,0};
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data(instance,position,10,color);
}

void calypso_framework_render_module_opengl_es_quad_render_quad_batched() 
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded;
    if (batch == NULL)
        return;

    // Clamp Batch Size
    if (batch->batch_size_current > batch->batch_size_max) 
        batch->batch_size_current = batch->batch_size_max;   

    // OpenGL
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, 6 * batch->batch_size_current, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_render_module_opengl_es_quad_create_default_shader_program_quad_batched(unsigned int (*operation)(const char*, const char*))
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
    return operation(vertex_shader_source,fragment_shader_source);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Quad) : Quad (Batch)(Textured)
------------------------------------------------------------------------------*/

calypso_framework_render_module_opengl_es_quad_batch_t calypso_framework_render_module_opengl_es_quad_create_quad_batch_textured(const unsigned int batch_size_max)
{
    // Create Batch | Set batch instance count
    calypso_framework_render_module_opengl_es_quad_batch_t batch;

    // Set Size Max
    batch.batch_size_max = batch_size_max;

    // Vertex
    const int vertex_data_stride = 10;
    const int batch_vertex_data_size = batch.vertex_buffer_data_size = (vertex_data_stride  * 4) * batch.batch_size_max * sizeof(float); // 4 because quad has 4 vertices
    batch.vertex_buffer = malloc(batch_vertex_data_size);

    // Indicies / Index Buffer
    //const unsigned int indices[] =
    //{
    //    0, 1, 2, 2, 3, 0,         // Quad 0
    //    4, 5, 6, 6, 7, 4,         // Quad 1
    //    8, 9, 10, 10, 11, 8,      // Quad 2
    //    12, 13, 14, 14, 15, 12,   // Quad 3
    //};
    // unsigned int index_buffer[CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_QUAD_BATCH_INDEX_BUFFER_SIZE];
    const unsigned int index_buffer_size = batch.batch_size_max * 6 * sizeof(unsigned int);
    unsigned int* index_buffer = malloc(index_buffer_size);
    for (int i = 0; i < batch.batch_size_max; i++)
    {
        const int offset = CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_BATCH_INDICIES_DATA_STRIDE * i;
        const int offsetV = 4 * i;

        index_buffer[offset + 0] = offsetV + 0;           index_buffer[offset + 3] = offsetV + 2;
        index_buffer[offset + 1] = offsetV + 1;           index_buffer[offset + 4] = offsetV + 3;
        index_buffer[offset + 2] = offsetV + 2;           index_buffer[offset + 5] = offsetV + 0;
    }

    //const int batch_data_size = batch.vertex_data_size = 40 * CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_QUAD_BATCH_INSTANCE_MAX_COUNT * sizeof(int);
    
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size,index_buffer, GL_STATIC_DRAW);
    
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

void calypso_framework_render_module_opengl_es_quad_bind_quad_batch_textured(calypso_framework_render_module_opengl_es_quad_batch_t* batch)
{
    _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured = batch;
}

void calypso_framework_render_module_opengl_es_quad_build_quad_batch_textured()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;
        
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER,batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,0,batch->vertex_buffer_data_size,batch->vertex_buffer);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(const int instance, const float position[3], const float size, const float color[4], int texture_index)
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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
    vertex_buffer[offset + 2] = position[2];                vertex_buffer[offset + 12] = position[2];
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
    vertex_buffer[offset + 22] = position[2];               vertex_buffer[offset + 32] = position[2]        ;
    vertex_buffer[offset + 23] = color[0];                  vertex_buffer[offset + 33] = color[0];
    vertex_buffer[offset + 24] = color[1];                  vertex_buffer[offset + 34] = color[1];
    vertex_buffer[offset + 25] = color[2];                  vertex_buffer[offset + 35] = color[2];
    vertex_buffer[offset + 26] = color[3];                  vertex_buffer[offset + 36] = color[3];
    vertex_buffer[offset + 27] = 1;                         vertex_buffer[offset + 37] = 0;
    vertex_buffer[offset + 28] = 1;                         vertex_buffer[offset + 38] = 1;
    vertex_buffer[offset + 29] = texture_index;             vertex_buffer[offset + 39] = texture_index;
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_transform_textured(const int instance, const float position[3], const float size)
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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
    vertex_buffer[offset + 2] = position[2];                vertex_buffer[offset + 12] = position[2];

     // Row Three                                           // Row Four
    vertex_buffer[offset + 20] = position[0] + size;        vertex_buffer[offset + 30] = position[0];
    vertex_buffer[offset + 21] = position[1] + size;        vertex_buffer[offset + 31] = position[1] + size;
    vertex_buffer[offset + 22] = position[2];               vertex_buffer[offset + 32] = position[2];
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_color_textured(const int instance, const float color[4])
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_texture_index_textured(const int instance, int texture_index)
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Validate
    if (instance < 0 || instance >= batch->batch_size_max)
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

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_default_textured()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Cache Repeated Values
    float position[3] = {0,0,0};
    float color[4] = {1,1,1,1};

    //Set Instance Data (Default)
    for (int i = 0; i < batch->batch_size_max; i++)
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(i,position,3,color,1);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_zeroed_textured()
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Cache Repeated Values
    float position[3] = {0,0,0};
    float color[4] = {0,0,0,0};

    //Set Instance Data (Default)
    for (int i = 0; i < batch->batch_size_max; i++)
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(i,position,0,color,10);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_default_textured(calypso_framework_render_module_opengl_es_quad_batch_t* batch, const int instance)
{
    float position[3] = {0,0,0};
    float color[4] = {1,1,1,1};
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(instance,position,10,color,10);
}

void calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_zeroed_textured(calypso_framework_render_module_opengl_es_quad_batch_t* batch, const int instance)
{
    float position[3] = {0,0,0};
    float color[4] = {0,0,0,0};
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(instance,position,10,color,0);
}

void calypso_framework_render_module_opengl_es_quad_render_quad_batched_textured() 
{
    // Validate Current Batch
    calypso_framework_render_module_opengl_es_quad_batch_t* batch = _calypso_framework_renderer_module_opengl_es_quad_batch_binded_textured;
    if (batch == NULL)
        return;

    // Clamp Batch Size
    if (batch->batch_size_current > batch->batch_size_max) 
        batch->batch_size_current = batch->batch_size_max;   
    
    // Render
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, 6 * batch->batch_size_current, GL_UNSIGNED_INT, 0);
}

unsigned int calypso_framework_render_module_opengl_es_quad_create_default_shader_program_batched_quad_textured(unsigned int (*operation)(const char*, const char*))
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
    return operation(vertex_shader_source,fragment_shader_source);
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