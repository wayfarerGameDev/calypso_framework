/// <summary>
/// Physics module that uses verlet formula in 2d enviorment
/// </summary>

#pragma once

// Includes
#include <stdbool.h>    // bool

// State
#define CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_NULL                          0b00000000
#define CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_INIT                          0b00000001
unsigned int _calypso_framework_physics_verlet_2d_state =                       CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_NULL;

// Bodies
float* _calypso_framework_physics_verlet_2d_bodies_position_x_current_array;
float* _calypso_framework_physics_verlet_2d_bodies_position_y_current_array;
float* _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array;
float* _calypso_framework_physics_verlet_2d_bodies_position_y_previous_array;
float* _calypso_framework_physics_verlet_2d_bodies_accelersation_x_array;
float* _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array;
float* _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array;
bool* _calypso_framework_physics_verlet_2d_bodies_created_array;
unsigned int _calypso_framework_physics_verlet_2d_bodies_max_count =            0;
unsigned int _calypso_framework_physics_verlet_2d_bodies_current_count =        0;

/**
 * Initializes physics
 * @param bodies_max_count const unsigned int
 * @return void
*/
void calypso_framework_physics_verlet_2d_init(const unsigned int bodies_max_count)
{
    // Only Init Once
    if (_calypso_framework_physics_verlet_2d_state != CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_NULL)
        return;

    // Set State To Init By Default
    _calypso_framework_physics_verlet_2d_state = CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_INIT;

    // Set Max Body Count
    _calypso_framework_physics_verlet_2d_bodies_max_count = bodies_max_count;

    // Allocate Body Data
    _calypso_framework_physics_verlet_2d_bodies_position_x_current_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_position_y_current_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_created_array = malloc(bodies_max_count * sizeof(bool));
}

/**
 * Set physics body positions
 * @param body_index const unsigned int
 * @param position_x const float
 * @param position_y const float
 * @return void
*/
void calypso_framework_physics_verlet_2d_set_body_position(const unsigned int body_index, const float position_x, const float position_y)
{
    // Return If Body Index Invalid
    if (body_index >= _calypso_framework_physics_verlet_2d_bodies_max_count)
        return;

    // Set Body Position Data
    _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[body_index] = position_y;
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[body_index] = position_y;
}

/**
 * Set physics body positions unsafe(no checks)
 * @param body_index const unsigned int
 * @param position_x const float
 * @param position_y const float
 * @return void
*/
void calypso_framework_physics_verlet_2d_set_body_position_unsafe(const unsigned int body_index, const float position_x, const float position_y)
{
    // Set Body Position Data
    _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[body_index] = position_y;
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[body_index] = position_y;
}

/**
 * Set physics body accelerations
 * @param body_index const unsigned int
 * @param acceleration_x const float
 * @param acceleration_y const float
 * @return void
*/
void calypso_framework_physics_verlet_2d_set_body_acceleration(const unsigned int body_index, const float acceleration_x, const float acceleration_y)
{
    // Return If Body Index Invalid
    if (body_index >= _calypso_framework_physics_verlet_2d_bodies_max_count)
        return;

    // Set Body acceleration Data
    _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array[body_index] = acceleration_x;
    _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array[body_index] = acceleration_y;
}

/**
 * Set physics body accelerations unsafe(no checks)
 * @param body_index const unsigned int
 * @param acceleration_x const float
 * @param acceleration_y const float
 * @return void
*/
void calypso_framework_physics_verlet_2d_set_body_acceleration_unsafe(const unsigned int body_index, const float acceleration_x, const float acceleration_y)
{
    // Set Body acceleration Data
    _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array[body_index] = acceleration_x;
    _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array[body_index] = acceleration_y;
}

void calypso_framework_physics_verlet_2d_update(const float delta_time)
{
     // Only If Init
    if (_calypso_framework_physics_verlet_2d_state != CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_INIT)
        return;

    // Cache Velocity
    float velocity_x = 0;
    float velocity_y = 0;

    // Update Positions
    for (int i = 0; i < _calypso_framework_physics_verlet_2d_bodies_max_count; i++)
    {
        //Continue Since Body Is Not Created
        if (!_calypso_framework_physics_verlet_2d_bodies_created_array[i])
            continue;

        // Get Velocity
        velocity_x = _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[i] - _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[i];
        velocity_y = _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[i] - _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[i];

        // Set Previous Location
        _calypso_framework_physics_verlet_2d_bodies_position_x_previous_array[i] = _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[i];
        _calypso_framework_physics_verlet_2d_bodies_position_y_previous_array[i] = _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[i];

        // Move
        _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[i] = _calypso_framework_physics_verlet_2d_bodies_position_x_current_array[i] + velocity_x + _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array[i] * delta_time * delta_time;
        _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[i] = _calypso_framework_physics_verlet_2d_bodies_position_y_current_array[i] + velocity_y + _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array[i] * delta_time * delta_time;
    
        // Reset Acceleration
        _calypso_framework_physics_verlet_2d_bodies_acceleration_x_array[i] = 0;
        _calypso_framework_physics_verlet_2d_bodies_acceleration_y_array[i] = 0;
    }

     
}