/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <dependencies/SDL2/SDL.h>

// Logging Callback
typedef void (*calypso_framework_app_sdl_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_app_sdl_log_callback_t _calypso_framework_app_sdl_log_callback;

// State
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL        0
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT        1
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING     2
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_SHUTDOWN    3
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR       4
unsigned int _calypso_framework_app_sdl_state       = CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL;

// Window
#define CALYPSO_FRAMEWORK_APP_SDL_SCREEN_WIDTH_DEFAULT  1280 
#define CALYPSO_FRAMEWORK_APP_SDL_SCREEN_HEIGHT_DEFAULT 720
SDL_Window* _calypso_framework_app_sdl_window;

// Open GL Context
SDL_GLContext _calypso_framework_app_sdl_gl_context;

// Time
#define CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED -1
#define CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_DEFAULT CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED
float _calypso_framework_app_sdl_time_frame_rate_target = CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_DEFAULT;
float _calypso_framework_app_sdl_time_frame_rate = 0;
float _calypso_framework_app_sdl_time_frame_time_target = 0;
float _calypso_framework_app_sdl_time_delta_time = 0;

// Events
typedef void (*calypso_framework_app_sdl_event_t)(void);
calypso_framework_app_sdl_event_t _calypso_framework_app_sdl_event_on_startup;
calypso_framework_app_sdl_event_t _calypso_framework_app_sdl_event_on_shutdown;
calypso_framework_app_sdl_event_t _calypso_framework_app_sdl_event_on_update;

/**
* \brief Set app's log callback
* \return void
*/
void calypso_framework_app_sdl_set_log_callback(calypso_framework_app_sdl_log_callback_t log_callback)
{
    _calypso_framework_app_sdl_log_callback = log_callback;
}

/**
* \brief Do app's log callback
* \return void
*/
void calypso_framework_app_sdl_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_app_sdl_log_callback == NULL)
        return;

    _calypso_framework_app_sdl_log_callback(log_msg,log_type);
}

void* calypso_framework_app_sdl_get_open_gl_proc_address()
{
    return SDL_GL_GetProcAddress;
}

/**
* \brief Gets app's sdl window
* \return SDL_Window*
*/
SDL_Window* calypso_framework_app_sdl_get_window_sdl_window(void)
{
    return _calypso_framework_app_sdl_window;
}

