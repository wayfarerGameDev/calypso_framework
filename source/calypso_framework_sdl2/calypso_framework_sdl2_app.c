/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t
#include <dependencies/SDL2/SDL.h>

// Logging Callback
typedef void (*calypso_framework_sdl2_app_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_sdl2_app_log_callback_t _calypso_framework_sdl2_app_log_callback;

// State
#define CALYPSO_FRAMEWORK_SDL2_APP_STATE_NULL                 0b00000000
#define CALYPSO_FRAMEWORK_SDL2_APP_STATE_INIT                 0b00000001
#define CALYPSO_FRAMEWORK_SDL2_APP_STATE_RUNNING              0b00000010
#define CALYPSO_FRAMEWORK_SDL2_APP_STATE_SHUTDOWN             0b00000011
#define CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR                0b00000100
unsigned int _calypso_framework_sdl2_app_state                = CALYPSO_FRAMEWORK_SDL2_APP_STATE_NULL;

// Window
#define CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_WIDTH_DEFAULT       1280 
#define CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_HEIGHT_DEFAULT      720
SDL_Window* _calypso_framework_sdl2_app_window_ptr;

// Open GL Context
SDL_GLContext _calypso_framework_sdl2_app_gl_context_ptr;

// Time
float _calypso_framework_sdl2_app_time_delta_time             = 0;
float _calypso_framework_sdl2_app_time_fps                    = 0;
char _calypso_framework_sdl2_app_time_fps_as_string[16];

// Events
typedef void (*calypso_framework_sdl2_app_event_t)(void);
calypso_framework_sdl2_app_event_t _calypso_framework_sdl2_app_event_on_startup;
calypso_framework_sdl2_app_event_t _calypso_framework_sdl2_app_event_on_shutdown;
calypso_framework_sdl2_app_event_t _calypso_framework_sdl2_app_event_on_update;
calypso_framework_sdl2_app_event_t _calypso_framework_sdl2_app_event_on_resize;


/*------------------------------------------------------------------------------
Calypso Framework SDL App : Log
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_app_set_log_callback(calypso_framework_sdl2_app_log_callback_t log_callback)
{
    _calypso_framework_sdl2_app_log_callback = log_callback;
}

void calypso_framework_sdl2_app_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_sdl2_app_log_callback == NULL)
        return;

    _calypso_framework_sdl2_app_log_callback(log_msg,log_type);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Window
------------------------------------------------------------------------------*/

SDL_Window* calypso_framework_sdl2_app_get_window_sdl2_window_ptr(void)
{
    return _calypso_framework_sdl2_app_window_ptr;
}

int calypso_framework_sdl2_app_get_window_width(void)
{
     // Not Valid Group
    if (!_calypso_framework_sdl2_app_window_ptr)
    {
        calypso_framework_sdl2_app_do_log_callback("App: Failed to get window width (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_sdl2_app_window_ptr,&w,&h);
    return w;
}

int calypso_framework_sdl2_app_get_window_height(void)
{
     // Not Valid Group
    if (!_calypso_framework_sdl2_app_window_ptr)
    {
        calypso_framework_sdl2_app_do_log_callback("App: Failed to get window height (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_sdl2_app_window_ptr,&w,&h);
    return h;
}

void calypso_framework_sdl2_app_set_window_icon(SDL_Surface* icon)
{
    // Return If Icon Is NULL
    if (icon == NULL)
    {
        calypso_framework_sdl2_app_do_log_callback("App: Failed To Set Window Icon",3);
        return;
    }

    SDL_SetWindowIcon(_calypso_framework_sdl2_app_window_ptr,icon);
}

void calypso_framework_sdl2_app_set_window_title(const char* title)
{
    SDL_SetWindowTitle(_calypso_framework_sdl2_app_window_ptr,title);
}

void calypso_framework_sdl2_app_set_window_resizable(const int is_resizable)
{
    SDL_SetWindowResizable(_calypso_framework_sdl2_app_window_ptr,is_resizable);
}

void calypso_framework_sdl2_app_maxamize_window()
{
    SDL_MaximizeWindow(_calypso_framework_sdl2_app_window_ptr);
}

void calypso_framework_sdl2_app_restore_window()
{
    SDL_RestoreWindow(_calypso_framework_sdl2_app_window_ptr);
}

void calypso_framework_sdl2_app_maxamize_restore_toggle_window()
{
    // Check if the window is maximized
    if (SDL_GetWindowFlags(_calypso_framework_sdl2_app_window_ptr) & SDL_WINDOW_MAXIMIZED) 
        SDL_RestoreWindow(_calypso_framework_sdl2_app_window_ptr);
    else 
        SDL_MaximizeWindow(_calypso_framework_sdl2_app_window_ptr);
}

void calypso_framework_sdl2_app_minimize_window()
{
    SDL_MinimizeWindow(_calypso_framework_sdl2_app_window_ptr);
}

void calypso_framework_sdl2_app_set_window_bordered(int is_bordered)
{
    SDL_SetWindowBordered(_calypso_framework_sdl2_app_window_ptr, is_bordered);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Time
------------------------------------------------------------------------------*/

float calypso_framework_sdl2_app_get_time_delta_time(void)
{
    return _calypso_framework_sdl2_app_time_delta_time;
}

float* calypso_framework_sdl2_app_get_time_delta_time_ptr(void)
{
    return &_calypso_framework_sdl2_app_time_delta_time;
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Main
------------------------------------------------------------------------------*/

void calypso_framework_sdl2_app_init()
{
    // Only Init Once
    if (_calypso_framework_sdl2_app_state != CALYPSO_FRAMEWORK_SDL2_APP_STATE_NULL)
    {
        calypso_framework_sdl2_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        calypso_framework_sdl2_app_do_log_callback("App: SDL failed to initialize\n",3);
        calypso_framework_sdl2_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl2_app_do_log_callback("\n",3);
        _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_sdl2_app_window_ptr = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_HEIGHT_DEFAULT,SDL_WINDOW_OPENGL);
    if(!_calypso_framework_sdl2_app_window_ptr)
    {
        calypso_framework_sdl2_app_do_log_callback("App: SDL failed to create window\n",3);
        calypso_framework_sdl2_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl2_app_do_log_callback("\n",3);
        _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR;
        return;
    }
}

void calypso_framework_sdl2_app_init_with_opengl(const int major_version, const int minor_version, const int context_profile)
{
    // Setup OpenGL Attributes
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,major_version);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,minor_version);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,context_profile); //MAY NEED TO CHANGE HOW THIS IS DONE
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    }

    // Only Init Once
    if (_calypso_framework_sdl2_app_state != CALYPSO_FRAMEWORK_SDL2_APP_STATE_NULL)
    {
        calypso_framework_sdl2_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        calypso_framework_sdl2_app_do_log_callback("App: SDL failed to initialize\n",3);
        calypso_framework_sdl2_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl2_app_do_log_callback("\n",3);
        _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_sdl2_app_window_ptr = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_SDL2_APP_SCREEN_HEIGHT_DEFAULT,SDL_WINDOW_OPENGL);
    if(!_calypso_framework_sdl2_app_window_ptr)
    {
        calypso_framework_sdl2_app_do_log_callback("App: SDL failed to create window\n",3);
        calypso_framework_sdl2_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl2_app_do_log_callback("\n",3);
        _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR;
        return;
    }

    //Open GL Context
    {
        _calypso_framework_sdl2_app_gl_context_ptr = SDL_GL_CreateContext(_calypso_framework_sdl2_app_window_ptr);
        if (!_calypso_framework_sdl2_app_gl_context_ptr)
        {
            calypso_framework_sdl2_app_do_log_callback("App: SDL failed to create opengl context\n",3);
            calypso_framework_sdl2_app_do_log_callback(SDL_GetError(),3);
            calypso_framework_sdl2_app_do_log_callback("\n",3);
            _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_ERROR;
            return;
        }
    }
}

void* calypso_framework_sdl2_app_get_open_gl_proc_address()
{
    return SDL_GL_GetProcAddress;
}

void calypso_framework_sdl2_app_shutdown(void)
{
     _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_SHUTDOWN;
}

void calypso_framework_sdl2_app_set_events(calypso_framework_sdl2_app_event_t event_on_startup, calypso_framework_sdl2_app_event_t event_on_shutdown, calypso_framework_sdl2_app_event_t event_on_update, calypso_framework_sdl2_app_event_t event_on_resize)
{
    _calypso_framework_sdl2_app_event_on_startup = event_on_startup;
    _calypso_framework_sdl2_app_event_on_shutdown = event_on_shutdown;
    _calypso_framework_sdl2_app_event_on_update = event_on_update;
    _calypso_framework_sdl2_app_event_on_resize = event_on_resize;
}

void calypso_framework_sdl2_app_run(void)
{
    // Only Run If State Is Initalized (Not Yet Running)
    if (_calypso_framework_sdl2_app_state != CALYPSO_FRAMEWORK_SDL2_APP_STATE_INIT)
        return;

    // On Event Startup
    if (_calypso_framework_sdl2_app_event_on_startup != NULL)
        _calypso_framework_sdl2_app_event_on_startup();

    // Set State To Running
    _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_RUNNING;

    // Time Data To Do Calculations
    Uint64 time_time_previous = SDL_GetTicks64();

    // Run
    while(_calypso_framework_sdl2_app_state == CALYPSO_FRAMEWORK_SDL2_APP_STATE_RUNNING)
    {
        // Event Loop
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT: _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_SHUTDOWN; break;
                    case SDL_WINDOWEVENT: if (event.window.event == SDL_WINDOWEVENT_RESIZED) _calypso_framework_sdl2_app_event_on_resize(); break;
                    default: break;
                }
            }
        }

        // Get Time
        {
            Uint32 currentTime = SDL_GetTicks();
            _calypso_framework_sdl2_app_time_delta_time  = (float)(currentTime - time_time_previous) / 1000.0f; // Convert to seconds
            time_time_previous = currentTime;
        }

        // Get FPS
        {
            // Get FPS (Float)
            _calypso_framework_sdl2_app_time_fps = 1 / _calypso_framework_sdl2_app_time_delta_time;  

            // Get FPS (String) | Check For Errors
            int len = snprintf(_calypso_framework_sdl2_app_time_fps_as_string, sizeof(_calypso_framework_sdl2_app_time_fps_as_string), "%.2f", 1.0 / _calypso_framework_sdl2_app_time_delta_time);
            if (len < 0 || len >= sizeof(_calypso_framework_sdl2_app_time_fps_as_string)) 
            {
                calypso_framework_sdl2_app_do_log_callback("FPS String Is Invalid",2);
            }

        }

         // On Event Update
         if (_calypso_framework_sdl2_app_event_on_update != NULL)
            _calypso_framework_sdl2_app_event_on_update();

        // Swap Window (OpenGL Is Using 2 Buffers)
        if (_calypso_framework_sdl2_app_gl_context_ptr)
            SDL_GL_SwapWindow(_calypso_framework_sdl2_app_window_ptr);  
    }

    // On Event Shutdown
    if (_calypso_framework_sdl2_app_event_on_shutdown != NULL)
        _calypso_framework_sdl2_app_event_on_shutdown();

    // Quit
    {
        // SDL
        SDL_DestroyWindow(_calypso_framework_sdl2_app_window_ptr);
        SDL_Quit();

        // OpenGL
        if (_calypso_framework_sdl2_app_gl_context_ptr)
            SDL_GL_DeleteContext(_calypso_framework_sdl2_app_gl_context_ptr);
    }

    // No State
    _calypso_framework_sdl2_app_state = CALYPSO_FRAMEWORK_SDL2_APP_STATE_NULL;
}