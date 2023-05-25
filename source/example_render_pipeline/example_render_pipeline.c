#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Calypso (Math)
#include "../calypso_framework_math/calypso_framework_math_colors.c"
#include "../calypso_framework_math/calypso_framework_math_matrix4.c"
#include "../calypso_framework_math/calypso_framework_math_random.c"

// Calypso (Render Modules)
#define CALYPSO_FRAMEWORK_OPENGL_ES_SHADER_DEBUGGING_ENABLED
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_core.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_quad.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_shader.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_texture.c"

// Render
void(*_example_render_pipeline_render_world_func_ptr)(void);
void(*_example_render_pipeline_render_screen_func_ptr)(void);
void(*_example_render_pipeline_render_end_func_ptr)(void);

// Texture
typedef struct example_render_pipeline_texture_t
{
    unsigned int texture;
    int source_width;
    int source_height;
    unsigned char is_valid;
} example_render_pipeline_texture_t;

// Model View Projection Matrix(s)
float _example_render_pipeline_projection_matrix[4][4];
float _example_render_pipeline_view_matrix[4][4];
float _example_render_pipeline_projection_view_matrix[4][4];

// Model Matrix
float _example_render_pipeline_model_matrix[4][4];

// Render Color
float _example_render_pipeline_render_color_r;
float _example_render_pipeline_render_color_g; 
float _example_render_pipeline_render_color_b;
float _example_render_pipeline_render_color_a;

// Render Scale
float _example_renderer_pipeline_render_scale_x;
float _example_renderer_pipeline_render_scale_y;

// Rect
unsigned int _example_render_pipleline_shader_program_rect;

// Spritebatch
typedef calypso_framework_render_module_opengl_es_quad_batch_t example_render_pipeline_sprite_batch_t;
unsigned int _example_render_pipleline_shader_program_sprite_batch;

/*------------------------------------------------------------------------------
Example Render Pipeline : Main
------------------------------------------------------------------------------*/

void example_render_pipeline_init(const void* opengl_processing_address, void(*render_world_func_ptr)(void),void(*render_screen_func_ptr)(void), void(*render_end_func_ptr)(void))
{
    // Init Render Modules
    calypso_framework_render_module_opengl_es_core_init(opengl_processing_address);

    // Set Clear
    calypso_framework_render_module_opengl_es_core_set_clear_color(0,0,0,1);
    calypso_framework_render_module_opengl_es_core_set_clear_depth(1);

    // Default Draw Scale
    _example_renderer_pipeline_render_scale_x = 100;
    _example_renderer_pipeline_render_scale_y = 100;

    // Enable Features
    calypso_framework_renderer_module_opengl_es_core_enable(GL_BLEND);
    calypso_framework_renderer_module_opengl_es_core_enable(GL_DEPTH_TEST);

    // Depth/Blend Function
    calypso_framework_renderer_module_opengl_es_core_set_blend_function(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    calypso_framework_renderer_module_opengl_es_core_set_depth_function(GL_LESS);
    
    // Rect
    {
        // Create Default Shader Program (Quad Immediate)
        _example_render_pipleline_shader_program_rect = calypso_framework_render_module_opengl_es_quad_create_default_shader_program_quad_immediate(calypso_framework_render_module_opengl_es_shader_create_shader);
        calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_example_render_pipleline_shader_program_rect);
        calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f("color_in",255,0,0,0);

        // Build Quad Immediate
        calypso_framework_render_module_opengl_es_quad_build_quad_immediate();
    }

    // Spritebatch 
    {
        // Shader Program
        _example_render_pipleline_shader_program_sprite_batch = calypso_framework_render_module_opengl_es_quad_create_default_shader_program_batched_quad_textured(calypso_framework_render_module_opengl_es_shader_create_shader);
    }

    // Render World | Screen
    _example_render_pipeline_render_world_func_ptr = render_world_func_ptr;
    _example_render_pipeline_render_screen_func_ptr = render_screen_func_ptr;
    _example_render_pipeline_render_end_func_ptr = render_end_func_ptr;
}

