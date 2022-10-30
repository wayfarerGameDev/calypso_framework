// Includes
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_input_sdl.c"
#include "calypso_framework_renderer_sdl.c"

// Game Data
float _game_delta_time;
char* _game_fps_char;
int _game_mouse_x;
int _game_mouse_y;

float y = 200;
float x = 200;

void start(void)
{
    // Setup Renderer
    calypso_framework_renderer_sdl_init(calypso_framework_app_sdl_get_sdl_window());
    calypso_framework_renderer_set_clear_color_from_color_array(_c_calypso_framework_renderer_sdl_color_array_black);
    calypso_framework_renderer_set_render_color_from_color_array(_c_calypso_framework_renderer_sdl_color_array_green);
}

void load_content(void)
{
    calypso_framework_renderer_sdl_render_add_font_ttf("content/Acme.ttf",20);
}

void end(void)
{
    // Stop Renderer
    calypso_framework_renderer_sdl_deinit();

    // Free Game data
    free (_game_fps_char);

    printf("\033[0;31m"); // Red
    printf("Goodbye cruel world :(\n");
    printf("\033[0;00m"); // White
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
    if (calypso_framework_input_sdl_get_key_up(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_MOUSE_LEFT))
        y -= 100 * _game_delta_time;
    if (calypso_framework_input_sdl_get_key_pressed(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_DOWN))
        y += 100;
    if (calypso_framework_input_sdl_get_key_released(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_LEFT))
        x -= 100;
    if (calypso_framework_input_sdl_get_key_down(CALYPSO_FRAMEWORK_INPUT_SDL_KEYCODE_RIGHT))
        x += 100 * _game_delta_time;
}

void render_start(void)
{
    calypso_framework_renderer_clear();
}

void render_present(void)
{
    calypso_framework_renderer_render_present();
}

void render_entities(void)
{
    // Render Line
    calypso_framework_renderer_set_render_color_from_color_array(_c_calypso_framework_renderer_sdl_color_array_green);
    for (int i = 0; i < 1000; i++)
    {
        calypso_framework_renderer_sdl_draw_line(x + 300 + i,200 + y,x + 500,700 + y);
    }
}

void render_gui(void)
{
    calypso_framework_renderer_set_render_color_from_color_array(_c_calypso_framework_renderer_sdl_color_array_white);

    _game_fps_char = calypso_framework_app_sdl_get_time_fps_as_string();
    calypso_framework_renderer_sdl_render_draw_text_ttf( _game_fps_char,10,10);
}

int main(int argc, char** argv)
{
    // Setup And Run App
    calypso_framework_app_sdl_init();
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_add_system(start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(load_content,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(end,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN);
    calypso_framework_app_sdl_add_system(update,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE);
    calypso_framework_app_sdl_add_system(render_start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE);
    calypso_framework_app_sdl_add_system(render_present,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE);
    calypso_framework_app_sdl_add_system(render_entities,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE);
    calypso_framework_app_sdl_add_system(render_gui,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE);
    calypso_framework_app_sdl_run();

    return 0;
}