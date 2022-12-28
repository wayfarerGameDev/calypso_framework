// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t


// Includes Calypso
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_benchmark_time.c"
#include "calypso_framework_colors.c"
#include "calypso_framework_entities_simple.c"
#include "calypso_framework_input_sdl.c"
#include "calypso_framework_io.c"
#include "calypso_framework_math_matrix4.c"
#include "calypso_framework_math_random.c"
#include "calypso_framework_spatial partitioning_grid_2d.c"
#include "calypso_framework_renderer_2d_opengl.c"

// Benchmark
int _benchmark_time_spatial_partitioning_grid_2d;

// Renderer (Viewport)
float _renderer_viewport_width;
float _renderer_viewport_height;
float _renderer_viewport_projection_matrix[4][4];
float _renderer_view_matrix[4][4];
float _renderer_projection_view_matrix[4][4];
float _renderer_viewport_position_x;
float _renderer_viewport_position_y;
float _renderer_viewport_scale_x;
float _renderer_viewport_scale_y;

// Render (Shader Programs)
float _renderer_model_matrix[4][4];
unsigned int _renderer_default_shader_immediate_program;
unsigned int* _renderer_shader_program_array;
unsigned int _renderer_shader_program_array_count;

// Renderer (Other)
bool _renderer_is_dirty;

// Entitie (Data)
unsigned int* _entity_count_max_ptr;
CalypsoFrameworkColorsColorRGBA* _entity_color_array;
float* _entity_position_x_array;
float* _entity_position_y_array;
float* _entity_bounds_x_array;
float* _entity_bounds_y_array;
unsigned int* _entity_collision_group_array;
bool* _entity_is_created_array;
bool* _entity_is_disabled_array;
bool* _entity_is_dirty_array;

// Input
float _mouse_cursor_x;
float _mouse_cursor_y;

// Colors (Arrays)
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
    // Default Color RGBA White
    CalypsoFrameworkColorsColorRGBA color_white_color_rgba = {.r = 255, .g = 255, .b = 255, .a = 255};

    // Viewport Width / Height
    _renderer_viewport_width = calypso_framework_app_sdl_get_window_width();
    _renderer_viewport_height = calypso_framework_app_sdl_get_window_height();

    // Init Benchmark Time
    _benchmark_time_spatial_partitioning_grid_2d = calypso_framework_benchmark_time_add_benchmark();

    // Init Entities
    calypso_framework_entities_simple_init(1000);
    _entity_count_max_ptr = calypso_framework_entities_simple_get_entity_count_max_ptr();
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(CalypsoFrameworkColorsColorRGBA,"color",_entity_color_array,color_white_color_rgba);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(float,"position_x",_entity_position_x_array,0);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(float,"position_x",_entity_position_x_array,0);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(float,"position_y",_entity_position_y_array,0);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(float,"bounds_x",_entity_bounds_x_array,30);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(float,"bounds_y",_entity_bounds_y_array,30);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(int,"collision_group",_entity_collision_group_array,0);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(bool,"is_created",_entity_is_created_array,true);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(bool,"is_disabled",_entity_is_disabled_array,false);
    CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(bool,"is_dirty",_entity_is_dirty_array,false);

    // Rand Our Entites
    {
        // Cache Max/Min Width/Height
        const int max_width = ((int)_renderer_viewport_width + 500);
        const int min_width = -max_width;
        const int max_height = ((int)_renderer_viewport_height + 400);
        const int min_height = -max_height;
        const uint8_t max_color = 255;
        const uint8_t min_color = 100;

        // Set Random Seed
        srand(time(0));

        // Set Entities Data
        for (int i = 0; i < *_entity_count_max_ptr; i++)
        {
            _entity_position_x_array[i] = (rand() % (max_width - min_width + 1)) + min_width;
            _entity_position_y_array[i] = (rand() % (max_height - min_height + 1)) + min_height;
        }
    }

    // Init Renderer
    {
        // Init OpengGl (Wee ned openGl processing address from our app)
        calypso_framework_renderer_2d_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());

        // Default Shader Program
        _renderer_default_shader_immediate_program = calypso_framework_renderer_2d_opengl_create_default_immediate_shader_program();
        _renderer_shader_program_array_count++;
        _renderer_shader_program_array = realloc(_renderer_shader_program_array,_renderer_shader_program_array_count * sizeof(unsigned int));
        _renderer_shader_program_array[_renderer_shader_program_array_count - 1] = _renderer_default_shader_immediate_program;
        calypso_framework_renderer_2d_opengl_set_current_render_shader_program(_renderer_default_shader_immediate_program);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",_c_color_white_array[0] / 255, _c_color_white_array[1] / 255, _c_color_white_array[2] / 255, _c_color_white_array[3] / 255);

        // Is Dirty By Default
        _renderer_is_dirty = true;
    }

    // Init Spacial Partitioning Grid 2D (We Pass In Entity Data)
    calypso_framework_spatial_partitioning_grid_2d_init(_renderer_viewport_width,_renderer_viewport_width,10,10,
        _entity_count_max_ptr,_entity_position_x_array,_entity_position_y_array,
        _entity_bounds_x_array, _entity_bounds_y_array,_entity_collision_group_array,
        _entity_is_created_array,_entity_is_disabled_array,_entity_is_dirty_array
    );
}