void example_render_pipeline_update(const int window_width, const int window_height)
{
    // Clear
    calypso_framework_render_module_opengl_es_core_clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update Viewport
    calypso_framework_render_module_opengl_es_core_set_viewport(window_width, window_height);

    // Movdel View Projection Matrix (World) | Render World
    {
        // Viewport Transform
        float position_x = window_width / 2;
        float position_y = window_height / 2;

        // View Matrix
        calypso_framework_math_matrix4_build_identity_matrix_f(_example_render_pipeline_view_matrix);
        calypso_framework_math_matrix4_modify_scale_f(0.3f,0.3f,1,_example_render_pipeline_view_matrix);
        calypso_framework_math_matrix4_modify_position_f(position_x,position_y,0,_example_render_pipeline_view_matrix);

        // Projection Matrix
        calypso_framework_math_matrix4_build_projection_ortho_matrix_f(0,window_width,0,window_height,-100,100,_example_render_pipeline_projection_matrix);

        // Projection * View Matrix
        calypso_framework_math_matrix4_modify_mult_f(_example_render_pipeline_projection_matrix,_example_render_pipeline_view_matrix,_example_render_pipeline_projection_view_matrix);
    
        // Render World
        _example_render_pipeline_render_world_func_ptr();
    }

    // Movdel View Projection Matrix (Screen) | Render Screen
    {
        // View Matrix
        calypso_framework_math_matrix4_build_identity_matrix_f(_example_render_pipeline_view_matrix);
        calypso_framework_math_matrix4_modify_scale_f(0.3f,0.3f,1,_example_render_pipeline_view_matrix);
        calypso_framework_math_matrix4_modify_position_f(0,0,0,_example_render_pipeline_view_matrix);

        // Projection Matrix
        calypso_framework_math_matrix4_build_projection_ortho_matrix_f(0,window_width,0,window_height,-100,100,_example_render_pipeline_projection_matrix);

        // Projection
        calypso_framework_math_matrix4_modify_mult_f(_example_render_pipeline_projection_matrix,_example_render_pipeline_view_matrix,_example_render_pipeline_projection_view_matrix);
    
        _example_render_pipeline_render_screen_func_ptr();
    }

    // TODO: Post Processing Here

    // Render End
    _example_render_pipeline_render_end_func_ptr();
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Render Scale
------------------------------------------------------------------------------*/

void example_render_pipeline_set_render_scale(const float x, const float y)
{
    _example_renderer_pipeline_render_scale_x = x;
    _example_renderer_pipeline_render_scale_y = y;
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Render Color
------------------------------------------------------------------------------*/

void example_render_pipeline_set_render_color_rgb(const unsigned char r, const unsigned char g, const unsigned char b)
{
    _example_render_pipeline_render_color_r = (float)r / 255;
    _example_render_pipeline_render_color_g = (float)g / 255;
    _example_render_pipeline_render_color_b = (float)b / 255;
    _example_render_pipeline_render_color_a = 1;
}

void example_render_pipeline_set_render_color_rgba(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
    _example_render_pipeline_render_color_r = (float)r / 255;
    _example_render_pipeline_render_color_g = (float)g / 255;
    _example_render_pipeline_render_color_b = (float)b / 255;
    _example_render_pipeline_render_color_a = (float)a / 255;
}

void example_render_pipeline_set_render_color_rgb_array(const unsigned char color_rgb_array[3])
{
    _example_render_pipeline_render_color_r = (float)color_rgb_array[0] / 255;
    _example_render_pipeline_render_color_g = (float)color_rgb_array[1] / 255;
    _example_render_pipeline_render_color_b = (float)color_rgb_array[2] / 255;
    _example_render_pipeline_render_color_a = 1;
}

void example_render_pipeline_set_render_color_rgba_array(const unsigned char color_rgba_array[4])
{
    _example_render_pipeline_render_color_r = (float)color_rgba_array[0] / 255;
    _example_render_pipeline_render_color_g = (float)color_rgba_array[1] / 255;
    _example_render_pipeline_render_color_b = (float)color_rgba_array[2] / 255;
    _example_render_pipeline_render_color_a = (float)color_rgba_array[3] / 255;
}

void example_render_pipeline_set_render_color_hex(int hex_value)
{
    _example_render_pipeline_render_color_r = (float)((hex_value >> 16) & 0xFF) / 255;
    _example_render_pipeline_render_color_g = (float)((hex_value >> 8) & 0xFF) / 255;
    _example_render_pipeline_render_color_b = (float)((hex_value) & 0xFF) / 255;
    _example_render_pipeline_render_color_a = 1;
}

void example_render_pipeline_set_render_color_hex_a(int hex_value, unsigned char a)
{
    _example_render_pipeline_render_color_r = (float)((hex_value >> 16) & 0xFF) / 255;
    _example_render_pipeline_render_color_g = (float)((hex_value >> 8) & 0xFF) / 255;
    _example_render_pipeline_render_color_b = (float)((hex_value) & 0xFF) / 255;
    _example_render_pipeline_render_color_a = (float)a / 255;
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Wireframe
------------------------------------------------------------------------------*/

void example_render_pipeline_set_wireframe_mode(const unsigned char value)
{
    calypso_framework_renderer_module_opengl_es_core_set_wireframe_mode(value);
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Texture
------------------------------------------------------------------------------*/

example_render_pipeline_texture_t example_render_pipeline_load_texture_file_tga(const char* file_path)
{
    // Load Texture
    example_render_pipeline_texture_t texture;
    texture.is_valid = 1;
    int image_column_count;
    unsigned char* image_data = stbi_load(file_path,&texture.source_width,&texture.source_height,&image_column_count,0);
    texture.texture = calypso_framework_render_module_opengl_es_shader_create_texture_2d_bgra(image_data,texture.source_width,texture.source_height);
    free(image_data);

    // Return Texture
    return texture;
}

void example_render_pipeline_bind_texture(const example_render_pipeline_texture_t* texture, const unsigned int texture_slot)
{
    // Validate
    if (texture == ((void*)0) || texture->is_valid != 1)
        return;

    // Bind
    calypso_framework_render_module_opengl_es_shader_bind_texture_2d(texture->texture,texture_slot);
}

void example_render_pipeline_unbind_texture()
{
    calypso_framework_render_module_opengl_es_shader_unbind_texture_2d();
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Render (Rect)
------------------------------------------------------------------------------*/

void example_render_pipeline_render_rect(const float position_x, const float position_y, const float position_z)
{
    // Model Matrix
    calypso_framework_math_matrix4_build_identity_matrix_f(_example_render_pipeline_model_matrix);
    calypso_framework_math_matrix4_modify_position_f(position_x,position_y,position_z,_example_render_pipeline_model_matrix);
    calypso_framework_math_matrix4_modify_scale_f(_example_renderer_pipeline_render_scale_x,_example_renderer_pipeline_render_scale_y,1,_example_render_pipeline_model_matrix);
    
    // Update Shader Program
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_example_render_pipleline_shader_program_rect);
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_example_render_pipeline_projection_view_matrix[0],0); // Apply Viewport Projection And View
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f("color_in",_example_render_pipeline_render_color_r,_example_render_pipeline_render_color_g,_example_render_pipeline_render_color_b,_example_render_pipeline_render_color_a);
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_example_render_pipeline_model_matrix[0],0); // Apply Transfor
    
    // Render
    calypso_framework_render_module_opengl_es_quad_render_quad_immediate();
}

/*------------------------------------------------------------------------------
Example Render Pipeline : Render Sprite
------------------------------------------------------------------------------*/


void example_render_pipeline_sprite_batch_apply_shaders()
{
    // Update Model Matrix
    calypso_framework_math_matrix4_build_identity_matrix_f(_example_render_pipeline_model_matrix);
    calypso_framework_math_matrix4_modify_scale_f(50,50,1,_example_render_pipeline_model_matrix);
    calypso_framework_math_matrix4_modify_position_f(0,0,0,_example_render_pipeline_model_matrix);
    
    // Update Shader Program
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_example_render_pipleline_shader_program_sprite_batch = calypso_framework_render_module_opengl_es_quad_create_default_shader_program_batched_quad_textured(calypso_framework_render_module_opengl_es_shader_create_shader));
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_example_render_pipeline_projection_view_matrix[0],0); // Apply Viewport Projection And View
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_example_render_pipeline_model_matrix[0],0); // Apply Transform
    calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_i("u_texture",0);
}

