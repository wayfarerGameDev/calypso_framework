// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

// Includes (Calypso Math) 
#include "calypso_framework_math/calypso_framework_math_colors.c"

// Includes (Calypso SDL) 
#include "calypso_framework_sdl/calypso_framework_sdl_app.c"
#include "calypso_framework_sdl/calypso_framework_sdl_input.c"
#include "calypso_framework_sdl/calypso_framework_sdl_renderer.c"

void log_msg(const char* log_msg, const uint8_t log_type)
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

void start()
{
    // Init Renderer
    calypso_framework_sdl_renderer_init(calypso_framework_sdl_app_get_window_sdl_window());
}

void end()
{
    // Deinit Renderer
    calypso_framework_sdl_renderer_deinit();
}

void update()
{
    calypso_framework_sdl_renderer_clear();
    calypso_framework_sdl_renderer_present();
}

void resize()
{

}

int main(int argc, char** argv)
{
    // App (SDL)
    calypso_framework_sdl_app_set_log_callback(log_msg);
    calypso_framework_sdl_app_init();
    calypso_framework_sdl_app_set_window_title("Testbed : Renderer2D (SDL)");
    calypso_framework_sdl_app_set_events(start,end,update);
    calypso_framework_sdl_app_run();

    return 0;
}