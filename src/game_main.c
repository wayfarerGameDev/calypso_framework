// Includes
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_colors.c"
#include "calypso_framework_input_sdl.c"
#include "calypso_framework_io.c"
#include "calypso_framework_math_matrix4.c"
#include "calypso_framework_renderer_pixel_opengl.c"
#include "calypso_framework_systems.c"

//Game Types
typedef float game_matrix4f_t[4][4];
typedef float game_vec3f_t[3];

// Camera
game_matrix4f_t game_camera_projection_matrix;
game_matrix4f_t game_camera_view_matrix;
game_matrix4f_t game_camera_projection_view_matrix;
game_vec3f_t game_camera_position;

//Model
game_matrix4f_t game_model_matrix;

//Shaders
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
    // Renderer
    {   
        //Set Renderer Log Callback | Init Renderer
        calypso_framework_renderer_pixel_opengl_set_log_callback(log_printf);
        calypso_framework_renderer_pixel_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());
        calypso_framework_renderer_pixel_opengl_set_screen_space_coordinates(1);
    }

    // Shader Programs
    {
        //Create Default Shader Program Red
        game_default_shader_program_red = calypso_framework_renderer_pixel_opengl_create_default_shader_program();
       
        //Create Default Shader Program Yellow
        game_default_shader_program_yellow = calypso_framework_renderer_pixel_opengl_create_default_shader_program();
    }
}

void end(void)
{
    // Stop Renderer
    calypso_framework_renderer_pixel_opengl_deinit();

    // :(
    log_printf("Goodbye cruel world :(\n",3);
}

void update(void)
{
    // Data
    const float viewport_width = calypso_framework_app_sdl_get_window_width();
    const float viewport_height = calypso_framework_app_sdl_get_window_height();
    const int game_mouse_x = calypso_framework_input_sdl_get_mouse_cursor_x();
    const int game_mouse_y = calypso_framework_input_sdl_get_mouse_cursor_y();
    const int game_delta_time = calypso_framework_app_sdl_get_time_delta_time();

    // Update Input
    calypso_framework_input_sdl_update();

    // Camera
    {
        // Camera Position
        game_camera_position[0] = viewport_width / 2;
        game_camera_position[1] = viewport_height / 2;
  
        //calypso_framework_math_matrix_build_projection_ortho_matrix4f(-8,8,-4.5f,4.5f,-1,1,game_camera_projection_matrix); // Vector Screen Space
        calypso_framework_math_matrix_build_projection_ortho_matrix4f(0,viewport_width,0,viewport_height,-1,1,game_camera_projection_matrix); // Pixel Screen Space Coordinates
        calypso_framework_math_matrix_build_identity_matrix4f(game_camera_view_matrix);
        calypso_framework_math_matrix_modify_set_position(game_camera_position[0],game_camera_position[1],game_camera_position[2],game_camera_view_matrix);
        calypso_framework_math_matrix_modify_mult(game_camera_projection_matrix,game_camera_view_matrix,game_camera_projection_view_matrix);
    }

    // Model View
    {
        calypso_framework_math_matrix_build_identity_matrix4f(game_model_matrix);
        calypso_framework_math_matrix_modify_set_position(0,0,0,game_model_matrix);
    }

    // Update Shaders
    {
        // Red Shader
        calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_red);
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_vec4f("color_in",1,0,0,1);
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("model_in",game_model_matrix); // Apply Transform
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",game_camera_projection_view_matrix); // Apply Camera Projection And View
       
        // Yellow Shader
        calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_vec4f("color_in",1,1,0,1);
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("model_in",game_model_matrix); // Transform
        calypso_framework_renderer_pixel_opengl_set_current_shader_program_parameter_matrix4f("projectionView_in",game_camera_projection_view_matrix); // Apply Camera Projection And View
    }

    // Render Start
    calypso_framework_renderer_pixel_opengl_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_black); // Don't need to  do this every frame but why not
    calypso_framework_renderer_pixel_opengl_clear();

    // Render Entities
    calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_red);
    calypso_framework_renderer_pixel_opengl_render_box(0,0,0,0);
    calypso_framework_renderer_pixel_opengl_set_current_render_shader_program(game_default_shader_program_yellow);
    calypso_framework_renderer_pixel_opengl_render_box(0,0,0,0);
}

int main(int argc, char** argv)
{
    // Setup | Run App
    calypso_framework_app_sdl_set_log_callback(log_printf);
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_set_events(start,end,update);
    calypso_framework_app_sdl_run();

    return 0;
}