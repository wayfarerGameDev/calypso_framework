/// <summary>
/// Benchmark module that uses time as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <time.h>       // clock_t | clock() | CLOCKS_PER_SEC

// Logging Callback
typedef void (*calypso_framework_benchmark_time_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_benchmark_time_log_callback_t _calypso_framework_benchmark_time_log_callback;

// Benchmark
clock_t* _calypso_framework_benchmark_time_benchmark_clock_start_array;
clock_t* _calypso_framework_benchmark_time_benchmark_clock_end_array;
double* _calypso_framework_benchmark_time_benchmark_seconds_array;
double* _calypso_framework_benchmark_time_benchmark_milliseconds_array;
unsigned int _calypso_framework_benchmark_time_benchmark_array_count = 0;

/**
* \brief Set Benchmark's log callback
* \return void
*/
void calypso_framework_benchmark_time_set_log_callback(calypso_framework_benchmark_time_log_callback_t log_callback)
{
    _calypso_framework_benchmark_time_log_callback = log_callback;
}

/**
* \brief Do Benchmark's log callback
* \return void
*/
void calypso_framework_benchmark_time_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_benchmark_time_log_callback == NULL)
        return;

    _calypso_framework_benchmark_time_log_callback(log_msg,log_type);
}

/**
 * Add benchmark 
 * @return int: benchmark index
*/
int calypso_framework_benchmark_time_add_benchmark()
{
    // Add New Benchmark Array Index
    const int count = _calypso_framework_benchmark_time_benchmark_array_count++;
    _calypso_framework_benchmark_time_benchmark_clock_start_array = realloc(_calypso_framework_benchmark_time_benchmark_clock_start_array, count * sizeof(clock_t));
    _calypso_framework_benchmark_time_benchmark_clock_end_array = realloc(_calypso_framework_benchmark_time_benchmark_clock_end_array,count * sizeof(clock_t));
    _calypso_framework_benchmark_time_benchmark_seconds_array =  realloc(_calypso_framework_benchmark_time_benchmark_seconds_array,count * sizeof(double));
    _calypso_framework_benchmark_time_benchmark_milliseconds_array = realloc(_calypso_framework_benchmark_time_benchmark_milliseconds_array,count * sizeof(double));
   
    // Get Benchmark Index
    const int benchmark_index = _calypso_framework_benchmark_time_benchmark_array_count - 1;

    // Set New Bechmark Array Values
    _calypso_framework_benchmark_time_benchmark_clock_start_array[benchmark_index] = 0;
    _calypso_framework_benchmark_time_benchmark_clock_end_array[benchmark_index] = 0;
    _calypso_framework_benchmark_time_benchmark_seconds_array[benchmark_index] = 0;
    _calypso_framework_benchmark_time_benchmark_milliseconds_array[benchmark_index] = 0;

    // Return Benchmark Index
    return benchmark_index;
}

/**
 * Start benchmark
 * @param uid const int: benchmark index 
*/
void calypso_framework_benchmark_time_start_benchmark(const int benchmark_index)
{
    // Not Valid Benchmark Index
    if (benchmark_index > _calypso_framework_benchmark_time_benchmark_array_count - 1)
    {
        calypso_framework_benchmark_time_do_log_callback("Benchmark Time: benchmark index not valid in start benchmark.\n",1);        
        return;
    }

    // Begin Benchmark
    _calypso_framework_benchmark_time_benchmark_clock_start_array[benchmark_index] = clock();
}

/**
 * End benchmark
 * @param uid const int: benchmark index 
 * @return void
*/
void calypso_framework_benchmark_time_end_benchmark(const int benchmark_index)
{
    // Not Valid Benchmark Index
    if (benchmark_index > _calypso_framework_benchmark_time_benchmark_array_count - 1)
    {
       calypso_framework_benchmark_time_do_log_callback("Benchmark Time: benchmark index not valid in start benchmark.\n",1);   
        return;
    }

    // End Benchmark
    const clock_t end = _calypso_framework_benchmark_time_benchmark_clock_end_array[benchmark_index] = clock();  
    const clock_t start = _calypso_framework_benchmark_time_benchmark_clock_start_array[benchmark_index];

    // Divide the difference (end - start) by CLOCKS_PER_SEC to convert to seconds
    const double seconds = _calypso_framework_benchmark_time_benchmark_seconds_array[benchmark_index] = (double)(end - start) / CLOCKS_PER_SEC;
    _calypso_framework_benchmark_time_benchmark_milliseconds_array[benchmark_index] = seconds * 0.001;
}   

/**
 * End benchmark
 * @param uid const int: benchmark index 
 * @return void
*/
void calypso_framework_benchmark_time_print_benchmark_in_ms(const int benchmark_index)
{
    // Not Valid Benchmark Index
    if (benchmark_index > _calypso_framework_benchmark_time_benchmark_array_count - 1)
    {
       calypso_framework_benchmark_time_do_log_callback("Benchmark Time: benchmark index not valid in start benchmark.\n",1);   
       return;
    }

     printf("ms = %lf\n", _calypso_framework_benchmark_time_benchmark_milliseconds_array[benchmark_index]);
}