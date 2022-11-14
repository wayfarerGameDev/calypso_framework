// Includes
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_colors.c"
#include "calypso_framework_input_sdl.c"
#include "calypso_framework_io.c"
#include "calypso_framework_math_matrix4.c"
#include "calypso_framework_renderer_2d_opengl.c"
#include "calypso_framework_systems.c"

float game_camera_projection_matrix[4][4];
float game_camera_view_matrix[4][4];
unsigned int game_default_shader_program_red;
unsigned int game_default_shader_program_yellow;

void log_printf(const char* log_msg, const Uint8 log_type)
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
    // Setup IO
    calypso_framework_io_set_log_callback(log_printf);

    // Renderer
    {   
        //Set Renderer Log Callback | Init Renderer
        calypso_framework_renderer_2d_opengl_set_log_callback(log_printf);
        calypso_framework_renderer_2d_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());

        //Camera
        calypso_framework_math_matrix_matrix4f_ortho(game_camera_projection_matrix,-8,8,-4.5f,4.5f,-1,1);
        
        // Create Default Shader Program Red
        game_default_shader_program_red = calypso_framework_renderer_2d_opengl_create_default_shader_program();
        calypso_framework_renderer_2d_opengl_set_current_render_shader_program(game_default_shader_program_red);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",1,0,0,1);
        calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_matrix4f("mvp_in",game_camera_projection_matrix); // Apply Camera
        // Create Default Shader Program Yellow

        //game_default_shader_program_yellow = calypso_framework_renderer_2d_opengl_create_default_shader_program();
        //calypso_framework_renderer_2d_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
        //calypso_framework_renderer_2d_opengl_set_current_shader_program_parameter_vec4f("color_in",1,1,0,1);
    }
}

void end(void)
{
    // Stop Renderer
    calypso_framework_renderer_2d_opengl_deinit();

    // :(
    log_printf("Goodbye cruel world :(\n",3);
}

void update(void)
{
    // Data
    const int game_mouse_x = calypso_framework_input_sdl_get_mouse_cursor_x();
    const int game_mouse_y = calypso_framework_input_sdl_get_mouse_cursor_y();
    const int game_delta_time = calypso_framework_app_sdl_get_time_delta_time();

    // Update Input
    calypso_framework_input_sdl_update();

    // Render Start
    calypso_framework_renderer_2d_opengl_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_black); // Don't need to  do this every frame but why not
    calypso_framework_renderer_2d_opengl_clear();

    // Render Entities
    calypso_framework_renderer_2d_opengl_set_current_render_shader_program(game_default_shader_program_red);
    calypso_framework_renderer_2d_opengl_render_box(0,0,0,0);

    //calypso_framework_renderer_2d_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
    //calypso_framework_renderer_2d_opengl_render_triangle(0,0,0,0);

    // Render GUI Here
}

int main(int argc, char** argv)
{
    // Setup | Run App
    calypso_framework_app_sdl_set_log_callback(log_printf);
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_set_events(start,end,update);
    calypso_framework_app_sdl_run();

    return 0;
}