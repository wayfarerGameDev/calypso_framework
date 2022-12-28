#pragma once
/// <summary>
/// Module for spatial partioning grid in 2d
/// </summary>

// Includes
#include <stdint.h>     // uint8_t
#include <stdbool.h>    // bool
#include <math.h>       // trunc


// Logging Callback
typedef void (*calypso_framework_spatial_partitioning_grid_2d_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_spatial_partitioning_grid_2d_log_callback_t _calypso_framework_spatial_partitioning_grid_2d_log_callback;

// State
#define CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_NULL                          0b00000000
#define CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_INIT                          0b00000001
unsigned int _calypso_framework_spatial_partitioning_grid_2d_state =                     CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_NULL;

// Grid
float _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_x;
float _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_y;
int _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_x;
int _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_y;
float _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_x;
float _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_y;

// Entities (data)
float* _calypso_framework_spatial_partitioning_grid_2d_entity_position_x_array;
float* _calypso_framework_spatial_partitioning_grid_2d_entity_position_y_array;
float* _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_x_array;
float* _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_y_array;
unsigned int* _calypso_framework_spatial_partitioning_grid_2d_entity_grid_cell_index_array;
bool* _calypso_framework_spatial_partitioning_grid_2d_entity_is_dirty_array;
bool* _calypso_framework_spatial_partitioning_grid_2d_entity_is_created_array;
bool* _calypso_framework_spatial_partitioning_grid_2d_entity_is_disabled_array;
unsigned int* _calypso_framework_spatial_partitioning_grid_2d_entity_array_count_max; // This is a pointer, not a array in use-case.

/**
* \brief Set app's log callback
* \return void
*/
void calypso_framework_spatial_partitioning_grid_2d_set_log_callback(calypso_framework_spatial_partitioning_grid_2d_log_callback_t log_callback)
{
    _calypso_framework_spatial_partitioning_grid_2d_log_callback = log_callback;
}

/**
* \brief Do app's log callback
* \return void
*/
void calypso_framework_spatial_partitioning_grid_2d_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_spatial_partitioning_grid_2d_log_callback == NULL)
        return;

    _calypso_framework_spatial_partitioning_grid_2d_log_callback(log_msg,log_type);
}

/**
* \brief Initializes spatial partitioning grid 2d with entity bindings (external arrays)
* \return void
*/
void calypso_framework_spatial_partitioning_grid_2d_init(const float grid_bounds_x, const float grid_bounds_y, const int cell_count_x, const int cell_count_y, unsigned int* entity_count_max, float* entity_position_x_array, float* entity_position_y_array,float* entity_bounds_x_array, float* entity_bounds_y_array, int* entity_grid_cell_index_array, bool* entity_is_created_array, bool* entity_is_disabled_array, bool* entity_is_dirty_array)
{
    // We Already Init | Init
    if (_calypso_framework_spatial_partitioning_grid_2d_state != CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_NULL)
    {
        calypso_framework_spatial_partitioning_grid_2d_do_log_callback("Spatial Partitioning Grid 2D : Already Initialized (Entity Bindings).",2);
        return;
    }
    _calypso_framework_spatial_partitioning_grid_2d_state = CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_INIT;

    // Init Grid
    _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_x = grid_bounds_x;
    _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_y = grid_bounds_y;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_x = cell_count_x;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_y = cell_count_y;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_x = grid_bounds_x / cell_count_x;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_y = grid_bounds_y / cell_count_y;

    // Init Entities (Bind To External Arrays)
    _calypso_framework_spatial_partitioning_grid_2d_entity_array_count_max = entity_count_max;
    _calypso_framework_spatial_partitioning_grid_2d_entity_position_x_array = entity_position_x_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_position_y_array = entity_position_y_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_x_array = entity_bounds_x_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_y_array = entity_bounds_y_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_grid_cell_index_array = entity_grid_cell_index_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_is_created_array = entity_is_created_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_is_disabled_array = entity_is_disabled_array;
    _calypso_framework_spatial_partitioning_grid_2d_entity_is_dirty_array = entity_is_dirty_array;
}

/**
* \brief Deinitializes spatial partitioning grid 2d
* \return void
*/
void calypso_framework_spatial_partitioning_grid_2d_deinit()
{
     // We Already Init | Init
    if (_calypso_framework_spatial_partitioning_grid_2d_state != CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_INIT)
    {
        calypso_framework_spatial_partitioning_grid_2d_do_log_callback("Spatial Partitioning Grid 2D : Not Init (No Entity Bindings).",2);
        return;
    }
    _calypso_framework_spatial_partitioning_grid_2d_state = CALYPSO_FRAMEWORK_SPATIAL_PARTIONING_GRID_2D_STATE_NULL;

    // Init Grid
    _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_x = 0;
    _calypso_framework_spatial_partitioning_grid_2d_grid_bounds_y = 0;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_x = 0;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_y = 0;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_x = 0;
    _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_y = 0;
}

