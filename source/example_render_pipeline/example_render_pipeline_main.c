#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Logging
#define CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
#include "../calypso_framework_misc/calypso_framework_log.c"

// Calypso (Math)
#include "../calypso_framework_math/calypso_framework_math_time.c"

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


#define SPRITE_COUNT 108216
example_render_pipeline_sprite_batch_t _sprite_batch;
example_render_pipeline_texture_t _example_renderer_pipeline_game_texture;
int _window_width, _window_height;
float position_x_buffer[SPRITE_COUNT];
float position_y_buffer[SPRITE_COUNT];
float position_z_buffer[SPRITE_COUNT];

void start(void)
{
    // Load Content
    _example_renderer_pipeline_game_texture = example_render_pipeline_load_texture_file_tga("content/testbed/test.tga");

    // Get Window Width
    {
         // Get Window Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        _window_width = calypso_framework_glfw_app_get_window_width();
        _window_height = calypso_framework_glfw_app_get_window_height();

        // Get Window Width / Height (SDL2)
        #else
        _window_width = calypso_framework_sdl2_app_get_window_width();
        _window_height = calypso_framework_sdl2_app_get_window_height();
        #endif
    }

    // Create Spritebatch
    _sprite_batch = example_render_pipeline_sprite_batch_create(SPRITE_COUNT);
}

void end(void)
{
}

void update(void)
{
    // Update Time (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_math_time_update(glfwGetTime());
    calypso_framework_glfw_app_set_title(calypso_framework_math_time_fps_as_string());

    // Update Time (SDL2)
    #else
    calypso_framework_math_time_update((double)SDL_GetTicks64() / 1000.0);
    calypso_framework_sdl2_app_set_title(calypso_framework_math_time_fps_as_string());
    #endif
    
    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        position_x_buffer[i] = rand() % 100 - 50;
        position_y_buffer[i] = rand() % 100 - 50;
        position_z_buffer[i] = 0;
        example_render_pipeline_sprite_batch_set_element(&_sprite_batch,i,position_x_buffer[i],position_y_buffer[i],position_z_buffer[i]);
    }
    example_render_pipeline_sprite_batch_build(&_sprite_batch);


    // Get Window Width
    {
         // Get Window Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        _window_width = calypso_framework_glfw_app_get_window_width();
        _window_height = calypso_framework_glfw_app_get_window_height();

        // Get Window Width / Height (SDL2)
        #else
        _window_width = calypso_framework_sdl2_app_get_window_width();
        _window_height = calypso_framework_sdl2_app_get_window_height();
        #endif
    }

    // Update Render Pipeline | Render Game
    example_render_pipeline_update(_window_width,_window_height);
}

void render_world(void)
{
     // Render Quads (Immediate)
    {
        // Cadet Blue
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_cadet_blue);
        example_render_pipeline_set_render_scale(100,100);
        example_render_pipeline_render_rect(100,100,20);

        // Cyan
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_cyan);
        example_render_pipeline_set_render_scale(50,50);
        example_render_pipeline_render_rect(200,100,25);
    }

    // Render Quads (Immediate)(Wireframe)
    {
        // Enable Wireframe
        example_render_pipeline_set_wireframe_mode(1);

        // Cadet Blue
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_red);
        example_render_pipeline_set_render_scale(100,100);
        example_render_pipeline_render_rect(100,100,20 + 1);

        // Cyan
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_red);
        example_render_pipeline_set_render_scale(50,50);
        example_render_pipeline_render_rect(200,100,25 + 1);

        // Disable Wireframe
        example_render_pipeline_set_wireframe_mode(0);
    }

    // Render Quads (Batched)
    {
        // Render Color White
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_white);
 
        // Bind Texture
        example_render_pipeline_bind_texture(&_example_renderer_pipeline_game_texture,0);

        // Set Render Scale
        example_render_pipeline_set_render_scale(3,3);

        // Spritebatch
        example_render_pipeline_sprite_batch_apply_shaders();
        example_render_pipeline_sprite_batch_draw(&_sprite_batch,SPRITE_COUNT);

        // Unbind Texture
        example_render_pipeline_unbind_texture();
    }
}

void render_screen(void)
{

}

void render_end(void)
{
    // Swap Buffers (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_set_swap_buffers();

    // Swap Buffers (SDL)
    #else
    calypso_framework_sdl2_app_set_swap_buffers();
    #endif
}

void resize(void)
{
}

int main(int argc, char** argv)
{
    // Init App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_CONTEXT_PROFILE);
    calypso_framework_glfw_app_set_title("Example Render Pipeline (GLFW)");
    calypso_framework_glfw_app_set_events(start,end,update,resize);
    calypso_framework_glfw_app_set_window_resizable(1);
    calypso_framework_glfw_app_set_swap_interval(0);

    // Init App (SDL)
    #else
    calypso_framework_sdl2_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_CONTEXT_PROFILE);
    calypso_framework_sdl2_app_set_title("Example Render Pipeline (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update,resize);
    calypso_framework_sdl2_app_set_window_resizable(1);
    calypso_framework_sdl2_app_set_swap_interval(0);
    #endif

    // Init Render Pipleine (GLFW)
    #if(USE_GLFW_OVER_SDL)
    example_render_pipeline_init(calypso_framework_glfw_app_get_open_gl_proc_address(),render_world,render_screen,render_end);

    // Init Render Pipleine (SDL2)
    #else
    example_render_pipeline_init(calypso_framework_sdl2_app_get_open_gl_proc_address(),render_world,render_screen,render_end);
    #endif

    // Run App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_run();
    
    // Run App (SDL)
    #else
    calypso_framework_sdl2_app_run();
    #endif
  
    // We Done Baby
    return 0;
}