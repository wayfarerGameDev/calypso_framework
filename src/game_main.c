// Includes
#include "calypso_framework_app_sdl.c"
#include "calypso_framework_renderer_sdl.c"

// Game Data
float _game_delta_time;

void startup(void)
{
    // Setup Renderer
    calypso_framework_renderer_sdl_init(calypso_framework_app_sdl_get_sdl_window());
    calypso_framework_renderer_set_clear_color_from_color_array(_c_calypso_framework_renderer_sdl_color_array_cornflower_blue);
}

void shutdown(void)
{
}

void update(void)
{
    // Get Game Delta Time From App
    _game_delta_time = calypso_framework_app_sdl_get_time_delta_time();
}

void render(void)
{
    // Clear Renderer
    calypso_framework_renderer_clear();
    calypso_framework_renderer_render_present();
}

int main(int argc, char** argv)
{
    // Setup And Run App
    calypso_framework_app_sdl_init();
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_add_system(startup,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(shutdown,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN);
    calypso_framework_app_sdl_add_system(update,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE);
    calypso_framework_app_sdl_add_system(render,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE);
    calypso_framework_app_sdl_run();

    // No Longer Running
    return 0;
}