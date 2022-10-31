/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <SDL2/SDL.h>

// State
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL        0
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT        1
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING     2
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_SHUTDOWN    3
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR       4
unsigned int _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL;

// Logging Callback
typedef void (*calypso_framework_app_sdl_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_app_sdl_log_callback_t _calypso_framework_app_sdl_log_callback;

// Window
#define CALYPSO_FRAMEWORK_APP_SDL_SCREEN_WIDTH_DEFAULT  1280 
#define CALYPSO_FRAMEWORK_APP_SDL_SCREEN_HEIGHT_DEFAULT 720
SDL_Window* _calypso_framework_app_sdl_window;

// Time
#define CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED -1
#define CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_DEFAULT CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_UNCAPPED
float _calypso_framework_app_sdl_time_frame_rate_target = CALYPSO_FRAMEWORK_APP_SDL_TIME_FPS_DEFAULT;
float _calypso_framework_app_sdl_time_frame_rate = 0;
float _calypso_framework_app_sdl_time_frame_time_target = 0;
float _calypso_framework_app_sdl_time_delta_time = 0;

// Systems
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED                 0
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ENABLED                  1
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ONESHOT                  2
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP        0
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP         1
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP              2
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN       3
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN        4
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN             5
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE         6
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE          7
#define CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE               8
typedef void (*calypso_framework_app_sdl_system_t)(void);
calypso_framework_app_sdl_system_t* _calypso_framework_app_sdl_systems;
int* _calypso_framework_app_sdl_systems_states;
int* _calypso_framework_app_sdl_systems_app_stages;
unsigned int _calypso_framework_app_sdl_system_count = 0;

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

/**
* \brief Gets app's sdl window
* \return SDL_Window*
*/
SDL_Window* calypso_framework_app_sdl_get_sdl_window(void)
{
    return _calypso_framework_app_sdl_window;
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


/**
* \brief Enable app system
* \param system void function with no paramaters
*/
void calypso_framework_app_sdl_enable_system(calypso_framework_app_sdl_system_t system)
{
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems[i] == system)
        {
            _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ENABLED;
            return;
        }

    calypso_framework_app_sdl_do_log_callback("App: System not enabled (no such system)",2);
}

/**
* \brief Disable app system
* \param system void function with no paramaters
*/
void calypso_framework_app_sdl_disable_system(calypso_framework_app_sdl_system_t system)
{
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems[i] == system)
        {
            _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED;
            return;
        }

    calypso_framework_app_sdl_do_log_callback("App: System not disabled (no such system)",2);
}

/**
* \brief Oneshot app system
* \param system void function with no paramaters
*/
void calypso_framework_app_sdl_one_shot_system(calypso_framework_app_sdl_system_t system)
{
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems[i] == system)
        {
            _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ONESHOT;
            return;
        }
}

