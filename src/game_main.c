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
    game_systems_set_log_callback(game_logger_log_printf);
    game_renderer_set_log_callback(game_logger_log_printf);
    calypso_framework_app_sdl_set_log_callback(game_logger_log_printf);
   
    // Systems
    game_systems_add_system(game_renderer_start,GAME_SYSTEMS_SYSTEM_STAGE_STARTUP);
    game_systems_add_system(game_renderer_end,GAME_SYSTEMS_SYSTEM_STAGE_SHUTDOWN);
    game_systems_add_system(end,GAME_SYSTEMS_SYSTEM_STAGE_SHUTDOWN);
    game_systems_add_system(game_renderer_update,GAME_SYSTEMS_SYSTEM_STAGE_UPDATE);

    // App
    game_app("Game",game_systems_do_startup_stage_systems,game_systems_do_shutdown_stage_systems,game_systems_do_update_stage_systems);

    return 0;
}