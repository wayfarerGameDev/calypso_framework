/// <summary>
/// App module that uses GLFW as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t
#include <dependencies/GLFW/glfw3.h>

// Logging Callback
typedef void (*calypso_framework_glfw_app_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_glfw_app_log_callback_t _calypso_framework_glfw_app_log_callback;

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
#define CALYPSO_FRAMEWORK_GLFW_APP_TIME_FPS_UNCAPPED          -1
#define CALYPSO_FRAMEWORK_GLFW_APP_TIME_FPS_DEFAULT            CALYPSO_FRAMEWORK_GLFW_APP_TIME_FPS_UNCAPPED
float _calypso_framework_glfw_app_time_frame_rate_target =     CALYPSO_FRAMEWORK_GLFW_APP_TIME_FPS_DEFAULT;
float _calypso_framework_glfw_app_time_frame_rate =            0;
float _calypso_framework_glfw_app_time_frame_time_target =     0;
float _calypso_framework_glfw_app_time_delta_time =            0;

// Events
typedef void (*calypso_framework_glfw_app_event_t)(void);
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_startup;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_shutdown;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_update;
calypso_framework_glfw_app_event_t _calypso_framework_glfw_app_event_on_resize;


void calypso_framework_glfw_app_set_log_callback(calypso_framework_glfw_app_log_callback_t log_callback)
{
    _calypso_framework_glfw_app_log_callback = log_callback;
}

void calypso_framework_glfw_app_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_glfw_app_log_callback == NULL)
        return;

    _calypso_framework_glfw_app_log_callback(log_msg,log_type);
}

void* calypso_framework_glfw_app_get_open_gl_proc_address()
{
    return glfwGetProcAddress;
}

GLFWwindow* calypso_framework_glfw_app_get_window_glfw_window(void)
{
    return _calypso_framework_glfw_app_window;
}

