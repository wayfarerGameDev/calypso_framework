// Calypso (Logging)
#define CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
#include "../calypso_framework_misc/calypso_framework_log.c"

// Includes (Calypso) 
#include "../calypso_framework_gui/calypso_framework_imgui_minimal.c"
#include "../calypso_framework_math/calypso_framework_math_colors.c"
#include "../calypso_framework_io/calypso_framework_io_file.c"
#include "../calypso_framework_io/calypso_framework_io_ini.c"

// Includes (Calypso SDL2) 
#include "../calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "../calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#include "../calypso_framework_sdl2/calypso_framework_sdl2_renderer.c"

char* CALYPSO_ENGINE_EDITOR_STYLE_APP_TITLE                         = "example_engine_sdl";
char* CALYPSO_ENGINE_EDITOR_STYLE_ICON_FILE_PATH                    = "content/example_engine_sdl/images/app_icon.ico";
char* CALYPSO_ENGINE_EDITOR_STYLE_FONT_FILE_PATH                    = "content/example_engine_sdl/fonts/OpenSans_Regular.ttf";

// Style
void* _style_font_ptr                                                = NULL;
int _style_font_size                                                = 13;
int _style_cutom_titlebar_enabled                                   = 0;
int _style_cutom_titlebar_height                                    = 30;
int _style_menubar_toolbar_height                                   = 30;
int _style_statusbar_height                                         = 30;

// Content
void* _calypso_engine_editor_icon_ptr;

/*------------------------------------------------------------------------------
Calypso Engine SDL (Editor) : Main
------------------------------------------------------------------------------*/

void calypso_engine_sdl_editor_apply_config()
{
    // Read | Parse File
    char* file_data = NULL;
    file_data = calypso_framework_io_file_read("./content/example_engine_sdl/editor_config.ini");
    // calypso_framework_io_ini_get_value_int(file_data,"style","style_font_size", &_style_font_size);
    printf("%s\n", file_data); 

    // Set Values

    // Free File Data
    free(file_data);
}

/*------------------------------------------------------------------------------
Calypso Engine SDL (Editor) : Main
------------------------------------------------------------------------------*/

void start()
{
    // Apply Editor Config
    calypso_engine_sdl_editor_apply_config();

    // Renderer
    {
        calypso_framework_sdl2_renderer_init(calypso_framework_sdl2_app_get_window_sdl2_window_ptr());
    }

    // Content
    {
        calypso_framework_sdl2_renderer_load_font_ttf(&_style_font_ptr,CALYPSO_ENGINE_EDITOR_STYLE_FONT_FILE_PATH,_style_font_size);
        calypso_framework_sdl2_renderer_load_texture(&_calypso_engine_editor_icon_ptr,CALYPSO_ENGINE_EDITOR_STYLE_ICON_FILE_PATH);
    }

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
            calypso_framework_sdl2_app_get_mouse_button_left_state_is_pressed,
            calypso_framework_sdl2_app_get_mouse_button_left_state_is_released);

        // Set Bindnigs
        calypso_framework_imgui_minimal_set_bindings(calypso_framework_sdl2_app_get_mouse_position_ptr());    
    }

    // App
    {
        // Custom Toolbar
        #if _style_cutom_titlebar_enabled == 1
        calypso_framework_sdl2_app_enable_window_custom_toolbar(1,_style_cutom_titlebar_height);
        #endif

        calypso_framework_sdl2_app_set_title(CALYPSO_ENGINE_EDITOR_STYLE_APP_TITLE);
        calypso_framework_sdl2_app_set_icon_bmp(CALYPSO_ENGINE_EDITOR_STYLE_ICON_FILE_PATH);
        calypso_framework_sdl2_app_set_window_resizable(1);
        calypso_framework_sdl2_app_maxamize_window();
    }
}

void end()
{
    // Deinit Renderer
    calypso_framework_sdl2_renderer_deinit();
}

void update()
{
    float window_width = (float)calypso_framework_sdl2_app_get_window_width();
    float window_height = (float)calypso_framework_sdl2_app_get_window_height();

     // Update Input
    calypso_framework_sdl2_input_update();

    // Render (Start)
    calypso_framework_sdl2_renderer_set_clear_color_rgb_hex(0x101010);
    calypso_framework_sdl2_renderer_clear();

    // Render (GUI)
    {
        // Set Font
        calypso_framework_imgui_minimal_set_font(_style_font_ptr);

        // No Zoom | Screen Space
        calpyso_framework_sdl2_renderer_set_render_scale(1,1);
        calypso_framework_sdl2_renderer_set_render_space(CALYPSO_FRAMEWORK_SDL2_RENDERER_RENDER_SPACE_SCREEN);

        // Titlebar
        if (_style_cutom_titlebar_enabled == 1)
        switch (calypso_framework_imgui_minimal_window_titlebar(_calypso_engine_editor_icon_ptr,CALYPSO_ENGINE_EDITOR_STYLE_APP_TITLE,window_width,30,20,45,_style_cutom_titlebar_height,0)) 
        {
            case 1: calypso_framework_sdl2_app_shutdown(); break;
            case 2: calypso_framework_sdl2_app_maxamize_restore_toggle_window(); break;
            case 3: calypso_framework_sdl2_app_minimize_window(); break;
            default: break;
        }
            
        
        // Menubar
        {
            if (_style_cutom_titlebar_enabled == 0)
                calypso_framework_imgui_minimal_rect(0,0,window_width,_style_menubar_toolbar_height,0);
            
            calypso_framework_imgui_minimal_button_text("File",40,0,50,_style_menubar_toolbar_height,0);
            calypso_framework_imgui_minimal_button_text("Edit",40 + 50,0,50,_style_menubar_toolbar_height,0);
            calypso_framework_imgui_minimal_button_text("View",40 + 100,0,50,_style_menubar_toolbar_height,0);
        }

        // Toolbar
        {
            int offset = _style_cutom_titlebar_enabled == 1 ? 45 : 45;

            calypso_framework_imgui_minimal_button_text("C",window_width - offset * 4,0,50,_style_menubar_toolbar_height,0);
            calypso_framework_imgui_minimal_button_text("R",window_width - offset * 5,0,50,_style_menubar_toolbar_height,0);
            calypso_framework_imgui_minimal_text("|",window_width - offset * 3,0,0); // Seperator
            calypso_framework_imgui_minimal_text("|",window_width - offset * 3,10,0);
        }

        // Status Bar
        {
            calypso_framework_imgui_minimal_rect(0,window_height - _style_statusbar_height,window_width,_style_statusbar_height,0);
            calypso_framework_imgui_minimal_text(_calypso_framework_sdl2_app_time_fps_as_string,10,window_height - _style_statusbar_height + 6,0);
        }

       // Render GUI (Box)
       {
            calypso_framework_imgui_minimal_rect(window_width - 375,_style_menubar_toolbar_height,375,window_height - _style_menubar_toolbar_height - _style_statusbar_height,1);
            calypso_framework_imgui_minimal_text("Properties",window_width - 375 + 20,40,0);
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
    calypso_framework_sdl2_app_init();
    calypso_framework_sdl2_app_set_events(start,end,update, resize);
    calypso_framework_sdl2_app_run();

    return 0;
}