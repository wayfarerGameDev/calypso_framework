// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

// Calypso (SDL or GLFW)
#define USE_GLFW_OVER_SDL 1
#if(USE_GLFW_OVER_SDL)
#include "calypso_framework_app_glfw.c"
#include "calypso_framework_input_glfw.c"
#else
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_input_sdl.c"
#endif


// Calypso
#include "calypso_framework_colors.c"
#include "calypso_framework_io.c"
#include "calypso_framework_math_matrix4.c"
#include "calypso_framework_math_random.c"
#include "calypso_framework_renderer_2d_opengl.c"

// Renderer (Viewport)
float _renderer_viewport_projection_matrix[4][4];
float _renderer_view_matrix[4][4];
float _renderer_projection_view_matrix[4][4];
float _renderer_viewport_position_x;
float _renderer_viewport_position_y;
float _renderer_viewport_width;
float _renderer_viewport_height;
float _renderer_viewport_scale_x;
float _renderer_viewport_scale_y;

// Render (Shader Programs)
float _renderer_model_matrix[4][4];
unsigned int _renderer_default_shader_immediate_program;
unsigned int _renderer_default_shader_batched_program;
unsigned int* _renderer_shader_program_array;
unsigned int _renderer_shader_program_array_count;

// Renderer (Other)
bool _renderer_is_dirty;
struct calypso_framework_renderer_2d_opengl_quad_batch _renderer_quad_batch;

// Colors
const uint8_t* _c_color_white_array = _c_calypso_framework_colors_color_byte_array_white;
const uint8_t* _c_color_red_array = _c_calypso_framework_colors_color_byte_array_red;
const uint8_t* _c_color_yellow_array = _c_calypso_framework_colors_color_byte_array_yellow;


void log_msg(const char* log_msg, const uint8_t log_type)
{
    // Color Log
    if (log_type == 1)
        printf("\033[0;32m"); // Green
    else if (log_type == 2)
        printf("\033[33m"); // Yellow
    else if (log_type == 3)
        printf("\033[0;31m"); // Red
    else 
        printf("\033[0;00m"); // White
    
    // Log
    printf(log_msg);

    // Reset Log
    printf("\033[0;00m"); // White
}

void start(void)
{
    // Viewport Width / Height (GLFW)
    #if(USE_GLFW_OVER_SDL)
    _renderer_viewport_width = calypso_framework_app_glfw_get_window_width();
    _renderer_viewport_height = calypso_framework_app_glfw_get_window_height();
    
    #else
    // Viewport Width / Height (SDL)
    _renderer_viewport_width = calypso_framework_app_sdl_get_window_width();
    _renderer_viewport_height = calypso_framework_app_sdl_get_window_height();
    #endif

    // Init Renderer
    {
        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        calypso_framework_renderer_2d_opengl_init(calypso_framework_app_glfw_get_open_gl_proc_address());
        #else
        calypso_framework_renderer_2d_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());
        #endif


        // Default Shader Program (Batched)
        _renderer_default_shader_batched_program = calypso_framework_renderer_2d_opengl_create_default_batched_circle_shader_program();
        _renderer_shader_program_array_count++;
        _renderer_shader_program_array = realloc(_renderer_shader_program_array,_renderer_shader_program_array_count * sizeof(unsigned int));
        _renderer_shader_program_array[_renderer_shader_program_array_count - 1] = _renderer_default_shader_batched_program;
       
        // Default Shader Program (Immediate)
        _renderer_default_shader_immediate_program = calypso_framework_renderer_2d_opengl_create_default_immediate_shader_program();
        _renderer_shader_program_array_count++;
        _renderer_shader_program_array = realloc(_renderer_shader_program_array,_renderer_shader_program_array_count * sizeof(unsigned int));
        _renderer_shader_program_array[_renderer_shader_program_array_count - 1] = _renderer_default_shader_immediate_program;
        calypso_framework_renderer_2d_opengl_set_current_render_shader_program(_renderer_default_shader_immediate_program);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",_c_color_white_array[0] / 255, _c_color_white_array[1] / 255, _c_color_white_array[2] / 255, _c_color_white_array[3] / 255);

        // Is Dirty By Default
        _renderer_is_dirty = true;
    }

    // Create render Quad (Immediate)
    calypso_framework_renderer_2d_create_build_quad_immediate();

    // Create Render Quad (Batch)
    {
        _renderer_quad_batch = calypso_framework_renderer_2d_opengl_create_quad_batch(300);
        calypso_framework_renderer_2d_opengl_set_quad_batch_data_default(&_renderer_quad_batch);

        // Randomize
        {
            // Cache Max/Min Width/Height
            const int max_width = ((int)_renderer_viewport_width) * 0.04f;
            const int min_width = -max_width;
            const int max_height = ((int)_renderer_viewport_height) * 0.04f;
            const int min_height = -max_height;

            // Set Entities Data
            float position[2] = {0,0};
            float color[4] = {0,0,0,1};
            calypso_framework_random_rand_set_seed_as_time();
            for (int i = 0; i < _renderer_quad_batch.instance_max_count; i++)
            {
                position[0] = calypso_framework_math_random_rand_range_i(min_width,max_width);
                position[1] = calypso_framework_math_random_rand_range_i(min_height,max_height);
                color[0] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[1] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[2] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[3] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;

                calypso_framework_renderer_2d_opengl_set_quad_batch_instance_data_position_size_pair(&_renderer_quad_batch,i,position,3);
                calypso_framework_renderer_2d_opengl_set_quad_batch_instance_data_color(&_renderer_quad_batch,i,color);
            }
        }

        calypso_framework_renderer_2d_opengl_build_quad_batch(&_renderer_quad_batch); 
    }
}


