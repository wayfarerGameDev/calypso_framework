/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t
#include <dependencies/SDL2/SDL.h>

// Logging Callback
typedef void (*calypso_framework_sdl_app_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_sdl_app_log_callback_t _calypso_framework_sdl_app_log_callback;

// State
#define CALYPSO_FRAMEWORK_SDL_APP_STATE_NULL                 0b00000000
#define CALYPSO_FRAMEWORK_SDL_APP_STATE_INIT                 0b00000001
#define CALYPSO_FRAMEWORK_SDL_APP_STATE_RUNNING              0b00000010
#define CALYPSO_FRAMEWORK_SDL_APP_STATE_SHUTDOWN             0b00000011
#define CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR                0b00000100
unsigned int _calypso_framework_sdl_app_state =              CALYPSO_FRAMEWORK_SDL_APP_STATE_NULL;

// Window
#define CALYPSO_FRAMEWORK_SDL_APP_SCREEN_WIDTH_DEFAULT       1280 
#define CALYPSO_FRAMEWORK_SDL_APP_SCREEN_HEIGHT_DEFAULT      720
SDL_Window* _calypso_framework_sdl_app_window;

// Open GL Context
SDL_GLContext _calypso_framework_sdl_app_gl_context;

// Time
#define CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_UNCAPPED          -1
#define CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_DEFAULT            CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_UNCAPPED
float _calypso_framework_sdl_app_time_frame_rate_target =     CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_DEFAULT;
float _calypso_framework_sdl_app_time_frame_rate =            0;
float _calypso_framework_sdl_app_time_frame_time_target =     0;
float _calypso_framework_sdl_app_time_delta_time =            0;

// Events
typedef void (*calypso_framework_sdl_app_event_t)(void);
calypso_framework_sdl_app_event_t _calypso_framework_sdl_app_event_on_startup;
calypso_framework_sdl_app_event_t _calypso_framework_sdl_app_event_on_shutdown;
calypso_framework_sdl_app_event_t _calypso_framework_sdl_app_event_on_update;


/*------------------------------------------------------------------------------
Calypso Framework SDL App : Log
------------------------------------------------------------------------------*/

void calypso_framework_sdl_app_set_log_callback(calypso_framework_sdl_app_log_callback_t log_callback)
{
    _calypso_framework_sdl_app_log_callback = log_callback;
}

void calypso_framework_sdl_app_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_sdl_app_log_callback == NULL)
        return;

    _calypso_framework_sdl_app_log_callback(log_msg,log_type);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Window
------------------------------------------------------------------------------*/

SDL_Window* calypso_framework_sdl_app_get_window_sdl_window(void)
{
    return _calypso_framework_sdl_app_window;
}

