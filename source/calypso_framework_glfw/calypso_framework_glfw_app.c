/// <summary>
/// App module that uses GLFW as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h> //snprintf
#include <dependencies/GLFW/glfw3.h>

// State
#define CALYPSO_FRAMEWORK_GLFW_APP_STATE_NULL                 0b00000000
#define CALYPSO_FRAMEWORK_GLFW_APP_STATE_INIT                 0b00000001
#define CALYPSO_FRAMEWORK_GLFW_APP_STATE_RUNNING              0b00000010
#define CALYPSO_FRAMEWORK_GLFW_APP_STATE_SHUTDOWN             0b00000011
#define CALYPSO_FRAMEWORK_GLFW_APP_STATE_ERROR                0b00000100
unsigned int _calypso_framework_glfw_app_state =              CALYPSO_FRAMEWORK_GLFW_APP_STATE_NULL;

// Window
#define CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_WIDTH_DEFAULT       1280 
#define CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_HEIGHT_DEFAULT      720
GLFWwindow* _calypso_framework_glfw_app_window;

// Time
float _calypso_framework_glfw_app_time_delta_time             = 0;
float _calypso_framework_glfw_app_time_fps                    = 0;
char _calypso_framework_glfw_app_time_fps_as_string[16];

// Events
typedef void (*calypso_framework_glfw_app_event_t)(void);
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_startup;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_shutdown;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_update;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_resize;


/*------------------------------------------------------------------------------
Calypso Framework GLFW App : Title
------------------------------------------------------------------------------*/

void calypso_framework_glfw_app_set_title(const char* title)
{
    //GLFW_SetWindowTitle(_calypso_framework_glfw_app_window,title);
    glfwSetWindowTitle(_calypso_framework_glfw_app_window,title);
}

void calypso_framework_glfw_app_set_window_icon()
{
    // Return If Icon Is NULL
    //if (icon == NULL)
    //{
    //    calypso_framework_glfw_app_do_log_callback("App: Failed To Set Window Icon",3);
    //    return;
    //}
}

void* calypso_framework_glfw_app_get_open_gl_proc_address()
{
    return glfwGetProcAddress;
}

GLFWwindow* calypso_framework_glfw_app_get_window_glfw_window(void)
{
    return _calypso_framework_glfw_app_window;
}

/*------------------------------------------------------------------------------
Calypso Framework GLFW App : Winodw
------------------------------------------------------------------------------*/

int calypso_framework_glfw_app_get_window_width(void)
{
     // Not Valid Group
    if (!_calypso_framework_glfw_app_window)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app","Failed to get window width (window is NULL)",3);
        #endif
        return 0;
    }

    int w = 0;
    int h = 0;
    glfwGetWindowSize(_calypso_framework_glfw_app_window,&w,&h);
    return w;
}

int calypso_framework_glfw_app_get_window_height(void)
{
     // Not Valid Group
    if (!_calypso_framework_glfw_app_window)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app","Failed to get window height (window is NULL)",3);
        #endif
        return 0;
    }

    int w = 0;
    int h = 0;
    glfwGetWindowSize(_calypso_framework_glfw_app_window,&w,&h);
    return h;
}

void calypso_framework_glfw_app_set_window_size(int with, int height)
{
    //GLFW_SetWindowTitle(_calypso_framework_glfw_app_window,title);
    glfwSetWindowSize(_calypso_framework_glfw_app_window,with,height);
}

