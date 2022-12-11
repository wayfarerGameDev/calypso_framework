// Includes
#include "game_includes.c"

void end(void)
{
    // :(
    game_logger_log_printf("Goodbye cruel world :(\n",3);
}

int main(int argc, char** argv)
{
    calypso_framework_math_random_rand_set_seed(50);
    int r = calypso_framework_math_random_rand_xorshift_int();
    printf("%d\n", r);
    
    calypso_framework_math_random_rand_set_seed(51);
    float f = calypso_framework_math_random_rand_xorshift_float();
    printf("%f\n", f);

    // Logging
    game_systems_set_log_callback(game_logger_log_printf);
    game_renderer_set_log_callback(game_logger_log_printf);
    calypso_framework_app_sdl_set_log_callback(game_logger_log_printf);
   
    // Systems
    game_systems_add_system(game_renderer_start,GAME_SYSTEMS_SYSTEM_STAGE_STARTUP); // Renderer
    game_systems_add_system(game_renderer_end,GAME_SYSTEMS_SYSTEM_STAGE_SHUTDOWN);
    game_systems_add_system(game_renderer_update_start,GAME_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE);
    game_systems_add_system(game_renderer_update,GAME_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE);
    game_systems_add_system(game_renderer_update_end,GAME_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE);
    game_systems_add_system(game_entities_player_input,GAME_SYSTEMS_SYSTEM_STAGE_EARLY_UPDATE); // Entites
    game_systems_add_system(game_entities_render,GAME_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE);

    // App
    game_app("Game",game_systems_do_startup_stage_systems,game_systems_do_shutdown_stage_systems,game_systems_do_update_stage_systems);

    return 0;
}