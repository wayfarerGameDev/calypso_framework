// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

// Includes (Calypso) 
#include "calypso_framework_gui/calypso_framework_imgui_minimal.c"
#include "calypso_framework_math/calypso_framework_math_colors.c"

// Includes (Calypso SDL2) 
#include "calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#include "calypso_framework_sdl2/calypso_framework_sdl2_renderer.c"

float* _rect_buffer_b;
int _rect_buffer_b_count = 200;

int _window_width;
int _window_height;

double* _camera_position_x_ptr = &_calypso_framework_sdl2_renderer_render_space_world_offset_x;

void* _image;
void* _font_text;
void* _font_icons;

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
    calypso_framework_sdl2_renderer_init(calypso_framework_sdl2_app_get_window_sdl2_window_ptr());
    calypso_framework_sdl2_renderer_set_log_callback(log_msg);

    // Rect Buffer
    calypso_framework_sdl2_renderer_create_rect_buffer_f(&_rect_buffer_b,_rect_buffer_b_count);

    // Rect 1
    for (int i = 0; i < _rect_buffer_b_count; i++)
        calypso_framework_sdl2_renderer_set_rect_buffer_element_f(_rect_buffer_b,i, rand() % 1024, rand() % 1024 , rand() % 255, rand() % 255);

    // Imgui(Minimal)
    {
        // Set Callbacks
        calypso_framework_imgui_minimal_set_callbacks(
            calypso_framework_sdl2_renderer_set_draw_color_rgb_hex,
            calypso_framework_sdl2_renderer_set_font_current,
            calypso_framework_sdl2_renderer_render_texture_f,
            calypso_framework_sdl2_renderer_render_texture_sized_f,
            calypso_framework_sdl2_renderer_render_rect_filled_f,
            calypso_framework_sdl2_renderer_render_text_ttf_f,
            calypso_framework_sdl2_renderer_get_text_width_i,
            calypso_framework_sdl2_renderer_get_text_height_i,
            calypso_framework_sdl2_app_get_mouse_button_left_state_is_pressed);

        // Set Bindnigs
        calypso_framework_imgui_minimal_set_bindings(calypso_framework_sdl2_app_get_mouse_position_ptr());    
    }

    // Load Font
    calypso_framework_sdl2_renderer_load_font_ttf(&_font_text,"content/fonts/OpenSans_Regular.ttf",13);
    calypso_framework_sdl2_renderer_load_font_ttf(&_font_icons,"content/fonts/windows_icons.ttf",13);

    // 
    calypso_framework_sdl2_renderer_load_texture(&_image,"content/images/app_icon.ico");

    // Maxamize Window
    calypso_framework_sdl2_app_maxamize_window();
}

void end()
{
    // Deinit Renderer
    calypso_framework_sdl2_renderer_deinit();
}

void update()
{
    // Get Properties
    {
        _window_width = calypso_framework_sdl2_app_get_window_width();
        _window_height = calypso_framework_sdl2_app_get_window_height();
    }

    // Update Input
    calypso_framework_sdl2_input_update();

    // Render (Start)
    calypso_framework_sdl2_renderer_set_clear_color_rgb_hex(0x101010);
    calypso_framework_sdl2_renderer_clear();

    // Render (Entities)
    {
        // Zoom
        calpyso_framework_sdl2_renderer_set_render_scale(2,2);
                
        // Set To World Space
        calypso_framework_sdl2_renderer_set_render_space(CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_WORLD);
        *_camera_position_x_ptr += 5 * _calypso_framework_sdl2_app_time_delta_time;

        // Render Rects
        calypso_framework_sdl2_renderer_set_draw_color_rgb(0,255,0);
        calypso_framework_sdl2_renderer_render_rect_filled_buffer_f(_rect_buffer_b,_rect_buffer_b_count);

        calypso_framework_sdl2_renderer_set_draw_color_rgb(0,0,0);
        calypso_framework_sdl2_renderer_render_rect_buffer_f(_rect_buffer_b,_rect_buffer_b_count);
    }

    // Render (GUI)
    {
        // Undo Zoom | Set To Screen Space
        calpyso_framework_sdl2_renderer_set_render_scale(1,1);
        calypso_framework_sdl2_renderer_set_render_space(CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_SCREEN);

        // Titlebar
        {
            // Set Font
            calypso_framework_imgui_minimal_set_font(_font_text);

            // Titlebar
            switch (calypso_framework_imgui_minimal_window_titlebar(_image,"testbed_sdl",_window_width,30,20,45,30,0)) 
            {
                case 1: calypso_framework_sdl2_app_shutdown(); break;
                case 2: calypso_framework_sdl2_app_maxamize_restore_toggle_window(); break;
                case 3: calypso_framework_sdl2_app_minimize_window(); break;
                default: break;
            }
        }

        // Set Font
        calypso_framework_imgui_minimal_set_font(_font_text);

        // Menubar
        {
            calypso_framework_imgui_minimal_button_text("File",40,0,50,30,0);
            calypso_framework_imgui_minimal_button_text("Edit",40 + 50,0,50,30,0);
            calypso_framework_imgui_minimal_button_text("View",40 + 100,0,50,30,0);
        }

        // Status Bar
        {
            calypso_framework_imgui_minimal_rect(0,_window_height - 30,_window_width,30,0);
            calypso_framework_imgui_minimal_text(_calypso_framework_sdl2_app_time_fps_as_string,10,_window_height - 30 + 6,0);
        }

       // Render GUI (Box)
       {
            calypso_framework_imgui_minimal_rect(_window_width - 375,30,375,_window_height - 30 - 30,1);
            calypso_framework_imgui_minimal_text("Properties",_window_width - 375 + 20,40,0);
       }
    }

    // Render (End)
    calypso_framework_sdl2_renderer_present();
}

void resize()
{
    calpyso_framework_sdl2_renderer_set_viewport_scaled(0,0,calypso_framework_sdl2_app_get_window_width(),calypso_framework_sdl2_app_get_window_height());
}

int main(int argc, char** argv)
{
    // App (SDL)
    calypso_framework_sdl2_app_set_log_callback(log_msg);
    calypso_framework_sdl2_app_init();
    calypso_framework_sdl2_app_set_window_title("Testbed : Renderer2D (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update, resize);
    calypso_framework_sdl2_app_set_window_resizable(1);
    calypso_framework_sdl2_app_set_window_bordered(0);
    calypso_framework_sdl2_app_run();

    return 0;
}