// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

#include <dependencies/SDL2/SDL.h>

// Includes (Calypso Math) 
#include "calypso_framework_math/calypso_framework_math_colors.c"

// Includes (Calypso SDL2) 
#include "calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#include "calypso_framework_sdl2/calypso_framework_sdl2_graphics_renderer.c"

float* _rect_buffer_b;
int _rect_buffer_b_count = 100;

TTF_Font* _font;

double* _camera_position_x_ptr = &_calypso_framework_sdl2_graphics_renderer_render_space_world_offset_x;

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
    calypso_framework_sdl2_graphics_renderer_init(calypso_framework_sdl2_app_get_window_sdl_window_ptr());

    // Rect Buffer
    calypso_framework_sdl2_graphics_renderer_create_rect_buffer_f(&_rect_buffer_b,_rect_buffer_b_count);

    // Rect 1
    for (int i = 0; i < _rect_buffer_b_count; i++)
        calypso_framework_sdl2_graphics_renderer_set_rect_buffer_element_f(_rect_buffer_b,i, rand() % 1024, rand() % 1024 , rand() % 255, rand() % 255);

    // Load Font
    calypso_framework_sdl2_graphics_renderer_load_ttf(&_font,"content/Acme.ttf",24);
}

void end()
{
    // Deinit Renderer
    calypso_framework_sdl2_graphics_renderer_deinit();
}

void update()
{
    // Render (Start)
    calypso_framework_sdl2_graphics_renderer_clear();

    // Render (Entities)
    {
        // Zoom
        calpyso_framework_sdl_graphics_renderer_set_render_scale(2,2);

        // Set To World Space
        calypso_framework_sdl2_graphics_renderer_set_render_space(CALYPSO_FRAMEWORK_SDL2_GRAPHICS_RENDERER_RENDER_SPACE_WORLD);
        *_camera_position_x_ptr += 50 * _calypso_framework_sdl2_app_time_delta_time;

        // Render Rects
        calypso_framework_sdl2_graphics_renderer_set_draw_color_rgb(0,255,0);
        calypso_framework_sdl2_graphics_renderer_render_rect_filled_buffer_f(_rect_buffer_b,_rect_buffer_b_count);

        calypso_framework_sdl2_graphics_renderer_set_draw_color_rgb(0,0,0);
        calypso_framework_sdl2_graphics_renderer_render_rect_buffer_f(_rect_buffer_b,_rect_buffer_b_count);
    }

    // Render (GUI)
    {
        // Undo Zoom
        calpyso_framework_sdl_graphics_renderer_set_render_scale(1,1);

        // Set To World Space
        calypso_framework_sdl2_graphics_renderer_set_render_space(CALYPSO_FRAMEWORK_SDL2_GRAPHICS_RENDERER_RENDER_SPACE_SCREEN);

        // Render GUI (Box)
        calypso_framework_sdl2_graphics_renderer_set_draw_color_rgb(255,0,0);
        calypso_framework_sdl2_graphics_renderer_render_rect_filled_f(10,10,100,100);
        // calypso_framework_sdl2_graphics_renderer_render_rect_i(0,0,100,100);

        // Render GUI (Font)
        calypso_framework_sdl2_graphics_renderer_set_draw_color_rgb(255,255,255);
        calypso_framework_sdl2_graphics_renderer_render_text_ttf_f(_font, "Test",10,10);
    }

    // Render (End)
    calypso_framework_sdl2_graphics_renderer_present();
}

void resize()
{
    calpyso_framework_sdl_graphics_renderer_set_viewport_scaled(0,0,calypso_framework_sdl2_app_get_window_width(),calypso_framework_sdl2_app_get_window_height());
}

int main(int argc, char** argv)
{
    // App (SDL)
    calypso_framework_sdl2_app_set_log_callback(log_msg);
    calypso_framework_sdl2_app_init();
    calypso_framework_sdl2_app_set_window_title("Testbed : Renderer2D (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update, resize);
    calypso_framework_sdl2_app_set_window_resizable(1);
    calypso_framework_sdl2_app_run();

    return 0;
}