#pragma once

// Includes
#include "game_includes.c"

// Logging Callback
typedef void (*game_renderer_log_callback_t)(const char* log_msg, const Uint8 log_type);

// Identity Matrix
float _game_renderer_identity_matrix[4][4];

// Viewport
float _game_renderer_viewport_projection_matrix[4][4];
float _game_renderer_viewport_view_matrix[4][4];
float _game_renderer_viewport_projection_view_matrix[4][4];
float _game_renderer_viewport_position_x;
float _game_renderer_viewport_position_y;
float _game_renderer_viewport_scale_x;
float _game_renderer_viewport_scale_y;

// Is Dirty
bool _game_renderer_is_dirty;

// Model Matrix
float _game_renderer_model_matrix[4][4];

// Shader Programs
unsigned int _game_renderer_default_shader_program;
unsigned int* _game_renderer_shader_programs;
unsigned int _game_renderer_shader_programs_count;

void game_renderer_set_log_callback(game_renderer_log_callback_t log_callback)
{
    calypso_framework_renderer_pixel_opengl_set_log_callback(log_callback);
}

unsigned int game_renderer_get_default_shader_program()
{
    return _game_renderer_default_shader_program;
}

void game_renderer_set_render_shader_program(unsigned int shader_program)
{
    calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(shader_program);
}

void game_renderer_set_current_shader_program_color(const Uint8 color[4])
{
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_vec4f("color_in",color[0] / 255, color[1] / 255, color[2] / 255, color[3] / 255); // Apply Color   
}

void game_renderer_start()
{
    // Init Renderer
    calypso_framework_renderer_pixel_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());

    // Identity Matrix
    calypso_framework_math_matrix_build_identity_matrix4f(_game_renderer_identity_matrix);

    // Default Shader Program
    _game_renderer_default_shader_program = calypso_framework_renderer_pixel_opengl_create_default_shader_program();
    _game_renderer_shader_programs_count++;
    _game_renderer_shader_programs = realloc(_game_renderer_shader_programs,_game_renderer_shader_programs_count * sizeof(unsigned int));
    _game_renderer_shader_programs[_game_renderer_shader_programs_count - 1] = _game_renderer_default_shader_program;
    game_renderer_set_render_shader_program(_game_renderer_default_shader_program);
    game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_white);

    // Is Dirty By Default
    _game_renderer_is_dirty = true;
}

void game_renderer_end()
{
    calypso_framework_renderer_pixel_opengl_deinit();
}

void game_renderer_update_start()
{
     // Render Start
    calypso_framework_renderer_pixel_opengl_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_black); // Don't need to  do this every frame but why not
    calypso_framework_renderer_pixel_opengl_clear();
}

void game_renderer_update_end()
{
    // Viewport dirty
    _game_renderer_is_dirty = false;
}

void game_renderer_update_viewport()
{
    if (_game_renderer_is_dirty)
    {
        // Viewport Width / Height
        const float viewport_width = calypso_framework_app_sdl_get_window_width();
        const float viewport_height = calypso_framework_app_sdl_get_window_height();

        // Viewport Transform
        _game_renderer_viewport_position_x = viewport_width / 2;
        _game_renderer_viewport_position_y = viewport_height / 2;
        _game_renderer_viewport_scale_x = 0.3f;
        _game_renderer_viewport_scale_y = 0.3f;

        // Viewport Matrix (Projection And View)
        calypso_framework_math_matrix_build_projection_ortho_matrix4f(0,viewport_width,0,viewport_height,-1,1,_game_renderer_viewport_projection_matrix);
        calypso_framework_math_matrix_build_identity_matrix4f(_game_renderer_viewport_view_matrix);
        calypso_framework_math_matrix_modify_set_scale(_game_renderer_viewport_scale_x,_game_renderer_viewport_scale_y,1,_game_renderer_viewport_view_matrix);
        calypso_framework_math_matrix_modify_set_position(_game_renderer_viewport_position_x,_game_renderer_viewport_position_y,0,_game_renderer_viewport_view_matrix);
        calypso_framework_math_matrix_modify_mult(_game_renderer_viewport_projection_matrix,_game_renderer_viewport_view_matrix,_game_renderer_viewport_projection_view_matrix);
    }
}

void game_renderer_update_shaders()
{
    if (_game_renderer_is_dirty)
    {
        for (int i = 0; i < _game_renderer_shader_programs_count; i++)
        {
            unsigned int shader_program = _game_renderer_shader_programs[i];
            calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(shader_program);
            calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",_game_renderer_viewport_projection_view_matrix); // Apply Viewport Projection And View
        }
    }
}

void game_renderer_update()
{
    game_renderer_update_viewport();
    game_renderer_update_shaders();
}

void game_renderer_render_sprite(const float pos_x, const float pos_y, const float scale_x, const float scale_y)
{
    // Model Matrix
    calypso_framework_math_matrix_build_identity_matrix4f(_game_renderer_model_matrix);
    calypso_framework_math_matrix_modify_set_scale(scale_x,scale_y,1,_game_renderer_model_matrix);
    calypso_framework_math_matrix_modify_set_position(pos_x,pos_y,0,_game_renderer_model_matrix);

    // Update Shader Program
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("model_in",_game_renderer_model_matrix); // Apply Transform
    
    // Render
    calypso_framework_renderer_pixel_opengl_render_quad();
}