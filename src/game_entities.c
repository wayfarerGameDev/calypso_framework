#pragma once

#include "game_includes.c"

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
    game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_red);
    game_renderer_render_sprite(0,0, 100, 100);

    game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_blue);
    game_renderer_render_sprite(100,100, 50, 50);

    // White
    game_renderer_set_current_shader_program_color(_c_calypso_framework_colors_color_byte_array_white);
}