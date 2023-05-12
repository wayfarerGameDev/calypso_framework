// Logging
#define CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
#include "../calypso_framework_misc/calypso_framework_log.c"

// Calypso (SDL or GLFW)
#define USE_GLFW_OVER_SDL 1
#if(USE_GLFW_OVER_SDL)
#include "../calypso_framework_glfw/calypso_framework_glfw_app.c"
#include "../calypso_framework_glfw/calypso_framework_glfw_input.c"
#else
#include "../calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "../calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#endif

// Calypso (Render Pipeline | Game)
#include "example_render_pipeline.c"
#include "example_render_pipeline_game.c"

void start(void)
{
    // Init Render Pipleine (GLFW)
    #if(USE_GLFW_OVER_SDL)
    example_render_pipeline_init(calypso_framework_glfw_app_get_open_gl_proc_address());

    // Init Render Pipleine (SDL2)
    #else
    example_render_pipeline_init(calypso_framework_sdl2_app_get_open_gl_proc_address());
    #endif

    // Start Game
    example_render_pipeline_game_start();
}

void end(void)
{
    // End Game
    example_render_pipeline_game_end();
}

void update(void)
{
    // Get Window Width / Height (GLFW)
    #if(USE_GLFW_OVER_SDL)
    const int window_width = calypso_framework_glfw_app_get_window_width();
    const int window_height = calypso_framework_glfw_app_get_window_height();
    
    // Get Window Width / Height (SDL2)
    #else
    const int window_width = calypso_framework_sdl2_app_get_window_width();
    const int window_height = calypso_framework_sdl2_app_get_window_height();
    #endif

    // Update Game
    example_render_pipeline_game_update();

    // Update Render Pipeline | Render Game
    example_render_pipeline_update(example_render_pipeline_game_draw_world,example_render_pipeline_game_draw_screen,window_width,window_height);
}

void resize(void)
{
}

int main(int argc, char** argv)
{
    // App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_CONTEXT_PROFILE);
    calypso_framework_glfw_app_set_title("Example Render Pipeline (GLFW)");
    calypso_framework_glfw_app_set_events(start,end,update,resize);
    calypso_framework_glfw_app_set_window_resizable(1);
    calypso_framework_glfw_app_run();
    
    #else
    // App (SDL)
    calypso_framework_sdl2_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_CONTEXT_PROFILE);
    calypso_framework_sdl2_app_set_title("Example Render Pipeline (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update,resize);
    calypso_framework_sdl2_app_set_window_resizable(1);
    calypso_framework_sdl2_app_run();
    #endif
  
    // We Done Baby
    return 0;
}