example_render_pipeline_sprite_batch_t example_render_pipeline_sprite_batch_create(const unsigned int batch_size)
{
    // Create Batch
    example_render_pipeline_sprite_batch_t batch = calypso_framework_render_module_opengl_es_quad_create_quad_batch_textured(batch_size);
    calypso_framework_render_module_opengl_es_quad_bind_quad_batch_textured(&batch);
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_zeroed_textured();

    return batch;
}

void example_render_pipeline_sprite_batch_build(example_render_pipeline_sprite_batch_t* batch_ptr)
{
    // Bind (Textured)
    calypso_framework_render_module_opengl_es_quad_bind_quad_batch_textured(batch_ptr);
    calypso_framework_render_module_opengl_es_quad_build_quad_batch_textured();
}

void example_render_pipeline_sprite_batch_draw(example_render_pipeline_sprite_batch_t* batch_ptr, const int count)
{    
    // Set Batch Size
    batch_ptr->batch_size_current = count;

    // Reuild batch | Render Batch
    calypso_framework_render_module_opengl_es_quad_render_quad_batched_textured();
}

void example_render_pipeline_sprite_batch_set_element(example_render_pipeline_sprite_batch_t* batch_ptr,const int index, const float position_x, const float position_y, const float position_z)
{   
    // Set Batch Data
    float position[3] = {position_x,position_y,position_z};
    float color[4] = {1,1,1,1};
    float scale = 3;

    // Bind (Textured)
    calypso_framework_render_module_opengl_es_quad_bind_quad_batch_textured(batch_ptr);

    // Set Data
    calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_textured(index,position,scale,color,0);
}
