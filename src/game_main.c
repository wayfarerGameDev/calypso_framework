// Includes
#include<stdio.h>
#include<conio.h>
#include "calypso_framework_app_sdl.c"

// Game Data
float _game_delta_time;

void early_start(void)
{
}

void late_start(void)
{
}

void start(void)
{
}

void early_end(void)
{
}

void late_end(void)
{
}

void end(void)
{
}

void early_update(void)
{
    _game_delta_time = calypso_framework_app_sdl_get_time_delta_time();
}

void late_update(void)
{
}

void update(void)
{
    //calypso_framework_app_sdl_remove_system(early_update);
    //calypso_framework_app_sdl_remove_system(late_update);

    //calypso_framework_app_sdl_clear_systems();
    //calypso_framework_app_sdl_remove_system(early_update);
    //calypso_framework_app_sdl_remove_system(early_update);

    printf("update\n");
}

int main(int argc, char** argv)
{
    // Setup And Run App
    calypso_framework_app_sdl_init();
    calypso_framework_app_sdl_set_window_title("Game");
    //calypso_framework_app_sdl_set_time_frame_target_rate(40); // Uncapped By Default
    calypso_framework_app_sdl_add_system(early_start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP);
    calypso_framework_app_sdl_add_system(late_start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP);
    calypso_framework_app_sdl_add_system(start,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP);
    calypso_framework_app_sdl_add_system(early_end,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN);
    calypso_framework_app_sdl_add_system(late_end,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN);
    calypso_framework_app_sdl_add_system(end,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN);
    calypso_framework_app_sdl_add_system(early_update,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE);
    calypso_framework_app_sdl_add_system(late_update,CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE);
    calypso_framework_app_sdl_run();

    // No Longer Running
    return 0;
}