/**
* \brief Get cell index by position
* \return int : cell_position
*/
int calypso_framework_spatial_partitioning_grid_2d_get_grid_cell_index_by_position(const float position_x, const float position_y)
{
    // Get Our Grid Cell Index. Simply Divide Position By Cell Size And Use Floor (Cast Float to Int After Using Trunc)
    const grid_cell_index_x = (int)(position_x / _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_x);
    const grid_cell_index_y = (int)(position_y / _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_y);

    // Return Cell Index. We Must Convert From 2D Index To 1D
    //Formula Is (We Are Using Row Colum Major Order)
    //1D index = (column * number_of_rows) + row
    return (grid_cell_index_y * _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_x) + grid_cell_index_x;
}

/**
* \brief Update
* \return void
*/
calypso_framework_spatial_partitioning_grid_2d_update()
{
    // Refrence Arrays With Smaller Names (Read Only) (Easier To Read Code)
    const bool* entity_is_created_array = _calypso_framework_spatial_partitioning_grid_2d_entity_is_created_array;
    const bool* entity_is_disabled_array = _calypso_framework_spatial_partitioning_grid_2d_entity_is_disabled_array;
    const bool* entity_is_dirty_array = _calypso_framework_spatial_partitioning_grid_2d_entity_is_dirty_array;
    const float* entity_position_x_array = _calypso_framework_spatial_partitioning_grid_2d_entity_position_x_array;
    const float* entity_position_y_array = _calypso_framework_spatial_partitioning_grid_2d_entity_position_y_array;
    const float* entity_bounds_x_array = _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_x_array;
    const float* entity_bounds_y_array = _calypso_framework_spatial_partitioning_grid_2d_entity_bounds_y_array;
    int* entity_grid_cell_index_array = _calypso_framework_spatial_partitioning_grid_2d_entity_grid_cell_index_array;
    const int grid_cell_count_x = _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_x;
    const int grid_cell_count_y = _calypso_framework_spatial_partitioning_grid_2d_grid_cell_count_y;
    const float grid_cell_size_x = _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_x;
    const float grid_cell_size_y = _calypso_framework_spatial_partitioning_grid_2d_grid_cell_size_y;

    // Refrence Arrays With Smaller Names (Writable) (Easier To Read)
    int entity_cell_index_array =  _calypso_framework_spatial_partitioning_grid_2d_entity_grid_cell_index_array;

    // Grid Cell Variables (Declare Once For Better Performance)
    unsigned int grid_cell_index_x, grid_cell_index_y;

    // Math Variables (Declare Once For Better Performance)
    float min_x, min_y, max_x, max_y, sat_x, sat_y;

    // Update
    // We Want To Get Which Cell On X/Y Entity Is On And Set Its Cell Index To It
    // Only If Entity Is Dirty, Is Created, And Not Disabled (Checked In Most Optimal Order For Most Likely Failed To least likely failed)
    for (int i = 0; i < *_calypso_framework_spatial_partitioning_grid_2d_entity_array_count_max; i++)
        if (entity_is_dirty_array[i] && entity_is_created_array[i] && !entity_is_disabled_array[i])
        {
            // Cache Our Data For Entity
            const float position_x = entity_position_x_array[i];
            const float position_y = entity_position_y_array[i];
            //const float bounds_x = entity_bounds_x_array[i];
            //const float bounds_y = entity_bounds_y_array[i];

            // We Following Math Formulas. We Do Not Want To Rely On External Dependencies
            // min = a < b ? a : b;
            // max = a > b ? a : b;
            // sat = min(max(a,b),c);
            // floor = just cast float to int after using trunc

            // Get Our Grid Cell Index. Simply Divide Position By Cell Size And Use Floor Stated Above
            grid_cell_index_x = (int)(trunc(position_x / grid_cell_size_x));
            grid_cell_index_y = (int)(trunc(position_y / grid_cell_size_y));

            // Set Entity Grid Cell Index. We Must Convert From 2D Index To 1D
            //Formula Is (We Are Using Row Colum Major Order)
            //1D index = (column * number_of_rows) + row
            entity_grid_cell_index_array[i] = (grid_cell_index_y * grid_cell_count_x) + grid_cell_index_x;
        }
    }