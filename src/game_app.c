#pragma once

#include "game_includes.c"

// Events
typedef void (*game_app_event_t)(void);

void game_app(char* title, game_app_event_t startup, game_app_event_t shutdown, game_app_event_t update)
{
    // App
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title(title);
    calypso_framework_app_sdl_set_events(startup,shutdown,update);
    calypso_framework_app_sdl_run();
}