void end(void)
{
    // Renderer
    calypso_framework_renderer_2d_opengl_deinit();
}


void update(void)
{
    // Update
    {

    }

    // Renderer (Update Viewport)
    if (_renderer_is_dirty)
    {
        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        _renderer_viewport_width = calypso_framework_app_glfw_get_window_width();
        _renderer_viewport_height = calypso_framework_app_glfw_get_window_height();
        
        #else
        // Viewport Width / Height (SDL)
        _renderer_viewport_width = calypso_framework_app_sdl_get_window_width();
        _renderer_viewport_height = calypso_framework_app_sdl_get_window_height();
        #endif

        // Viewport Transform
        _renderer_viewport_position_x = _renderer_viewport_width / 2;
        _renderer_viewport_position_y = _renderer_viewport_height / 2;
        _renderer_viewport_scale_x = 0.3f;
        _renderer_viewport_scale_y = 0.3f;

        // Viewport Matrix (Projection And View) (Ortho 2D)
        calypso_framework_math_matrix_build_projection_ortho_matrix4f(0,_renderer_viewport_width,0,_renderer_viewport_height,-1,1,_renderer_viewport_projection_matrix);
        calypso_framework_math_matrix_build_identity_matrix4f(_renderer_view_matrix);
        calypso_framework_math_matrix_modify_set_scale(_renderer_viewport_scale_x,_renderer_viewport_scale_y,1,_renderer_view_matrix);
        calypso_framework_math_matrix_modify_set_position(_renderer_viewport_position_x,_renderer_viewport_position_y,0,_renderer_view_matrix);
        calypso_framework_math_matrix_modify_mult(_renderer_viewport_projection_matrix,_renderer_view_matrix,_renderer_projection_view_matrix);
    }

    // Renderer (Update Shader Programs)
    if (_renderer_is_dirty)
        for (int i = 0; i < _renderer_shader_program_array_count; i++)
        {
            calypso_framework_renderer_2d_opengl_set_current_render_shader_program( _renderer_shader_program_array[i]);
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("projection_view_in",_renderer_projection_view_matrix); // Apply Viewport Projection And View
        }


    // Render (Start)
    {        
        // Render Start
        const uint8_t color[4] = {10,10,10,255};
        calypso_framework_renderer_2d_opengl_set_renderer_clear_color_by_byte_color_array(color); // Don't need to  do this every frame but why not
        calypso_framework_renderer_2d_opengl_renderer_clear();
    }

    // Render Entities(Immediate)
    if (1 == 0)
    {
        // Entity (Red)
        {
            // Model Matrix
            calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_scale(100,100,1,_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_position(0,0,0,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_renderer_2d_opengl_set_current_render_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",_c_color_red_array[0] / 255, _c_color_red_array[1] / 255, _c_color_red_array[2] / 255, _c_color_red_array[3] / 255);
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix); // Apply Transform
    
            // Render
            calypso_framework_renderer_2d_opengl_render_quad_immediate();
        }

        // Entity (Yellow)
        {
            // Model Matrix
            calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_scale(50,50,1,_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_position(100,100,0,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_renderer_2d_opengl_set_current_render_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",_c_color_yellow_array[0] / 255, _c_color_yellow_array[1] / 255, _c_color_yellow_array[2] / 255, _c_color_yellow_array[3] / 255);
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix); // Apply Transform
    
            // Render
            calypso_framework_renderer_2d_opengl_render_quad_immediate();
        }
    }

    // Render Entities (Batched)
    else
    {
        calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_scale(50,50,1,_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_position(0,0,0,_renderer_model_matrix);

        // Update Shader Program
        calypso_framework_renderer_2d_opengl_set_current_render_shader_program(_renderer_default_shader_batched_program);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix); // Apply Transform

        calypso_framework_renderer_2d_opengl_render_quad_batched(&_renderer_quad_batch);
    }

    // Renderer (End)
    _renderer_is_dirty = false;
}

int main(int argc, char** argv)
{
    // Logging
    calypso_framework_renderer_2d_opengl_set_log_callback(log_msg);

        // App (GLFW)
        #if(USE_GLFW_OVER_SDL)
        calypso_framework_app_glfw_set_log_callback(log_msg);
        calypso_framework_app_glfw_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_CONTEXT_PROFILE);
        calypso_framework_app_glfw_set_window_title("Testbed : Renderer2D (GLFW)");
        calypso_framework_app_glfw_set_events(start,end,update);
        calypso_framework_app_glfw_run();
        
        #else
        // App (SDL)
        calypso_framework_app_sdl_set_log_callback(log_msg);
        calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_CONTEXT_PROFILE);
        calypso_framework_app_sdl_set_window_title("Testbed : Renderer2D (SDL)");
        calypso_framework_app_sdl_set_events(start,end,update);
        calypso_framework_app_sdl_run();
        #endif

   
    // We Done Baby
    return 0;
}