/**
* \brief Add app system
* \param system void function with no paramaters
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param app_stage CALYPSO_FclsRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_app_sdl_add_system(calypso_framework_app_sdl_system_t system, int app_stage)
{
    // Not Valid Group
    if (app_stage < 0 || app_stage > 8)
    {
        calypso_framework_app_sdl_do_log_callback("App: Failed to add system (invalid app_stage)\n",3);
        return;
    }

    // Already Added
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
    {
        if (_calypso_framework_app_sdl_systems[i] == system)
        {
            calypso_framework_app_sdl_do_log_callback("App: Failed to add system (system already added)\n",2);
            return;
        }
    }

    // Add System
    _calypso_framework_app_sdl_system_count++;
    _calypso_framework_app_sdl_systems = realloc(_calypso_framework_app_sdl_systems,_calypso_framework_app_sdl_system_count* sizeof(calypso_framework_app_sdl_system_t));
    _calypso_framework_app_sdl_systems_states = realloc(_calypso_framework_app_sdl_systems_states,_calypso_framework_app_sdl_system_count* sizeof(int));
    _calypso_framework_app_sdl_systems_app_stages = realloc(_calypso_framework_app_sdl_systems_app_stages,_calypso_framework_app_sdl_system_count* sizeof(int));
    _calypso_framework_app_sdl_systems[_calypso_framework_app_sdl_system_count - 1] = system;
    _calypso_framework_app_sdl_systems_states[_calypso_framework_app_sdl_system_count - 1] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ENABLED;
    _calypso_framework_app_sdl_systems_app_stages[_calypso_framework_app_sdl_system_count - 1] = app_stage;
    
}

/**
* \brief Add app system that is disabled
* \param system void function with no paramaters
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param app_stage CALYPSO_FclsRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_app_sdl_add_system_disabled(calypso_framework_app_sdl_system_t system, int app_stage)
{
    calypso_framework_app_sdl_add_system(system,app_stage);
    calypso_framework_app_sdl_disable_system(system);
}

/**
* \brief Add app system that is to play once and than disable
* \param system void function with no paramaters
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param app_stage CALYPSO_FclsRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param app_stage CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_app_sdl_add_system_one_shot(calypso_framework_app_sdl_system_t system, int app_stage)
{
    calypso_framework_app_sdl_add_system(system,app_stage);
    calypso_framework_app_sdl_one_shot_system(system);
}

/**
* \brief Initializes app
* \return void
*/
void calypso_framework_app_sdl_init(void)
{
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
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_app_sdl_window = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_APP_SDL_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_APP_SDL_SCREEN_HEIGHT_DEFAULT, 0);
    if(!_calypso_framework_app_sdl_window)
    {
        calypso_framework_app_sdl_do_log_callback("App: SDL failed to create window\n",3);
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
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

    // Run Early Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_STARTUP)
                _calypso_framework_app_sdl_systems[i]();
            
    // Run Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_STARTUP)
                _calypso_framework_app_sdl_systems[i]();

    // Run Late Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_STARTUP)
                _calypso_framework_app_sdl_systems[i]();

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

        // Run Early Update App Stage Systems
        for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
            if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
                if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_UPDATE)
                {
                    if (_calypso_framework_app_sdl_systems_states[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ONESHOT)
                        _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED;
                    _calypso_framework_app_sdl_systems[i]();
                }

        // Run Update App Stage Systems
        for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
            if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
                if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_UPDATE)
                {
                    if (_calypso_framework_app_sdl_systems_states[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ONESHOT)
                        _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED;
                    _calypso_framework_app_sdl_systems[i]();
                }

        // Run Late Update App Stage Systems
        for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
            if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
                if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_UPDATE)
                {
                    if (_calypso_framework_app_sdl_systems_states[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_ONESHOT)
                        _calypso_framework_app_sdl_systems_states[i] = CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED;
                    _calypso_framework_app_sdl_systems[i]();
                }
    }

    // Run Early Shutdown App Stage Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_EARLY_SHUTDOWN)
                _calypso_framework_app_sdl_systems[i]();
            
    // Run Shutdown App Stage Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_SHUTDOWN)
                _calypso_framework_app_sdl_systems[i]();

    // Run Late Shutdown App Stage  Systems
    for (int i = 0; i < _calypso_framework_app_sdl_system_count; i++)
        if (_calypso_framework_app_sdl_systems_states[i] != CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_app_sdl_systems_app_stages[i] == CALYPSO_FRAMEWORK_APP_SDL_SYSTEM_APP_STAGE_LATE_SHUTDOWN)
                _calypso_framework_app_sdl_systems[i]();

    // Clear Systems
    free(_calypso_framework_app_sdl_systems);
    free(_calypso_framework_app_sdl_systems_app_stages);
    _calypso_framework_app_sdl_system_count = 0;

    // Quit
    SDL_DestroyWindow(_calypso_framework_app_sdl_window);
    SDL_Quit();
}