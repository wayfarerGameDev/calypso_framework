/// <summary>
/// Math module for time
/// </summary>

#pragma once

// FPS
double _calypso_framework_math_time_fps                          = 0;
double _calypso_framework_math_time_fps_time_previous            = 0;
int _calypso_framework_math_time_fps_frame_count_current         = 0;
int _calypso_framework_math_time_fps_frame_count_previous        = 0;

// Delta Time
double _calypso_framework_math_time_delta_time_time_previous     = 0;
double _calypso_framework_math_time_delta_time                   = 0;


void calypso_framework_math_time_printf_fps() 
{
    printf("calypso_framework_math_time->fps : %f\n", _calypso_framework_math_time_fps);
}

void calypso_framework_math_time_printf_delta_time() 
{
    printf("calypso_framework_math_time->delta time : %f\n", _calypso_framework_math_time_delta_time);
}

char* calypso_framework_math_time_fps_as_string() 
{
    int bufferSize = snprintf(NULL, 0, "%f", _calypso_framework_math_time_fps);
    char* str = (char*)malloc(sizeof(char) * (bufferSize + 1));
    snprintf(str, bufferSize + 1, "%f", _calypso_framework_math_time_fps);
    return str;
}

char* calypso_framework_math_time_delta_time_as_string() 
{
    int bufferSize = snprintf(NULL, 0, "%f", _calypso_framework_math_time_delta_time);
    char* str = (char*)malloc(sizeof(char) * (bufferSize + 1));
    snprintf(str, bufferSize + 1, "%f", _calypso_framework_math_time_delta_time);
    return str;
}

void calypso_framework_math_time_start()
{
    // FPS
    _calypso_framework_math_time_fps_time_previous = 0;
    _calypso_framework_math_time_fps_frame_count_current = 0;
    _calypso_framework_math_time_fps_frame_count_previous = 0;
    _calypso_framework_math_time_fps = 0;

    // Delta Time
    _calypso_framework_math_time_delta_time_time_previous = 0;
    _calypso_framework_math_time_delta_time = 0;
}

void calypso_framework_math_time_update(const double time_as_seconds)
{
    // FPS
    {
         // Increase Frame Count
        _calypso_framework_math_time_fps_frame_count_current += 1;

        // Get Elapsed Time | Previous Time
        const double elapsed = time_as_seconds - _calypso_framework_math_time_fps_time_previous;
        if (elapsed < 0.5)
            return;
        _calypso_framework_math_time_fps_time_previous = time_as_seconds;

        // Get FPS
        _calypso_framework_math_time_fps = (int)((_calypso_framework_math_time_fps_frame_count_current - _calypso_framework_math_time_fps_frame_count_previous) / elapsed);
        _calypso_framework_math_time_fps_frame_count_previous = _calypso_framework_math_time_fps_frame_count_current;
  }

  // Delta Time
  {
     _calypso_framework_math_time_delta_time = time_as_seconds - _calypso_framework_math_time_delta_time_time_previous;
     _calypso_framework_math_time_delta_time_time_previous = time_as_seconds;
  }
}