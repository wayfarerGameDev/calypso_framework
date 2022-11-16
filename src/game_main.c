// Includes
#include "game_includes.c"

void end(void)
{
    // :(
    game_logger_log_printf("Goodbye cruel world :(\n",3);
}

int main(int argc, char** argv)
{
    // Logging
    game_renderer_set_log_callback(game_logger_log_printf);
    calypso_framework_app_sdl_set_log_callback(game_logger_log_printf);
   
    // Systems
    calypso_framework_systems_add_system(game_renderer_start,CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_STARTUP);
    calypso_framework_systems_add_system(game_renderer_end,CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_SHUTDOWN);
    calypso_framework_systems_add_system(end,CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_SHUTDOWN);
    calypso_framework_systems_add_system(game_renderer_update,CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_UPDATE);

    // App
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title("Game");
    calypso_framework_app_sdl_set_events(calypso_framework_systems_do_startup_stage_systems,calypso_framework_systems_do_shutdown_stage_systems,calypso_framework_systems_do_update_stage_systems);
    calypso_framework_app_sdl_run();

    return 0;
}