void calypso_framework_glfw_app_set_window_resizable(const unsigned char bIsResizable)
{
    glfwSetWindowAttrib(_calypso_framework_glfw_app_window, GLFW_RESIZABLE,bIsResizable == 1);
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Time
------------------------------------------------------------------------------*/

float calypso_framework_glfw_app_get_time_delta_time(void)
{
    return _calypso_framework_glfw_app_time_delta_time;
}

float* calypso_framework_glfw_app_get_time_delta_time_ptr(void)
{
    return &_calypso_framework_glfw_app_time_delta_time;
}

/*------------------------------------------------------------------------------
Calypso Framework SDL App : Main
------------------------------------------------------------------------------*/

void calypso_framework_glfw_app_set_events(calypso_framework_glfw_app_event_t event_on_startup, calypso_framework_glfw_app_event_t event_on_shutdown, calypso_framework_glfw_app_event_t event_on_update,  calypso_framework_glfw_app_event_t event_on_resize)
{
    _calypso_framework_glfw_app_event_on_startup = event_on_startup;
    _calypso_framework_glfw_app_event_on_shutdown = event_on_shutdown;
    _calypso_framework_glfw_app_event_on_update = event_on_update;
    _calypso_framework_glfw_app_event_on_resize = event_on_resize;
}

void calypso_framework_glfw_app_init_with_opengl(const int major_version, const int minor_version, const int context_profile)
{
    // Setup OpenGL Attributes
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, context_profile);
    }

    // Only Init Once
    if (_calypso_framework_glfw_app_state != CALYPSO_FRAMEWORK_GLFW_APP_STATE_NULL)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app->init_with_opengl","Already initialized",2);
        #endif
        return;
    }

    // Set State To Init By Default
    _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_INIT;

    // Init GLFW (Everything)
    if(!glfwInit())
    {
         #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app->init_with_opengl","Failed to initialize",3);
        #endif
        glfwTerminate();
        _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_ERROR;
        return;
    }

    // Create GLFW Window
    _calypso_framework_glfw_app_window  = glfwCreateWindow(CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_HEIGHT_DEFAULT, "App", NULL, NULL);
    if(!_calypso_framework_glfw_app_window)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app->init_with_opengl","Failed to create window",3);
        #endif
        glfwTerminate();
        _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_ERROR;
        return;
    }

    //Open GL Context
    glfwMakeContextCurrent(_calypso_framework_glfw_app_window);

    // Not Resizable By Default
    calypso_framework_glfw_app_set_window_resizable(0);
}

void calypso_framework_glfw_app_shutdown(void)
{
     _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_SHUTDOWN;
}

void calypso_framework_glfw_app_run(void)
{
    // Only Run If State Is Initalized (Not Yet Running)
    if (_calypso_framework_glfw_app_state != CALYPSO_FRAMEWORK_GLFW_APP_STATE_INIT)
        return;

    // On Event Startup
    if (_calypso_framework_glfw_app_event_on_startup != NULL)
        _calypso_framework_glfw_app_event_on_startup();

    // Set State To Running
    _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_RUNNING;

    glfwSwapInterval(1);

    // Time Data To Do Calculations
    double time_time_previous =  glfwGetTime();

    // Window Size Properties
    int window_width_previous;
    int window_height_previous;

    // Run
    while (_calypso_framework_glfw_app_state == CALYPSO_FRAMEWORK_GLFW_APP_STATE_RUNNING && !glfwWindowShouldClose(_calypso_framework_glfw_app_window))
    {  
        // Resize
        if (window_width_previous != calypso_framework_glfw_app_get_window_width() || window_height_previous != calypso_framework_glfw_app_get_window_height())
        {
            window_width_previous = calypso_framework_glfw_app_get_window_width();
            window_height_previous = calypso_framework_glfw_app_get_window_height();
            _calypso_framework_glfw_app_event_on_resize();
        }

        // Event Loop
        glfwPollEvents();
        if (glfwWindowShouldClose(_calypso_framework_glfw_app_window))
            _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_SHUTDOWN;

         // Get Time
        {
            double currentTime = glfwGetTime();
            _calypso_framework_glfw_app_time_delta_time  = (float)(currentTime - time_time_previous) / 1000.0f; // Convert to seconds
            time_time_previous = currentTime;
        }

        // Get FPS
        {
            // Get FPS (Float)
            _calypso_framework_glfw_app_time_fps = 1 / _calypso_framework_glfw_app_time_delta_time;  

            // Get FPS (String) | Check For Errors
            int len = snprintf(_calypso_framework_glfw_app_time_fps_as_string, sizeof(_calypso_framework_glfw_app_time_fps_as_string), "%.2f", 1.0 / _calypso_framework_glfw_app_time_delta_time);
            if (len < 0 || len >= sizeof(_calypso_framework_glfw_app_time_fps_as_string)) 
            {
                #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
                CALYPSO_FRAMEWORK_LOG_MESSAGE("glfw_app->run","FPS string(char*) is invalid",2);
                #endif
            }
        }

        // On Event Update
        if (_calypso_framework_glfw_app_event_on_update != NULL)
            _calypso_framework_glfw_app_event_on_update();

        // Swap Back And Front Buffers
        glfwSwapBuffers(_calypso_framework_glfw_app_window);
    }

    // On Event Shutdown
    if (_calypso_framework_glfw_app_event_on_shutdown != NULL)
        _calypso_framework_glfw_app_event_on_shutdown();

    // Quit
    glfwDestroyWindow(_calypso_framework_glfw_app_window);
    glfwTerminate();

     // No State
    _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_NULL;
}