int calypso_framework_glfw_app_get_window_width(void)
{
     // Not Valid Group
    if (!_calypso_framework_glfw_app_window)
    {
        calypso_framework_glfw_app_do_log_callback("App: Failed to get window width (window is NULL)\n",3);
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
        calypso_framework_glfw_app_do_log_callback("App: Failed to get window height (window is NULL)\n",3);
        return 0;
    }

    int w = 0;
    int h = 0;
    glfwGetWindowSize(_calypso_framework_glfw_app_window,&w,&h);
    return h;
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

void calypso_framework_glfw_app_set_window_title(const char* title)
{
    //GLFW_SetWindowTitle(_calypso_framework_glfw_app_window,title);
    glfwSetWindowTitle(_calypso_framework_glfw_app_window,title);
}

void calypso_framework_glfw_app_set_window_size(int with, int height)
{
    //GLFW_SetWindowTitle(_calypso_framework_glfw_app_window,title);
    glfwSetWindowSize(_calypso_framework_glfw_app_window,with,height);
}

void calypso_framework_glfw_app_set_window_resizable(const uint8_t bIsResizable)
{
    glfwSetWindowAttrib(_calypso_framework_glfw_app_window, GLFW_RESIZABLE,bIsResizable == 1);
}

void calypso_framework_glfw_app_set_time_frame_rate_target_uncapped(void)
{
    // Time
    _calypso_framework_glfw_app_time_frame_rate_target = CALYPSO_FRAMEWORK_GLFW_APP_TIME_FPS_UNCAPPED;
    _calypso_framework_glfw_app_time_frame_time_target = 0;
}

void calypso_framework_glfw_app_set_time_frame_target_rate(const unsigned int frame_rate)
{
    _calypso_framework_glfw_app_time_frame_rate_target = frame_rate;
    _calypso_framework_glfw_app_time_frame_time_target = 1000 / frame_rate;
}

float calypso_framework_glfw_app_get_time_frame_rate(void)
{
    return _calypso_framework_glfw_app_time_frame_rate;
}

float* calypso_framework_glfw_app_get_time_frame_rate_ptr(void)
{
    return &_calypso_framework_glfw_app_time_frame_rate;
}

float calypso_framework_glfw_app_get_time_delta_time(void)
{
    return _calypso_framework_glfw_app_time_delta_time;
}

float* calypso_framework_glfw_app_get_time_delta_time_ptr(void)
{
    return &_calypso_framework_glfw_app_time_delta_time;
}

char* calypso_framework_glfw_app_get_time_fps_as_string(void)
{
    int len = snprintf(NULL, 0, "%i", (int)_calypso_framework_glfw_app_time_frame_rate);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%i", (int)_calypso_framework_glfw_app_time_frame_rate);
    return result;
}

char* calypso_framework_glfw_app_get_time_delta_time_as_string(void)
{
    int len = snprintf(NULL, 0, "%f", _calypso_framework_glfw_app_time_delta_time);
    char* result = malloc(len + 1);
    snprintf(result, len + 1, "%f", _calypso_framework_glfw_app_time_delta_time);
    return result;
}

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
        //glfwWindowHint(GLFW_DOUBLEBUFFER,1);
        //glfwWindowHint(GLFW_DEPTH_BITS,24);

        //GLFW_GL_SetAttribute(GLFW_GL_RED_SIZE,5);
        //GLFW_GL_SetAttribute(GLFW_GL_GREEN_SIZE,5);
        //GLFW_GL_SetAttribute(GLFW_GL_BLUE_SIZE,5);
        //GLFW_GL_SetAttribute(GLFW_GL_DEPTH_SIZE,16);
        //GLFW_GL_SetAttribute(GLFW_GL_DOUBLEBUFFER,1);
    }

    // Only Init Once
    if (_calypso_framework_glfw_app_state != CALYPSO_FRAMEWORK_GLFW_APP_STATE_NULL)
    {
        calypso_framework_glfw_app_do_log_callback("App: App already init\n",2);
        return;
    }

    // Set State To Init By Default
    _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_INIT;

    // Init GLFW (Everything)
    if(!glfwInit())
    {
        calypso_framework_glfw_app_do_log_callback("App: GLFW failed to initialize\n",3);
        //calypso_framework_glfw_app_do_log_callback(GLFW_ERRO),3);
        //calypso_framework_glfw_app_do_log_callback("\n",3);
        _calypso_framework_glfw_app_state = CALYPSO_FRAMEWORK_GLFW_APP_STATE_ERROR;
        return;
    }

    // Create GLFW Window
    _calypso_framework_glfw_app_window  = glfwCreateWindow(CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_WIDTH_DEFAULT, CALYPSO_FRAMEWORK_GLFW_APP_SCREEN_HEIGHT_DEFAULT, "App", NULL, NULL);
    if(!_calypso_framework_glfw_app_window)
    {
        calypso_framework_glfw_app_do_log_callback("App: GLFW failed to create window\n",3);
        glfwTerminate();
        //calypso_framework_glfw_app_do_log_callback(GLFW_GetError(),3);
        //calypso_framework_glfw_app_do_log_callback("\n",3);
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
    int time_time_last = 0;
    int time_time_delay = 0;
    int time_frame_count = 0;
    int time_frame_last = 0;

    // Window Size Properties
    int _calypso_framework_glfw_app_window_width_previous;
    int _calypso_framework_glfw_app_window_height_previous;

    // Run
    while (_calypso_framework_glfw_app_state == CALYPSO_FRAMEWORK_GLFW_APP_STATE_RUNNING && !glfwWindowShouldClose(_calypso_framework_glfw_app_window))
    {  
        // Resize
        if (_calypso_framework_glfw_app_window_width_previous != calypso_framework_glfw_app_get_window_width() || _calypso_framework_glfw_app_window_height_previous != calypso_framework_glfw_app_get_window_height())
        {
            _calypso_framework_glfw_app_window_width_previous = calypso_framework_glfw_app_get_window_width();
            _calypso_framework_glfw_app_window_height_previous = calypso_framework_glfw_app_get_window_height();
            _calypso_framework_glfw_app_event_on_resize();
        }

        // Event Loop
        glfwPollEvents();
        if (glfwWindowShouldClose(_calypso_framework_glfw_app_window))
            _calypso_framework_glfw_app_state == CALYPSO_FRAMEWORK_GLFW_APP_STATE_SHUTDOWN;

        // On Event Update
        if (_calypso_framework_glfw_app_event_on_update != NULL)
            _calypso_framework_glfw_app_event_on_update();

        // Swap Window (Open GL Is Using 2 Buffers)
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