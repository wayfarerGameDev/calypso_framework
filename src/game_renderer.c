#pragma once

// Includes
#include "game_includes.c"

// Logging Callback
typedef void (*game_renderer_log_callback_t)(const char* log_msg, const Uint8 log_type);

// Identity Matrix
float game_renderer_identity_matrix[4][4];

// Viewport
float game_renderer_viewport_projection_matrix[4][4];
float game_renderer_viewport_view_matrix[4][4];
float game_renderer_viewport_projection_view_matrix[4][4];
float game_renderer_viewport_position_x;
float game_renderer_viewport_position_y;
float game_renderer_viewport_scale_x;
float game_renderer_viewport_scale_y;

//Model
float game_model_matrix[4][4];

//Shaders
unsigned int game_default_shader_program_red;
unsigned int game_default_shader_program_yellow;

void game_renderer_set_log_callback(game_renderer_log_callback_t log_callback)
{
    calypso_framework_renderer_pixel_opengl_set_log_callback(log_callback);
}

void game_renderer_start()
{
    calypso_framework_renderer_pixel_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());

    // Identity Matrix
    calypso_framework_math_matrix_build_identity_matrix4f(game_renderer_identity_matrix);

    // Shader Programs
    {
        //Create Default Shader Program Red
        game_default_shader_program_red = calypso_framework_renderer_pixel_opengl_create_default_shader_program();
       
        //Create Default Shader Program Yellow
        game_default_shader_program_yellow = calypso_framework_renderer_pixel_opengl_create_default_shader_program();
    }
}

void game_renderer_end()
{
    calypso_framework_renderer_pixel_opengl_deinit();
}

void game_renderer_update_viewport()
{
    // Viewport Width / Height
    const float viewport_width = calypso_framework_app_sdl_get_window_width();
    const float viewport_height = calypso_framework_app_sdl_get_window_height();

    // Viewport Transform
    game_renderer_viewport_position_x = viewport_width / 2;
    game_renderer_viewport_position_y = viewport_height / 2;
    game_renderer_viewport_scale_x = 0.3f;
    game_renderer_viewport_scale_y = 0.3f;

    // Viewport Matrix (Projection And View)
    calypso_framework_math_matrix_build_projection_ortho_matrix4f(0,viewport_width,0,viewport_height,-1,1,game_renderer_viewport_projection_matrix);
    calypso_framework_math_matrix_build_identity_matrix4f(game_renderer_viewport_view_matrix);
    calypso_framework_math_matrix_modify_set_scale(game_renderer_viewport_scale_x,game_renderer_viewport_scale_y,1,game_renderer_viewport_view_matrix);
    calypso_framework_math_matrix_modify_set_position(game_renderer_viewport_position_x,game_renderer_viewport_position_y,0,game_renderer_viewport_view_matrix);
    calypso_framework_math_matrix_modify_mult(game_renderer_viewport_projection_matrix,game_renderer_viewport_view_matrix,game_renderer_viewport_projection_view_matrix);
}

void game_renderer_update_shaders()
{
     // Red Shader
    calypso_framework_math_matrix_build_identity_matrix4f(game_model_matrix);
    calypso_framework_math_matrix_modify_set_scale(100,100,1,game_model_matrix);
    calypso_framework_math_matrix_modify_set_position(0,0,0,game_model_matrix);

    calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_red);
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_vec4f("color_in",1,0,0,1);
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("model_in",game_model_matrix); // Apply Transform
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",game_renderer_viewport_projection_view_matrix); // Apply Viewport Projection And View
       
    // Yellow Shader
    calypso_framework_math_matrix_build_identity_matrix4f(game_model_matrix);
    calypso_framework_math_matrix_modify_set_scale(50,25,1,game_model_matrix);
    calypso_framework_math_matrix_modify_set_position(50,50,-1,game_model_matrix);

    calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_vec4f("color_in",1,1,0,1);
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("model_in",game_model_matrix); // Transform
    calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",game_renderer_viewport_projection_view_matrix); // Apply Viewport Projection And View
}

void game_renderer_update()
{
    game_renderer_update_viewport();
    game_renderer_update_shaders();

    // Render Start
    calypso_framework_renderer_pixel_opengl_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_black); // Don't need to  do this every frame but why not
    calypso_framework_renderer_pixel_opengl_clear();

    // Render Entities
    {
        calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_red);
        calypso_framework_renderer_pixel_opengl_render_quad();
            
        calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
        calypso_framework_renderer_pixel_opengl_render_quad();
    }
}