int calypso_framework_sdl_app_get_window_width(void)
{
     // Not Valid Group
    if (!_calypso_framework_sdl_app_window)
    {
        calypso_framework_sdl_app_do_log_callback("App: Failed to get window width (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_sdl_app_window,&w,&h);
    return w;
}

int calypso_framework_sdl_app_get_window_height(void)
{
     // Not Valid Group
    if (!_calypso_framework_sdl_app_window)
    {
        calypso_framework_sdl_app_do_log_callback("App: Failed to get window height (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_sdl_app_window,&w,&h);
    return h;
}

void calypso_framework_sdl_app_set_window_icon(SDL_Surface* icon)
{
    // Return If Icon Is NULL
    if (icon == NULL)
    {
        calypso_framework_sdl_app_do_log_callback("App: Failed To Set Window Icon",3);
        return;
    }

    SDL_SetWindowIcon(_calypso_framework_sdl_app_window,icon);
}

void calypso_framework_sdl_app_set_window_title(const char* title)
{
    SDL_SetWindowTitle(_calypso_framework_sdl_app_window,title);
}

void calypso_framework_sdl_app_set_window_resizable(const uint8_t bIsResizable)
{
    SDL_SetWindowResizable(_calypso_framework_sdl_app_window,bIsResizable);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Time
------------------------------------------------------------------------------*/

void calypso_framework_sdl_app_set_time_frame_rate_target_uncapped(void)
{
    // Time
    _calypso_framework_sdl_app_time_frame_rate_target = CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_UNCAPPED;
    _calypso_framework_sdl_app_time_frame_time_target = 0;
}

void calypso_framework_sdl_app_set_time_frame_target_rate(const unsigned int frame_rate)
{
    _calypso_framework_sdl_app_time_frame_rate_target = frame_rate;
    _calypso_framework_sdl_app_time_frame_time_target = 1000 / frame_rate;
}

float calypso_framework_sdl_app_get_time_frame_rate(void)
{
    return _calypso_framework_sdl_app_time_frame_rate;
}

float* calypso_framework_sdl_app_get_time_frame_rate_ptr(void)
{
    return &_calypso_framework_sdl_app_time_frame_rate;
}

float calypso_framework_sdl_app_get_time_delta_time(void)
{
    return _calypso_framework_sdl_app_time_delta_time;
}

float* calypso_framework_sdl_app_get_time_delta_time_ptr(void)
{
    return &_calypso_framework_sdl_app_time_delta_time;
}

char* calypso_framework_sdl_app_get_time_fps_as_string(void)
{
    int len = snprintf(NULL, 0, "%i", (int)_calypso_framework_sdl_app_time_frame_rate);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%i", (int)_calypso_framework_sdl_app_time_frame_rate);
    return result;
}

char* calypso_framework_sdl_app_get_time_delta_time_as_string(void)
{
    int len = snprintf(NULL, 0, "%f", _calypso_framework_sdl_app_time_delta_time);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%f", _calypso_framework_sdl_app_time_delta_time);
    return result;
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Main
------------------------------------------------------------------------------*/

void calypso_framework_sdl_app_init()
{
    // Only Init Once
    if (_calypso_framework_sdl_app_state != CALYPSO_FRAMEWORK_SDL_APP_STATE_NULL)
    {
        calypso_framework_sdl_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        calypso_framework_sdl_app_do_log_callback("App: SDL failed to initialize\n",3);
        calypso_framework_sdl_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl_app_do_log_callback("\n",3);
        _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_sdl_app_window = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_SDL_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_SDL_APP_SCREEN_HEIGHT_DEFAULT,SDL_WINDOW_OPENGL);
    if(!_calypso_framework_sdl_app_window)
    {
        calypso_framework_sdl_app_do_log_callback("App: SDL failed to create window\n",3);
        calypso_framework_sdl_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl_app_do_log_callback("\n",3);
        _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR;
        return;
    }
}

void calypso_framework_sdl_app_init_with_opengl(const int major_version, const int minor_version, const int context_profile)
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
    if (_calypso_framework_sdl_app_state != CALYPSO_FRAMEWORK_SDL_APP_STATE_NULL)
    {
        calypso_framework_sdl_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        calypso_framework_sdl_app_do_log_callback("App: SDL failed to initialize\n",3);
        calypso_framework_sdl_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl_app_do_log_callback("\n",3);
        _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_sdl_app_window = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_SDL_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_SDL_APP_SCREEN_HEIGHT_DEFAULT,SDL_WINDOW_OPENGL);
    if(!_calypso_framework_sdl_app_window)
    {
        calypso_framework_sdl_app_do_log_callback("App: SDL failed to create window\n",3);
        calypso_framework_sdl_app_do_log_callback(SDL_GetError(),3);
        calypso_framework_sdl_app_do_log_callback("\n",3);
        _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR;
        return;
    }

    //Open GL Context
    {
        _calypso_framework_sdl_app_gl_context = SDL_GL_CreateContext(_calypso_framework_sdl_app_window);
        if (!_calypso_framework_sdl_app_gl_context)
        {
            calypso_framework_sdl_app_do_log_callback("App: SDL failed to create opengl context\n",3);
            calypso_framework_sdl_app_do_log_callback(SDL_GetError(),3);
            calypso_framework_sdl_app_do_log_callback("\n",3);
            _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_ERROR;
            return;
        }
    }
}

void* calypso_framework_sdl_app_get_open_gl_proc_address()
{
    return SDL_GL_GetProcAddress;
}

void calypso_framework_sdl_app_shutdown(void)
{
     _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_SHUTDOWN;
}

void calypso_framework_sdl_app_set_events(calypso_framework_sdl_app_event_t event_on_startup, calypso_framework_sdl_app_event_t event_on_shutdown, calypso_framework_sdl_app_event_t event_on_update)
{
    _calypso_framework_sdl_app_event_on_startup = event_on_startup;
    _calypso_framework_sdl_app_event_on_shutdown = event_on_shutdown;
    _calypso_framework_sdl_app_event_on_update = event_on_update;
}

void calypso_framework_sdl_app_run(void)
{
    // Only Run If State Is Initalized (Not Yet Running)
    if (_calypso_framework_sdl_app_state != CALYPSO_FRAMEWORK_SDL_APP_STATE_INIT)
        return;

    // On Event Startup
    if (_calypso_framework_sdl_app_event_on_startup != NULL)
        _calypso_framework_sdl_app_event_on_startup();

    // Set State To Running
    _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_RUNNING;

    // Time Data To Do Calculations
    int time_time_last = 0;
    int time_time_delay = 0;
    int time_frame_count = 0;
    int time_frame_last = 0;

    // Run
    while(_calypso_framework_sdl_app_state == CALYPSO_FRAMEWORK_SDL_APP_STATE_RUNNING)
    {
        // Do Time (Capped Frame Rate)
        if (_calypso_framework_sdl_app_time_frame_rate_target != CALYPSO_FRAMEWORK_SDL_APP_TIME_FPS_UNCAPPED)
        {
            // Delay Our Timestep By Frame Rate Target
            time_time_delay =  _calypso_framework_sdl_app_time_frame_time_target - (SDL_GetTicks() - time_time_last);
                if (time_time_delay > 0 && time_time_delay < _calypso_framework_sdl_app_time_frame_time_target)
                {
                    time_frame_count -= time_time_delay;
                    time_frame_last += time_time_delay;
                    SDL_Delay(time_time_delay);
                }

            // Get Frame Rate Every 1 Seconds
            ++time_frame_count;
            if (SDL_GetTicks() - time_frame_last >= 1000.f)
            {
                _calypso_framework_sdl_app_time_frame_rate = time_frame_count;
                time_frame_count = 0;
                time_frame_last = SDL_GetTicks();
            }

             // Get Delta Time (As Seconds) | Set Time Last To Time Current
            _calypso_framework_sdl_app_time_delta_time = (SDL_GetTicks() - time_time_last)* 0.001f;;
            time_time_last = SDL_GetTicks();
        }

        // Do Time (Uncapped Frame Rate)
        else
        {
            // Get Frame Rate Every 1 Seconds
            ++time_frame_count;
            if (SDL_GetTicks() - time_frame_last >= 1000.f)
            {
                _calypso_framework_sdl_app_time_frame_rate = time_frame_count;
                time_frame_count = 0;
                time_frame_last = SDL_GetTicks();
            }

            // Get Delta Time (As Seconds) | Set Time Last To Time Current
            _calypso_framework_sdl_app_time_delta_time = (SDL_GetTicks() - time_time_last)* 0.001f;
            time_time_last = SDL_GetTicks();
        }

        // Event Loop
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT: _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_SHUTDOWN; break;
                    default: break;
                }
            }
        }

         // On Event Update
         if (_calypso_framework_sdl_app_event_on_update != NULL)
            _calypso_framework_sdl_app_event_on_update();

        // Swap Window (Open GL Is Using 2 Buffers)
        if (_calypso_framework_sdl_app_gl_context)
            SDL_GL_SwapWindow(_calypso_framework_sdl_app_window);
    }

    // On Event Shutdown
    if (_calypso_framework_sdl_app_event_on_shutdown != NULL)
        _calypso_framework_sdl_app_event_on_shutdown();

    // Quit
    {
        // SDL
        SDL_DestroyWindow(_calypso_framework_sdl_app_window);
        SDL_Quit();

        // OpenGL
        if (_calypso_framework_sdl_app_gl_context)
            SDL_GL_DeleteContext(_calypso_framework_sdl_app_gl_context);
    }

    // No State
    _calypso_framework_sdl_app_state = CALYPSO_FRAMEWORK_SDL_APP_STATE_NULL;
}