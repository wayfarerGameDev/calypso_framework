// Includes
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_colors.c"
#include "calypso_framework_input_sdl.c"
#include "calypso_framework_renderer_2d.c"

// Game Data
float _game_delta_time;
char* _game_fps_char;
int _game_mouse_x;
int _game_mouse_y;

float y = 200;
float x = 200;

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
    // Setup Renderer
    calypso_framework_renderer_2d_set_log_callback(log_printf);
    calypso_framework_renderer_2d_init(calypso_framework_app_sdl_get_open_gl_proc_address());
}

void load_content(void)
{
}

void end(void)
{
    // Stop Renderer
    calypso_framework_renderer_2d_deinit();

    // Free Game data
    free(_game_fps_char);

    // :(
    log_printf("Goodbye cruel world :(\n",3);
}

void update(void)
{
    // Get Game Delta Time From App
    _game_delta_time = calypso_framework_app_sdl_get_time_delta_time();

    // Update Input
    calypso_framework_input_sdl_update();

    _game_mouse_x = calypso_framework_input_sdl_get_mouse_cursor_x();
    _game_mouse_y = calypso_framework_input_sdl_get_mouse_cursor_y();

    // Move Lines
    if (calypso_framework_input_sdl_get_key_up(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_UP))
        y -= 100 * _game_delta_time;
    if (calypso_framework_input_sdl_get_key_pressed(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_DOWN))
        y += 100;
    if (calypso_framework_input_sdl_get_key_released(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_LEFT))
        x -= 100;
    if (calypso_framework_input_sdl_get_key_down(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_RIGHT))
        x += 100 * _game_delta_time;
}

void render(void)
{
    // Data
    const int w = calypso_framework_app_sdl_get_window_width();
    const int h = calypso_framework_app_sdl_get_window_width();

    // Start
    calypso_framework_renderer_2d_set_clear_color_by_byte_color_array(_c_calypso_framework_colors_color_byte_array_pink); // Don't need to do this every frame but why not
    calypso_framework_renderer_2d_set_viewport(0,0,w,h); // Don't need to do this every frame but why not
    calypso_framework_renderer_2d_clear();

    // Entities Here
    //calypso_framework_renderer_2d_draw_line();

    // GUI Here

    
}

int main(int argc, char** argv)
{
    // Setup And Run App
    calypso_framework_app_sdl_set_log_callback(log_printf);
    calypso_framework_app_sdl_pre_init_opengl_context(CALYPSO_FRAMEWORK_RENDERER_GL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_GL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_GL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_init_window();
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_add_system(start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(load_content,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(end,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN);
    calypso_framework_app_sdl_add_system(update,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE);
    calypso_framework_app_sdl_add_system(render,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE);
    calypso_framework_app_sdl_run();

    return 0;
}