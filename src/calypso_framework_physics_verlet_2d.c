/// <summary>
/// Physics module that uses verlet formula in 2d enviorment
/// </summary>

#pragma once

// State
#define CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_NULL  0
#define CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_INIT  1
unsigned int _calypso_framework_physics_verlet_2d_state = CALYPSO_FRAMEWORK_PHYSICS_VERLET_2D_STATE_NULL;

// Bodies
unsigned int _calypso_framework_physics_verlet_2d_bodies_max_count = 0;
unsigned int _calypso_framework_physics_verlet_2d_bodies_current_count = 0;
float* _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs;
float* _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys;
float* _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs;
float* _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys;
float* _calypso_framework_physics_verlet_2d_bodies_accelerations_xs;
float* _calypso_framework_physics_verlet_2d_bodies_accelerations_ys;
float* _calypso_framework_physics_verlet_2d_bodies_accelerations_ys;
bool* _calypso_framework_physics_verlet_2d_bodies_createds;

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
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_accelerations_xs = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_accelerations_ys = malloc(bodies_max_count * sizeof(float));
    _calypso_framework_physics_verlet_2d_bodies_createds = malloc(bodies_max_count * sizeof(bool));
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
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys[body_index] = position_y;
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys[body_index] = position_y;
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
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys[body_index] = position_y;
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs[body_index] = position_x;
    _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys[body_index] = position_y;
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
    _calypso_framework_physics_verlet_2d_bodies_accelerations_xs[body_index] = acceleration_x;
    _calypso_framework_physics_verlet_2d_bodies_accelerations_ys[body_index] = acceleration_y;
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
    _calypso_framework_physics_verlet_2d_bodies_accelerations_xs[body_index] = acceleration_x;
    _calypso_framework_physics_verlet_2d_bodies_accelerations_ys[body_index] = acceleration_y;
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
        if (!_calypso_framework_physics_verlet_2d_bodies_createds[i])
            continue;

        // Get Velocity
        velocity_x = _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[i] - _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs[i];
        velocity_y = _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys[i] - _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys[i];

        // Set Previous Location
        _calypso_framework_physics_verlet_2d_bodies_positions_previouses_xs[i] = _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[i];
        _calypso_framework_physics_verlet_2d_bodies_positions_previouses_ys[i] = _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys[i];

        // Move
        _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[i] = _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[i] + velocity_x + _calypso_framework_physics_verlet_2d_bodies_accelerations_xs[i] * delta_time * delta_time;
        _calypso_framework_physics_verlet_2d_bodies_positions_currents_xs[i] = _calypso_framework_physics_verlet_2d_bodies_positions_currents_ys[i] + velocity_y + _calypso_framework_physics_verlet_2d_bodies_accelerations_ys[i] * delta_time * delta_time;
    
        // Reset Acceleration
        _calypso_framework_physics_verlet_2d_bodies_accelerations_xs[i] = 0;
        _calypso_framework_physics_verlet_2d_bodies_accelerations_ys[i] = 0;
    }

     
}