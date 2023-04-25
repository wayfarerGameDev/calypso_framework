// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

// Calypso (SDL or GLFW)
#define USE_GLFW_OVER_SDL 1
#if(USE_GLFW_OVER_SDL)
#include "calypso_framework/calypso_framework_app_glfw.c"
#include "calypso_framework/calypso_framework_input_glfw.c"
#else
#include "calypso_framework/calypso_framework_app_sdl.c"
#include "calypso_framework/calypso_framework_input_sdl.c"
#endif

// Calypso
#include "calypso_framework/calypso_framework_colors.c"
#include "calypso_framework/calypso_framework_io.c"
#include "calypso_framework/calypso_framework_math_matrix4.c"
#include "calypso_framework/calypso_framework_math_random.c"
#include "calypso_framework/calypso_framework_renderer_pixel_opengl.c"

// App Properties
const int _window_width  = 800;
const int _window_height = 800;
int _pixel_count_y = 800 / 8;
int _pixel_count_x = 800 / 8;

calypso_framework_renderer_pixel_opengl_pixel_buffer_t pixel_buffer_foreground;
calypso_framework_renderer_pixel_opengl_pixel_buffer_t pixel_buffer_midground;

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

void start(void)
{
    // Create Pixel Buffer (Foreground | Midground)
    calypso_framework_renderer_pixel_opengl_create_pixel_buffer(&pixel_buffer_foreground,_pixel_count_x,_pixel_count_y);
    calypso_framework_renderer_pixel_opengl_create_pixel_buffer(&pixel_buffer_midground,_pixel_count_x,_pixel_count_y);

    // Init Renderer
    {
        // _pixel_count_x = calypso_framework_app_glfw_get_window_width();
        // _pixel_count_y = calypso_framework_app_glfw_get_window_height();

        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        calypso_framework_renderer_pixel_opengl_init(calypso_framework_app_glfw_get_open_gl_proc_address(),_pixel_count_x,_pixel_count_y);
        #else
        calypso_framework_renderer_pixel_opengl_init(calypso_framework_app_sdl_get_open_gl_proc_address());
        #endif
    }    
}


void end(void)
{
    // Renderer
    calypso_framework_renderer_pixel_opengl_deinit();
}


void update(void)
{
    // Set Pixel Buffer Pixel Data
    for (int x = 0; x < _pixel_count_x; x++)
        for (int y = 0; y < _pixel_count_y; y++)
        {
            calypso_framework_renderer_pixel_opengl_renderer_set_pixel_buffer_pixel(&pixel_buffer_foreground,x,y,rand() % 255,rand() % 255,rand() % 255);
            calypso_framework_renderer_pixel_opengl_renderer_set_pixel_buffer_pixel(&pixel_buffer_midground,x,y,255,0,0);
        }

    // Render
    {        
        calypso_framework_renderer_pixel_opengl_renderer_clear();
        calypso_framework_renderer_pixel_opengl_render_pixel_buffer(&pixel_buffer_foreground);
        // calypso_framework_renderer_pixel_opengl_render_pixel_buffer(&pixel_buffer_midground);
    }
}

void resize(void)
{
    // Resize Renderer
    calypso_framework_renderer_pixel_opengl_renderer_resize(calypso_framework_app_glfw_get_window_width(),calypso_framework_app_glfw_get_window_height());
}

int main(int argc, char** argv)
{
    // Logging
    calypso_framework_renderer_pixel_opengl_set_log_callback(log_msg);

    // App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_app_glfw_set_log_callback(log_msg);
    calypso_framework_app_glfw_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_glfw_set_window_title("Testbed : RendererPixel (GLFW)");
    calypso_framework_app_glfw_set_events(start,end,update, resize);
    calypso_framework_app_glfw_set_window_size(_window_width,_window_height);
    calypso_framework_app_glfw_run();
    
    #else
    // App (SDL)
    calypso_framework_app_sdl_set_log_callback(log_msg);
    calypso_framework_app_sdl_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_PIXEL_OPENGL_CONTEXT_PROFILE);
    calypso_framework_app_sdl_set_window_title("Testbed : RendererPixel (SDL)");
    calypso_framework_app_sdl_set_events(start,end,update);
    calypso_framework_app_sdl_run();
    #endif

   
    // We Done Baby
    return 0;
}