void end(void)
{
    // Renderer
    calypso_framework_renderer_2d_opengl_deinit();
}

void update(void)
{
    // Update (Input)
    calypso_framework_input_sdl_get_mouse_cursor_xy_f(&_mouse_cursor_x,&_mouse_cursor_y);

    // Update (Spacial Partitioning Grid 2D)
    calypso_framework_benchmark_time_start_benchmark(_benchmark_time_spatial_partitioning_grid_2d);
    calypso_framework_spatial_partitioning_grid_2d_update();
    calypso_framework_benchmark_time_end_benchmark(_benchmark_time_spatial_partitioning_grid_2d);

    // Renderer (Update Viewport)
    if (_renderer_is_dirty)
    {
         // Viewport Width / Height
        _renderer_viewport_width = calypso_framework_app_sdl_get_window_width();
        _renderer_viewport_height = calypso_framework_app_sdl_get_window_height();

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
            calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",_renderer_projection_view_matrix); // Apply Viewport Projection And View
        }


    // Render (Start)
    calypso_framework_renderer_2d_opengl_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_black); // Don't need to  do this every frame but why not
    calypso_framework_renderer_2d_opengl_clear();

    // Render (Render Entities)
    for (int i = 0; i < *_entity_count_max_ptr; i++)
    {
        // Only If Entity Is Created And Not Disabled
        if (!_entity_is_created_array[i] || _entity_is_disabled_array[i])
            continue;

        // Get Color
        const CalypsoFrameworkColorsColorRGBA color = _entity_color_array[i];

        // Model Matrix
        calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_scale(_entity_bounds_x_array[i],_entity_bounds_y_array[i],1,_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_position(_entity_position_x_array[i],_entity_position_y_array[i],0,_renderer_model_matrix);

        // Update Shader Program
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",color.r / 255, color.g / 255, color.b / 255, color.a / 255);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix); // Apply Transform
    
        // Render
        calypso_framework_renderer_2d_opengl_render_quad_immediate();
    }

    // Renderer (End)
    _renderer_is_dirty = false;
}

int main(int argc, char** argv)
{
    // Logging
    calypso_framework_renderer_2d_opengl_set_log_callback(log_msg);
    calypso_framework_app_sdl_set_log_callback(log_msg);
   
    // App
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title("Testbed : Renderer2D");
    calypso_framework_app_sdl_set_events(start,end,update);
    calypso_framework_app_sdl_run();

    // We Done Baby
    return 0;
}