/**
* \brief Gets app's window width
* \return SDL_Window*
*/
int calypso_framework_app_sdl_get_window_width(void)
{
     // Not Valid Group
    if (!_calypso_framework_app_sdl_window)
    {
        calypso_framework_app_sdl_do_log_callback("App: Failed to get window width (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_app_sdl_window,&w,&h);
    return w;
}

/**
* \brief Gets app's window height
* \return SDL_Window*
*/
int calypso_framework_app_sdl_get_window_height(void)
{
     // Not Valid Group
    if (!_calypso_framework_app_sdl_window)
    {
        calypso_framework_app_sdl_do_log_callback("App: Failed to get window height (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_calypso_framework_app_sdl_window,&w,&h);
    return h;
}

/**
* \brief Sets window's icon
* \param icon SDL_Surface*
* \return void
*/
void calypso_framework_app_sdl_set_window_icon(SDL_Surface* icon)
{
    // Return If Icon Is NULL
    if (icon == NULL)
    {
        calypso_framework_app_sdl_do_log_callback("App: Failed To Set Window Icon",3);
        return;
    }

    SDL_SetWindowIcon(_calypso_framework_app_sdl_window,icon);
}

/**
* \brief window's title
* 
* \param title const char*
* \return void
*/
void calypso_framework_app_sdl_set_window_title(const char* title)
{
    SDL_SetWindowTitle(_calypso_framework_app_sdl_window,title);
}

/**
* \brief Sets window's ability to be resizable enabled
* \param bIsResizable const Uint8
* \return void
*/
void calypso_framework_app_sdl_set_window_resizable(const Uint8 bIsResizable)
{
    SDL_SetWindowResizable(_calypso_framework_app_sdl_window,bIsResizable);
}

/**
* \brief Sets app's time frame rate to be uncapped
* \return void
*/
void calypso_framework_app_sdl_set_time_frame_rate_target_uncapped(void)
{
    // Time
    _calypso_framework_app_sdl_time_frame_rate_target = CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED;
    _calypso_framework_app_sdl_time_frame_time_target = 0;
}

/**
* \brief Sets app's time frame rate target
* \param frame_rate const unsigned int
* \return void
*/
void calypso_framework_app_sdl_set_time_frame_target_rate(const unsigned int frame_rate)
{
    _calypso_framework_app_sdl_time_frame_rate_target = frame_rate;
    _calypso_framework_app_sdl_time_frame_time_target = 1000 / frame_rate;
}

/**
* \brief Gets app's time frame rate
* \return float
*/
float calypso_framework_app_sdl_get_time_frame_rate(void)
{
    return _calypso_framework_app_sdl_time_frame_rate;
}

/**
* \brief Gets app's time frame rate as ptr
* \return float
*/
float* calypso_framework_app_sdl_get_time_frame_rate_ptr(void)
{
    return &_calypso_framework_app_sdl_time_frame_rate;
}

/**
* \brief Gets app's time delta time
* \return float
*/
float calypso_framework_app_sdl_get_time_delta_time(void)
{
    return _calypso_framework_app_sdl_time_delta_time;
}

/**
* \brief Gets app's time delta time as ptr
* \return float
*/
float* calypso_framework_app_sdl_get_time_delta_time_ptr(void)
{
    return &_calypso_framework_app_sdl_time_delta_time;
}

/**
* \brief Gets app's time fps as char*
* \return void
*/
char* calypso_framework_app_sdl_get_time_fps_as_string(void)
{
    int len = snprintf(NULL, 0, "%i", (int)_calypso_framework_app_sdl_time_frame_rate);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%i", (int)_calypso_framework_app_sdl_time_frame_rate);
    return result;
}

/**
* \brief Gets app's time fps as char*
* \return void
*/
char* calypso_framework_app_sdl_get_time_delta_time_as_string(void)
{
    int len = snprintf(NULL, 0, "%f", _calypso_framework_app_sdl_time_delta_time);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%f", _calypso_framework_app_sdl_time_delta_time);
    return result;
}

void calypso_framework_app_sdl_set_events(calypso_framework_app_sdl_event_t event_on_startup, calypso_framework_app_sdl_event_t event_on_shutdown, calypso_framework_app_sdl_event_t event_on_update)
{
    _calypso_framework_app_sdl_event_on_startup = event_on_startup;
    _calypso_framework_app_sdl_event_on_shutdown = event_on_shutdown;
    _calypso_framework_app_sdl_event_on_update = event_on_update;
}

/**
* \brief Initializes app window
* \return void
*/
void calypso_framework_app_sdl_init_with_opengl(const int major_version, const int minor_version, const int context_profile)
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
    if (_calypso_framework_app_sdl_state != CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL)
    {
        calypso_framework_app_sdl_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        calypso_framework_app_sdl_do_log_callback("App: SDL failed to initialize\n",3);
        calypso_framework_app_sdl_do_log_callback(SDL_GetError(),3);
        calypso_framework_app_sdl_do_log_callback("\n",3);
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_app_sdl_window = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_APP_SDL_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_APP_SDL_SCREEN_HEIGHT_DEFAULT,SDL_WINDOW_OPENGL);
    if(!_calypso_framework_app_sdl_window)
    {
        calypso_framework_app_sdl_do_log_callback("App: SDL failed to create window\n",3);
        calypso_framework_app_sdl_do_log_callback(SDL_GetError(),3);
        calypso_framework_app_sdl_do_log_callback("\n",3);
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
    }

    //Open GL Context
    {
        _calypso_framework_app_sdl_gl_context = SDL_GL_CreateContext(_calypso_framework_app_sdl_window);
        if (!_calypso_framework_app_sdl_gl_context)
        {
            calypso_framework_app_sdl_do_log_callback("App: SDL failed to create opengl context\n",3);
            calypso_framework_app_sdl_do_log_callback(SDL_GetError(),3);
            calypso_framework_app_sdl_do_log_callback("\n",3);
            _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
            return;
        }
    }
}

/**
* \brief Runs app, will halt code below call until app is no longer running
* \return void
*/
void calypso_framework_app_sdl_shutdown(void)
{
     _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_SHUTDOWN;
}

/**
 \brief Runs app
 \warning app, will halt code below call until app is no longer running
 \return void
*/
void calypso_framework_app_sdl_run(void)
{
    // Only Run If State Is Initalized (Not Yet Running)
    if (_calypso_framework_app_sdl_state != CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT)
        return;

    // On Event Startup
    if (_calypso_framework_app_sdl_event_on_startup != NULL)
        _calypso_framework_app_sdl_event_on_startup();

    // Set State To Running
    _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING;

    // Time Data To Do Calculations
    int time_time_last = 0;
    int time_time_delay = 0;
    int time_frame_count = 0;
    int time_frame_last = 0;

    // Run
    while(_calypso_framework_app_sdl_state == CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING)
    {
        // Do Time (Capped Frame Rate)
        if (_calypso_framework_app_sdl_time_frame_rate_target != CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED)
        {
            // Delay Our Timestep By Frame Rate Target
            time_time_delay =  _calypso_framework_app_sdl_time_frame_time_target - (SDL_GetTicks() - time_time_last);
                if (time_time_delay > 0 && time_time_delay < _calypso_framework_app_sdl_time_frame_time_target)
                {
                    time_frame_count -= time_time_delay;
                    time_frame_last += time_time_delay;
                    SDL_Delay(time_time_delay);
                }

            // Get Frame Rate Every 1 Seconds
            ++time_frame_count;
            if (SDL_GetTicks() - time_frame_last >= 1000.f)
            {
                _calypso_framework_app_sdl_time_frame_rate = time_frame_count;
                time_frame_count = 0;
                time_frame_last = SDL_GetTicks();
            }

             // Get Delta Time (As Seconds) | Set Time Last To Time Current
            _calypso_framework_app_sdl_time_delta_time = (SDL_GetTicks() - time_time_last)* 0.001f;;
            time_time_last = SDL_GetTicks();
        }

        // Do Time (Uncapped Frame Rate)
        else
        {
            // Get Frame Rate Every 1 Seconds
            ++time_frame_count;
            if (SDL_GetTicks() - time_frame_last >= 1000.f)
            {
                _calypso_framework_app_sdl_time_frame_rate = time_frame_count;
                time_frame_count = 0;
                time_frame_last = SDL_GetTicks();
            }

            // Get Delta Time (As Seconds) | Set Time Last To Time Current
            _calypso_framework_app_sdl_time_delta_time = (SDL_GetTicks() - time_time_last)* 0.001f;
            time_time_last = SDL_GetTicks();
        }

        // Event Loop
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT: _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_SHUTDOWN; break;
                    default: break;
                }
            }
        }

         // On Event Update
         if (_calypso_framework_app_sdl_event_on_update != NULL)
            _calypso_framework_app_sdl_event_on_update();

        // Swap Window (Open GL Is Using 2 Buffers)
        if (_calypso_framework_app_sdl_gl_context)
            SDL_GL_SwapWindow(_calypso_framework_app_sdl_window);
    }

    // On Event Shutdown
    if (_calypso_framework_app_sdl_event_on_shutdown != NULL)
        _calypso_framework_app_sdl_event_on_shutdown();

    // Quit OpenGL
    if (_calypso_framework_app_sdl_gl_context)
        SDL_GL_DeleteContext(_calypso_framework_app_sdl_gl_context);

    // Quit
    SDL_DestroyWindow(_calypso_framework_app_sdl_window);
    SDL_Quit();
}