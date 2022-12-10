#pragma once

#include "game_includes.c"

// Benchmark
int _game_entities_benchmark_index = -1;

// Max Entities
#define GAME_ENTITIES_MAX            1000      

// Transform Entities Data
float game_entities_position_xs[GAME_ENTITIES_MAX];
float game_entities_position_ys[GAME_ENTITIES_MAX];
float game_entities_angles[GAME_ENTITIES_MAX];

// Render Entities Data
unsigned int game_entities_render_shader_programs[GAME_ENTITIES_MAX];

void game_entities_create_entity()
{
    
}

void game_entities_player_input()
{

}

void game_entities_render()
{
    // Create Benchmark
    if (_game_entities_benchmark_index == -1)
        _game_entities_benchmark_index = calypso_framework_benchmark_time_add_benchmark();

    // Start Benchmark
    calypso_framework_benchmark_time_start_benchmark(_game_entities_benchmark_index);

    for (int i = 0; i < 10000; i++)
    {
        // Red Entity
        game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_red);
        game_renderer_render_sprite(i,0, 100, 100);

        // Blue Entity
        game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_blue);
        game_renderer_render_sprite(100,100 + i, 50, 50);
    }

    // White
    game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_white);

    // End Benchmark
    calypso_framework_benchmark_time_end_benchmark(_game_entities_benchmark_index);
    calypso_framework_benchmark_time_print_benchmark_in_ms(_game_entities_benchmark_index);   
}