/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// State
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL        0
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT        1
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING     2
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_EXIT        3
#define CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR       4
int _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_NULL;

// Window
#define CALYPSO_FRAMEWORK_APP_SDL_DEFAULT_SCREEN_WIDTH 1280 
#define CALYPSO_FRAMEWORK_APP_SDL_DEFAULT_SCREEN_HEIGHT 720
SDL_Window* _calypso_framework_app_sdl_window;

// Start / End Systems
typedef void (*calypso_framework_app_sdl_start_end_system)();
calypso_framework_app_sdl_start_end_system* _calypso_framework_app_sdl_start_systems;
calypso_framework_app_sdl_start_end_system* _calypso_framework_app_sdl_end_systems;
int _calypso_framework_app_sdl_start_system_count = 0;
int _calypso_framework_app_sdl_end_system_count = 0;

// Update Systems
typedef void (*calypso_framework_app_sdl_update_system)(float delta_time);
calypso_framework_app_sdl_update_system* _calypso_framework_app_sdl_update_systems;
int _calypso_framework_app_sdl_update_system_count = 0;

/**
 * initializes App
 * @return void
*/
void calypso_framework_app_sdl_init()
{
    // Set State To Init By Default
    _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT;

    // Init SDL (Everything)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
    }

    // Create SDL Window
    _calypso_framework_app_sdl_window = SDL_CreateWindow("App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CALYPSO_FRAMEWORK_APP_SDL_DEFAULT_SCREEN_WIDTH, CALYPSO_FRAMEWORK_APP_SDL_DEFAULT_SCREEN_HEIGHT, 0);
    if(!_calypso_framework_app_sdl_window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_ERROR;
        return;
    }
}

/**
 * Gets app's sdl window
 * 
 * @return SDL_Window*
*/
SDL_Window* calypso_framework_app_sdl_get_sdl_window()
{
    return _calypso_framework_app_sdl_window;
}

/**
 * Sets window's icon
 * 
 * @param icon SDL_Surface*
 * @return void
*/
void calypso_framework_app_sdl_set_window_icon(SDL_Surface* icon)
{
    // Return If Icon Is NULL
    if (icon == NULL)
    {
         printf("Error: Failed To Set Window Icon\n");
        return;
    }

    SDL_SetWindowIcon(_calypso_framework_app_sdl_window,icon);
}

/**
 * Sets window's title
 * 
 * @param title const char*
 * @return void
*/
void calypso_framework_app_sdl_set_window_title(const char* title)
{
    SDL_SetWindowTitle(_calypso_framework_app_sdl_window,title);
}

/**
 * Sets window's ability to be resizable enabled
 * @param bIsResizable const bool
 * @return void
*/
void calypso_framework_app_sdl_set_window_resizable(const bool bIsResizable)
{
    SDL_SetWindowResizable(_calypso_framework_app_sdl_window,bIsResizable);
}

/**
 * Adds start system
 * 
 * @param system void function no paramaters
 * @return void
*/
void calypso_framework_app_sdl_add_start_system(calypso_framework_app_sdl_start_end_system system)
{
    // Add Start System (First Time)
    if (_calypso_framework_app_sdl_start_system_count == 0)
    {
        _calypso_framework_app_sdl_start_system_count++;
        _calypso_framework_app_sdl_start_systems = malloc(_calypso_framework_app_sdl_start_system_count * sizeof(calypso_framework_app_sdl_start_end_system));
        _calypso_framework_app_sdl_start_systems[0] = system;
    }

    // Add Start System (After First Time)
    else
    {
        _calypso_framework_app_sdl_start_system_count++;
        _calypso_framework_app_sdl_start_systems = realloc(_calypso_framework_app_sdl_start_systems,_calypso_framework_app_sdl_start_system_count);
        _calypso_framework_app_sdl_start_systems[_calypso_framework_app_sdl_start_system_count - 1] = system;
    }
}

/**
 * Adds end system
 * 
 * @param system void function no paramaters
 * @return void
*/
void calypso_framework_app_sdl_add_end_system(calypso_framework_app_sdl_start_end_system system)
{
    // Add End System (First Time)
    if (_calypso_framework_app_sdl_end_system_count == 0)
    {
        _calypso_framework_app_sdl_end_system_count++;
        _calypso_framework_app_sdl_end_systems = malloc(_calypso_framework_app_sdl_end_system_count * sizeof(calypso_framework_app_sdl_start_end_system));
        _calypso_framework_app_sdl_end_systems[0] = system;
    }

    // Add End System (After First Time)
    else
    {
        _calypso_framework_app_sdl_end_system_count++;
        _calypso_framework_app_sdl_end_systems = realloc(_calypso_framework_app_sdl_end_systems,_calypso_framework_app_sdl_end_system_count);
        _calypso_framework_app_sdl_end_systems[_calypso_framework_app_sdl_end_system_count - 1] = system;
    }
}

/**
 * Adds update system
 * 
 * @param system void function with paramater delta_time[float]
 * @return void
*/
void calypso_framework_app_sdl_add_update_system(calypso_framework_app_sdl_update_system system)
{
    // Add Update System (First Time)
    if (_calypso_framework_app_sdl_update_system_count == 0)
    {
        _calypso_framework_app_sdl_update_system_count++;
        _calypso_framework_app_sdl_update_systems = malloc(_calypso_framework_app_sdl_update_system_count * sizeof(calypso_framework_app_sdl_update_system));
        _calypso_framework_app_sdl_update_systems[0] = system;
    }

    // Add Update System (After First Time)
    else
    {
        _calypso_framework_app_sdl_update_system_count++;
        _calypso_framework_app_sdl_update_systems = realloc(_calypso_framework_app_sdl_update_systems,_calypso_framework_app_sdl_update_system_count);
        _calypso_framework_app_sdl_update_systems[_calypso_framework_app_sdl_update_system_count - 1] = system;
    }
}

/**
 * Runs app, will halt code below call until app is no longer running
 * @return void
*/
void calypso_framework_app_sdl_run()
{
    // Only Run If State Is Initalized (Not Yet Running)
    if (_calypso_framework_app_sdl_state != CALYPSO_FRAMEWORK_APP_SDL_STATE_INIT)
        return;

    // Run Start Systems
    for (int i = 0; i < _calypso_framework_app_sdl_start_system_count; i++)
        _calypso_framework_app_sdl_start_systems[i]();

    // Set State To Running
    _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING;

    // Run Data (Time)
    float delta_time = 0;

    // Run
    while(_calypso_framework_app_sdl_state == CALYPSO_FRAMEWORK_APP_SDL_STATE_RUNNING)
    {
        // Event Loop
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT: _calypso_framework_app_sdl_state = CALYPSO_FRAMEWORK_APP_SDL_STATE_EXIT; break;
                    default: break;
                }
            }
        }

        // Run Update Systems
        for (int i = 0; i < _calypso_framework_app_sdl_update_system_count; i++)
            _calypso_framework_app_sdl_update_systems[i](delta_time);
    }

    // Run End Systems
    for (int i = 0; i < _calypso_framework_app_sdl_end_system_count; i++)
        _calypso_framework_app_sdl_end_systems[i]();
}